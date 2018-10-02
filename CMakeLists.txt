# # lua bindings shootout
# The MIT License (MIT)
# 
# Copyright � 2018 ThePhD
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.10.0)

project("lua bindings shootout" 
	VERSION 1.0.0 
	DESCRIPTION "A library for benchmarking the runtime of various different Lua bindings, since there are so many of them" 
	LANGUAGES C CXX
)

add_compile_options($<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>:/std:c++latest>)

# # CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

# # Options
# whether or not we should build as 32-bit
if (CMAKE_SIZEOF_VOID_P EQUAL 4 OR LB_SHOOTOUT_BUILD_32_BITS)
	set(LB_SHOOTOUT_BUILD_32_BITS ON CACHE BOOL "Enable a 32-bit build.")
	set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/lib")
	set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/bin")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CFG_INT_DIR}/lib")
else()
	set(LB_SHOOTOUT_BUILD_32_BITS OFF CACHE BOOL "Enable a 32-bit build.")
	set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/lib")
	set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/bin")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CFG_INT_DIR}/lib")
endif(CMAKE_SIZEOF_VOID_P EQUAL 4 OR LB_SHOOTOUT_BUILD_32_BITS)

# # Get Lua Build through find_package
# Wrap it in shared specifiers...
set(BUILD_SHARED_LIBS_SAVED ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS TRUE)
find_package(LuaDev 5.3.4 REQUIRED)
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_SAVED})
set(BUILD_SHARED_LIBS_SAVED "")

find_package(Threads REQUIRED)

# # Get all dependent packages
find_package(KaguyaDev REQUIRED)
find_package(SeleneDev REQUIRED)
find_package(LuwraDev REQUIRED)
find_package(LuaIntfDev REQUIRED)
find_package(ToLuappDev REQUIRED)
find_package(LuaApippDev REQUIRED)
find_package(LuaBridgeDev REQUIRED)
find_package(LuabindDev REQUIRED)
find_package(OOLuaDev REQUIRED)
find_package(LuaCppInterface REQUIRED)
find_package(Luawrapper REQUIRED)

# Subdirectory Google Benchmark, after setting all cache variables
set(BENCHMARK_ENABLE_EXCEPTIONS ON CACHE INTERNAL "Enable the use of exceptions in the benchmark library." FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "Enable testing of the benchmark library." FORCE)
set(BENCHMARK_ENABLE_LTO OFF CACHE INTERNAL "Enable link time optimisation of the benchmark library." FORCE)
set(BENCHMARK_USE_LIBCXX OFF CACHE INTERNAL "Build and test using libc++ as the standard library." FORCE)
set(BENCHMARK_BUILD_32_BITS ${LB_SHOOTOUT_BUILD_32_BITS} CACHE INTERNAL "Build a 32 bit version of the library." FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE INTERNAL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE INTERNAL "Allow the downloading and in-tree building of unmet dependencies" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "Enable building the unit tests which depend on gtest" FORCE)
# Google bnechmark must be built as a static library,
# it doesn't contain export definitions
set(BUILD_SHARED_LIBS_SAVED ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(vendor/benchmark)
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_SAVED})
set(BUILD_SHARED_LIBS_SAVED "")

add_subdirectory(vendor/sol3/sol3)

set(lua_bindings_shootout_sources 
	"source/benchmark.hpp"
	"source/lbs_lib.hpp"
	"source/lbs_lua.hpp"

	"source/luawrapper.cpp"
	"source/luacppinterface.cpp"

	"source/swig.cpp"
	"source/toluapp.cpp"
	"source/luabind.cpp"
	"source/lua-api-pp.cpp"
	"source/oolua.cpp"
	"source/luabridge.cpp"
	"source/lua-intf.cpp"
	"source/luwra.cpp"
	"source/plain_c.cpp"
	"source/selene.cpp"
	"source/kaguya.cpp"
	"source/old_sol.cpp"
	"source/sol2.cpp"
	"source/sol3.cpp"

	"source/lua_bindings_shootout.cpp"
)

set(LB_SHOOTOUT_LUA_REPETITIONS 50
	CACHE STRING "Number of times to re-run a block of Lua code in the benchmarks"
)

