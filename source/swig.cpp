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

#include "swig_lib.gen.hpp"

void swig_table_global_string_get_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_table_global_string_set_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_table_get_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_table_set_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_table_chained_get_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_table_chained_set_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_c_function_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "f = swig_lib.basic_call");

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_lua_function_in_c_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_c_function_through_lua_in_c_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_member_function_call_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "b = swig_lib.basic()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "b = swig_lib.basic()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// int64_t is not treated as an integral type
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "b = swig_lib.basic_large()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// int64_t is not treated as an integral type
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "b = swig_lib.basic_large()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_stateful_function_object_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_multi_return_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_multi_return_lua_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "f = swig_lib.basic_multi_return_out");

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_optional_success_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_optional_half_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_optional_failure_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void swig_return_userdata_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "f = swig_lib.basic_return");
	lbs::lua_bench_do_or_die(L, "h = swig_lib.basic_get_var");

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void swig_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// E.g., we're doing something wrong
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();


	luaopen_swig_lib(L);
	lbs::lua_bench_do_or_die(L, "b = swig_lib.complex_ab()");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(swig_table_global_string_get_measure);
BENCHMARK(swig_table_global_string_set_measure);
BENCHMARK(swig_table_get_measure);
BENCHMARK(swig_table_set_measure);
BENCHMARK(swig_table_chained_get_measure);
BENCHMARK(swig_table_chained_set_measure);
BENCHMARK(swig_c_function_measure);
BENCHMARK(swig_c_function_through_lua_in_c_measure);
BENCHMARK(swig_lua_function_in_c_measure);
BENCHMARK(swig_member_function_call_measure);
BENCHMARK(swig_userdata_variable_access_measure);
BENCHMARK(swig_userdata_variable_access_large_measure);
BENCHMARK(swig_userdata_variable_access_last_measure);
BENCHMARK(swig_multi_return_measure);
BENCHMARK(swig_multi_return_lua_measure);
BENCHMARK(swig_stateful_function_object_measure);
BENCHMARK(swig_base_derived_measure);
BENCHMARK(swig_return_userdata_measure);
BENCHMARK(swig_optional_success_measure);
BENCHMARK(swig_optional_half_failure_measure);
BENCHMARK(swig_optional_failure_measure);
BENCHMARK(swig_implicit_inheritance_measure);
