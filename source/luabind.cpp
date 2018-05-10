
#include <luabind/luabind.hpp>
#include <luabind/out_value_policy.hpp>

#include "lbs_lib.hpp"
#include "lbs_lua.hpp"
#include "benchmark.hpp"

void luabind_global_string_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "value = " + lbs::magic_value_string());
	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o = luabind::globals(L)["value"];
		o.push(L);
		int v = static_cast<int>(lua_tointeger(L, -1));
		lua_pop(L, -1);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_global_string_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "value = " + lbs::magic_value_string());
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		luabind::globals(L)["value"] = v;
	}
	luabind::object o = luabind::globals(L)["value"];
	o.push(L);
	double x = lua_tonumber(L, -1);
	lua_pop(L, -1);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_table_chained_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "ulahibe = { warble = { value = " + lbs::magic_value_string() + " } }");

	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o = luabind::globals(L)["ulahibe"]["warble"]["value"];
		o.push(L);
		double v = lua_tonumber(L, -1);
		lua_pop(L, -1);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_table_chained_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "ulahibe = { warble = { value = 0 } }");
	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		luabind::globals(L)["ulahibe"]["warble"]["value"] = v;
	}
	luabind::object o = luabind::globals(L)["ulahibe"]["warble"]["value"];
	o.push(L);
	double x = lua_tonumber(L, -1);
	lua_pop(L, -1);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_table_get_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "warble = { value = " + lbs::magic_value_string() + " }");

	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o = luabind::globals(L)["warble"]["value"];
		o.push(L);
		double v = lua_tonumber(L, -1);
		lua_pop(L, -1);
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_table_set_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "warble = { value = " + lbs::magic_value_string() + " }");

	double v = 0;
	for (auto _ : benchmark_state) {
		v += lbs::magic_value();
		luabind::globals(L)["warble"]["value"] = v;
	}
	luabind::object o = luabind::globals(L)["warble"]["value"];
	o.push(L);
	double x = lua_tonumber(L, -1);
	lua_pop(L, -1);
	lbs::expect(benchmark_state, x, v);
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
	lbs::expect(benchmark_state, v, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_c_function_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::def("f", lbs::basic_call)];

	lbs::lua_bench_do_or_die(L, lbs::c_function_check);

	std::string code = lbs::repeated_code(lbs::c_function_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_lua_function_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, "function f (i) return i end");

	luabind::object func = luabind::globals(L)["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = luabind::call_function<double>(func, lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_lua_function_through_c_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::def("f", lbs::basic_call)];
	luabind::object func = luabind::globals(L)["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = luabind::call_function<double>(func, lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_member_function_call_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic>("c")
					    .def(luabind::constructor<>())
					    .def_nonconst("set", &lbs::basic::set)
					    .def_const("get", &lbs::basic::get)];
	lbs::lua_bench_do_or_die(L, "b = c()");

	lbs::lua_bench_do_or_die(L, lbs::member_function_call_check);

	std::string code = lbs::repeated_code(lbs::member_function_call_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_userdata_variable_access_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic>("c")
					    .def(luabind::constructor<>())
					    .def_readwrite("var", &lbs::basic::var)
					    .def_readwrite("var0", &lbs::basic::var0)
					    .def_readwrite("var1", &lbs::basic::var1)
					    .def_readwrite("var2", &lbs::basic::var2)
					    .def_readwrite("var3", &lbs::basic::var3)
					    .def_readwrite("var4", &lbs::basic::var4)];
	
	lbs::lua_bench_do_or_die(L, "b = c()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_userdata_variable_access_large_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic_large>("cl")
					    .def(luabind::constructor<>())
					    .def_readwrite("var", &lbs::basic_large::var)
					    .def_readwrite("var0", &lbs::basic_large::var0)
					    .def_readwrite("var1", &lbs::basic_large::var1)
					    .def_readwrite("var2", &lbs::basic_large::var2)
					    .def_readwrite("var3", &lbs::basic_large::var3)
					    .def_readwrite("var4", &lbs::basic_large::var4)
					    .def_readwrite("var5", &lbs::basic_large::var5)
					    .def_readwrite("var6", &lbs::basic_large::var6)
					    .def_readwrite("var7", &lbs::basic_large::var7)
					    .def_readwrite("var8", &lbs::basic_large::var8)
					    .def_readwrite("var9", &lbs::basic_large::var9)
					    .def_readwrite("var10", &lbs::basic_large::var10)
					    .def_readwrite("var11", &lbs::basic_large::var11)
					    .def_readwrite("var12", &lbs::basic_large::var12)
					    .def_readwrite("var13", &lbs::basic_large::var13)
					    .def_readwrite("var14", &lbs::basic_large::var14)
					    .def_readwrite("var15", &lbs::basic_large::var15)
					    .def_readwrite("var16", &lbs::basic_large::var16)
					    .def_readwrite("var17", &lbs::basic_large::var17)
					    .def_readwrite("var18", &lbs::basic_large::var18)
					    .def_readwrite("var19", &lbs::basic_large::var19)
					    .def_readwrite("var20", &lbs::basic_large::var20)
					    .def_readwrite("var21", &lbs::basic_large::var21)
					    .def_readwrite("var22", &lbs::basic_large::var22)
					    .def_readwrite("var23", &lbs::basic_large::var23)
					    .def_readwrite("var24", &lbs::basic_large::var24)
					    .def_readwrite("var25", &lbs::basic_large::var25)
					    .def_readwrite("var26", &lbs::basic_large::var26)
					    .def_readwrite("var27", &lbs::basic_large::var27)
					    .def_readwrite("var28", &lbs::basic_large::var28)
					    .def_readwrite("var29", &lbs::basic_large::var29)
					    .def_readwrite("var30", &lbs::basic_large::var30)
					    .def_readwrite("var31", &lbs::basic_large::var31)
					    .def_readwrite("var32", &lbs::basic_large::var32)
					    .def_readwrite("var33", &lbs::basic_large::var33)
					    .def_readwrite("var34", &lbs::basic_large::var34)
					    .def_readwrite("var35", &lbs::basic_large::var35)
					    .def_readwrite("var36", &lbs::basic_large::var36)
					    .def_readwrite("var37", &lbs::basic_large::var37)
					    .def_readwrite("var38", &lbs::basic_large::var38)
					    .def_readwrite("var39", &lbs::basic_large::var39)
					    .def_readwrite("var40", &lbs::basic_large::var40)
					    .def_readwrite("var41", &lbs::basic_large::var41)
					    .def_readwrite("var42", &lbs::basic_large::var42)
					    .def_readwrite("var43", &lbs::basic_large::var43)
					    .def_readwrite("var44", &lbs::basic_large::var44)
					    .def_readwrite("var45", &lbs::basic_large::var45)
					    .def_readwrite("var46", &lbs::basic_large::var46)
					    .def_readwrite("var47", &lbs::basic_large::var47)
					    .def_readwrite("var48", &lbs::basic_large::var48)
					    .def_readwrite("var49", &lbs::basic_large::var49)];
	lbs::lua_bench_do_or_die(L, "b = cl()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_userdata_variable_access_last_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic_large>("cl")
					    .def(luabind::constructor<>())
					    .def_readwrite("var", &lbs::basic_large::var)
					    .def_readwrite("var0", &lbs::basic_large::var0)
					    .def_readwrite("var1", &lbs::basic_large::var1)
					    .def_readwrite("var2", &lbs::basic_large::var2)
					    .def_readwrite("var3", &lbs::basic_large::var3)
					    .def_readwrite("var4", &lbs::basic_large::var4)
					    .def_readwrite("var5", &lbs::basic_large::var5)
					    .def_readwrite("var6", &lbs::basic_large::var6)
					    .def_readwrite("var7", &lbs::basic_large::var7)
					    .def_readwrite("var8", &lbs::basic_large::var8)
					    .def_readwrite("var9", &lbs::basic_large::var9)
					    .def_readwrite("var10", &lbs::basic_large::var10)
					    .def_readwrite("var11", &lbs::basic_large::var11)
					    .def_readwrite("var12", &lbs::basic_large::var12)
					    .def_readwrite("var13", &lbs::basic_large::var13)
					    .def_readwrite("var14", &lbs::basic_large::var14)
					    .def_readwrite("var15", &lbs::basic_large::var15)
					    .def_readwrite("var16", &lbs::basic_large::var16)
					    .def_readwrite("var17", &lbs::basic_large::var17)
					    .def_readwrite("var18", &lbs::basic_large::var18)
					    .def_readwrite("var19", &lbs::basic_large::var19)
					    .def_readwrite("var20", &lbs::basic_large::var20)
					    .def_readwrite("var21", &lbs::basic_large::var21)
					    .def_readwrite("var22", &lbs::basic_large::var22)
					    .def_readwrite("var23", &lbs::basic_large::var23)
					    .def_readwrite("var24", &lbs::basic_large::var24)
					    .def_readwrite("var25", &lbs::basic_large::var25)
					    .def_readwrite("var26", &lbs::basic_large::var26)
					    .def_readwrite("var27", &lbs::basic_large::var27)
					    .def_readwrite("var28", &lbs::basic_large::var28)
					    .def_readwrite("var29", &lbs::basic_large::var29)
					    .def_readwrite("var30", &lbs::basic_large::var30)
					    .def_readwrite("var31", &lbs::basic_large::var31)
					    .def_readwrite("var32", &lbs::basic_large::var32)
					    .def_readwrite("var33", &lbs::basic_large::var33)
					    .def_readwrite("var34", &lbs::basic_large::var34)
					    .def_readwrite("var35", &lbs::basic_large::var35)
					    .def_readwrite("var36", &lbs::basic_large::var36)
					    .def_readwrite("var37", &lbs::basic_large::var37)
					    .def_readwrite("var38", &lbs::basic_large::var38)
					    .def_readwrite("var39", &lbs::basic_large::var39)
					    .def_readwrite("var40", &lbs::basic_large::var40)
					    .def_readwrite("var41", &lbs::basic_large::var41)
					    .def_readwrite("var42", &lbs::basic_large::var42)
					    .def_readwrite("var43", &lbs::basic_large::var43)
					    .def_readwrite("var44", &lbs::basic_large::var44)
					    .def_readwrite("var45", &lbs::basic_large::var45)
					    .def_readwrite("var46", &lbs::basic_large::var46)
					    .def_readwrite("var47", &lbs::basic_large::var47)
					    .def_readwrite("var48", &lbs::basic_large::var48)
					    .def_readwrite("var49", &lbs::basic_large::var49)];
	lbs::lua_bench_do_or_die(L, "b = cl()");

	lbs::lua_bench_do_or_die(L, lbs::userdata_variable_access_large_last_check);

	std::string code = lbs::repeated_code(lbs::userdata_variable_access_large_last_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_stateful_function_object_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic_stateful>("cs")
		.def(luabind::constructor<>())
		.def("__call", &lbs::basic_stateful::operator())];
	lbs::lua_bench_do_or_die(L, "f = cs()");

	luabind::object func = luabind::globals(L)["f"];
	double x = 0;
	for (auto _ : benchmark_state) {
		double v = luabind::call_function<double>(func, lbs::magic_value());
		x += v;
	}
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_multi_return_measure(benchmark::State& benchmark_state) {
	// Unsupported: requires you to register
	// every kind of tuple you want individually
	// In BetterTwitchTV terms: LUL
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::def("f", lbs::basic_multi_return),
		luabind::class_<std::tuple<double, double>>("std_tuple_double_double")
	];
	luabind::object func = luabind::globals(L)["f"];

	double x = 0;
	for (auto _ : benchmark_state) {
		// what's worse is this won't ACTUALLY return x, y = f() into lua
		// it just returns 1 opaque piece of trash...
		std::tuple<double, double> v = luabind::call_function<std::tuple<double, double>>(func, lbs::magic_value());
		x += std::get<0>(v);
		x += std::get<1>(v);
	}
}

