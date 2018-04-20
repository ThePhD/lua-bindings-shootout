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
include(FindPackageHandleStandardArgs)

# Contain literally everything inside of this function to prevent spillage
function(find_lua_dev lua_version)
	# # # Variables
	# # Core Paths
	string(TOLOWER ${lua_version} LUA_DEV_NORMALIZED_LUA_VERSION)
	if (LUA_DEV_NORMALIZED_LUA_VERSION MATCHES "luajit")
		set(LUA_DEV_LIBNAME ${lua_version})
	elseif (BUILD_LUAJIT)
		set(LUA_DEV_LIBNAME luajit-${lua_version})
	elseif (LUA_DEV_NORMALIZED_LUA_VERSION MATCHES "lua")
		set(LUA_DEV_LIBNAME ${lua_version})
	elseif (BUILD_LUA)
		set(LUA_DEV_LIBNAME lua-${lua_version})
	else()
		set(LUA_DEV_LIBNAME lua-${lua_version})
	endif()
	set(LUA_DEV_TOPLEVEL "${CMAKE_BINARY_DIR}/vendor/${LUA_DEV_LIBNAME}")
	set(LUA_DEV_INSTALL_DIR "${LUA_DEV_TOPLEVEL}")
	# # Misc needed variables
	set(LUA_DEV_LIBRARY_DESCRIPTION "The base name of the library to build either the static or the dynamic library")

	# Object file suffixes
	if (MSVC)
		set(LUA_DEV_BUILD_DLL_DEFAULT ON)
		set(LUA_DEV_OBJECT_FILE_SUFFIX .obj)
	else()
		set(LUA_DEV_BUILD_DLL_DEFAULT OFF)
		set(LUA_DEV_OBJECT_FILE_SUFFIX .o)
	endif()

	STRING(TOLOWER ${LUA_DEV_LIBNAME} LUA_DEV_NORMALIZED_LIBNAME)
	if (NOT LUA_LIBRARY_NAME)
		if (LUA_DEV_NORMALIZED_LIBNAME MATCHES "luajit")
			set(LUA_LIBRARY luajit)
		else()
			set(LUA_LIBRARY ${LUA_DEV_LIBNAME})
		endif()
	else()
		set(LUA_LIBRARY_NAME ${LUA_LIBRARY_NAME}
			CACHE STRING
			${LUA_DEV_LIBRARY_DESCRIPTION})
	endif()

	# # # Build Lua
	# # Select either LuaJIT or Vanilla Lua here, based on what we discover
	set(LUA_VERSION ${lua_version})
	if (BUILD_LUAJIT OR LUA_DEV_NORMALIZED_LUA_VERSION MATCHES "luajit")
		include(${CMAKE_CURRENT_LIST_DIR}/FindLuaDev/LuaJIT.cmake)
		set(LUA_VERSION_STRING ${LUA_JIT_VERSION})
	else()
		include(${CMAKE_CURRENT_LIST_DIR}/FindLuaDev/LuaVanilla.cmake)
		set(LUA_VERSION_STRING ${LUA_VANILLA_VERSION})
	endif()

	# # Export variables to the parent scope
	set(LUA_LIBRARIES ${LUA_LIBRARIES} PARENT_SCOPE)
	set(LUA_INTERPRETER ${LUA_INTERPRETER} PARENT_SCOPE)
	set(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIRS} PARENT_SCOPE)
	set(LUA_VERSION_STRING ${LUA_VERSION_STRING} PARENT_SCOPE)
	set(LUADEV_FOUND TRUE PARENT_SCOPE)
endfunction(find_lua_dev)

if (LuaDev_FIND_COMPONENTS)
	list(GET LuaDev_FIND_COMPONENTS 0 lua_version)
endif(LuaDev_FIND_COMPONENTS)
if (LuaDev_FIND_VERSION)
	if (lua_version)
		set(lua_version "${lua_version}-${LuaDev_FIND_VERSION}")
	else()
		set(lua_version ${LuaDev_FIND_VERSION})
	endif(lua_version)
endif(LuaDev_FIND_VERSION)
if (BUILD_SHARED_LIBS)
	set(LUA_DEV_LIBRARY_TYPE SHARED)
else()
	set(LUA_DEV_LIBRARY_TYPE STATIC)
endif(BUILD_SHARED_LIBS)
if (NOT lua_version)
	set(lua_version 5.3.4)
endif(NOT lua_version)

# Call...
find_lua_dev(${lua_version})
# and then immediately undefine to avoid polluting the current scope
unset(find_lua_dev)

# handle the QUIETLY and REQUIRED arguments and set LuaDev_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaDev
	FOUND_VAR LUADEV_FOUND
	REQUIRED_VARS LUA_LIBRARIES LUA_INTERPRETER LUA_INCLUDE_DIRS
	VERSION_VAR LUA_VERSION_STRING)
