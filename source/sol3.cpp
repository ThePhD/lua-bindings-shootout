#define SOL_NO_EXCEPTIONS 1
#define SOL_NO_CHECK_NUMBER_PRECISION 1
#include <sol3/sol.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

void sol_global_string_get_measure(benchmark::State& bstate_) {
	sol::state lua;
	lua["value"] = 24;
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = lua.get<int>("value");
			x += v;
		}
	}
}

void sol_global_string_set_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	for (auto _ : bstate_) {
		for (int i = 0; i < repetition; ++i) {
			lua.set("value", i);
		}
	}
}

void sol_table_get_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.create_table("warble", 0, 0, "value", 24);
	sol::table t = lua["warble"];
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = t["value"];
			x += v;
		}
		return x;
	}
}

void sol_table_set_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.create_table("warble", 0, 0);
	sol::table x = lua["warble"];
	for (auto _ : bstate_) {
		for (int i = 0; i < repetition; ++i)
			x.set("value", i);
	}
}

void sol_chained_get_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = lua["ulahibe"]["warble"]["value"];
			x += v;
		}
		return x;
	}
}

void sol_chained_set_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.create_table("ulahibe", 0, 0, "warble", lua.create_table(0, 0, "value", 24));
	for (auto _ : bstate_) {
		for (int i = 0; i < repetition; ++i)
			lua["ulahibe"]["warble"]["value"] = i;
	}
}

void sol_c_function_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.set_function("f", sol::c_call<decltype(&basic_call), &basic_call>);
	std::string code = repeated_code("f(i)");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_lua_function_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.script(R"(function f (i)
		return i;
	end)");
	sol::function f = lua["f"];
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = f.call<int>(i);
			x += v;
		}
		return x;
	}
}

void sol_c_through_lua_function_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.set_function("f", sol::c_call<decltype(&basic_call), &basic_call>);
	sol::function f = lua["f"];
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = f.call<int>(i);
			x += v;
		}
		return x;
	}
}

