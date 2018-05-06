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
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#define SOL_NO_EXCEPTIONS 1
#define SOL_NO_CHECK_NUMBER_PRECISION 1
#include <old_sol/old_sol.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

void old_sol_global_string_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_global_string_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua.set("value", v);
	}
	double x = lua["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_table_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("warble = { value = " + lbs::magic_value_string() + " }");
	old_sol::table t = lua["warble"].get<old_sol::table>();

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_table_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.create_table("warble", 0, 0);
	old_sol::table t = lua["warble"].get<old_sol::table>();

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		t.set("value", v);
	}
	double x = t["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_table_chained_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("ulahibe = { warble = { value = " + lbs::magic_value_string() + " } }");

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"].get<double>();
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_table_chained_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("ulahibe = { warble = { value = 24 } }");

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"] = v;
	}
	double x = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"].get<double>();
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_c_function_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", &lbs::basic_call);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_lua_function_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script(R"(function f (i)
		return i;
	end)");
	old_sol::function f = lua["f"];

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.set_function("f", &lbs::basic_call);
	old_sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_member_function_call_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.new_usertype<lbs::basic>("c",
		"get", &lbs::basic::get,
		"set", &lbs::basic::set);
	lua.script("b = c:new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.new_usertype<lbs::basic>("c",
		"var", &lbs::basic::var);
	lua.script("b = c:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();

	lua.new_usertype<lbs::basic_large>("cl",
		"var", &lbs::basic_large::var,
		"var0", &lbs::basic_large::var0,
		"var1", &lbs::basic_large::var1,
		"var2", &lbs::basic_large::var2,
		"var3", &lbs::basic_large::var3,
		"var4", &lbs::basic_large::var4,
		"var5", &lbs::basic_large::var5,
		"var6", &lbs::basic_large::var6,
		"var7", &lbs::basic_large::var7,
		"var8", &lbs::basic_large::var8,
		"var9", &lbs::basic_large::var9,
		"var10", &lbs::basic_large::var10,
		"var11", &lbs::basic_large::var11,
		"var12", &lbs::basic_large::var12,
		"var13", &lbs::basic_large::var13,
		"var14", &lbs::basic_large::var14,
		"var15", &lbs::basic_large::var15,
		"var16", &lbs::basic_large::var16,
		"var17", &lbs::basic_large::var17,
		"var18", &lbs::basic_large::var18,
		"var19", &lbs::basic_large::var19,
		"var20", &lbs::basic_large::var20,
		"var21", &lbs::basic_large::var21,
		"var22", &lbs::basic_large::var22,
		"var23", &lbs::basic_large::var23,
		"var24", &lbs::basic_large::var24,
		"var25", &lbs::basic_large::var25,
		"var26", &lbs::basic_large::var26,
		"var27", &lbs::basic_large::var27,
		"var28", &lbs::basic_large::var28,
		"var29", &lbs::basic_large::var29,
		"var30", &lbs::basic_large::var30,
		"var31", &lbs::basic_large::var31,
		"var32", &lbs::basic_large::var32,
		"var33", &lbs::basic_large::var33,
		"var34", &lbs::basic_large::var34,
		"var35", &lbs::basic_large::var35,
		"var36", &lbs::basic_large::var36,
		"var37", &lbs::basic_large::var37,
		"var38", &lbs::basic_large::var38,
		"var39", &lbs::basic_large::var39,
		"var40", &lbs::basic_large::var40,
		"var41", &lbs::basic_large::var41,
		"var42", &lbs::basic_large::var42,
		"var43", &lbs::basic_large::var43,
		"var44", &lbs::basic_large::var44,
		"var45", &lbs::basic_large::var45,
		"var46", &lbs::basic_large::var46,
		"var47", &lbs::basic_large::var47,
		"var48", &lbs::basic_large::var48,
		"var49", &lbs::basic_large::var49);

	lua.script("b = cl:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();
	lua.new_usertype<lbs::basic_large>("cl",
		"var", &lbs::basic_large::var,
		"var0", &lbs::basic_large::var0,
		"var1", &lbs::basic_large::var1,
		"var2", &lbs::basic_large::var2,
		"var3", &lbs::basic_large::var3,
		"var4", &lbs::basic_large::var4,
		"var5", &lbs::basic_large::var5,
		"var6", &lbs::basic_large::var6,
		"var7", &lbs::basic_large::var7,
		"var8", &lbs::basic_large::var8,
		"var9", &lbs::basic_large::var9,
		"var10", &lbs::basic_large::var10,
		"var11", &lbs::basic_large::var11,
		"var12", &lbs::basic_large::var12,
		"var13", &lbs::basic_large::var13,
		"var14", &lbs::basic_large::var14,
		"var15", &lbs::basic_large::var15,
		"var16", &lbs::basic_large::var16,
		"var17", &lbs::basic_large::var17,
		"var18", &lbs::basic_large::var18,
		"var19", &lbs::basic_large::var19,
		"var20", &lbs::basic_large::var20,
		"var21", &lbs::basic_large::var21,
		"var22", &lbs::basic_large::var22,
		"var23", &lbs::basic_large::var23,
		"var24", &lbs::basic_large::var24,
		"var25", &lbs::basic_large::var25,
		"var26", &lbs::basic_large::var26,
		"var27", &lbs::basic_large::var27,
		"var28", &lbs::basic_large::var28,
		"var29", &lbs::basic_large::var29,
		"var30", &lbs::basic_large::var30,
		"var31", &lbs::basic_large::var31,
		"var32", &lbs::basic_large::var32,
		"var33", &lbs::basic_large::var33,
		"var34", &lbs::basic_large::var34,
		"var35", &lbs::basic_large::var35,
		"var36", &lbs::basic_large::var36,
		"var37", &lbs::basic_large::var37,
		"var38", &lbs::basic_large::var38,
		"var39", &lbs::basic_large::var39,
		"var40", &lbs::basic_large::var40,
		"var41", &lbs::basic_large::var41,
		"var42", &lbs::basic_large::var42,
		"var43", &lbs::basic_large::var43,
		"var44", &lbs::basic_large::var44,
		"var45", &lbs::basic_large::var45,
		"var46", &lbs::basic_large::var46,
		"var47", &lbs::basic_large::var47,
		"var48", &lbs::basic_large::var48,
		"var49", &lbs::basic_large::var49);

	lua.script("b = cl:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_stateful_function_object_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.set_function("f", lbs::basic_stateful());
	old_sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_multi_return_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", &lbs::basic_multi_return);
	old_sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f.call<double, double>(lbs::magic_value());
		x += static_cast<int>(std::get<0>(v));
		x += static_cast<int>(std::get<1>(v));
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void old_sol_lua_multi_return_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", &lbs::basic_multi_return);

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void old_sol_optional_failure_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		old_sol::object o1 = lua["warble"];
		if (o1.get_type() == old_sol::type::table) {
			old_sol::table t1 = o1.as<old_sol::table>();
			old_sol::object o2 = t1["value"];
			if (o2.get_type() == old_sol::type::number) {
				x += o2.as<double>();
				continue;
			}
		}
		x += 1;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void old_sol_optional_half_failure_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script(lbs::optional_half_failure_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		old_sol::object o1 = lua["warble"];
		if (o1.get_type() == old_sol::type::table) {
			old_sol::table t1 = o1.as<old_sol::table>();
			old_sol::object o2 = t1["value"];
			if (o2.get_type() == old_sol::type::number) {
				x += o2.as<double>();
				continue;
			}
		}
		x += 1;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void old_sol_optional_success_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script(lbs::optional_success_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		old_sol::object o1 = lua["warble"];
		if (o1.get_type() == old_sol::type::table) {
			old_sol::table t1 = o1.as<old_sol::table>();
			old_sol::object o2 = t1["value"];
			if (o2.get_type() == old_sol::type::number) {
				x += o2.as<double>();
				continue;
			}
		}
		x += 1;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void old_sol_return_userdata_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua.open_libraries();
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", lbs::basic_return);
	lua.set_function("h", lbs::basic_get_var);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
}

BENCHMARK(old_sol_global_string_get_measure);
BENCHMARK(old_sol_global_string_set_measure);
BENCHMARK(old_sol_table_get_measure);
BENCHMARK(old_sol_table_set_measure);
BENCHMARK(old_sol_table_chained_get_measure);
BENCHMARK(old_sol_table_chained_set_measure);
BENCHMARK(old_sol_c_function_measure);
BENCHMARK(old_sol_c_through_lua_function_measure);
BENCHMARK(old_sol_lua_function_measure);
BENCHMARK(old_sol_member_function_call_measure);
BENCHMARK(old_sol_userdata_variable_access_measure);
BENCHMARK(old_sol_userdata_variable_access_large_measure);
BENCHMARK(old_sol_userdata_variable_access_last_measure);
BENCHMARK(old_sol_multi_return_measure);
BENCHMARK(old_sol_lua_multi_return_measure);
BENCHMARK(old_sol_stateful_function_object_measure);
BENCHMARK(old_sol_base_derived_measure);
BENCHMARK(old_sol_return_userdata_measure);
BENCHMARK(old_sol_optional_success_measure);
BENCHMARK(old_sol_optional_half_failure_measure);
BENCHMARK(old_sol_optional_failure_measure);
BENCHMARK(old_sol_implicit_inheritance_measure);