void luabind_multi_return_lua_measure(benchmark::State& benchmark_state) {
	// Unsupported.
	// The irony.
	// This was supported in defunct, vanilla LuaBind,
	// but the new people actually removed the capability for multiple policies
	// and mandated that you only get 1 policy, ever.
	// E V O L V I N G B A CK W A R D S :D
	lbs::unsupported(benchmark_state);
	return;

	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	//luabind::module(L)[luabind::def("f", lbs::basic_multi_return_out, luabind::policy_list<luabind::pure_out_value<2, luabind::policy_list<luabind::pure_out_value<3>>>>())];

	lbs::lua_bench_do_or_die(L, lbs::lua_multi_return_check);

	std::string code = lbs::repeated_code(lbs::lua_multi_return_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_base_derived_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// You'd have to figure out the casting yourself and use the Lua API,
	// at which point it's not really an abstraction anymore, is it?
	lbs::unsupported(benchmark_state);
	return;
}

void luabind_return_userdata_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	luabind::module(L)[luabind::class_<lbs::basic>("lbs::basic")
					    .def(luabind::constructor<>())];

	luabind::module(L)[luabind::def("f", lbs::basic_return), luabind::def("h", lbs::basic_get_var)];

	lbs::lua_bench_do_or_die(L, lbs::return_userdata_check);

	std::string code = lbs::repeated_code(lbs::return_userdata_code);
	int code_index = lbs::lua_bench_load_up(L, code.c_str(), code.size());
	for (auto _ : benchmark_state) {
		lbs::lua_bench_preload_do_or_die(L, code_index);
	}
	lbs::lua_bench_unload(L, code_index);
}

