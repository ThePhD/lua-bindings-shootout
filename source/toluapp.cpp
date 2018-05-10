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

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

// generated file must be included after
// and we must modify API inludes
#include <tolua++.h>
#ifdef TOLUA_API
#undef TOLUA_API
#endif
#define TOLUA_API inline
#include "toluapp_lib.gen.hpp"
#undef TOLUA_API

void toluapp_global_string_get_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_global_string_set_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_table_chained_get_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_table_chained_set_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_table_get_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_table_set_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_c_function_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "f = basic_call");

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_lua_function_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_lua_function_through_c_measure(benchmark::State& benchmark_state) {
	// No table abstraction
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_member_function_call_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "b = c:new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "b = c:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// ** tolua warning: No support for operator (), ignoring.
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "b = cl:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// ** tolua warning: No support for operator (), ignoring.
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "b = cl:new()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_stateful_function_object_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// ** tolua warning: No support for operator (), ignoring.
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_multi_return_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// tolua does not support multiple returns that are not ALSO input
	// parameters...
	// kinda crappy tbh
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_return_userdata_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "f = basic_return");
	lbs::lua_bench_do_or_die(L, "h = basic_get_var");

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void toluapp_optional_success_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_optional_half_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_optional_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void toluapp_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	lua_atpanic(L, lbs::panic_throw);

	tolua_open(L);
	tolua_toluapp_lib_open(L);

	lbs::lua_bench_do_or_die(L, "b = cab:new()");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(toluapp_global_string_get_measure);
BENCHMARK(toluapp_global_string_set_measure);
BENCHMARK(toluapp_table_get_measure);
BENCHMARK(toluapp_table_set_measure);
BENCHMARK(toluapp_table_chained_get_measure);
BENCHMARK(toluapp_table_chained_set_measure);
BENCHMARK(toluapp_c_function_measure);
BENCHMARK(toluapp_lua_function_through_c_measure);
BENCHMARK(toluapp_lua_function_measure);
BENCHMARK(toluapp_member_function_call_measure);
BENCHMARK(toluapp_userdata_variable_access_measure);
BENCHMARK(toluapp_userdata_variable_access_large_measure);
BENCHMARK(toluapp_userdata_variable_access_last_measure);
BENCHMARK(toluapp_multi_return_measure);
BENCHMARK(toluapp_stateful_function_object_measure);
BENCHMARK(toluapp_base_derived_measure);
BENCHMARK(toluapp_return_userdata_measure);
BENCHMARK(toluapp_optional_success_measure);
BENCHMARK(toluapp_optional_half_failure_measure);
BENCHMARK(toluapp_optional_failure_measure);
BENCHMARK(toluapp_implicit_inheritance_measure);
