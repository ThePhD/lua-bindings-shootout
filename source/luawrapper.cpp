// lua bindings shootout
// The MIT License (MIT)

// Copyright � 2018 ThePhD

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

#include <LuaContext.hpp>

static lua_State* get_luawrapper_main_state(LuaContext& lua, bool open_libs = false) {
	auto crap = lua.createThread();
	lua_State* L = crap.state;
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_MAINTHREAD);
	// grab the state: fuck you for hiding it, luawrapper
	L = lua_tothread(L, -1);
	lua.destroyThread(crap);
	if (open_libs) {
		luaL_openlibs(L);
	}
	lua_atpanic(L, lbs::panic_throw);
	return L;
}

void luawrapper_table_global_string_get_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeVariable("value", lbs::magic_value());
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.readVariable<double>("value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_table_global_string_set_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.writeVariable("value", v);
	}
	double x = lua.readVariable<double>("value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_table_chained_get_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeVariable("ulahibe",
		std::map<std::string, std::map<std::string, double>>{
			{ "warble",
				std::map<std::string, double>{
					{ "value", lbs::magic_value() } } },
		});
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.readVariable<double>("ulahibe", "warble", "value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_table_chained_set_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeVariable("ulahibe",
		std::map<std::string, std::map<std::string, double>>{
			{ "warble",
				std::map<std::string, double>{
					{ "value", lbs::magic_value() } } },
		});
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.writeVariable("ulahibe", "warble", "value", v);
	}
	double x = lua.readVariable<double>("ulahibe", "warble", "value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_table_get_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeVariable("warble",
		std::map<std::string, double>{
			{ "value", lbs::magic_value() } });
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.readVariable<double>("warble", "value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_table_set_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeVariable("warble",
		std::map<std::string, double>{
			{ "value", lbs::magic_value() } });
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.writeVariable("warble", "value", v);
	}
	double x = lua.readVariable<double>("warble", "value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_c_function_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeFunction("f", &lbs::basic_call);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_lua_function_in_c_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.executeCode(R"(function f (i)
			return i;
		end)");
	auto f = lua.readVariable<std::function<double(double)>>("f");

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_c_function_through_lua_in_c_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeFunction("f", &lbs::basic_call);
	auto f = lua.readVariable<std::function<double(double)>>("f");

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_member_function_call_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.registerFunction<double (lbs::basic::*)()>("get", [](lbs::basic& b) { return b.get(); });
	lua.registerFunction<void (lbs::basic::*)(double)>("set", [](lbs::basic& b, double num) { b.set(num); });
	lua.writeVariable("b", lbs::basic());

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.registerMember("var", &lbs::basic::var);
	lua.registerMember("var0", &lbs::basic::var0);
	lua.registerMember("var1", &lbs::basic::var1);
	lua.registerMember("var2", &lbs::basic::var2);
	lua.registerMember("var3", &lbs::basic::var3);
	lua.registerMember("var4", &lbs::basic::var4);
	lua.writeVariable("b", lbs::basic());

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.registerMember("var", &lbs::basic_large::var);
	lua.registerMember("var0", &lbs::basic_large::var0);
	lua.registerMember("var1", &lbs::basic_large::var1);
	lua.registerMember("var2", &lbs::basic_large::var2);
	lua.registerMember("var3", &lbs::basic_large::var3);
	lua.registerMember("var4", &lbs::basic_large::var4);
	lua.registerMember("var5", &lbs::basic_large::var5);
	lua.registerMember("var6", &lbs::basic_large::var6);
	lua.registerMember("var7", &lbs::basic_large::var7);
	lua.registerMember("var8", &lbs::basic_large::var8);
	lua.registerMember("var9", &lbs::basic_large::var9);
	lua.registerMember("var10", &lbs::basic_large::var10);
	lua.registerMember("var11", &lbs::basic_large::var11);
	lua.registerMember("var12", &lbs::basic_large::var12);
	lua.registerMember("var13", &lbs::basic_large::var13);
	lua.registerMember("var14", &lbs::basic_large::var14);
	lua.registerMember("var15", &lbs::basic_large::var15);
	lua.registerMember("var16", &lbs::basic_large::var16);
	lua.registerMember("var17", &lbs::basic_large::var17);
	lua.registerMember("var18", &lbs::basic_large::var18);
	lua.registerMember("var19", &lbs::basic_large::var19);
	lua.registerMember("var20", &lbs::basic_large::var20);
	lua.registerMember("var21", &lbs::basic_large::var21);
	lua.registerMember("var22", &lbs::basic_large::var22);
	lua.registerMember("var23", &lbs::basic_large::var23);
	lua.registerMember("var24", &lbs::basic_large::var24);
	lua.registerMember("var25", &lbs::basic_large::var25);
	lua.registerMember("var26", &lbs::basic_large::var26);
	lua.registerMember("var27", &lbs::basic_large::var27);
	lua.registerMember("var28", &lbs::basic_large::var28);
	lua.registerMember("var29", &lbs::basic_large::var29);
	lua.registerMember("var30", &lbs::basic_large::var30);
	lua.registerMember("var31", &lbs::basic_large::var31);
	lua.registerMember("var32", &lbs::basic_large::var32);
	lua.registerMember("var33", &lbs::basic_large::var33);
	lua.registerMember("var34", &lbs::basic_large::var34);
	lua.registerMember("var35", &lbs::basic_large::var35);
	lua.registerMember("var36", &lbs::basic_large::var36);
	lua.registerMember("var37", &lbs::basic_large::var37);
	lua.registerMember("var38", &lbs::basic_large::var38);
	lua.registerMember("var39", &lbs::basic_large::var39);
	lua.registerMember("var40", &lbs::basic_large::var40);
	lua.registerMember("var41", &lbs::basic_large::var41);
	lua.registerMember("var42", &lbs::basic_large::var42);
	lua.registerMember("var43", &lbs::basic_large::var43);
	lua.registerMember("var44", &lbs::basic_large::var44);
	lua.registerMember("var45", &lbs::basic_large::var45);
	lua.registerMember("var46", &lbs::basic_large::var46);
	lua.registerMember("var47", &lbs::basic_large::var47);
	lua.registerMember("var48", &lbs::basic_large::var48);
	lua.registerMember("var49", &lbs::basic_large::var49);
	lua.writeVariable("b", lbs::basic_large());

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.registerMember("var", &lbs::basic_large::var);
	lua.registerMember("var0", &lbs::basic_large::var0);
	lua.registerMember("var1", &lbs::basic_large::var1);
	lua.registerMember("var2", &lbs::basic_large::var2);
	lua.registerMember("var3", &lbs::basic_large::var3);
	lua.registerMember("var4", &lbs::basic_large::var4);
	lua.registerMember("var5", &lbs::basic_large::var5);
	lua.registerMember("var6", &lbs::basic_large::var6);
	lua.registerMember("var7", &lbs::basic_large::var7);
	lua.registerMember("var8", &lbs::basic_large::var8);
	lua.registerMember("var9", &lbs::basic_large::var9);
	lua.registerMember("var10", &lbs::basic_large::var10);
	lua.registerMember("var11", &lbs::basic_large::var11);
	lua.registerMember("var12", &lbs::basic_large::var12);
	lua.registerMember("var13", &lbs::basic_large::var13);
	lua.registerMember("var14", &lbs::basic_large::var14);
	lua.registerMember("var15", &lbs::basic_large::var15);
	lua.registerMember("var16", &lbs::basic_large::var16);
	lua.registerMember("var17", &lbs::basic_large::var17);
	lua.registerMember("var18", &lbs::basic_large::var18);
	lua.registerMember("var19", &lbs::basic_large::var19);
	lua.registerMember("var20", &lbs::basic_large::var20);
	lua.registerMember("var21", &lbs::basic_large::var21);
	lua.registerMember("var22", &lbs::basic_large::var22);
	lua.registerMember("var23", &lbs::basic_large::var23);
	lua.registerMember("var24", &lbs::basic_large::var24);
	lua.registerMember("var25", &lbs::basic_large::var25);
	lua.registerMember("var26", &lbs::basic_large::var26);
	lua.registerMember("var27", &lbs::basic_large::var27);
	lua.registerMember("var28", &lbs::basic_large::var28);
	lua.registerMember("var29", &lbs::basic_large::var29);
	lua.registerMember("var30", &lbs::basic_large::var30);
	lua.registerMember("var31", &lbs::basic_large::var31);
	lua.registerMember("var32", &lbs::basic_large::var32);
	lua.registerMember("var33", &lbs::basic_large::var33);
	lua.registerMember("var34", &lbs::basic_large::var34);
	lua.registerMember("var35", &lbs::basic_large::var35);
	lua.registerMember("var36", &lbs::basic_large::var36);
	lua.registerMember("var37", &lbs::basic_large::var37);
	lua.registerMember("var38", &lbs::basic_large::var38);
	lua.registerMember("var39", &lbs::basic_large::var39);
	lua.registerMember("var40", &lbs::basic_large::var40);
	lua.registerMember("var41", &lbs::basic_large::var41);
	lua.registerMember("var42", &lbs::basic_large::var42);
	lua.registerMember("var43", &lbs::basic_large::var43);
	lua.registerMember("var44", &lbs::basic_large::var44);
	lua.registerMember("var45", &lbs::basic_large::var45);
	lua.registerMember("var46", &lbs::basic_large::var46);
	lua.registerMember("var47", &lbs::basic_large::var47);
	lua.registerMember("var48", &lbs::basic_large::var48);
	lua.registerMember("var49", &lbs::basic_large::var49);
	lua.writeVariable("b", lbs::basic_large());

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}


