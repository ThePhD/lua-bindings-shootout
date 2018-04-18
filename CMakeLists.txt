# # benchmark lua binding
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

cmake_minimum_required(3.10.0)

project(benchmark_lua_binding VERSION 1.0.0 PROJECT_DESCRIPTION "A library for benchmarking the runtime of various different Lua bindings, since there are so many of them")

# # Options
# whether or not we should build as 32-bit
if (CMAKE_SIZEOF_VOID_P EQ 4)
	set(BENCHMARK_LUA_BINDING_BUILD_32_BITS ON CACHE BOOL "Enable a 32-bit build.")
else()
	set(BENCHMARK_LUA_BINDING_BUILD_32_BITS OFF CACHE BOOL "Enable a 32-bit build.")
endif(CMAKE_SIZEOF_VOID_P EQ 4)

# Subdirectory Google Benchmark, after setting all cache variables
set(BENCHMARK_ENABLE_EXCEPTIONS ON CACHE INTERNAL "Enable the use of exceptions in the benchmark library." FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "Enable testing of the benchmark library." FORCE)
set(BENCHMARK_ENABLE_LTO OFF CACHE INTERNAL "Enable link time optimisation of the benchmark library." FORCE)
set(BENCHMARK_USE_LIBCXX OFF CACHE INTERNAL "Build and test using libc++ as the standard library." FORCE)
set(BENCHMARK_BUILD_32_BITS ${BENCHMARK_LUA_BINDING_BUILD_32_BITS} CACHE INTERNAL "Build a 32 bit version of the library." FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE INTERNAL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE INTERNAL "Allow the downloading and in-tree building of unmet dependencies" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "Enable building the unit tests which depend on gtest" FORCE)
add_subdirectory(vendor/benchmark)

# Get Lua Build through FindLua
find_package(LuaBuild 5.3.4 REQUIRED)

# # Visualization Targets
