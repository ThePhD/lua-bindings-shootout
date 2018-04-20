#define SOL_NO_EXCEPTIONS 1
#define SOL_NO_CHECK_NUMBER_PRECISION 1
#include <old_sol/old_sol.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

void old_sol_global_string_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua["value"] = 3;
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_global_string_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	double v = 0;
	for (auto _ : benchmark_state) {
		lua.set("value", v);
		v += 3;
	}
	double x = lua["value"];
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void old_sol_table_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("warble = { value = 24 }");
	old_sol::table t = lua["warble"].get<old_sol::table>();

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_table_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.create_table("warble", 0, 0);
	old_sol::table t = lua["warble"].get<old_sol::table>();

	double v = 0;
	for (auto _ : benchmark_state) {
		t.set("value", v);
		v += 3;
	}
	double x = t["value"];
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void old_sol_table_chained_get_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("ulahibe = { warble = { value = 24 } }");

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"].get<double>();
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_table_chained_set_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.script("ulahibe = { warble = { value = 24 } }");

	double v = 0;
	for (auto _ : benchmark_state) {
		lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"] = v;
		v += 3;
	}
	double x = lua["ulahibe"].get<old_sol::table>()["warble"].get<old_sol::table>()["value"].get<double>();
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void old_sol_c_function_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", &lbs::basic_call);
	std::string code = lbs::repeated_code("f(i)");

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
		double v = f.call<double>(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua.set_function("f", &lbs::basic_call);
	old_sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_member_function_call_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();
	lua.new_usertype<lbs::basic>("lbs::basic",
		"get", &lbs::basic::get,
		"set", &lbs::basic::set);
	lua.script("b = lbs::basic:new()");
	std::string code = lbs::repeated_code("b:set(i) b:get()");

	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();

	lua.new_usertype<lbs::basic>("basic",
		"var", &lbs::basic::var);
	lua.script("b = basic:new()");
	std::string code = lbs::repeated_code(
		lbs::userdata_variable_access_code);

	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();

	lua.new_usertype<lbs::basic_large>("basic",
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

	lua.script("b = basic:new()");
	std::string code = lbs::repeated_code(
		lbs::userdata_variable_access_large_code);

	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	lua_State* L = lua.lua_state();
	lua.new_usertype<lbs::basic_large>("lbs::basic_large",
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

	lua.script("b = basic_large:new()");
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
		double v = f.call<double>(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void old_sol_multi_return_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", &lbs::basic_multi_return);
	old_sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f.call<double, double>(3);
		x += static_cast<int>(std::get<0>(v));
		x += static_cast<int>(std::get<1>(v));
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 6);
}

void old_sol_base_derived_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
}

void old_sol_optional_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		old_sol::table o1 = lua["warble"];
		if (o1.get_type() == old_sol::type::table) {
			old_sol::object o2 = o1["value"];
			if (o2.get_type() == old_sol::type::number) {
				x += o2.as<double>();
				continue;
			}
		}
		x += 1;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void old_sol_return_userdata_measure(benchmark::State& benchmark_state) {
	old_sol::state lua;
	lua_atpanic(lua.lua_state(), lbs::panic_throw);
	lua_State* L = lua.lua_state();

	lua.set_function("f", lbs::basic_return);
	std::string code = lbs::repeated_code("b = f(i)");

	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void old_sol_implicit_inheritance_call_measure(benchmark::State& benchmark_state) {
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
BENCHMARK(old_sol_stateful_function_object_measure);
BENCHMARK(old_sol_base_derived_measure);
BENCHMARK(old_sol_base_derived_measure);
BENCHMARK(old_sol_return_userdata_measure);
BENCHMARK(old_sol_optional_measure);
BENCHMARK(old_sol_implicit_inheritance_call_measure);