void luawrapper_stateful_function_object_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, false);

	lua.writeFunction("f", lbs::basic_stateful());
	auto f = lua.readVariable<std::function<int(int)>>("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luawrapper_multi_return_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua);

	lua.writeFunction("f", &lbs::basic_multi_return);
	auto f = lua.readVariable<std::function<std::tuple<int, int>(int)>>("f");

	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<int, int> v = f(lbs::magic_value());
		x += std::get<0>(v);
		x += std::get<1>(v);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void luawrapper_multi_return_lua_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.writeFunction("f", &lbs::basic_multi_return);

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported:
	// Errors directly on cast and there's no base/derived template plug
	// thusly, explicitly mark as unsupported
	// even if it compiles
	lbs::unsupported(benchmark_state);
	return;

	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lbs::complex_ab ab;
	lua.writeVariable("b", &ab);
	{
		// cannot quite do this
		lbs::complex_base_a* va = lua.readVariable<lbs::complex_base_a*>("b");
		lbs::complex_base_b* vb = lua.readVariable<lbs::complex_base_b*>("b");
		if (!lbs::verify_base_correctness(*va, *vb, ab)) {
			lbs::unsupported(benchmark_state);
			return;
		}
	}
	double x = 0;
	for (auto _ : benchmark_state) {
		lbs::complex_base_a* va = lua.readVariable<lbs::complex_base_a*>("b");
		lbs::complex_base_b* vb = lua.readVariable<lbs::complex_base_b*>("b");
		x += va->a_func();
		x += vb->b_func();
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 2));
}

