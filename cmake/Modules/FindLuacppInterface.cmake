
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
set(luacppinterface_version 1.3.0)
set(luacppinterface_lib luacppinterface_lib_${luacppinterface_version})

# # Useful locations
set(luacppinterface_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/luacppinterface_${luacppinterface_version}")
set(luacppinterface_include_dirs "${luacppinterface_dev_toplevel}")

# # luacppinterface library sources
set(luacppinterface_sources
	"LuaCppInterface/luacoroutine.cpp"
	"LuaCppInterface/luacppinterface.cpp"
	"LuaCppInterface/luafunction.cpp"
	"LuaCppInterface/luareference.cpp"
	"LuaCppInterface/luatable.cpp"
	"LuaCppInterface/luaerror.cpp"

	"LuaCppInterface/luacoroutine.h"
	"LuaCppInterface/luacppinterface.h"
	"LuaCppInterface/luafunction.h"
	"LuaCppInterface/luafunctionbase.h"
	"LuaCppInterface/luageneralgenericfunctions.h"
	"LuaCppInterface/luagenericfunction.h"
	"LuaCppInterface/lualightuserdata.h"
	"LuaCppInterface/luareference.h"
	"LuaCppInterface/luatable.h"
	"LuaCppInterface/luatype.h"
	"LuaCppInterface/luatypetemplates.h"
	"LuaCppInterface/luauserdata.h"
	"LuaCppInterface/luauserdatabindtemplates.h"
	"LuaCppInterface/luauserdataforwards.h"
	"LuaCppInterface/luavoidgenericfunctions.h"
)
prepend(luacppinterface_sources "${luacppinterface_dev_toplevel}/" ${luacppinterface_sources})

# # External project to get sources
ExternalProject_Add(LUACPPINTERFACEDEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS FALSE
	# # Use Git to get what we need
	GIT_SHALLOW TRUE
	GIT_SUBMODULES ""
	GIT_REPOSITORY https://github.com/davidsiaw/luacppinterface.git
	PREFIX ${luacppinterface_dev_toplevel}
	SOURCE_DIR ${luacppinterface_dev_toplevel}
	DOWNLOAD_DIR ${luacppinterface_dev_toplevel}
	TMP_DIR "${luacppinterface_dev_toplevel}-tmp"
	STAMP_DIR "${luacppinterface_dev_toplevel}-stamp"
	INSTALL_DIR "${luacppinterface_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${luacppinterface_sources}")

add_library(${luacppinterface_lib} STATIC ${luacppinterface_sources})
add_dependencies(${luacppinterface_lib} LUACPPINTERFACEDEV_SOURCE)
target_include_directories(${luacppinterface_lib} INTERFACE ${luacppinterface_include_dirs})
if (NOT MSVC)
	target_compile_options(${luacppinterface_lib} INTERFACE
		-Wno-noexcept-type -Wno-ignored-qualifiers -Wno-unused-parameter)
endif()
target_link_libraries(${luacppinterface_lib} 
	PUBLIC ${LUA_LIBRARIES}
)
if (CMAKE_DL_LIBS)
	target_link_libraries(${luacppinterface_lib} 
		PRIVATE ${CMAKE_DL_LIBS}
	)
endif()

set(LUACPPINTERFACEDEV_FOUND TRUE)
set(LUACPPINTERFACE_LIBRARIES ${luacppinterface_lib})
set(LUACPPINTERFACE_INCLUDE_DIRS ${luacppinterface_include_dirs})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaCppInterfaceDev
	FOUND_VAR LUACPPINTERFACEDEV_FOUND
	REQUIRED_VARS LUACPPINTERFACE_LIBRARIES LUACPPINTERFACE_INCLUDE_DIRS
	VERSION_VAR luacppinterface_version)