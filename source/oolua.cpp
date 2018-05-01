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

#include <oolua.h>
#include <oolua_dsl.h>
#include <oolua_dsl_export.h>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

namespace OOLUA {
	using basic = lbs::basic;
	using basic_large = lbs::basic_large;
	using basic_stateful = lbs::basic_stateful;
	using complex_base_a = lbs::complex_base_a;
	using complex_base_b = lbs::complex_base_b;
	using complex_ab = lbs::complex_ab;
} // namespace OOLUA

OOLUA_PROXY(basic)
OOLUA_MGET_MSET(var)
OOLUA_MFUNC_CONST(get)
OOLUA_MFUNC(set)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS_CONST(basic, get)
OOLUA_EXPORT_FUNCTIONS(basic, set)

OOLUA_PROXY(basic_stateful)
//OOLUA_MEM_FUNC_RENAME("__call", double, operator(), double)
OOLUA_PROXY_END

//OOLUA_EXPORT_FUNCTIONS(basic_stateful, operator())
OOLUA_EXPORT_FUNCTIONS(basic_stateful)
OOLUA_EXPORT_FUNCTIONS_CONST(basic_stateful)

OOLUA_PROXY(complex_base_a)
OOLUA_MGET_MSET(a)
OOLUA_MFUNC_CONST(a_func)
OOLUA_PROXY_END

OOLUA_PROXY(complex_base_b)
OOLUA_MGET_MSET(b)
OOLUA_MFUNC_CONST(b_func)
OOLUA_PROXY_END

OOLUA_PROXY(complex_ab, complex_base_a, complex_base_b)
OOLUA_MGET_MSET(ab)
OOLUA_MFUNC_CONST(ab_func)
OOLUA_PROXY_END

OOLUA_EXPORT_FUNCTIONS(complex_base_a)
OOLUA_EXPORT_FUNCTIONS(complex_base_b)
OOLUA_EXPORT_FUNCTIONS(complex_ab)
OOLUA_EXPORT_FUNCTIONS_CONST(complex_base_a, a_func)
OOLUA_EXPORT_FUNCTIONS_CONST(complex_base_b, b_func)
OOLUA_EXPORT_FUNCTIONS_CONST(complex_ab, ab_func)

OOLUA_CFUNC(lbs::basic_call, oo_basic_call)
OOLUA_CFUNC(lbs::basic_get, oo_basic_get)
int oo_basic_multi_return(lua_State* vm) {
	using namespace OOLUA;
	OOLUA_C_FUNCTION(void, lbs::basic_multi_return_out, double, in_out_p<double&>, in_out_p<double&>)
}
OOLUA_CFUNC(lbs::basic_return, oo_basic_return)

static const double oolua_value = 3;
static const std::string oolua_f = "f";
static const std::string oolua_h = "h";

void oolua_global_string_get_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);
	set_global(vm, "value", oolua_value);
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = 0;
		get_global(vm, "value", v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_global_string_set_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	set_global(vm, "value", oolua_value);
	double v = 0;
	for (auto _ : benchmark_state) {
		v += oolua_value;
		set_global(vm, "value", v);
	}
	double x = 0;
	get_global(vm, "value", x);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * oolua_value);
}

void oolua_table_chained_get_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	Table tu = new_table(vm);
	set_global(vm, "ulahibe", tu);
	Table tw = new_table(vm);
	tu.set("warble", tw);
	tw.set("value", oolua_value);

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = 0;
		Table tw;
		Table tu;
		get_global(vm, "ulahibe", tu);
		tu.at("warble", tw);
		tw.at("value", v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_table_chained_set_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	Table tu = new_table(vm);
	set_global(vm, "ulahibe", tu);
	Table tw = new_table(vm);
	tu.set("warble", tw);
	tw.set("value", 24);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += oolua_value;
		Table tw;
		Table tu;
		get_global(vm, "ulahibe", tu);
		tu.at("warble", tw);
		tw.set("value", v);
	}
	double x = 0;
	tw.at("value", x);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * oolua_value);
}

void oolua_table_get_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	Table tu = new_table(vm);
	set_global(vm, "warble", tu);
	Table tw;
	get_global(vm, "warble", tw);
	tw.set("value", oolua_value);

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = 0;
		tw.at("value", v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_table_set_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	Table tu = new_table(vm);
	set_global(vm, "warble", tu);
	Table tw;
	get_global(vm, "warble", tw);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += oolua_value;
		tw.set("value", v);
	}
	double x = 0;
	tw.at("value", x);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * oolua_value);
}