add_executable(lua_bindings_shootout ${lua_bindings_shootout_sources})
target_link_libraries(lua_bindings_shootout
	PRIVATE 
	# lua library
	${LUA_LIBRARIES}
	# binding libraries
	${LUACPPINTERFACE_LIBRARIES}
	${LUAWRAPPER_LIBRARIES}
	${TOLUAPP_LIBRARIES}
	${LUABIND_LIBRARIES}
	${LUAAPIPP_LIBRARIES}
	${LUABRIDGE_LIBRARIES}
	${KAGUYA_LIBRARIES}
	${SELENE_LIBRARIES}
	${LUWRA_LIBRARIES}
	${LUAINTF_LIBRARIES}
	${OOLUA_LIBRARIES}
	sol2::sol2
	# benchmarking library and utilities
	Threads::Threads
	benchmark
)
target_compile_definitions(lua_bindings_shootout
	PRIVATE
	_CRT_SECURE_NO_WARNINGS
	_SCL_SECURE_NO_WARNINGS
	SLB_EXTERNAL_LUA
	SLB_DYNAMIC_LIBRARY
	LUA_COMPAT_ALL
	LUA_COMPAT_52
	LUA_COMPAT_51
	LUA_COMPAT_APIINTCASTS
	"LUA_BINDINGS_SHOOTOUT_LUA_REPETITIONS=${LB_SHOOTOUT_LUA_REPETITIONS}"
)
target_include_directories(lua_bindings_shootout
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/vendor/sol2"
	"${CMAKE_CURRENT_SOURCE_DIR}/vendor/old_sol"
)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
	target_compile_options(lua_bindings_shootout
		PRIVATE -ftemplate-depth=2048
	)
endif()

set(LB_SHOOTOUT_REPETITIONS 150
	CACHE STRING "The number of times to re-rerun the benchmarks to gather additional data"
)
set(LB_SHOOTOUT_FORMAT json 
	CACHE STRING "The output format of the data. Must be json or csv")
string(TOLOWER ${LB_SHOOTOUT_FORMAT} LB_SHOOTOUT_FORMAT_LOWER)
set(LB_SHOOTOUT_FORMAT ${LB_SHOOTOUT_FORMAT_LOWER} 
	CACHE STRING "The output format of the data. Must be json or csv" FORCE)

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/benchmark_results")
set(LB_SHOOTOUT_OUTFILE "${CMAKE_SOURCE_DIR}/benchmark_results/lua_bindings_shootout.${LB_SHOOTOUT_FORMAT}")
set(LB_SHOOTOUT_GRAPH_OUTFILE "${CMAKE_SOURCE_DIR}/benchmark_results/")

add_custom_target(shootout
	COMMAND lua_bindings_shootout "--benchmark_out=${LB_SHOOTOUT_OUTFILE}" 
	"--benchmark_out_format=${LB_SHOOTOUT_FORMAT}" 
	"--benchmark_repetitions=${LB_SHOOTOUT_REPETITIONS}"
	COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/tools/generate_graphs.py" 
		"--input=${LB_SHOOTOUT_OUTFILE}"
		"--input_format=${LB_SHOOTOUT_FORMAT}"
		"--output_dir=${LB_SHOOTOUT_GRAPH_OUTFILE}"
		"--categories=${lb_shootout_categories}"
		"--scale_categories=${lb_shootout_scale_categories}"
		"--scale=${LB_SHOOTOUT_LUA_REPETITIONS}"
	DEPENDS lua_bindings_shootout
	BYPRODUCTS ${LB_SHOOTOUT_OUTFILE}
	COMMENT "Executing Benchmarks and outputting to '${LB_SHOOTOUT_OUTFILE}' then running graphs for '${LB_SHOOTOUT_GRAPH_OUTFILE}'"
)

set(lb_shootout_categories table_global_string_get_measure,table_global_string_set_measure,table_get_measure,table_set_measure,table_chained_get_measure,table_chained_set_measure,c_function_measure,c_function_through_lua_in_c_measure,lua_function_in_c_measure,member_function_call_measure,userdata_variable_access_measure,userdata_variable_access_large_measure,userdata_variable_access_last_measure,multi_return_lua_measure,multi_return_measure,stateful_function_object_measure,base_derived_measure,return_userdata_measure,optional_success_measure,optional_half_failure_measure,optional_failure_measure,implicit_inheritance_measure)
set(lb_shootout_scale_categories c_function_measure,member_function_call_measure,userdata_variable_access_measure,userdata_variable_access_large_measure,userdata_variable_access_last_measure,multi_return_lua_measure,return_userdata_measure,implicit_inheritance_measure)

add_custom_target(graphs
	COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/tools/generate_graphs.py" 
		"--input=${LB_SHOOTOUT_OUTFILE}"
		"--input_format=${LB_SHOOTOUT_FORMAT}"
		"--output_dir=${LB_SHOOTOUT_GRAPH_OUTFILE}"
		"--categories=${lb_shootout_categories}"
		"--scale_categories=${lb_shootout_scale_categories}"
		"--scale=${LB_SHOOTOUT_LUA_REPETITIONS}"
	DEPENDS lua_bindings_shootout shootout
	COMMENT "Generating graphs for '${LB_SHOOTOUT_OUTFILE}'"
)
