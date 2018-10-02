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
#include <sol/sol.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

SOL_DERIVED_CLASSES(lbs::complex_base_a, lbs::complex_ab);
SOL_DERIVED_CLASSES(lbs::complex_base_b, lbs::complex_ab);
SOL_BASE_CLASSES(lbs::complex_ab, lbs::complex_base_a, lbs::complex_base_b);

void sol3_table_global_string_get_measure(benchmark::State& benchmark_state) {
	sol::state lua;
	lua["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void sol3_table_global_string_set_measure(benchmark::State& benchmark_state) {
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

void sol3_lua_function_in_c_measure(benchmark::State& benchmark_state) {
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

void sol3_c_function_through_lua_in_c_measure(benchmark::State& benchmark_state) {
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
	auto ut = lua.new_usertype<lbs::basic>("c");
	ut["get"] = sol::c_call<decltype(&lbs::basic::get), &lbs::basic::get>;
	ut["set"] = sol::c_call<decltype(&lbs::basic::set), &lbs::basic::set>;
	lua.script("b = c.new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
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
	auto ut = lua.new_usertype<lbs::basic>("c");
	ut["var"] = &lbs::basic::var;
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

	auto ut = lua.new_usertype<lbs::basic_large>("cl");
	ut["var"] = &lbs::basic_large::var;
	ut["var0"] = &lbs::basic_large::var0;
	ut["var1"] = &lbs::basic_large::var1;
	ut["var2"] = &lbs::basic_large::var2;
	ut["var3"] = &lbs::basic_large::var3;
	ut["var4"] = &lbs::basic_large::var4;
	ut["var5"] = &lbs::basic_large::var5;
	ut["var6"] = &lbs::basic_large::var6;
	ut["var7"] = &lbs::basic_large::var7;
	ut["var8"] = &lbs::basic_large::var8;
	ut["var9"] = &lbs::basic_large::var9;
	ut["var10"] = &lbs::basic_large::var10;
	ut["var11"] = &lbs::basic_large::var11;
	ut["var12"] = &lbs::basic_large::var12;
	ut["var13"] = &lbs::basic_large::var13;
	ut["var14"] = &lbs::basic_large::var14;
	ut["var15"] = &lbs::basic_large::var15;
	ut["var16"] = &lbs::basic_large::var16;
	ut["var17"] = &lbs::basic_large::var17;
	ut["var18"] = &lbs::basic_large::var18;
	ut["var19"] = &lbs::basic_large::var19;
	ut["var20"] = &lbs::basic_large::var20;
	ut["var21"] = &lbs::basic_large::var21;
	ut["var22"] = &lbs::basic_large::var22;
	ut["var23"] = &lbs::basic_large::var23;
	ut["var24"] = &lbs::basic_large::var24;
	ut["var25"] = &lbs::basic_large::var25;
	ut["var26"] = &lbs::basic_large::var26;
	ut["var27"] = &lbs::basic_large::var27;
	ut["var28"] = &lbs::basic_large::var28;
	ut["var29"] = &lbs::basic_large::var29;
	ut["var30"] = &lbs::basic_large::var30;
	ut["var31"] = &lbs::basic_large::var31;
	ut["var32"] = &lbs::basic_large::var32;
	ut["var33"] = &lbs::basic_large::var33;
	ut["var34"] = &lbs::basic_large::var34;
	ut["var35"] = &lbs::basic_large::var35;
	ut["var36"] = &lbs::basic_large::var36;
	ut["var37"] = &lbs::basic_large::var37;
	ut["var38"] = &lbs::basic_large::var38;
	ut["var39"] = &lbs::basic_large::var39;
	ut["var40"] = &lbs::basic_large::var40;
	ut["var41"] = &lbs::basic_large::var41;
	ut["var42"] = &lbs::basic_large::var42;
	ut["var43"] = &lbs::basic_large::var43;
	ut["var44"] = &lbs::basic_large::var44;
	ut["var45"] = &lbs::basic_large::var45;
	ut["var46"] = &lbs::basic_large::var46;
	ut["var47"] = &lbs::basic_large::var47;
	ut["var48"] = &lbs::basic_large::var48;
	ut["var49"] = &lbs::basic_large::var49;
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
	auto ut = lua.new_usertype<lbs::basic_large>("cl");
	ut["var"] = &lbs::basic_large::var;
	ut["var0"] = &lbs::basic_large::var0;
	ut["var1"] = &lbs::basic_large::var1;
	ut["var2"] = &lbs::basic_large::var2;
	ut["var3"] = &lbs::basic_large::var3;
	ut["var4"] = &lbs::basic_large::var4;
	ut["var5"] = &lbs::basic_large::var5;
	ut["var6"] = &lbs::basic_large::var6;
	ut["var7"] = &lbs::basic_large::var7;
	ut["var8"] = &lbs::basic_large::var8;
	ut["var9"] = &lbs::basic_large::var9;
	ut["var10"] = &lbs::basic_large::var10;
	ut["var11"] = &lbs::basic_large::var11;
	ut["var12"] = &lbs::basic_large::var12;
	ut["var13"] = &lbs::basic_large::var13;
	ut["var14"] = &lbs::basic_large::var14;
	ut["var15"] = &lbs::basic_large::var15;
	ut["var16"] = &lbs::basic_large::var16;
	ut["var17"] = &lbs::basic_large::var17;
	ut["var18"] = &lbs::basic_large::var18;
	ut["var19"] = &lbs::basic_large::var19;
	ut["var20"] = &lbs::basic_large::var20;
	ut["var21"] = &lbs::basic_large::var21;
	ut["var22"] = &lbs::basic_large::var22;
	ut["var23"] = &lbs::basic_large::var23;
	ut["var24"] = &lbs::basic_large::var24;
	ut["var25"] = &lbs::basic_large::var25;
	ut["var26"] = &lbs::basic_large::var26;
	ut["var27"] = &lbs::basic_large::var27;
	ut["var28"] = &lbs::basic_large::var28;
	ut["var29"] = &lbs::basic_large::var29;
	ut["var30"] = &lbs::basic_large::var30;
	ut["var31"] = &lbs::basic_large::var31;
	ut["var32"] = &lbs::basic_large::var32;
	ut["var33"] = &lbs::basic_large::var33;
	ut["var34"] = &lbs::basic_large::var34;
	ut["var35"] = &lbs::basic_large::var35;
	ut["var36"] = &lbs::basic_large::var36;
	ut["var37"] = &lbs::basic_large::var37;
	ut["var38"] = &lbs::basic_large::var38;
	ut["var39"] = &lbs::basic_large::var39;
	ut["var40"] = &lbs::basic_large::var40;
	ut["var41"] = &lbs::basic_large::var41;
	ut["var42"] = &lbs::basic_large::var42;
	ut["var43"] = &lbs::basic_large::var43;
	ut["var44"] = &lbs::basic_large::var44;
	ut["var45"] = &lbs::basic_large::var45;
	ut["var46"] = &lbs::basic_large::var46;
	ut["var47"] = &lbs::basic_large::var47;
	ut["var48"] = &lbs::basic_large::var48;
	ut["var49"] = &lbs::basic_large::var49;
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

void sol3_multi_return_lua_measure(benchmark::State& benchmark_state) {
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
	auto ut = lua.new_usertype<lbs::complex_ab>("cab");
	ut["a_func"] = sol::c_call<decltype(&lbs::complex_ab::a_func), &lbs::complex_ab::a_func>;
	ut["b_func"] = sol::c_call<decltype(&lbs::complex_ab::b_func), &lbs::complex_ab::b_func>;
	ut["ab_func"] = sol::c_call<decltype(&lbs::complex_ab::ab_func), &lbs::complex_ab::ab_func>;
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
	lua.set_function("h", &lbs::basic_get_var);

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

	auto uta = lua.new_usertype<lbs::complex_base_a>("ca");
	uta["a"] = &lbs::complex_base_a::a;
	uta["a_func"] = sol::c_call<decltype(&lbs::complex_base_a::a_func), &lbs::complex_base_a::a_func>;

	auto utb = lua.new_usertype<lbs::complex_base_b>("cb");
	utb["b"] = &lbs::complex_base_b::b;
	utb["b_func"] = sol::c_call<decltype(&lbs::complex_base_b::b_func), &lbs::complex_base_b::b_func>;

	auto utab = lua.new_usertype<lbs::complex_ab>("cab");
	utab["ab"] = &lbs::complex_ab::ab;
	utab["ab_func"] = sol::c_call<decltype(&lbs::complex_ab::ab_func), &lbs::complex_ab::ab_func>;

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

BENCHMARK(sol3_table_global_string_get_measure);
BENCHMARK(sol3_table_global_string_set_measure);
BENCHMARK(sol3_table_get_measure);
BENCHMARK(sol3_table_set_measure);
BENCHMARK(sol3_table_chained_get_measure);
BENCHMARK(sol3_table_chained_set_measure);
BENCHMARK(sol3_c_function_measure);
BENCHMARK(sol3_c_function_through_lua_in_c_measure);
BENCHMARK(sol3_lua_function_in_c_measure);
BENCHMARK(sol3_member_function_call_measure);
BENCHMARK(sol3_userdata_variable_access_measure);
BENCHMARK(sol3_userdata_variable_access_large_measure);
BENCHMARK(sol3_userdata_variable_access_last_measure);
BENCHMARK(sol3_multi_return_lua_measure);
BENCHMARK(sol3_multi_return_measure);
BENCHMARK(sol3_stateful_function_object_measure);
BENCHMARK(sol3_base_derived_measure);
BENCHMARK(sol3_return_userdata_measure);
BENCHMARK(sol3_optional_success_measure);
BENCHMARK(sol3_optional_half_failure_measure);
BENCHMARK(sol3_optional_failure_measure);
BENCHMARK(sol3_implicit_inheritance_measure);