void sol_member_function_call_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_usertype<basic>("basic",
		"get", sol::c_call<decltype(&basic::get), &basic::get>,
		"set", sol::c_call<decltype(&basic::set), &basic::set>);
	lua.script("b = basic:new()");
	std::string code = repeated_code("b:set(i) b:get()");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_member_function_call_simple_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_simple_usertype<basic>("basic",
		"get", sol::c_call<decltype(&basic::get), &basic::get>,
		"set", sol::c_call<decltype(&basic::set), &basic::set>);
	lua.script("b = basic:new()");
	std::string code = repeated_code("b:set(i) b:get()");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_usertype<basic>("basic",
		"var", &basic::var);
	lua.script("b = basic:new()");
	std::string code = repeated_code(
		userdata_variable_access_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_simple_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_simple_usertype<basic>("basic",
		"var", &basic::var);
	lua.script("b = basic:new()");
	std::string code = repeated_code(
		userdata_variable_access_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_complex_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;

	lua.new_usertype<basic_large>("basic",
		"var", &basic_large::var,
		"var0", &basic_large::var0,
		"var1", &basic_large::var1,
		"var2", &basic_large::var2,
		"var3", &basic_large::var3,
		"var4", &basic_large::var4,
		"var5", &basic_large::var5,
		"var6", &basic_large::var6,
		"var7", &basic_large::var7,
		"var8", &basic_large::var8,
		"var9", &basic_large::var9,
		"var10", &basic_large::var10,
		"var11", &basic_large::var11,
		"var12", &basic_large::var12,
		"var13", &basic_large::var13,
		"var14", &basic_large::var14,
		"var15", &basic_large::var15,
		"var16", &basic_large::var16,
		"var17", &basic_large::var17,
		"var18", &basic_large::var18,
		"var19", &basic_large::var19,
		"var20", &basic_large::var20,
		"var21", &basic_large::var21,
		"var22", &basic_large::var22,
		"var23", &basic_large::var23,
		"var24", &basic_large::var24,
		"var25", &basic_large::var25,
		"var26", &basic_large::var26,
		"var27", &basic_large::var27,
		"var28", &basic_large::var28,
		"var29", &basic_large::var29,
		"var30", &basic_large::var30,
		"var31", &basic_large::var31,
		"var32", &basic_large::var32,
		"var33", &basic_large::var33,
		"var34", &basic_large::var34,
		"var35", &basic_large::var35,
		"var36", &basic_large::var36,
		"var37", &basic_large::var37,
		"var38", &basic_large::var38,
		"var39", &basic_large::var39,
		"var40", &basic_large::var40,
		"var41", &basic_large::var41,
		"var42", &basic_large::var42,
		"var43", &basic_large::var43,
		"var44", &basic_large::var44,
		"var45", &basic_large::var45,
		"var46", &basic_large::var46,
		"var47", &basic_large::var47,
		"var48", &basic_large::var48,
		"var49", &basic_large::var49);
	lua.script("b = basic:new()");
	std::string code = repeated_code(
		userdata_variable_access_large_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_complex_simple_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_simple_usertype<basic_large>("basic_large",
		"var", &basic_large::var,
		"var0", &basic_large::var0,
		"var1", &basic_large::var1,
		"var2", &basic_large::var2,
		"var3", &basic_large::var3,
		"var4", &basic_large::var4,
		"var5", &basic_large::var5,
		"var6", &basic_large::var6,
		"var7", &basic_large::var7,
		"var8", &basic_large::var8,
		"var9", &basic_large::var9,
		"var10", &basic_large::var10,
		"var11", &basic_large::var11,
		"var12", &basic_large::var12,
		"var13", &basic_large::var13,
		"var14", &basic_large::var14,
		"var15", &basic_large::var15,
		"var16", &basic_large::var16,
		"var17", &basic_large::var17,
		"var18", &basic_large::var18,
		"var19", &basic_large::var19,
		"var20", &basic_large::var20,
		"var21", &basic_large::var21,
		"var22", &basic_large::var22,
		"var23", &basic_large::var23,
		"var24", &basic_large::var24,
		"var25", &basic_large::var25,
		"var26", &basic_large::var26,
		"var27", &basic_large::var27,
		"var28", &basic_large::var28,
		"var29", &basic_large::var29,
		"var30", &basic_large::var30,
		"var31", &basic_large::var31,
		"var32", &basic_large::var32,
		"var33", &basic_large::var33,
		"var34", &basic_large::var34,
		"var35", &basic_large::var35,
		"var36", &basic_large::var36,
		"var37", &basic_large::var37,
		"var38", &basic_large::var38,
		"var39", &basic_large::var39,
		"var40", &basic_large::var40,
		"var41", &basic_large::var41,
		"var42", &basic_large::var42,
		"var43", &basic_large::var43,
		"var44", &basic_large::var44,
		"var45", &basic_large::var45,
		"var46", &basic_large::var46,
		"var47", &basic_large::var47,
		"var48", &basic_large::var48,
		"var49", &basic_large::var49);

	lua.script("b = basic_large:new()");
	std::string code = repeated_code(
		userdata_variable_access_large_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_last_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_usertype<basic_large>("basic_large",
		"var", &basic_large::var,
		"var0", &basic_large::var0,
		"var1", &basic_large::var1,
		"var2", &basic_large::var2,
		"var3", &basic_large::var3,
		"var4", &basic_large::var4,
		"var5", &basic_large::var5,
		"var6", &basic_large::var6,
		"var7", &basic_large::var7,
		"var8", &basic_large::var8,
		"var9", &basic_large::var9,
		"var10", &basic_large::var10,
		"var11", &basic_large::var11,
		"var12", &basic_large::var12,
		"var13", &basic_large::var13,
		"var14", &basic_large::var14,
		"var15", &basic_large::var15,
		"var16", &basic_large::var16,
		"var17", &basic_large::var17,
		"var18", &basic_large::var18,
		"var19", &basic_large::var19,
		"var20", &basic_large::var20,
		"var21", &basic_large::var21,
		"var22", &basic_large::var22,
		"var23", &basic_large::var23,
		"var24", &basic_large::var24,
		"var25", &basic_large::var25,
		"var26", &basic_large::var26,
		"var27", &basic_large::var27,
		"var28", &basic_large::var28,
		"var29", &basic_large::var29,
		"var30", &basic_large::var30,
		"var31", &basic_large::var31,
		"var32", &basic_large::var32,
		"var33", &basic_large::var33,
		"var34", &basic_large::var34,
		"var35", &basic_large::var35,
		"var36", &basic_large::var36,
		"var37", &basic_large::var37,
		"var38", &basic_large::var38,
		"var39", &basic_large::var39,
		"var40", &basic_large::var40,
		"var41", &basic_large::var41,
		"var42", &basic_large::var42,
		"var43", &basic_large::var43,
		"var44", &basic_large::var44,
		"var45", &basic_large::var45,
		"var46", &basic_large::var46,
		"var47", &basic_large::var47,
		"var48", &basic_large::var48,
		"var49", &basic_large::var49);
	lua.script("b = basic_large:new()");
	std::string code = repeated_code(userdata_variable_access_large_last_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_userdata_variable_access_last_simple_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.new_simple_usertype<basic_large>("basic_large",
		"var", &basic_large::var,
		"var0", &basic_large::var0,
		"var1", &basic_large::var1,
		"var2", &basic_large::var2,
		"var3", &basic_large::var3,
		"var4", &basic_large::var4,
		"var5", &basic_large::var5,
		"var6", &basic_large::var6,
		"var7", &basic_large::var7,
		"var8", &basic_large::var8,
		"var9", &basic_large::var9,
		"var10", &basic_large::var10,
		"var11", &basic_large::var11,
		"var12", &basic_large::var12,
		"var13", &basic_large::var13,
		"var14", &basic_large::var14,
		"var15", &basic_large::var15,
		"var16", &basic_large::var16,
		"var17", &basic_large::var17,
		"var18", &basic_large::var18,
		"var19", &basic_large::var19,
		"var20", &basic_large::var20,
		"var21", &basic_large::var21,
		"var22", &basic_large::var22,
		"var23", &basic_large::var23,
		"var24", &basic_large::var24,
		"var25", &basic_large::var25,
		"var26", &basic_large::var26,
		"var27", &basic_large::var27,
		"var28", &basic_large::var28,
		"var29", &basic_large::var29,
		"var30", &basic_large::var30,
		"var31", &basic_large::var31,
		"var32", &basic_large::var32,
		"var33", &basic_large::var33,
		"var34", &basic_large::var34,
		"var35", &basic_large::var35,
		"var36", &basic_large::var36,
		"var37", &basic_large::var37,
		"var38", &basic_large::var38,
		"var39", &basic_large::var39,
		"var40", &basic_large::var40,
		"var41", &basic_large::var41,
		"var42", &basic_large::var42,
		"var43", &basic_large::var43,
		"var44", &basic_large::var44,
		"var45", &basic_large::var45,
		"var46", &basic_large::var46,
		"var47", &basic_large::var47,
		"var48", &basic_large::var48,
		"var49", &basic_large::var49);

	lua.script("b = basic_large:new()");
	std::string code = repeated_code(
		userdata_variable_access_large_last_code);

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_stateful_function_object_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	int storage = 0;
	lua.set_function("f", basic_stateful());
	sol::function f = lua["f"];
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = f.call<int>(i);
			x += v;
		}
		return x;
	}
}

void sol_multi_return_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;

	lua.set_function("f", sol::c_call<decltype(&basic_multi_return), basic_multi_return>);
	sol::function f = lua["f"];
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			std::tuple<int, int> v = f.call<int, int>(i);
			x += static_cast<int>(std::get<0>(v));
			x += static_cast<int>(std::get<1>(v));
		}
		return x;
	}
}

