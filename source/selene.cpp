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

#include "lbs_lua.hpp"
#include "lbs_lib.hpp"
#include "benchmark.hpp"

#include <selene.h>

void selene_global_string_get_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);
	lua["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_global_string_set_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);
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

void selene_table_chained_get_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["ulahibe"]["warble"]["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = lua["ulahibe"]["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_table_chained_set_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

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

void selene_table_get_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	auto t = lua["warble"];
	t["value"] = lbs::magic_value();
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_table_set_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	auto t = lua["value"];
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		t["warble"] = v;
	}
	double x = t["warble"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void selene_c_function_measure(benchmark::State& benchmark_state) {
	sel::State lua{ true };
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["f"] = lbs::basic_call;
	std::string code = lbs::repeated_code("f(i)");
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

void selene_lua_function_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua(R"(function f (i)
			return i;
		end)");
	sel::function<int(int)> f = lua["f"];

	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["f"] = lbs::basic_call;
	sel::function<int(int)> f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_member_function_call_measure(benchmark::State& benchmark_state) {
	sel::State lua{ true };
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["c"].SetClass<lbs::basic>(
		"get", &lbs::basic::get,
		"set", &lbs::basic::set);
	lua("b = c.new()");

	lua(lbs::member_function_call_check.c_str());

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

void selene_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// just converts everything to functions
	lbs::unsupported(benchmark_state);
	return;

	sel::State lua{ true };
	lua["c"].SetClass<lbs::basic>(
		"var", &lbs::basic::var,
		"set", &lbs::basic::set,
		"get", &lbs::basic::get);
	lua("b = c.new()");
	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

void selene_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// just converts everything to functions
	lbs::unsupported(benchmark_state);
	return;
}

void selene_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// just converts everything to functions

	lbs::unsupported(benchmark_state);
	return;
}

void selene_stateful_function_object_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["f"] = lbs::basic_stateful();
	sel::function<double(double)> f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = f(lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_lua_multi_return_measure(benchmark::State& benchmark_state) {
	sel::State lua{ true };
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["f"] = lbs::basic_multi_return;

	lua(lbs::lua_multi_return_check.c_str());

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

void selene_multi_return_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["f"] = lbs::basic_multi_return;
	sel::function<std::tuple<double, double>(double)> f = lua["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		std::tuple<double, double> v = f(lbs::magic_value());
		x += std::get<0>(v);
		x += std::get<1>(v);
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void selene_base_derived_measure(benchmark::State& benchmark_state) {
	// Explicitly unsupported,
	// as stated by the Readme for inheritance
	lbs::unsupported(benchmark_state);
	return;
}

void selene_optional_success_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua(lbs::optional_success_precode.c_str());

	double x = 0;
	for (auto _ : benchmark_state) {
		auto cache = lua["warble"]["value"];
		if (cache.exists()) {
			double v = cache;
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void selene_optional_half_failure_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua(lbs::optional_half_failure_precode.c_str());

	double x = 0;
	for (auto _ : benchmark_state) {
		auto cache = lua["warble"]["value"];
		if (cache.exists()) {
			double v = cache;
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void selene_optional_failure_measure(benchmark::State& benchmark_state) {
	sel::State lua;
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	double x = 0;
	for (auto _ : benchmark_state) {
		auto cache = lua["warble"]["value"];
		if (cache.exists()) {
			double v = cache;
			x += v;
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void selene_return_userdata_measure(benchmark::State& benchmark_state) {
	sel::State lua{ true };
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["c"].SetClass<lbs::basic>();
	lua["f"] = lbs::basic_return;
	lua["h"] = lbs::basic_get_var;

	lua(lbs::return_userdata_check.c_str());

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

void selene_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// UNSUPPORTED
	// The below code doesn't work and calls panic
	lbs::unsupported(benchmark_state);
	return;

	sel::State lua{ true };
	lua.HandleExceptionsWith(lbs::selene_panic_throw);

	lua["ca"].SetClass<lbs::complex_base_a>(
		"a", &lbs::complex_base_a::a,
		"a_func", &lbs::complex_base_a::a_func);
	lua["cb"].SetClass<lbs::complex_base_b>(
		"b", &lbs::complex_base_b::b,
		"b_func", &lbs::complex_base_b::b_func);
	lua["cab"].SetClass<lbs::complex_ab>(
		"ab", &lbs::complex_ab::ab,
		"ab_func", &lbs::complex_ab::ab_func);

	lua("b = cab.new()");

	lua(lbs::implicit_inheritance_check.c_str());

	std::string code = lbs::repeated_code(lbs::implicit_inheritance_code);
	for (auto _ : benchmark_state) {
		lua(code.c_str());
	}
}

BENCHMARK(selene_global_string_get_measure);
BENCHMARK(selene_global_string_set_measure);
BENCHMARK(selene_table_get_measure);
BENCHMARK(selene_table_set_measure);
BENCHMARK(selene_table_chained_get_measure);
BENCHMARK(selene_table_chained_set_measure);
BENCHMARK(selene_c_function_measure);
BENCHMARK(selene_c_through_lua_function_measure);
BENCHMARK(selene_lua_function_measure);
BENCHMARK(selene_member_function_call_measure);
BENCHMARK(selene_userdata_variable_access_measure);
BENCHMARK(selene_userdata_variable_access_large_measure);
BENCHMARK(selene_userdata_variable_access_last_measure);
BENCHMARK(selene_lua_multi_return_measure);
BENCHMARK(selene_multi_return_measure);
BENCHMARK(selene_stateful_function_object_measure);
BENCHMARK(selene_base_derived_measure);
BENCHMARK(selene_return_userdata_measure);
BENCHMARK(selene_optional_success_measure);
BENCHMARK(selene_optional_half_failure_measure);
BENCHMARK(selene_optional_failure_measure);
BENCHMARK(selene_implicit_inheritance_measure);
