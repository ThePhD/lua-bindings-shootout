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
#include <lua.hpp>
#include "lua bench.hpp"
#include "basic.hpp"
#include "basic_lua.hpp"

LUAPP_USERDATA(basic, "basic");
LUAPP_USERDATA(complex_base_a, "complex_base_a");
LUAPP_USERDATA(complex_base_b, "complex_base_b");
LUAPP_USERDATA(complex_ab, "complex_ab");

lua::Retval setup(lua::Context& c) {
	c.mt<basic>() = lua::Table::records(c,
		"__index", lua::Table::records(c, "var", &basic::var, "get", &basic::get, "set", &basic::set));
	c.global["basic_new"] = static_cast<basic (*)()>([]() {
		return basic(); }
	return c.ret();
}

lua::Retval basic_multi_return_setup(lua::Context& c) {
	auto r = basic_multi_return(c.args[1].to<int>());
	return c.ret(std::get<0>(r), std::get<1>(r));
}

/*lua::Retval basic_stateful_setup(lua::Context& c) {
	auto upv = c.upvalues[2];
	basic_stateful& bs = upv.cast<basic_stateful>();
	auto r = bs(c.args[1].to<int>());
	return c.ret(r);
}*/

void toluapp_global_string_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("value", 24);
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["value"];
			x += v;
		}
		return x;
	}
}

void toluapp_global_string_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	for (auto _ : benchmark_state) {
		for (int i = 0; i < repetition; ++i) {
			L.global.set("value", 24);
		}
	}
}

void toluapp_chained_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", 24)));
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["ulahibe"]["warble"]["value"];
			v += x;
		}
		return x;
	}
}

void toluapp_chained_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("ulahibe", lua::Table::records(L, "warble", lua::Table::records(L, "value", 24)));
	for (auto _ : benchmark_state) {
		for (int i = 0; i < repetition; ++i) {
			L.global["ulahibe"]["warble"]["value"] = 24;
		}
	}
}

void toluapp_table_get_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("warble", lua::Table::records(L, "value", 24));
	lua::Table t = L.global["warble"];
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = t["value"];
			x += v;
		}
		return x;
	}
}

void toluapp_table_set_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("warble", lua::Table::records(L, "value", 24));
	lua::Table t = L.global["warble"];
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = t["value"];
			x += v;
		}
		return x;
	}
}

void toluapp_c_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_State* L = l.getRawState();
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context Lc(l.getRawState(), lua::Context::initializeExplicitly);
	Lc.global.set("f", basic_call);
	std::string code = repeated_code("f(i)");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void toluapp_lua_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	l.runString("function f (i) return i end");
	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["f"](i);
			x += v;
		}
		return x;
	}
}

void toluapp_c_through_lua_function_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", basic_call);
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["f"](i);
			x += v;
		}
		return x;
	}
}

void toluapp_member_function_call_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_State* L = l.getRawState();
	lua_atpanic(l.getRawState(), panic_throw);

	l.call(lua::mkcf<setup>);
	l.runString("b = basic_new()");
	std::string code = repeated_code("b:set(i) b:get()");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void toluapp_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	// Unsupported
	/*lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);
	l.call(lua::mkcf<setup>);
	l.runString("b = basic_new()");
	std::string code = repeated_code("b.var = i\nx = b.var");
	for (auto _ : benchmark_state ) {
		l.runString(code);
	}*/
}

void toluapp_stateful_function_object_measure(benchmark::State& benchmark_state) {
	// Unsupported
	/*lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);
	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global["f"] = L.closure(lua::mkcf<basic_stateful_setup>, basic_stateful());
	for (auto _ : benchmark_state ) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["f"](i);
			x += v;
		}
		return x;
	}*/
}

void toluapp_multi_return_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", lua::mkcf<basic_multi_return_setup>);
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			int v = L.global["f"](i);
			x += v;
		}
		return x;
	}
}

void toluapp_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
}

void toluapp_return_userdata_measure(benchmark::State& benchmark_state) {
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	L.global.set("f", basic_return);
	std::string code = repeated_code("b = f(i)");

	int code_index = lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lua_bench_preload_do_or_die(L, code_index);
	}
	lua_bench_unload(L, code_index);
}

void toluapp_optional_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// Crashes the API because it does not check all the way through
	lua::State l;
	lua_atpanic(l.getRawState(), panic_throw);

	lua::Context L(l.getRawState(), lua::Context::initializeExplicitly);
	for (auto _ : benchmark_state) {
		int x = 0;
		for (int i = 0; i < repetition; ++i) {
			if (L.global["warble"]["value"].is<int>()) {
				int v = L.global["warble"]["value"];
				x += v;
			}
			else {
				x += 1;
			}
		}
		return x;
	}
}

BENCHMARK(toluapp_global_string_get_measure);
BENCHMARK(toluapp_global_string_set_measure);
BENCHMARK(toluapp_table_get_measure);
BENCHMARK(toluapp_table_set_measure);
BENCHMARK(toluapp_table_chained_get_measure);
BENCHMARK(toluapp_table_chained_set_measure);
BENCHMARK(toluapp_c_function_measure);
BENCHMARK(toluapp_c_through_lua_function_measure);
BENCHMARK(toluapp_lua_function_measure);
BENCHMARK(toluapp_member_function_call_measure);
BENCHMARK(toluapp_userdata_variable_access_measure);
BENCHMARK(toluapp_userdata_variable_access_large_measure);
BENCHMARK(toluapp_userdata_variable_access_last_measure);
BENCHMARK(toluapp_multi_return_measure);
BENCHMARK(toluapp_stateful_function_object_measure);
BENCHMARK(toluapp_base_derived_measure);
BENCHMARK(toluapp_return_userdata_measure);
BENCHMARK(toluapp_optional_measure);
BENCHMARK(toluapp_implicit_inheritance_measure);
