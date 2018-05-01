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

include(ExternalProject)
include(FindPackageHandleStandardArgs)
include(Common/Core)

# # Base variables
set(luaintf_version 1.0.0)
set(luaintf_lib luaintf_lib_${luaintf_version})

# # Useful locations
set(luaintf_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/luaintf_${luaintf_version}")
set(luaintf_include_dirs "${luaintf_dev_toplevel}/")

# # luaintf library sources
set(luaintf_sources LuaIntf.h)
prepend(luaintf_sources "${luaintf_dev_toplevel}/LuaIntf/" ${luaintf_sources})

# # External project to get sources
ExternalProject_Add(LUAINTFDEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS FALSE
	# # Use Git to get what we need
	GIT_SHALLOW TRUE
	#GIT_TAG e513907fc8c2d59ebd91cd5992eddf54f7e23e21
	GIT_REPOSITORY https://github.com/SteveKChiu/lua-intf.git
	PREFIX ${luaintf_dev_toplevel}
	SOURCE_DIR ${luaintf_dev_toplevel}
	DOWNLOAD_DIR ${luaintf_dev_toplevel}
	TMP_DIR "${luaintf_dev_toplevel}-tmp"
	STAMP_DIR "${luaintf_dev_toplevel}-stamp"
	INSTALL_DIR "${luaintf_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${luaintf_sources}")

add_library(${luaintf_lib} INTERFACE)
add_dependencies(${luaintf_lib} LUAINTFDEV_SOURCE)
target_include_directories(${luaintf_lib} INTERFACE ${luaintf_include_dirs})
target_link_libraries(${luaintf_lib} INTERFACE ${LUA_LIBRARIES})
if (NOT MSVC)
	target_compile_options(${luaintf_lib} INTERFACE
		-Wno-noexcept-type -Wno-ignored-qualifiers -Wno-unused-parameter)
endif()

set(LUAINTFDEV_FOUND TRUE)
set(LUAINTF_LIBRARIES ${luaintf_lib})
set(LUAINTF_INCLUDE_DIRS ${luaintf_include_dirs})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaIntfDev
	FOUND_VAR LUAINTFDEV_FOUND
	REQUIRED_VARS LUAINTF_LIBRARIES LUAINTF_INCLUDE_DIRS
	VERSION_VAR luaintf_version)
