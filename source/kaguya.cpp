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

#include <kaguya/kaguya.hpp>

#include "benchmark.hpp"
#include "lbs_lib.hpp"
#include "lbs_lua.hpp"

void kaguya_global_string_get_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["value"] = 3;
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_global_string_set_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += 3;
		lua["value"] = v;
	}
	double x = lua["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void kaguya_table_get_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["warble"] = kaguya::NewTable();
	lua["warble"]["value"] = 3;
	kaguya::LuaTable t = lua["warble"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_table_set_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["warble"] = kaguya::NewTable();
	kaguya::LuaTable t = lua["warble"];
	double v = 0;
	for (auto _ : benchmark_state) {
		v += 3;
		t["value"] = v;
	}
	double x = t["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void kaguya_table_chained_get_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["ulahibe"] = kaguya::NewTable();
	lua["ulahibe"]["warble"] = kaguya::NewTable();
	lua["ulahibe"]["warble"]["value"] = 3;
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"]["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_table_chained_set_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["ulahibe"] = kaguya::NewTable();
	lua["ulahibe"]["warble"] = kaguya::NewTable();
	lua["ulahibe"]["warble"]["value"] = 3;
	double v = 0;
	for (auto _ : benchmark_state) {
		v += 3;
		lua["ulahibe"]["warble"]["value"] = v;
	}
	double x = lua["ulahibe"]["warble"]["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * 3);
}

void kaguya_c_function_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua_State* L = lua.state();

	lua.setErrorHandler(lbs::kaguya_panic_throw);
	lua["f"].setFunction(lbs::basic_call);


	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void kaguya_lua_function_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua(R"(function f (i)
		return i;
	end)");
	kaguya::LuaFunction f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["f"].setFunction(lbs::basic_call);
	kaguya::LuaFunction f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_member_function_call_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua_State* L = lua.state();

	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["c"].setClass<lbs::basic>(kaguya::UserdataMetatable<lbs::basic>()
								.setConstructors<lbs::basic()>()
								.addFunction("get", &lbs::basic::get)
								.addFunction("set", &lbs::basic::set));
	lua("b = c.new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void kaguya_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Does not support member variable syntax:
	// turns it into a function, unfortunately
	//for (auto _ : benchmark_state) {
	//}
	lbs::unsupported(benchmark_state);
}

void kaguya_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Does not support member variable syntax:
	// turns it into a function, unfortunately
	//for (auto _ : benchmark_state) {
	//}
	lbs::unsupported(benchmark_state);
}

void kaguya_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Does not support member variable syntax:
	// turns it into a function, unfortunately
	//for (auto _ : benchmark_state) {
	//}
	lbs::unsupported(benchmark_state);
}

void kaguya_stateful_function_object_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["f"] = kaguya::function(lbs::basic_stateful());
	kaguya::LuaFunction f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(3);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 3);
}

void kaguya_multi_return_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["f"].setFunction(lbs::basic_multi_return);
	kaguya::LuaFunction f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double a, b;
		kaguya::tie(a, b) = f(3);
		x += a;
		x += b;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 9);
}

void kaguya_base_derived_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["cab"].setClass(
		kaguya::UserdataMetatable<lbs::complex_ab, kaguya::MultipleBase<lbs::complex_base_a, lbs::complex_base_b>>()
			.setConstructors<lbs::complex_ab()>()
			.addFunction("a_func", &lbs::complex_ab::a_func)
			.addFunction("b_func", &lbs::complex_ab::b_func)
			.addFunction("ab_func", &lbs::complex_ab::ab_func));
	lbs::complex_ab ab;
	// Set and verify correctness
	lua["b"] = std::ref(ab);
	{
		lbs::complex_base_a* va = lua["b"];
		lbs::complex_base_b* vb = lua["b"];
		if (va->a_func() != ab.a_func() || va->a != ab.a) {
			lbs::unsupported(benchmark_state, "unsupported: base class not found");
			return;
		}
		if (vb->b_func() != ab.b_func() || vb->b != ab.b) {
			lbs::unsupported(benchmark_state, "unsupported: base class not found");
			return;
		}
	}
	double x = 0;
	for (auto _ : benchmark_state) {
		lbs::complex_base_a* va = lua["b"];
		lbs::complex_base_b* vb = lua["b"];
		x += va->a_func();
		x += vb->b_func();
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 6);
}

void kaguya_return_userdata_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua_State* L = lua.state();
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	lua["f"].setFunction(lbs::basic_return);
	lua["h"].setFunction(lbs::basic_get);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void kaguya_optional_measure(benchmark::State& benchmark_state) {
	// Almost unsupported
	// Converting directly to `optional<T>` fails,
	// have to use value_or on the proxy
	kaguya::State lua;
	lua.setErrorHandler(lbs::kaguya_panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["warble"]["value"].value_or<double>(1);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void kaguya_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	kaguya::State lua;
	lua_State* L = lua.state();
	lua.setErrorHandler(lbs::kaguya_panic_throw);
	lua["ca"].setClass(
		kaguya::UserdataMetatable<lbs::complex_base_a>()
			.setConstructors<lbs::complex_base_a()>()
			.addFunction("a_func", &lbs::complex_base_a::a_func)
			.addFunction("a", &lbs::complex_base_a::a));

	lua["cb"].setClass(
		kaguya::UserdataMetatable<lbs::complex_base_b>()
			.setConstructors<lbs::complex_base_b()>()
			.addFunction("b_func", &lbs::complex_base_b::b_func)
			.addFunction("b", &lbs::complex_base_b::b));

	lua["cab"].setClass(
		kaguya::UserdataMetatable<lbs::complex_ab, kaguya::MultipleBase<lbs::complex_base_a, lbs::complex_base_b>>()
			.setConstructors<lbs::complex_ab()>()
			.addFunction("ab_func", &lbs::complex_ab::ab_func)
			.addFunction("ab", &lbs::complex_ab::ab));

	lua("b = cab.new()");

	lbs::lua_bench_do_or_die(L, lbs::implicit_inheritance_check);

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

BENCHMARK(kaguya_global_string_get_measure);
BENCHMARK(kaguya_global_string_set_measure);
BENCHMARK(kaguya_table_get_measure);
BENCHMARK(kaguya_table_set_measure);
BENCHMARK(kaguya_table_chained_get_measure);
BENCHMARK(kaguya_table_chained_set_measure);
BENCHMARK(kaguya_c_function_measure);
BENCHMARK(kaguya_c_through_lua_function_measure);
BENCHMARK(kaguya_lua_function_measure);
BENCHMARK(kaguya_member_function_call_measure);
BENCHMARK(kaguya_userdata_variable_access_measure);
BENCHMARK(kaguya_userdata_variable_access_large_measure);
BENCHMARK(kaguya_userdata_variable_access_last_measure);
BENCHMARK(kaguya_multi_return_measure);
BENCHMARK(kaguya_stateful_function_object_measure);
BENCHMARK(kaguya_base_derived_measure);
BENCHMARK(kaguya_base_derived_measure);
BENCHMARK(kaguya_return_userdata_measure);
BENCHMARK(kaguya_optional_measure);
BENCHMARK(kaguya_implicit_inheritance_measure);
