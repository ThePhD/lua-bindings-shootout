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

#include <lua.hpp>

#include "lbs_lua.hpp"
#include "lbs_lib.hpp"
#include "benchmark.hpp"

void plain_c_table_global_string_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_pushnumber(L, lbs::magic_value());
	lua_setglobal(L, "value");
	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "value");
		double v = lua_tonumber(L, -1);
		x += v;
		lua_pop(L, 1);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_table_global_string_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua_pushnumber(L, v);
		lua_setglobal(L, "value");
	}
	lua_getglobal(L, "value");
	double x = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_table_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_createtable(L, 0, 0);
	lua_pushnumber(L, lbs::magic_value());
	lua_setfield(L, -2, "value");
	lua_setglobal(L, "warble");

	lua_getglobal(L, "warble");
	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getfield(L, -1, "value");
		double v = lua_tonumber(L, -1);
		x += v;
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_table_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_createtable(L, 0, 0);
	lua_pushnumber(L, lbs::magic_value());
	lua_setfield(L, -2, "value");
	lua_setglobal(L, "warble");

	lua_getglobal(L, "warble");
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua_pushnumber(L, v);
		lua_setfield(L, -2, "value");
	}
	lua_getfield(L, -1, "value");
	double x = lua_tonumber(L, -1);
	lua_pop(L, 2);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_table_chained_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_createtable(L, 0, 0);
	lua_createtable(L, 0, 0);
	lua_pushnumber(L, lbs::magic_value());
	lua_setfield(L, -2, "value");
	lua_setfield(L, -2, "warble");
	lua_setglobal(L, "ulahibe");
	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "ulahibe");
		lua_getfield(L, -1, "warble");
		lua_getfield(L, -1, "value");
		double v = static_cast<double>(lua_tonumber(L, -1));
		x += v;
		lua_pop(L, 3);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_table_chained_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_createtable(L, 0, 0);
	lua_createtable(L, 0, 0);
	lua_pushnumber(L, lbs::magic_value());
	lua_setfield(L, -2, "value");
	lua_setfield(L, -2, "warble");
	lua_setglobal(L, "ulahibe");
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua_getglobal(L, "ulahibe");
		lua_getfield(L, -1, "warble");
		lua_pushnumber(L, v);
		lua_setfield(L, -2, "value");
		lua_pop(L, 2);
	}
	lua_getglobal(L, "ulahibe");
	lua_getfield(L, -1, "warble");
	lua_getfield(L, -1, "value");
	double x = lua_tonumber(L, -1);
	lua_pop(L, 3);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_c_function_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lua_pushcfunction(L, &lbs::basic_call_wrap);
	lua_setglobal(L, "f");

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_lua_function_in_c_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lbs::lua_bench_do_or_die(L, "function f (i) return i end");
	lua_getglobal(L, "f");
	int registry_index = luaL_ref(L, LUA_REGISTRYINDEX);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, registry_index);
		lua_pushnumber(L, lbs::magic_value());
		lua_callk(L, 1, 1, 0, nullptr);
		double v = lua_tonumber(L, -1);
		lua_pop(L, 1);
		x += v;
	}
	luaL_unref(L, LUA_REGISTRYINDEX, registry_index);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_c_function_through_lua_in_c_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lua_pushcfunction(L, &lbs::basic_call_wrap);
	lua_setglobal(L, "f");
	lua_getglobal(L, "f");
	int registry_index = luaL_ref(L, LUA_REGISTRYINDEX);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, registry_index);
		lua_pushnumber(L, lbs::magic_value());
		lua_callk(L, 1, 1, 0, nullptr);
		double v = lua_tonumber(L, -1);
		x += v;
		lua_pop(L, 1);
	}
	luaL_unref(L, LUA_REGISTRYINDEX, registry_index);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_member_function_call_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lbs::basic** s = static_cast<lbs::basic**>(lua_newuserdata(L, sizeof(lbs::basic*)));
	lbs::basic b;
	*s = &b;
	luaL_Reg funcs[] = {
		//{ "__index", &lbs::basic_index_wrap },
		//{ "__newindex", &lbs::basic_newindex_wrap },
		{ "set", &lbs::basic_set_wrap },
		{ "get", &lbs::basic_get_wrap },
		{ nullptr, nullptr }
	};
	luaL_newmetatable(L, "c");
	lua_createtable(L, 0, 0);
	luaL_setfuncs(L, funcs, 0);
	lua_setfield(L, -2, "__index");
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lbs::basic** s = static_cast<lbs::basic**>(lua_newuserdata(L, sizeof(lbs::basic*)));
	lbs::basic b;
	*s = &b;
	luaL_Reg funcs[] = {
		{ "__index", &lbs::basic_index_wrap },
		{ "__newindex", &lbs::basic_newindex_wrap },
		{ nullptr, nullptr }
	};
	luaL_newmetatable(L, "c");
	luaL_setfuncs(L, funcs, 0);
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lbs::basic_large** s = static_cast<lbs::basic_large**>(lua_newuserdata(L, sizeof(lbs::basic_large*)));
	lbs::basic_large b;
	*s = &b;
	luaL_Reg funcs[] = {
		{ "__index", &lbs::basic_large_index_wrap },
		{ "__newindex", &lbs::basic_large_newindex_wrap },
		{ nullptr, nullptr }
	};
	luaL_newmetatable(L, "cl");
	luaL_setfuncs(L, funcs, 0);
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lbs::basic_large** s = static_cast<lbs::basic_large**>(lua_newuserdata(L, sizeof(lbs::basic_large*)));
	lbs::basic_large b;
	*s = &b;
	luaL_Reg funcs[] = {
		{ "__index", &lbs::basic_large_index_wrap },
		{ "__newindex", &lbs::basic_large_newindex_wrap },
		{ nullptr, nullptr }
	};
	luaL_newmetatable(L, "cl");
	luaL_setfuncs(L, funcs, 0);
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_stateful_function_object_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	new (lua_newuserdata(L, sizeof(lbs::basic_stateful))) lbs::basic_stateful();
	lua_createtable(L, 0, 1);
	lua_pushcclosure(L, &lbs::gc_wrap<lbs::basic_stateful>, 0);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	lua_pushcclosure(L, &lbs::basic_stateful_wrap, 1);
	lua_setglobal(L, "f");
	lua_getglobal(L, "f");
	int registry_index = luaL_ref(L, LUA_REGISTRYINDEX);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, registry_index);
		lua_pushnumber(L, lbs::magic_value());
		lua_callk(L, 1, 1, 0, nullptr);
		double v = lua_tonumber(L, -1);
		x += v;
		lua_pop(L, 1);
	}
	luaL_unref(L, LUA_REGISTRYINDEX, registry_index);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_multi_return_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lua_pushcclosure(L, &lbs::basic_multi_return_wrap, 0);
	lua_setglobal(L, "f");
	lua_getglobal(L, "f");
	int registry_index = luaL_ref(L, LUA_REGISTRYINDEX);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, registry_index);
		lua_pushnumber(L, lbs::magic_value());
		lua_callk(L, 1, 2, 0, nullptr);
		double v = lua_tonumber(L, -1);
		double w = lua_tonumber(L, -2);
		x += v;
		x += w;
		lua_pop(L, 2);
	}
	luaL_unref(L, LUA_REGISTRYINDEX, registry_index);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void plain_c_multi_return_lua_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lua_pushcclosure(L, &lbs::basic_multi_return_wrap, 0);
	lua_setglobal(L, "f");

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_base_derived_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lbs::complex_ab* pab = static_cast<lbs::complex_ab*>(lua_newuserdata(L, sizeof(lbs::complex_ab)));
	new (pab) lbs::complex_ab();
	lbs::complex_ab& ab = *pab;
	// ensure destruction no matter what
	struct kill_me {
		lbs::complex_ab& ab;

		kill_me(lbs::complex_ab& ab_)
		: ab(ab_) {
		}
		~kill_me() {
			ab.~complex_ab();
		}
	} pls(ab);

	lua_createtable(L, 0, 1);
	lua_pushcclosure(L, &lbs::gc_wrap<lbs::complex_ab>, 0);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	{ // verify correctness
		lua_getglobal(L, "b");
		lbs::complex_base_a& va = *static_cast<lbs::complex_base_a*>(static_cast<lbs::complex_ab*>(lua_touserdata(L, -1)));
		lbs::complex_base_b& vb = *static_cast<lbs::complex_base_b*>(static_cast<lbs::complex_ab*>(lua_touserdata(L, -1)));
		lua_pop(L, 1);
		if (!lbs::verify_base_correctness(va, vb, ab)) {
			return;
		}
	}

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "b");
		lbs::complex_base_a& va = *static_cast<lbs::complex_base_a*>(static_cast<lbs::complex_ab*>(lua_touserdata(L, -1)));
		lbs::complex_base_b& vb = *static_cast<lbs::complex_base_b*>(static_cast<lbs::complex_ab*>(lua_touserdata(L, -1)));

		x += va.a_func();
		x += vb.b_func();

		lua_pop(L, 1);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 2));
}