void sol_base_derived_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua.new_usertype<complex_ab>("complex_ab",
		"a_func", &complex_ab::a_func,
		"b_func", &complex_ab::b_func,
		"ab_func", &complex_ab::ab_func,
		sol::base_classes, sol::bases<complex_base_a, complex_base_b>());
	complex_ab ab;
	// Set and verify correctness
	lua.set("b", &ab);
	{
		complex_base_a& va = lua["b"];
		complex_base_b& vb = lua["b"];
		if (va.a_func() != ab.a_func() || va.a != ab.a) {
			throw std::logic_error("proper base class casting not provided: failing test");
		}
		if (vb.b_func() != ab.b_func() || vb.b != ab.b) {
			throw std::logic_error("proper base class casting not provided: failing test");
		}
	}
	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			complex_base_a& va = lua["b"];
			complex_base_b& vb = lua["b"];
			x += va.a_func();
			x += vb.b_func();
		}
		return x;
	}
}

void sol_optional_measure(benchmark::State& bstate_) {
	sol::state lua;
	lua.set_panic(panic_throw);

	for (auto _ : bstate_) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			sol::optional<int> v = lua["warble"]["value"];
			x += v.value_or(1);
		}
		return x;
	}
}

void sol_return_userdata_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;
	lua.set_function("f", sol::c_call<decltype(&basic_return), basic_return>);
	std::string code = repeated_code("b = f(i)");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void sol_implicit_inheritance_call_measure(benchmark::State& bstate_) {
	sol::state lua(panic_throw);
	lua_State* L = lua;

	lua.new_usertype<complex_base_a>("complex_base_a",
		"a", &complex_base_a::a,
		"a_func", &complex_base_a::a_func);

	lua.new_usertype<complex_base_b>("complex_base_b",
		"b", &complex_base_b::b,
		"b_func", &complex_base_b::b_func);

	lua.new_usertype<complex_ab>("complex_ab",
		"ab", &complex_ab::ab,
		"ab_func", &complex_ab::ab_func,
		sol::base_classes, sol::bases<complex_base_a, complex_base_b>());

	complex_ab ab;
	// Set and verify correctness
	lua.set("b", &ab);

	std::string code = repeated_code("b:b_func()");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : bstate_) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}