void luawrapper_return_userdata_measure(benchmark::State& benchmark_state) {
	LuaContext lua;
	lua_State* L = get_luawrapper_main_state(lua, true);

	lua.writeFunction("f", &lbs::basic_return);
	lua.writeFunction("h", &lbs::basic_get_var);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luawrapper_optional_success_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luawrapper_optional_half_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luawrapper_optional_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luawrapper_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}



BENCHMARK(luawrapper_table_global_string_get_measure);
BENCHMARK(luawrapper_table_global_string_set_measure);
BENCHMARK(luawrapper_table_get_measure);
BENCHMARK(luawrapper_table_set_measure);
BENCHMARK(luawrapper_table_chained_get_measure);
BENCHMARK(luawrapper_table_chained_set_measure);
BENCHMARK(luawrapper_c_function_measure);
BENCHMARK(luawrapper_c_function_through_lua_in_c_measure);
BENCHMARK(luawrapper_lua_function_in_c_measure);
BENCHMARK(luawrapper_member_function_call_measure);
BENCHMARK(luawrapper_userdata_variable_access_measure);
BENCHMARK(luawrapper_userdata_variable_access_large_measure);
BENCHMARK(luawrapper_userdata_variable_access_last_measure);
BENCHMARK(luawrapper_multi_return_lua_measure);
BENCHMARK(luawrapper_multi_return_measure);
BENCHMARK(luawrapper_stateful_function_object_measure);
BENCHMARK(luawrapper_base_derived_measure);
BENCHMARK(luawrapper_return_userdata_measure);
BENCHMARK(luawrapper_optional_success_measure);
BENCHMARK(luawrapper_optional_half_failure_measure);
BENCHMARK(luawrapper_optional_failure_measure);
BENCHMARK(luawrapper_implicit_inheritance_measure);
