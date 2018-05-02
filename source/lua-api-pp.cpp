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

#include <luapp/lua.hpp>

#include "lbs_lib.hpp"
#include "lbs_lua.hpp"
#include "benchmark.hpp"

LUAPP_USERDATA(lbs::basic, "c");
LUAPP_USERDATA(lbs::basic_large, "cl");
LUAPP_USERDATA(lbs::complex_base_a, "ca");
LUAPP_USERDATA(lbs::complex_base_b, "cb");
LUAPP_USERDATA(lbs::complex_ab, "cab");

lua::Retval basic_setup(lua::Context& c) {
	c.mt<lbs::basic>() = lua::Table::records(c,
		"__index", lua::Table::records(c, "var", &lbs::basic::var, "get", &lbs::basic::get, "set", &lbs::basic::set));
	c.global["basic_new"] = static_cast<lbs::basic(*)()>([]() {
		return lbs::basic();
	});
	return c.ret();
}

lua::Retval basic_multi_return_setup(lua::Context& c) {
	auto r = lbs::basic_multi_return(c.args[0].to<double>());
	return c.ret(std::get<0>(r), std::get<1>(r));
}

lua::Retval basic_return_setup(lua::Context& c) {
	lbs::basic r = lbs::basic_return(c.args[0].to<double>());
	return c.ret(std::move(r));
}

lua::Retval basic_get_setup(lua::Context& c) {
	double r = lbs::basic_get(c.args[0].to<lbs::basic>());
	return c.ret(r);
}

/* 
// unsupported: Linker errors?!
lua::Retval basic_stateful_setup(lua::Context& c) {
	auto upv = c.upvalues[2];
	lbs::basic_stateful& bs = upv.cast<lbs::basic_stateful>();
	auto r = bs(c.args[1].to<double>());
	return c.ret(r);
}
*/

void lua_api_pp_global_string_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("value", lbs::magic_value());
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = L.global["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_global_string_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		L.global.set("value", v);
	}
	double x = L.global["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_table_chained_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", lbs::magic_value())));
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = L.global["ulahibe"]["warble"]["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_table_chained_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", lbs::magic_value())));
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		L.global["ulahibe"]["warble"]["value"] = v;
	}
	double x = L.global["ulahibe"]["warble"]["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_table_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("warble", lua::Table::records(L, "value", lbs::magic_value()));
	lua::Table t = L.global["warble"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = t["value"];
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_table_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("warble", lua::Table::records(L, "value", lbs::magic_value()));
	lua::Table t = L.global["warble"];
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		t["value"] = v;
	}
	double x = t["value"];
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_c_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_State* L = l.getRawState();
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context Lc(l.getRawState(), lua::Context::initializeExplicitly);
	Lc.global.set("f", lbs::basic_call);

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_api_pp_lua_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	l.runString("function f (i) return i end");
	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = L.global["f"](lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", lbs::basic_call);
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = L.global["f"](lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void lua_api_pp_member_function_call_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_State* L = l.getRawState();
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	l.call(lua::mkcf<basic_setup>);
	l.runString("b = basic_new()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_api_pp_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
	/*lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);
	l.call(lua::mkcf<setup>);
	l.runString("b = basic_new()");
	std::string code = lbs::repeated_code("b.var = i\nx = b.var");
	for (auto _ : benchmark_state ) {
	l.runString(code);
	}*/
}

void lua_api_pp_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void lua_api_pp_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void lua_api_pp_stateful_function_object_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// Cannot modify __call directly, it seems??
	// cannot set arbitrary upvalues either...
	// L.wrap does not handle it...
	lbs::unsupported(benchmark_state);
	return;
	
	/*lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);
	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global["f"] = L.wrap(lbs::basic_stateful());
	double x = 0;
	for (auto _ : benchmark_state ) {
		double v = L.global["f"](lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	*/
}

void lua_api_pp_multi_return_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", lua::mkcf<basic_multi_return_setup>);
	double x = 0;
	for (auto _ : benchmark_state) {
		lua::Valset results = L.global["f"](lbs::magic_value());
		double v = results[0];
		double w = results[1];
		x += v;
		x += w;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * (lbs::magic_value() * 3));
}

void lua_api_pp_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}

void lua_api_pp_return_userdata_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", lua::mkcf<basic_return_setup>);
	L.global.set("h", lua::mkcf<basic_get_setup>);

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void lua_api_pp_optional_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), lbs::panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);

	double x = 0;
	for (auto _ : benchmark_state) {
		if (L.global["warble"].type() == lua::ValueType::Table) {
			if (L.global["warble"]["value"].is<double>()) {
				double v = L.global["warble"]["value"];
				x += v;
			}
			else {
				x += 1;
			}
		}
		else {
			x += 1;
		}
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * 1);
}

void lua_api_pp_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported
	lbs::unsupported(benchmark_state);
	return;
}


BENCHMARK(lua_api_pp_global_string_get_measure);
BENCHMARK(lua_api_pp_global_string_set_measure);
BENCHMARK(lua_api_pp_table_get_measure);
BENCHMARK(lua_api_pp_table_set_measure);
BENCHMARK(lua_api_pp_table_chained_get_measure);
BENCHMARK(lua_api_pp_table_chained_set_measure);
BENCHMARK(lua_api_pp_c_function_measure);
BENCHMARK(lua_api_pp_c_through_lua_function_measure);
BENCHMARK(lua_api_pp_lua_function_measure);
BENCHMARK(lua_api_pp_member_function_call_measure);
BENCHMARK(lua_api_pp_userdata_variable_access_measure);
BENCHMARK(lua_api_pp_userdata_variable_access_large_measure);
BENCHMARK(lua_api_pp_userdata_variable_access_last_measure);
BENCHMARK(lua_api_pp_multi_return_measure);
BENCHMARK(lua_api_pp_stateful_function_object_measure);
BENCHMARK(lua_api_pp_base_derived_measure);
BENCHMARK(lua_api_pp_return_userdata_measure);
BENCHMARK(lua_api_pp_optional_measure);
BENCHMARK(lua_api_pp_implicit_inheritance_measure);
