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
set(oolua_version 2.0.1)

# # Useful locations
set(oolua_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/oolua_${oolua_version}")
set(oolua_include_dirs "${oolua_dev_toplevel}/include")

# # OOLua library sources
file(GLOB_RECURSE oolua_sources 
	LIST_DIRECTORIES false 
	"${oolua_dev_toplevel}/src/*.cpp"
	"${oolua_dev_toplevel}/src/*.c"
)
#prepend(oolua_sources "${oolua_dev_toplevel}/src/" ${oolua_sources})
list(APPEND oolua_sources "${oolua_dev_toplevel}/include/oolua.h")

# # External project to get sources
ExternalProject_Add(OOLUA_DEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS FALSE
	# # Use Git to get what we need
	#GIT_SUBMODULES ""
	GIT_SHALLOW TRUE
	GIT_REPOSITORY https://github.com/ThePhD/oolua.git
	PREFIX ${oolua_dev_toplevel}
	SOURCE_DIR ${oolua_dev_toplevel}
	DOWNLOAD_DIR ${oolua_dev_toplevel}
	TMP_DIR "${oolua_dev_toplevel}-tmp"
	STAMP_DIR "${oolua_dev_toplevel}-stamp"
	INSTALL_DIR "${oolua_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${oolua_sources}")

set(oolua_lib oolua_lib_${oolua_version})
add_library(${oolua_lib} STATIC ${oolua_sources})
add_dependencies(${oolua_lib} OOLUA_DEV_SOURCE)
set_target_properties(${oolua_lib} PROPERTIES
	OUTPUT_NAME oolua-${oolua_version}
	LINKER_LANGUAGE CXX
	POSITION_INDEPENDENT_CODE TRUE)
target_include_directories(${oolua_lib}
	PUBLIC ${oolua_include_dirs})
target_link_libraries(${oolua_lib} PRIVATE ${LUA_LIBRARIES})
target_compile_definitions(${oolua_lib}
	PUBLIC 
	"OOLUA_USE_EXCEPTIONS=0"
	"OOLUA_RUNTIME_CHECKS_ENABLED=0"
)
if (MSVC)
	target_compile_options(${oolua_lib}
		PRIVATE /W1
	)
else()
	target_compile_options(${oolua_lib}
		PRIVATE -w
		PUBLIC -Wno-unused-parameter
	)
endif()
if (CMAKE_DL_LIBS)
	target_link_libraries(${oolua_lib} PRIVATE ${CMAKE_DL_LIBS})
endif()

# # Variables required by OOLua
set(OOLUA_LIBRARIES ${oolua_lib})
set(OOLUA_INCLUDE_DIRS ${oolua_include_dirs})
set(OOLUADEV_FOUND TRUE)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(OOLuaDev
	FOUND_VAR OOLUADEV_FOUND
	REQUIRED_VARS OOLUA_LIBRARIES OOLUA_INCLUDE_DIRS
	VERSION_VAR oolua_version)
