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

# # Standard CMake Libraries
include(ExternalProject)
include(FindPackageHandleStandardArgs)
include(Common/Core)

# # Base variables
set(luaapipp_version v2015-02-12-3)

# # Useful locations
set(luaapipp_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/luaapipp_${luaapipp_version}")
set(luaapipp_include_dirs "${luaapipp_dev_toplevel}/")

# # LuaApipp library sources
file(GLOB_RECURSE luaapipp_sources 
	LIST_DIRECTORIES false 
	"${luaapipp_dev_toplevel}/impl/*.cpp"
)
#prepend(luaapipp_sources "${luaapipp_dev_toplevel}/src/" ${luaapipp_sources})
list(APPEND luaapipp_sources "${luaapipp_dev_toplevel}/luapp/lua.hpp")

# # External project to get sources
ExternalProject_Add(LUAAPIPP_DEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS FALSE
	# # Use Git to get what we need
	#GIT_SUBMODULES ""
	GIT_SHALLOW TRUE
	GIT_REPOSITORY https://github.com/ThePhD/lua-api-pp.git
	PREFIX ${luaapipp_dev_toplevel}
	SOURCE_DIR ${luaapipp_dev_toplevel}
	DOWNLOAD_DIR ${luaapipp_dev_toplevel}
	TMP_DIR "${luaapipp_dev_toplevel}-tmp"
	STAMP_DIR "${luaapipp_dev_toplevel}-stamp"
	INSTALL_DIR "${luaapipp_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${luaapipp_sources}")

set(luaapipp_lib luaapipp_lib_${luaapipp_version})
add_library(${luaapipp_lib} INTERFACE)
add_dependencies(${luaapipp_lib} LUAAPIPP_DEV_SOURCE)
target_include_directories(${luaapipp_lib}
	INTERFACE ${luaapipp_include_dirs})
target_link_libraries(${luaapipp_lib} INTERFACE ${LUA_LIBRARIES})

# # Variables required by LuaApipp
set(LUAAPIPP_LIBRARIES ${luaapipp_lib})
set(LUAAPIPP_INCLUDE_DIRS ${luaapipp_include_dirs})
set(LUAAPIPPDEV_FOUND TRUE)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaApippDev
	FOUND_VAR LUAAPIPPDEV_FOUND
	REQUIRED_VARS LUAAPIPP_LIBRARIES LUAAPIPP_INCLUDE_DIRS
	VERSION_VAR luaapipp_version)
