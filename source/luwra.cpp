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

#include <luwra.hpp>

#include "benchmark.hpp"
#include "lbs_lua.hpp"
#include "lbs_lib.hpp"

void luwra_global_string_get_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	lua["value"] = lbs::magic_value();

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_global_string_set_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua["value"] = v;
	}
	double x = lua["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_table_chained_get_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "ulahibe={warble={value = " + lbs::magic_value_string() + "}}";
	lua.runString(precode.c_str());

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"]["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_table_chained_set_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "ulahibe={warble={value = " + lbs::magic_value_string() + "}}";
	lua.runString(precode.c_str());

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

void luwra_table_get_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "warble={value = " + lbs::magic_value_string() + "}";
	lua.runString(precode.c_str());
	
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_table_set_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	std::string precode = "warble={value = " + lbs::magic_value_string() + "}";
	lua.runString(precode.c_str());

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		lua["warble"]["value"] = v;
	}
	double x = lua["warble"]["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_c_function_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	luaL_openlibs(L);
	lua_atpanic(L, lbs::panic_throw);

	lua["f"] = LUWRA_WRAP(lbs::basic_call);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luwra_lua_function_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(L, lbs::panic_throw);

	lua.runString(R"(function f (i) return i end)");
	// Unless we specifically get it like this,
	// it picks the wrong overload in VC++
	// I am too tired to fix this and honestly this bullshit shouldn't
	// be happening, who the fuck overloads on `const &&` ????
	luwra::Function<double> f = lua["f"].read<luwra::Function<double>>();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	lua["f"] = LUWRA_WRAP(lbs::basic_call);

	// Unless we specifically get it like this,
	// it picks the wrong overload in VC++
	// I am too tired to fix this and honestly this bullshit shouldn't
	// be happening, who the fuck overloads on `const &&` ????
	luwra::Function<double> f = lua["f"].read<luwra::Function<double>>();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_member_function_call_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	luaL_openlibs(L);
	lua_atpanic(lua, lbs::panic_throw);

	lua.registerUserType<lbs::basic()>(
		"basic",
		{ LUWRA_MEMBER(lbs::basic, get), LUWRA_MEMBER(lbs::basic, set) });
	lua.runString("b = basic()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luwra_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
	/*
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);
	lua.registerMember("var", &lbs::basic::var);
	lua.writeVariable("b", lbs::basic());
	std::string code = lbs::repeated_code("b.var = i\nx = b.var");
	for (auto _ : benchmark_state) {
		lua.runString(code.c_str());
	}
	*/
}

void luwra_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luwra_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void luwra_stateful_function_object_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	luaL_openlibs(L);
	lua_atpanic(lua, lbs::panic_throw);

	// Have to register as a usertype to get it.
	lua.registerUserType<lbs::basic_stateful()>(
		"cs",
		{},
		{ { "__call", LUWRA_WRAP_MEMBER(lbs::basic_stateful, operator()) } });
	lua.set("f", lbs::basic_stateful());
	// Unless we specifically get it like this,
	// it picks the wrong overload in VC++
	// I am too tired to fix this and honestly this bullshit shouldn't
	// be happening, who the fuck overloads on `const &&` ????
	luwra::Function<int> f = lua["f"].read<luwra::Function<int>>();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luwra_multi_return_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// std::tuple returns still not supported...
	// G R E A T

	lbs::unsupported(benchmark_state);
	return;

	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	luaL_openlibs(L);
	lua_atpanic(lua, lbs::panic_throw);

	lua.set("f", LUWRA_WRAP(lbs::basic_multi_return));
	// Unless we specifically get it like this,
	// it picks the wrong overload in VC++
	// I am too tired to fix this and honestly this bullshit shouldn't
	// be happening, who the fuck overloads on `const &&` ????
	luwra::Function<std::tuple<double, double>> f = lua["f"].read<luwra::Function<std::tuple<double, double>>>();
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f(lbs::magic_value());
		x += static_cast<double>(std::get<0>(v));
		x += static_cast<double>(std::get<1>(v));
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void luwra_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported:
	// Luwra does not internally handle base classes
	// have to do it yourself

	lbs::unsupported(benchmark_state);
	return;

	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	lua.registerUserType<lbs::complex_ab>();
	lbs::complex_ab ab;
	// Set and verify correctness
	lua.set("b", &ab);
	{
		lbs::complex_base_a& va = lua["b"].read<lbs::complex_base_a>();
		lbs::complex_base_b& vb = lua["b"].read<lbs::complex_base_b>();
		if (!lbs::verify_base_correctness(va, vb, ab)) {
			lbs::unsupported(benchmark_state);
			return;
		}
	}
	double x = 0;
	for (auto _ : benchmark_state) {
		lbs::complex_base_a& va = lua["b"].read<lbs::complex_base_a>();
		lbs::complex_base_b& vb = lua["b"].read<lbs::complex_base_b>();
		x += va.a_func();
		x += vb.b_func();
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 2));
}

void luwra_return_userdata_measure(benchmark::State& benchmark_state) {
	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	luaL_openlibs(L);
	lua_atpanic(lua, lbs::panic_throw);

	lua.set("f", LUWRA_WRAP(lbs::basic_return));
	lua.set("h", LUWRA_WRAP(lbs::basic_get));

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luwra_optional_measure(benchmark::State& benchmark_state) {
	// UNSUPPORTED:
	// Luwra does not let you check if something exists with its own abstractions,
	// therefore will call panic function

	lbs::unsupported(benchmark_state);
	return;

	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void luwra_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported?
	// Should contact author about whether or not this would work

	lbs::unsupported(benchmark_state);
	return;

	luwra::StateWrapper lua;
	lua_State* L = lua.state.get();
	lua_atpanic(lua, lbs::panic_throw);
}

BENCHMARK(luwra_global_string_get_measure);
BENCHMARK(luwra_global_string_set_measure);
BENCHMARK(luwra_table_get_measure);
BENCHMARK(luwra_table_set_measure);
BENCHMARK(luwra_table_chained_get_measure);
BENCHMARK(luwra_table_chained_set_measure);
BENCHMARK(luwra_c_function_measure);
BENCHMARK(luwra_c_through_lua_function_measure);
BENCHMARK(luwra_lua_function_measure);
BENCHMARK(luwra_member_function_call_measure);
BENCHMARK(luwra_userdata_variable_access_measure);
BENCHMARK(luwra_userdata_variable_access_large_measure);
BENCHMARK(luwra_userdata_variable_access_last_measure);
BENCHMARK(luwra_multi_return_measure);
BENCHMARK(luwra_stateful_function_object_measure);
BENCHMARK(luwra_base_derived_measure);
BENCHMARK(luwra_return_userdata_measure);
BENCHMARK(luwra_optional_measure);
BENCHMARK(luwra_implicit_inheritance_measure);