void plain_c_return_userdata_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lua_pushcclosure(L, &lbs::basic_return_wrap, 0);
	lua_setglobal(L, "f");
	lua_pushcclosure(L, &lbs::basic_get_wrap, 0);
	lua_setglobal(L, "h");

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void plain_c_optional_failure_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "warble");
		if (lua_type(L, -1) != LUA_TNIL) {
			lua_getfield(L, -1, "value");
			if (lua_type(L, -1) != LUA_TNIL) {
				double v = lua_tonumber(L, -1);
				x += v;
			}
			else {
				x += 1;
			}
			lua_pop(L, 2);
		}
		else {
			lua_pop(L, 1);
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void plain_c_optional_half_failure_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lbs::lua_bench_do_or_die(L, lbs::optional_half_failure_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "warble");
		if (lua_type(L, -1) != LUA_TNIL) {
			lua_getfield(L, -1, "value");
			if (lua_type(L, -1) != LUA_TNIL) {
				double v = lua_tonumber(L, -1);
				x += v;
			}
			else {
				x += 1;
			}
			lua_pop(L, 2);
		}
		else {
			lua_pop(L, 1);
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void plain_c_optional_success_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(false);
	lua_State* L = lua.get();

	lbs::lua_bench_do_or_die(L, lbs::optional_success_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		lua_getglobal(L, "warble");
		if (lua_type(L, -1) != LUA_TNIL) {
			lua_getfield(L, -1, "value");
			if (lua_type(L, -1) != LUA_TNIL) {
				double v = lua_tonumber(L, -1);
				x += v;
			}
			else {
				x += 1;
			}
			lua_pop(L, 2);
		}
		else {
			lua_pop(L, 1);
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void plain_c_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();

	lbs::complex_ab** s = static_cast<lbs::complex_ab**>(lua_newuserdata(L, sizeof(lbs::complex_ab*)));
	lbs::complex_ab b;
	*s = &b;
	luaL_Reg funcs[] = {
		{ "__index", &lbs::complex_ab_index_wrap },
		{ nullptr, nullptr }
	};
	luaL_newmetatable(L, "cab");
	luaL_setfuncs(L, funcs, 0);
	lua_setmetatable(L, -2);
	lua_setglobal(L, "b");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(plain_c_table_global_string_get_measure);
BENCHMARK(plain_c_table_global_string_set_measure);
BENCHMARK(plain_c_table_get_measure);
BENCHMARK(plain_c_table_set_measure);
BENCHMARK(plain_c_table_chained_get_measure);
BENCHMARK(plain_c_table_chained_set_measure);
BENCHMARK(plain_c_c_function_measure);
BENCHMARK(plain_c_c_function_through_lua_in_c_measure);
BENCHMARK(plain_c_lua_function_in_c_measure);
BENCHMARK(plain_c_member_function_call_measure);
BENCHMARK(plain_c_userdata_variable_access_measure);
BENCHMARK(plain_c_userdata_variable_access_large_measure);
BENCHMARK(plain_c_userdata_variable_access_last_measure);
BENCHMARK(plain_c_multi_return_lua_measure);
BENCHMARK(plain_c_multi_return_measure);
BENCHMARK(plain_c_stateful_function_object_measure);
BENCHMARK(plain_c_base_derived_measure);
BENCHMARK(plain_c_return_userdata_measure);
BENCHMARK(plain_c_optional_failure_measure);
BENCHMARK(plain_c_optional_half_failure_measure);
BENCHMARK(plain_c_optional_success_measure);
BENCHMARK(plain_c_implicit_inheritance_measure);
