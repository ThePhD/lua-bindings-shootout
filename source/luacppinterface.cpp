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

#include <LuaCppInterface/luacppinterface.h>

void luacppinterface_global_string_get_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	lua.Set("value", lbs::magic_value());
	double x = 0;
	for (auto _ : benchmark_state) {
		x += lua.Get<double>("value");
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_global_string_set_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.Set("value", v);
	}
	double x = lua.Get<double>("value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_table_get_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	lua.Set("warble", l.CreateTable());
	LuaTable t = lua.Get<LuaTable>("warble");
	t.Set("value", lbs::magic_value());

	double x = 0;
	for (auto _ : benchmark_state) {
		x += t.Get<double>("value");
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_table_set_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	lua.Set("warble", l.CreateTable());
	LuaTable t = lua.Get<LuaTable>("warble");
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		t.Set("value", v);
	}
	double x = lua.Get<LuaTable>("warble").Get<double>("value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_table_chained_get_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	lua.Set("ulahibe", l.CreateTable());
	LuaTable tu = lua.Get<LuaTable>("ulahibe");
	tu.Set("warble", l.CreateTable());
	LuaTable tw = tu.Get<LuaTable>("warble");
	tw.Set("value", lbs::magic_value());
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.Get<LuaTable>("ulahibe").Get<LuaTable>("warble").Get<double>("value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_table_chained_set_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_atpanic(lua.GetState().get(), lbs::panic_throw);

	lua.Set("ulahibe", l.CreateTable());
	LuaTable tu = lua.Get<LuaTable>("ulahibe");
	tu.Set("warble", l.CreateTable());
	LuaTable tw = tu.Get<LuaTable>("warble");
	tw.Set("value", lbs::magic_value());
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.Get<LuaTable>("ulahibe").Get<LuaTable>("warble").Set("value", v);
	}
	double x = lua.Get<LuaTable>("ulahibe").Get<LuaTable>("warble").Get<double>("value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_c_function_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	lua.Set("f", l.CreateFunction<double(double)>(lbs::basic_call));


	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luacppinterface_lua_function_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	lua_atpanic(L, lbs::panic_throw);

	if (l.RunScript(R"(function f (i)
			return i;
		end)")
		!= "No errors") {
		lua_error(lua.GetState().get());
	}

	auto f = lua.Get<LuaFunction<double(double)>>("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.Invoke(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_lua_function_through_c_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	lua_atpanic(L, lbs::panic_throw);

	lua.Set("f", l.CreateFunction<double(double)>(lbs::basic_call));

	auto f = lua.Get<LuaFunction<double(double)>>("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.Invoke(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_member_function_call_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	auto image = l.CreateUserdata<lbs::basic>(new lbs::basic());
	lua.Set("b", image);
	image.Bind<void>("set", &lbs::basic::set);
	image.Bind<double>("get", &lbs::basic::get);

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luacppinterface_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_stateful_function_object_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	lua_atpanic(L, lbs::panic_throw);

	lua.Set("f", l.CreateFunction<double(double)>(lbs::basic_stateful()));

	auto f = lua.Get<LuaFunction<double(double)>>("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.Invoke(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luacppinterface_multi_return_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_multi_return_lua_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// The userdata pulls out the wrong base class and fails
	// with the exceptions below
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	lua_atpanic(L, lbs::panic_throw);

	auto lud = l.CreateUserdata<lbs::complex_ab>(new lbs::complex_ab());
	lua.Set("b", lud);
	{
		LuaUserdata<lbs::complex_ab> lab = lua.Get<LuaUserdata<lbs::complex_ab>>("b");
		LuaUserdata<lbs::complex_base_a> la = lua.Get<LuaUserdata<lbs::complex_base_a>>("b");
		LuaUserdata<lbs::complex_base_b> lb = lua.Get<LuaUserdata<lbs::complex_base_b>>("b");
		lbs::complex_ab& ab = *lab.GetPointer();
		lbs::complex_base_a& va = *la.GetPointer();
		lbs::complex_base_b& vb = *lb.GetPointer();
		if (!lbs::verify_base_correctness(va, vb, ab)) {
			lbs::unsupported(benchmark_state);
			return;
		}
	}
	double x = 0;
	for (auto _ : benchmark_state) {
		LuaUserdata<lbs::complex_base_a> la = lua.Get<LuaUserdata<lbs::complex_base_a>>("b");
		LuaUserdata<lbs::complex_base_b> lb = lua.Get<LuaUserdata<lbs::complex_base_b>>("b");
		lbs::complex_base_a& va = *la.GetPointer();
		lbs::complex_base_b& vb = *lb.GetPointer();
		x += va.a_func();
		x += vb.b_func();
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 2));
}

void luacppinterface_return_userdata_measure(benchmark::State& benchmark_state) {
	Lua l;
	auto lua = l.GetGlobalEnvironment();
	lua_State* L = lua.GetState().get();
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	lua.Set("f", l.CreateFunction<LuaUserdata<lbs::basic>(double)>([&](double i) -> LuaUserdata<lbs::basic> {
		return l.CreateUserdata(new lbs::basic(lbs::basic_return(i)));
	}));
	lua.Set("h", l.CreateFunction<double(LuaUserdata<lbs::basic>)>([&](LuaUserdata<lbs::basic> b) -> double {
		return lbs::basic_get_var(*b.RetrieveData());
	}));
	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luacppinterface_optional_success_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_optional_half_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_optional_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luacppinterface_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

BENCHMARK(luacppinterface_global_string_get_measure);
BENCHMARK(luacppinterface_global_string_set_measure);
BENCHMARK(luacppinterface_table_get_measure);
BENCHMARK(luacppinterface_table_set_measure);
BENCHMARK(luacppinterface_table_chained_get_measure);
BENCHMARK(luacppinterface_table_chained_set_measure);
BENCHMARK(luacppinterface_c_function_measure);
BENCHMARK(luacppinterface_lua_function_through_c_measure);
BENCHMARK(luacppinterface_lua_function_measure);
BENCHMARK(luacppinterface_member_function_call_measure);
BENCHMARK(luacppinterface_userdata_variable_access_measure);
BENCHMARK(luacppinterface_userdata_variable_access_large_measure);
BENCHMARK(luacppinterface_userdata_variable_access_last_measure);
BENCHMARK(luacppinterface_multi_return_measure);
BENCHMARK(luacppinterface_multi_return_lua_measure);
BENCHMARK(luacppinterface_stateful_function_object_measure);
BENCHMARK(luacppinterface_base_derived_measure);
BENCHMARK(luacppinterface_return_userdata_measure);
BENCHMARK(luacppinterface_optional_success_measure);
BENCHMARK(luacppinterface_optional_half_failure_measure);
BENCHMARK(luacppinterface_optional_failure_measure);
BENCHMARK(luacppinterface_implicit_inheritance_measure);