void luabind_optional_success_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, lbs::optional_success_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o1 = luabind::globals(L)["warble"];
		if (o1) {
			luabind::object o2 = o1["value"];
			if (o2) {
				o2.push(L);
				double v = lua_tonumber(L, -1);
				lua_pop(L, -1);
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
	lbs::expect(benchmark_state, x, benchmark_state.iterations() * lbs::magic_value());
}

void luabind_optional_half_failure_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	lbs::lua_bench_do_or_die(L, lbs::optional_half_failure_precode);

	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o1 = luabind::globals(L)["warble"];
		if (o1) {
			luabind::object o2 = luabind::globals(L)["value"];
			if (o2) {
				o2.push(L);
				double v = lua_tonumber(L, -1);
				lua_pop(L, -1);
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

void luabind_optional_failure_measure(benchmark::State& benchmark_state) {
	auto lua = lbs::create_state(true);
	lua_State* L = lua.get();
	luabind::open(L);

	double x = 0;
	for (auto _ : benchmark_state) {
		luabind::object o1 = luabind::globals(L)["warble"];
		if (o1) {
			luabind::object o2 = luabind::globals(L)["value"];
			if (o2) {
				o2.push(L);
				double v = lua_tonumber(L, -1);
				lua_pop(L, -1);
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

void luabind_implicit_inheritance_measure(benchmark::State& benchmark_state) {
	// Unsupported
	// You'd have to figure out the casting yourself and use the Lua API,
	// at which point it's not really an abstraction anymore, is it?
	lbs::unsupported(benchmark_state);
	return;
}

BENCHMARK(luabind_global_string_get_measure);
BENCHMARK(luabind_global_string_set_measure);
BENCHMARK(luabind_table_get_measure);
BENCHMARK(luabind_table_set_measure);
BENCHMARK(luabind_table_chained_get_measure);
BENCHMARK(luabind_table_chained_set_measure);
BENCHMARK(luabind_c_function_measure);
BENCHMARK(luabind_lua_function_through_c_measure);
BENCHMARK(luabind_lua_function_measure);
BENCHMARK(luabind_member_function_call_measure);
BENCHMARK(luabind_userdata_variable_access_measure);
BENCHMARK(luabind_userdata_variable_access_large_measure);
BENCHMARK(luabind_userdata_variable_access_last_measure);
BENCHMARK(luabind_multi_return_lua_measure);
BENCHMARK(luabind_multi_return_measure);
BENCHMARK(luabind_stateful_function_object_measure);
BENCHMARK(luabind_base_derived_measure);
BENCHMARK(luabind_return_userdata_measure);
BENCHMARK(luabind_optional_failure_measure);
BENCHMARK(luabind_optional_half_failure_measure);
BENCHMARK(luabind_optional_success_measure);
BENCHMARK(luabind_implicit_inheritance_measure);
