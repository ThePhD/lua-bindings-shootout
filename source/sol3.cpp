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
#include <sol.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

void sol3_global_string_get_measure(benchmark::State& benchmark_state) {
	sol::state lua;
	lua["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_global_string_set_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
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

void sol3_table_get_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.create_table("warble", 0, 0, "value", lbs::magic_value());
	sol::table t = lua["warble"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_table_set_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.create_table("warble", 0, 0);
	sol::table t = lua["warble"];
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

void sol3_table_chained_get_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);

	lua["ulahibe"] = sol::create;
	lua["ulahibe"]["warble"] = sol::create;
	lua["ulahibe"]["warble"]["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"]["warble"]["value"];
		x += v;
	}
}

void sol3_table_chained_set_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua["ulahibe"]["warble"]["value"] = v;
	}
	double x = lua["ulahibe"]["warble"]["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_c_function_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;
	lua.set_function("f", sol::c_call<decltype(&lbs::basic_call), &lbs::basic_call>);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_lua_function_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.script(R"(function f (i)
		return i;
	end)");
	sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.set_function("f", sol::c_call<decltype(&lbs::basic_call), &lbs::basic_call>);
	sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_member_function_call_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;
	lua.new_usertype<lbs::basic>("c",
		"get", sol::c_call<decltype(&lbs::basic::get), &lbs::basic::get>,
		"set", sol::c_call<decltype(&lbs::basic::set), &lbs::basic::set>);
	lua.script("b = c.new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code("b:set(i) b:get()");
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;
	lua.new_usertype<lbs::basic>("c",
		"var", &lbs::basic::var);
	lua.script("b = c.new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;

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
	lua.script("b = cl.new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;
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
	lua.script("b = cl.new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_stateful_function_object_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.set_function("f", lbs::basic_stateful());
	sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f.call<double>(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_lua_multi_return_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;

	lua.set_function("f", sol::c_call<decltype(&lbs::basic_multi_return), &lbs::basic_multi_return>);

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_multi_return_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua_State* L = lua;

	lua.set_function("f", sol::c_call<decltype(&lbs::basic_multi_return), &lbs::basic_multi_return>);
	sol::function f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f.call<double, double>(lbs::magic_value());
		x += static_cast<int>(std::get<0>(v));
		x += static_cast<int>(std::get<1>(v));
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void sol3_base_derived_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.new_usertype<lbs::complex_ab>("cab",
		"a_func", sol::c_call<decltype(&lbs::complex_ab::a_func), &lbs::complex_ab::a_func>,
		"b_func", sol::c_call<decltype(&lbs::complex_ab::b_func), &lbs::complex_ab::b_func>,
		"ab_func", sol::c_call<decltype(&lbs::complex_ab::ab_func), &lbs::complex_ab::ab_func>,
		sol::base_classes, sol::bases<lbs::complex_base_a, lbs::complex_base_b>());
	lbs::complex_ab ab;
	// Set and verify correctness
	lua.set("b", &ab);
	{
		lbs::complex_base_a& va = lua["b"];
		lbs::complex_base_b& vb = lua["b"];
		if (!lbs::verify_base_correctness(va, vb, ab)) {
			lbs::unsupported(benchmark_state);
			return;
		}
	}
	double x = 0;
	for (auto _ : benchmark_state) {
		lbs::complex_base_a& va = lua["b"];
		lbs::complex_base_b& vb = lua["b"];
		x += va.a_func();
		x += vb.b_func();
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 2));
}

void sol3_optional_success_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);

	lua.script(lbs::optional_success_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		sol::optional<double> v = lua["warble"]["value"];
		x += v.value_or(1);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_optional_half_failure_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);

	lua.script(lbs::optional_half_failure_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		sol::optional<double> v = lua["warble"]["value"];
		x += v.value_or(1);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void sol3_optional_failure_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		sol::optional<double> v = lua["warble"]["value"];
		x += v.value_or(1);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void sol3_return_userdata_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;

	lua.set_function("f", sol::c_call<decltype(&lbs::basic_return), lbs::basic_return>);
	lua.set_function("h", lbs::basic_get_var);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void sol3_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	sol::state lua(lbs::panic_throw);
	lua.open_libraries();
	lua_State* L = lua;

	lua.new_usertype<lbs::complex_base_a>("ca",
		"a", &lbs::complex_base_a::a,
		"a_func", sol::c_call<decltype(&lbs::complex_base_a::a_func), &lbs::complex_base_a::a_func>);

	lua.new_usertype<lbs::complex_base_b>("cb",
		"b", &lbs::complex_base_b::b,
		"b_func", sol::c_call<decltype(&lbs::complex_base_b::b_func), &lbs::complex_base_b::b_func>);

	lua.new_usertype<lbs::complex_ab>("cab",
		"ab", &lbs::complex_ab::ab,
		"ab_func", sol::c_call<decltype(&lbs::complex_ab::ab_func), &lbs::complex_ab::ab_func>,
		sol::base_classes, sol::bases<lbs::complex_base_a, lbs::complex_base_b>());

	lbs::complex_ab ab;
	// Set and verify correctness
	lua.set("b", &ab);

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(sol3_global_string_get_measure);
BENCHMARK(sol3_global_string_set_measure);
BENCHMARK(sol3_table_get_measure);
BENCHMARK(sol3_table_set_measure);
BENCHMARK(sol3_table_chained_get_measure);
BENCHMARK(sol3_table_chained_set_measure);
BENCHMARK(sol3_c_function_measure);
BENCHMARK(sol3_c_through_lua_function_measure);
BENCHMARK(sol3_lua_function_measure);
BENCHMARK(sol3_member_function_call_measure);
BENCHMARK(sol3_userdata_variable_access_measure);
BENCHMARK(sol3_userdata_variable_access_large_measure);
BENCHMARK(sol3_userdata_variable_access_last_measure);
BENCHMARK(sol3_lua_multi_return_measure);
BENCHMARK(sol3_multi_return_measure);
BENCHMARK(sol3_stateful_function_object_measure);
BENCHMARK(sol3_base_derived_measure);
BENCHMARK(sol3_return_userdata_measure);
BENCHMARK(sol3_optional_success_measure);
BENCHMARK(sol3_optional_half_failure_measure);
BENCHMARK(sol3_optional_failure_measure);
BENCHMARK(sol3_implicit_inheritance_measure);