void oolua_c_function_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_State* L = vm;
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	set_global(vm, oolua_f.c_str(), oo_basic_call);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void oolua_lua_function_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	vm.run_chunk(R"(function f (i)
			return i;
		end)");
	Lua_function f(vm);
	double x = 0;
	for (auto _ : benchmark_state) {
		bool success = f(oolua_f, oolua_value);
		double v = 0;
		pull(vm, v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	set_global(vm, oolua_f.c_str(), oo_basic_call);
	Lua_function f(vm);
	double x = 0;
	for (auto _ : benchmark_state) {
		bool success = f(oolua_f, oolua_value);
		double v = 0;
		pull(vm, v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_member_function_call_measure(benchmark::State& benchmark_state) {
	// Is not actually unsupported,
	// but the documentation website is now defunct
	// making it impossible to figure out WTF to do
	//lbs::unsupported(benchmark_state);
	//return;

	using namespace OOLUA;
	Script vm;
	lua_State* L = vm;
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	vm.register_class<lbs::basic>();
	vm.run_chunk("b = basic.new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void oolua_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;
	// Actually unsupported
	// Turns it into member functions: illegal
	/*
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);
	
	vm.register_class<basic>();
	vm.run_chunk("b = basic.new()");
	std::string code = lbs::repeated_code("b.var = i\nx = b.var");
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
	*/
}

void oolua_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;
	// Actually unsupported
	// Turns it into member functions: illegal
	/*
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);
	
	vm.register_class<basic>();
	vm.run_chunk("b = basic.new()");
	std::string code = lbs::repeated_code("b.var = i\nx = b.var");
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
	*/
}

void oolua_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;
	// Actually unsupported
	// Turns it into member functions: illegal
	/*
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);
	
	vm.register_class<basic>();
	vm.run_chunk("b = basic.new()");
	std::string code = lbs::repeated_code("b.var = i\nx = b.var");
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
	*/
}

void oolua_stateful_function_object_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;
	// Unsupported?
	// Cannot seem to register a class with operator()
	// registered on it quite yet... might have to ask
	// library dev?
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	vm.register_class<lbs::basic_stateful>();
	vm.run_chunk("f = basic_stateful.new()");

	Lua_function f(vm);
	double x = 0;
	for (auto _ : benchmark_state) {
		// fails here: cannot bind an
		// operator() to the "__mul" methods?
		bool success = f(oolua_f, oolua_value);
		double v;
		pull(vm, v);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * oolua_value);
}

void oolua_multi_return_measure(benchmark::State& benchmark_state) {
	using namespace OOLUA;
	Script vm;
	lua_atpanic(vm, lbs::panic_throw);

	set_global(vm, oolua_f.c_str(), oo_basic_multi_return);
	Lua_function f(vm);
	double x = 0;
	for (auto _ : benchmark_state) {
		bool success = f(oolua_f, oolua_value);
		double v = 0, w = 0;
		pull(vm, v);
		pull(vm, w);
		x += v;
		x += w;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (oolua_value * 3));
}

void oolua_base_derived_measure(benchmark::State& benchmark_state) {
	lbs::unsupported(benchmark_state);
	return;

	// Unsupported?
	// Definitely unsupported: would have to get derived first, and then grab the base
	// Note that OOLua has mechanisms for this,
	// but it's only available internally to its userdata/usertype implementation
	// which sucks for us =/
}

void oolua_return_userdata_measure(benchmark::State& benchmark_state) {
	// Caveat: must register class into VM to use
	using namespace OOLUA;
	Script vm;
	lua_State* L = vm;
	luaL_openlibs(L);
	lua_atpanic(vm, lbs::panic_throw);


	vm.register_class<lbs::basic>();
	set_global(vm, oolua_f.c_str(), oo_basic_return);
	set_global(vm, oolua_h.c_str(), oo_basic_get);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void oolua_optional_measure(benchmark::State& benchmark_state) {
	// Unsupported?
	lbs::unsupported(benchmark_state);
	return;
}

void oolua_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported?
	// Weird linker errors...
	//lbs::unsupported(benchmark_state);
	//return;

	using namespace OOLUA;
	Script vm;
	lua_State* L = vm;
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	vm.register_class<lbs::complex_base_a>();
	vm.register_class<lbs::complex_base_b>();
	vm.register_class<lbs::complex_ab>();
	vm.run_chunk("b = complex_ab.new()");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(oolua_global_string_get_measure);
BENCHMARK(oolua_global_string_set_measure);
BENCHMARK(oolua_table_get_measure);
BENCHMARK(oolua_table_set_measure);
BENCHMARK(oolua_table_chained_get_measure);
BENCHMARK(oolua_table_chained_set_measure);
BENCHMARK(oolua_c_function_measure);
BENCHMARK(oolua_c_through_lua_function_measure);
BENCHMARK(oolua_lua_function_measure);
BENCHMARK(oolua_member_function_call_measure);
BENCHMARK(oolua_userdata_variable_access_measure);
BENCHMARK(oolua_userdata_variable_access_large_measure);
BENCHMARK(oolua_userdata_variable_access_last_measure);
BENCHMARK(oolua_multi_return_measure);
BENCHMARK(oolua_stateful_function_object_measure);
BENCHMARK(oolua_base_derived_measure);
BENCHMARK(oolua_return_userdata_measure);
BENCHMARK(oolua_optional_measure);
BENCHMARK(oolua_implicit_inheritance_measure);
