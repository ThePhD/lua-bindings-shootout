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
set(luabind_version 0.9.0)

# # Useful locations
set(luabind_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/luabind_${luabind_version}")
set(luabind_include_dirs "${luabind_dev_toplevel}/")

# # Luabind library sources
file(GLOB_RECURSE luabind_sources 
	LIST_DIRECTORIES false 
	"${luabind_dev_toplevel}/src/*.cpp"
	"${luabind_dev_toplevel}/src/*.c"
)
#prepend(luabind_sources "${luabind_dev_toplevel}/src/" ${luabind_sources})
list(APPEND luabind_sources "${luabind_dev_toplevel}/luabind/luabind.hpp")

# # External project to get sources
ExternalProject_Add(LUABIND_DEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS TRUE
	# # Use Git to get what we need
	#GIT_SUBMODULES ""
	GIT_SHALLOW TRUE
	GIT_REPOSITORY https://github.com/WohlSoft/luabind-deboostified.git
	PREFIX ${luabind_dev_toplevel}
	SOURCE_DIR ${luabind_dev_toplevel}
	DOWNLOAD_DIR ${luabind_dev_toplevel}
	TMP_DIR "${luabind_dev_toplevel}-tmp"
	STAMP_DIR "${luabind_dev_toplevel}-stamp"
	INSTALL_DIR "${luabind_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${luabind_sources}")

set(luabind_lib luabind_lib_${luabind_version})
add_library(${luabind_lib} ${luabind_sources})
add_dependencies(${luabind_lib} LUABIND_DEV_SOURCE)
set_target_properties(${luabind_lib} PROPERTIES
	OUTPUT_NAME luabind-${luabind_version}
	LANGUAGE CXX
	LINKER_LANGUAGE CXX
	POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(${luabind_lib}
	PUBLIC ${luabind_include_dirs})
target_link_libraries(${luabind_lib} PRIVATE ${LUA_LIBRARIES})
get_target_property(luabind_lib_shared ${luabind_lib} TYPE)
#target_compile_definitions(${luabind_lib}
#	PRIVATE
#	"LUABIND_BUILDING=1"
#)
if (luabind_lib_shared MATCHES "SHARED")
	target_compile_definitions(${luabind_lib}
		PUBLIC
		"LUABIND_DYNAMIC_LINK=1"
	)
endif()
target_compile_definitions(${luabind_lib}
	PUBLIC
	$<$<CONFIG:Release>:LUABIND_NO_ERROR_CHECKING=1>
	$<$<CONFIG:MinSizeRel>:LUABIND_NO_ERROR_CHECKING=1>
	$<$<CONFIG:RelWithDebInfo>:LUABIND_NO_ERROR_CHECKING=1>
)

if (CMAKE_DL_LIBS)
	target_link_libraries(${luabind_lib} PRIVATE ${CMAKE_DL_LIBS})
endif()

# # Variables required by Luabind
set(LUABIND_LIBRARIES ${luabind_lib})
set(LUABIND_INCLUDE_DIRS ${luabind_include_dirs})
set(LUABINDDEV_FOUND TRUE)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuabindDev
	FOUND_VAR LUABINDDEV_FOUND
	REQUIRED_VARS LUABIND_LIBRARIES LUABIND_INCLUDE_DIRS
	VERSION_VAR luabind_version)
