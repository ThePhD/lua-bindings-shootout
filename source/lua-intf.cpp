// lua bindings shootout
// The MIT License (MIT)

// Copyright © 2018 ThePhD

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
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER1
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <LuaIntf/LuaIntf.h>

#include "benchmark.hpp"
#include "lbs_lua.hpp"
#include "lbs_lib.hpp"

void lua_intf_table_global_string_get_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "value = " + lbs::magic_value_string();
	lua.doString(precode.c_str());

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.getGlobal<double>("value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_table_global_string_set_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "value = " + lbs::magic_value_string();
	lua.doString(precode.c_str());

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.setGlobal("value", v);
	}
	double x = lua.getGlobal<double>("value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_table_chained_get_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "ulahibe = {warble = {value = " + lbs::magic_value_string() + "}}";
	lua.doString(precode.c_str());

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua.getGlobal<double>("ulahibe.warble.value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_table_chained_set_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "ulahibe = {warble = {value = " + lbs::magic_value_string() + "}}";
	lua.doString(precode.c_str());

	double v = 0;
	for (auto _ : benchmark_state) {
		LuaIntf::LuaRef tu = lua.getGlobal("ulahibe")["warble"];
		v += lbs::magic_value();
		tu.set("value", v);
	}
	double x = lua.getGlobal<double>("ulahibe.warble.value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_table_get_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string code = "warble = {value = " + lbs::magic_value_string() + "}";
	lua.doString(code.c_str());

	LuaIntf::LuaRef t = lua.getGlobal("warble");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t.get<double>("value");
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_table_set_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "warble = {value = " + lbs::magic_value_string() + "}";
	lua.doString(precode.c_str());

	LuaIntf::LuaRef t = lua.getGlobal("warble");
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		t.set("value", v);
	}
	double x = lua.getGlobal<double>("warble.value");
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_c_function_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	lua.setGlobal("f", lbs::basic_call);
	LuaIntf::LuaRef f = lua.getGlobal("f");

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_lua_function_in_c_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	lua.doString("function f(i) return i end");
	LuaIntf::LuaRef f = lua.getGlobal("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_c_function_through_lua_in_c_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	lua.setGlobal("f", lbs::basic_call);
	LuaIntf::LuaRef f = lua.getGlobal("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_member_function_call_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::basic>("c")
		.addConstructor(LUA_ARGS())
		.addFunction("set", &lbs::basic::set)
		.addFunction("get", &lbs::basic::get)
		.endClass();

	lua.doString("b = c()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	auto code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::basic>("c")
		.addConstructor(LUA_ARGS())
		.addVariable("var", &lbs::basic::var)
		.addVariable("var0", &lbs::basic::var0)
		.addVariable("var1", &lbs::basic::var1)
		.addVariable("var2", &lbs::basic::var2)
		.addVariable("var3", &lbs::basic::var3)
		.addVariable("var4", &lbs::basic::var4)
		.endClass();

	lua.doString("b = c()");
	auto code = lbs::repeated_code(
		lbs::userdata_variable_access_code);

	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::basic_large>("cl")
		.addConstructor(LUA_ARGS())
		.addVariable("var", &lbs::basic_large::var)
		.addVariable("var0", &lbs::basic_large::var0)
		.addVariable("var1", &lbs::basic_large::var1)
		.addVariable("var2", &lbs::basic_large::var2)
		.addVariable("var3", &lbs::basic_large::var3)
		.addVariable("var4", &lbs::basic_large::var4)
		.addVariable("var5", &lbs::basic_large::var5)
		.addVariable("var6", &lbs::basic_large::var6)
		.addVariable("var7", &lbs::basic_large::var7)
		.addVariable("var8", &lbs::basic_large::var8)
		.addVariable("var9", &lbs::basic_large::var9)
		.addVariable("var10", &lbs::basic_large::var10)
		.addVariable("var11", &lbs::basic_large::var11)
		.addVariable("var12", &lbs::basic_large::var12)
		.addVariable("var13", &lbs::basic_large::var13)
		.addVariable("var14", &lbs::basic_large::var14)
		.addVariable("var15", &lbs::basic_large::var15)
		.addVariable("var16", &lbs::basic_large::var16)
		.addVariable("var17", &lbs::basic_large::var17)
		.addVariable("var18", &lbs::basic_large::var18)
		.addVariable("var19", &lbs::basic_large::var19)
		.addVariable("var20", &lbs::basic_large::var20)
		.addVariable("var21", &lbs::basic_large::var21)
		.addVariable("var22", &lbs::basic_large::var22)
		.addVariable("var23", &lbs::basic_large::var23)
		.addVariable("var24", &lbs::basic_large::var24)
		.addVariable("var25", &lbs::basic_large::var25)
		.addVariable("var26", &lbs::basic_large::var26)
		.addVariable("var27", &lbs::basic_large::var27)
		.addVariable("var28", &lbs::basic_large::var28)
		.addVariable("var29", &lbs::basic_large::var29)
		.addVariable("var30", &lbs::basic_large::var30)
		.addVariable("var31", &lbs::basic_large::var31)
		.addVariable("var32", &lbs::basic_large::var32)
		.addVariable("var33", &lbs::basic_large::var33)
		.addVariable("var34", &lbs::basic_large::var34)
		.addVariable("var35", &lbs::basic_large::var35)
		.addVariable("var36", &lbs::basic_large::var36)
		.addVariable("var37", &lbs::basic_large::var37)
		.addVariable("var38", &lbs::basic_large::var38)
		.addVariable("var39", &lbs::basic_large::var39)
		.addVariable("var40", &lbs::basic_large::var40)
		.addVariable("var41", &lbs::basic_large::var41)
		.addVariable("var42", &lbs::basic_large::var42)
		.addVariable("var43", &lbs::basic_large::var43)
		.addVariable("var44", &lbs::basic_large::var44)
		.addVariable("var45", &lbs::basic_large::var45)
		.addVariable("var46", &lbs::basic_large::var46)
		.addVariable("var47", &lbs::basic_large::var47)
		.addVariable("var48", &lbs::basic_large::var48)
		.addVariable("var49", &lbs::basic_large::var49)
		.endClass();

	lua.doString("b = cl()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	auto code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::basic_large>("cl")
		.addConstructor(LUA_ARGS())
		.addVariable("var", &lbs::basic_large::var)
		.addVariable("var0", &lbs::basic_large::var0)
		.addVariable("var1", &lbs::basic_large::var1)
		.addVariable("var2", &lbs::basic_large::var2)
		.addVariable("var3", &lbs::basic_large::var3)
		.addVariable("var4", &lbs::basic_large::var4)
		.addVariable("var5", &lbs::basic_large::var5)
		.addVariable("var6", &lbs::basic_large::var6)
		.addVariable("var7", &lbs::basic_large::var7)
		.addVariable("var8", &lbs::basic_large::var8)
		.addVariable("var9", &lbs::basic_large::var9)
		.addVariable("var10", &lbs::basic_large::var10)
		.addVariable("var11", &lbs::basic_large::var11)
		.addVariable("var12", &lbs::basic_large::var12)
		.addVariable("var13", &lbs::basic_large::var13)
		.addVariable("var14", &lbs::basic_large::var14)
		.addVariable("var15", &lbs::basic_large::var15)
		.addVariable("var16", &lbs::basic_large::var16)
		.addVariable("var17", &lbs::basic_large::var17)
		.addVariable("var18", &lbs::basic_large::var18)
		.addVariable("var19", &lbs::basic_large::var19)
		.addVariable("var20", &lbs::basic_large::var20)
		.addVariable("var21", &lbs::basic_large::var21)
		.addVariable("var22", &lbs::basic_large::var22)
		.addVariable("var23", &lbs::basic_large::var23)
		.addVariable("var24", &lbs::basic_large::var24)
		.addVariable("var25", &lbs::basic_large::var25)
		.addVariable("var26", &lbs::basic_large::var26)
		.addVariable("var27", &lbs::basic_large::var27)
		.addVariable("var28", &lbs::basic_large::var28)
		.addVariable("var29", &lbs::basic_large::var29)
		.addVariable("var30", &lbs::basic_large::var30)
		.addVariable("var31", &lbs::basic_large::var31)
		.addVariable("var32", &lbs::basic_large::var32)
		.addVariable("var33", &lbs::basic_large::var33)
		.addVariable("var34", &lbs::basic_large::var34)
		.addVariable("var35", &lbs::basic_large::var35)
		.addVariable("var36", &lbs::basic_large::var36)
		.addVariable("var37", &lbs::basic_large::var37)
		.addVariable("var38", &lbs::basic_large::var38)
		.addVariable("var39", &lbs::basic_large::var39)
		.addVariable("var40", &lbs::basic_large::var40)
		.addVariable("var41", &lbs::basic_large::var41)
		.addVariable("var42", &lbs::basic_large::var42)
		.addVariable("var43", &lbs::basic_large::var43)
		.addVariable("var44", &lbs::basic_large::var44)
		.addVariable("var45", &lbs::basic_large::var45)
		.addVariable("var46", &lbs::basic_large::var46)
		.addVariable("var47", &lbs::basic_large::var47)
		.addVariable("var48", &lbs::basic_large::var48)
		.addVariable("var49", &lbs::basic_large::var49)
		.endClass();

	lua.doString("b = cl()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	auto code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_stateful_function_object_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.addFunction("f", lbs::basic_stateful());
	LuaIntf::LuaRef f = lua.getGlobal("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_multi_return_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	lua.setGlobal("f", &lbs::basic_multi_return);
	LuaIntf::LuaRef f = lua.getGlobal("f");
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f.call<std::tuple<double, double>>(lbs::magic_value());
		x += std::get<0>(v);
		x += std::get<1>(v);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void lua_intf_multi_return_lua_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(lua, lbs::panic_throw);

	lua.setGlobal("f", &lbs::basic_multi_return);

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	auto code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported?
	// It seems like lua_intf has no facilities for base casting
	// from a derived stored in Lua
	lbs::unsupported(benchmark_state);
	return;
}

void lua_intf_return_userdata_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::basic>("c")
		.endClass();

	lua.setGlobal("f", &lbs::basic_return);
	lua.setGlobal("h", &lbs::basic_get_var);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	auto code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_intf_optional_failure_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		LuaIntf::LuaRef tu = lua.getGlobal("warble.value");
		if (tu.type() == LuaIntf::LuaTypeID::NUMBER) {
			double v = tu.toValue<double>();
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void lua_intf_optional_half_failure_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	lbs::lua_bench_do_or_die(lua, lbs::optional_half_failure_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		LuaIntf::LuaRef tu = lua.getGlobal("warble.value");
		if (tu.type() == LuaIntf::LuaTypeID::NUMBER) {
			double v = tu.toValue<double>();
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void lua_intf_optional_success_measure(benchmark::State& benchmark_state) {
	LuaIntf::LuaContext lua;
	lua_atpanic(lua, lbs::panic_throw);

	lbs::lua_bench_do_or_die(lua, lbs::optional_success_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		LuaIntf::LuaRef tu = lua.getGlobal("warble.value");
		if (tu.type() == LuaIntf::LuaTypeID::NUMBER) {
			double v = tu.toValue<double>();
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_intf_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;
	// Unsupported?
	// Ask author
	LuaIntf::LuaContext lua;
	lua_State* L = lua;
	lua_atpanic(L, lbs::panic_throw);

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::complex_base_a>("ca")
		.addConstructor(LUA_ARGS())
		.addFunction("a_func", &lbs::complex_base_a::a_func)
		.addVariable("a", &lbs::complex_base_a::a)
		.endClass();

	LuaIntf::LuaBinding(lua)
		.beginClass<lbs::complex_base_b>("cb")
		.addConstructor(LUA_ARGS())
		.addFunction("b_func", &lbs::complex_base_b::b_func)
		.addVariable("b", &lbs::complex_base_b::b)
		.endClass();

	LuaIntf::LuaBinding(lua)
		.beginExtendClass<lbs::complex_ab, lbs::complex_base_b>("cab")
		.addConstructor(LUA_ARGS())
		.addFunction("ab_func", &lbs::complex_ab::ab_func)
		.addVariable("ab", &lbs::complex_ab::ab)
		.endClass();

	lua.doString("b = cab()");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(lua_intf_table_global_string_get_measure);
BENCHMARK(lua_intf_table_global_string_set_measure);
BENCHMARK(lua_intf_table_get_measure);
BENCHMARK(lua_intf_table_set_measure);
BENCHMARK(lua_intf_table_chained_get_measure);
BENCHMARK(lua_intf_table_chained_set_measure);
BENCHMARK(lua_intf_c_function_measure);
BENCHMARK(lua_intf_c_function_through_lua_in_c_measure);
BENCHMARK(lua_intf_lua_function_in_c_measure);
BENCHMARK(lua_intf_member_function_call_measure);
BENCHMARK(lua_intf_userdata_variable_access_measure);
BENCHMARK(lua_intf_userdata_variable_access_large_measure);
BENCHMARK(lua_intf_userdata_variable_access_last_measure);
BENCHMARK(lua_intf_multi_return_measure);
BENCHMARK(lua_intf_multi_return_lua_measure);
BENCHMARK(lua_intf_stateful_function_object_measure);
BENCHMARK(lua_intf_base_derived_measure);
BENCHMARK(lua_intf_return_userdata_measure);
BENCHMARK(lua_intf_optional_success_measure);
BENCHMARK(lua_intf_optional_half_failure_measure);
BENCHMARK(lua_intf_optional_failure_measure);
BENCHMARK(lua_intf_implicit_inheritance_measure);
