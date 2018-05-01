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
set(selene_version 0.4.0)
set(selene_lib selene_lib_${selene_version})

# # Useful locations
set(selene_dev_toplevel "${CMAKE_BINARY_DIR}/vendor/selene_${selene_version}")
set(selene_include_dirs "${selene_dev_toplevel}/include")

# # selene library sources
set(selene_sources selene.h)
prepend(selene_sources "${selene_dev_toplevel}/include/" ${selene_sources})

# # External project to get sources
ExternalProject_Add(SELENEDEV_SOURCE
	BUILD_IN_SOURCE TRUE
	BUILD_ALWAYS FALSE
	# # Use Git to get what we need
	GIT_SHALLOW TRUE
	GIT_REPOSITORY https://github.com/ThePhD/selene
	PREFIX ${selene_dev_toplevel}
	SOURCE_DIR ${selene_dev_toplevel}
	DOWNLOAD_DIR ${selene_dev_toplevel}
	TMP_DIR "${selene_dev_toplevel}-tmp"
	STAMP_DIR "${selene_dev_toplevel}-stamp"
	INSTALL_DIR "${selene_dev_toplevel}/local"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_BYPRODUCTS "${selene_sources}")

add_library(${selene_lib} INTERFACE)
add_dependencies(${selene_lib} SELENEDEV_SOURCE)
target_include_directories(${selene_lib} INTERFACE ${selene_include_dirs})
target_link_libraries(${selene_lib} INTERFACE ${LUA_LIBRARIES})
if (NOT MSVC)
	target_compile_options(${selene_lib} INTERFACE
		-Wno-noexcept-type -Wno-ignored-qualifiers -Wno-unused-parameter)
endif()

set(SELENEDEV_FOUND TRUE)
set(SELENE_LIBRARIES ${selene_lib})
set(SELENE_INCLUDE_DIRS ${selene_include_dirs})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SeleneDev
	FOUND_VAR SELENEDEV_FOUND
	REQUIRED_VARS SELENE_LIBRARIES SELENE_INCLUDE_DIRS
	VERSION_VAR selene_version)
