// lua bindings shootout
// The MIT License (MIT)

// Copyright © 2018 ThePhD

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/*
** Lua binding: toluapp_lib
** Generated automatically by tolua++-1.0.93-lua53 on Thu May  3 20:41:02 2018.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_toluapp_lib_open (lua_State* tolua_S);

using namespace lbs;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_basic (lua_State* tolua_S)
{
 basic* self = (basic*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_basic_large (lua_State* tolua_S)
{
 basic_large* self = (basic_large*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_complex_base_b (lua_State* tolua_S)
{
 complex_base_b* self = (complex_base_b*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_complex_base_a (lua_State* tolua_S)
{
 complex_base_a* self = (complex_base_a*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_complex_ab (lua_State* tolua_S)
{
 complex_ab* self = (complex_ab*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"basic");
 tolua_usertype(tolua_S,"int64_t");
 tolua_usertype(tolua_S,"basic_large");
 tolua_usertype(tolua_S,"complex_base_b");
 tolua_usertype(tolua_S,"complex_base_a");
 tolua_usertype(tolua_S,"complex_ab");
}

/* get function: var of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var
static int tolua_get_basic_var(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var
static int tolua_set_basic_var(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var0 of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var0
static int tolua_get_basic_var0(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var0'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var0);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var0 of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var0
static int tolua_set_basic_var0(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var0'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var0 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var1 of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var1
static int tolua_get_basic_var1(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var1'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var1 of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var1
static int tolua_set_basic_var1(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var1'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var1 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var2 of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var2
static int tolua_get_basic_var2(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var2'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var2 of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var2
static int tolua_set_basic_var2(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var2'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var2 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var3 of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var3
static int tolua_get_basic_var3(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var3'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var3 of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var3
static int tolua_set_basic_var3(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var3'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var3 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var4 of class  basic */
#ifndef TOLUA_DISABLE_tolua_get_basic_var4
static int tolua_get_basic_var4(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var4'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var4 of class  basic */
#ifndef TOLUA_DISABLE_tolua_set_basic_var4
static int tolua_set_basic_var4(lua_State* tolua_S)
{
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var4'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var4 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_new00
static int tolua_toluapp_lib_c_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   basic* tolua_ret = (basic*)  Mtolua_new((basic)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_new00_local
static int tolua_toluapp_lib_c_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   basic* tolua_ret = (basic*)  Mtolua_new((basic)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_new01
static int tolua_toluapp_lib_c_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   basic* tolua_ret = (basic*)  Mtolua_new((basic)(x));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic");
  }
 }
 return 1;
tolua_lerror:
 return tolua_toluapp_lib_c_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_new01_local
static int tolua_toluapp_lib_c_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   basic* tolua_ret = (basic*)  Mtolua_new((basic)(x));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_toluapp_lib_c_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_get00
static int tolua_toluapp_lib_c_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const basic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const basic* self = (const basic*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
   double tolua_ret = (double)  self->get();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  basic */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_c_set00
static int tolua_toluapp_lib_c_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"basic",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  basic* self = (basic*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
   self->set(x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var
static int tolua_get_basic_large_var(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var
static int tolua_set_basic_large_var(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var0 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var0
static int tolua_get_basic_large_var0(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var0'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var0);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var0 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var0
static int tolua_set_basic_large_var0(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var0'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var0 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var1 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var1
static int tolua_get_basic_large_var1(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var1'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var1 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var1
static int tolua_set_basic_large_var1(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var1'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var1 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var2 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var2
static int tolua_get_basic_large_var2(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var2'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var2 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var2
static int tolua_set_basic_large_var2(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var2'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var2 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var3 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var3
static int tolua_get_basic_large_var3(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var3'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var3 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var3
static int tolua_set_basic_large_var3(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var3'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var3 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var4 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var4
static int tolua_get_basic_large_var4(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var4'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var4 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var4
static int tolua_set_basic_large_var4(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var4'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var4 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var5 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var5
static int tolua_get_basic_large_var5(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var5'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var5 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var5
static int tolua_set_basic_large_var5(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var5'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var5 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var6 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var6
static int tolua_get_basic_large_var6(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var6'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var6);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var6 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var6
static int tolua_set_basic_large_var6(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var6'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var6 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var7 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var7
static int tolua_get_basic_large_var7(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var7'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var7);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var7 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var7
static int tolua_set_basic_large_var7(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var7'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var7 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var8 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var8
static int tolua_get_basic_large_var8(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var8'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var8);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var8 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var8
static int tolua_set_basic_large_var8(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var8'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var8 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var9 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var9
static int tolua_get_basic_large_var9(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var9'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var9);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var9 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var9
static int tolua_set_basic_large_var9(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var9'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var9 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var10 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var10
static int tolua_get_basic_large_var10(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var10'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var10);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var10 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var10
static int tolua_set_basic_large_var10(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var10'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var10 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var11 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var11
static int tolua_get_basic_large_var11(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var11'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var11);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var11 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var11
static int tolua_set_basic_large_var11(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var11'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var11 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var12 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var12
static int tolua_get_basic_large_var12(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var12'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var12);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var12 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var12
static int tolua_set_basic_large_var12(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var12'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var12 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var13 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var13
static int tolua_get_basic_large_var13(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var13'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var13);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var13 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var13
static int tolua_set_basic_large_var13(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var13'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var13 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var14 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var14
static int tolua_get_basic_large_var14(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var14'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var14);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var14 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var14
static int tolua_set_basic_large_var14(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var14'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var14 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var15 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var15
static int tolua_get_basic_large_var15(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var15'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var15);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var15 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var15
static int tolua_set_basic_large_var15(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var15'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var15 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var16 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var16
static int tolua_get_basic_large_var16(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var16'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var16);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var16 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var16
static int tolua_set_basic_large_var16(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var16'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var16 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var17 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var17
static int tolua_get_basic_large_var17(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var17'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var17);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var17 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var17
static int tolua_set_basic_large_var17(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var17'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var17 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var18 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var18
static int tolua_get_basic_large_var18(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var18'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var18);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var18 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var18
static int tolua_set_basic_large_var18(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var18'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var18 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var19 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var19
static int tolua_get_basic_large_var19(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var19'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var19);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var19 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var19
static int tolua_set_basic_large_var19(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var19'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var19 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var20 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var20
static int tolua_get_basic_large_var20(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var20'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var20);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var20 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var20
static int tolua_set_basic_large_var20(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var20'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var20 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var21 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var21
static int tolua_get_basic_large_var21(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var21'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var21);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var21 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var21
static int tolua_set_basic_large_var21(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var21'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var21 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var22 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var22
static int tolua_get_basic_large_var22(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var22'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var22);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var22 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var22
static int tolua_set_basic_large_var22(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var22'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var22 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var23 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var23
static int tolua_get_basic_large_var23(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var23'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var23);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var23 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var23
static int tolua_set_basic_large_var23(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var23'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var23 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var24 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var24
static int tolua_get_basic_large_var24(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var24'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var24);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var24 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var24
static int tolua_set_basic_large_var24(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var24'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var24 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var25 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var25
static int tolua_get_basic_large_var25(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var25'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var25);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var25 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var25
static int tolua_set_basic_large_var25(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var25'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var25 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var26 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var26
static int tolua_get_basic_large_var26(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var26'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var26);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var26 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var26
static int tolua_set_basic_large_var26(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var26'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var26 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var27 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var27
static int tolua_get_basic_large_var27(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var27'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var27);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var27 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var27
static int tolua_set_basic_large_var27(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var27'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var27 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var28 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var28
static int tolua_get_basic_large_var28(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var28'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var28);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var28 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var28
static int tolua_set_basic_large_var28(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var28'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var28 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var29 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var29
static int tolua_get_basic_large_var29(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var29'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var29);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var29 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var29
static int tolua_set_basic_large_var29(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var29'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var29 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var30 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var30
static int tolua_get_basic_large_var30(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var30'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var30);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var30 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var30
static int tolua_set_basic_large_var30(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var30'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var30 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var31 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var31
static int tolua_get_basic_large_var31(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var31'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var31);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var31 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var31
static int tolua_set_basic_large_var31(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var31'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var31 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var32 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var32
static int tolua_get_basic_large_var32(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var32'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var32);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var32 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var32
static int tolua_set_basic_large_var32(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var32'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var32 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var33 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var33
static int tolua_get_basic_large_var33(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var33'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var33);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var33 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var33
static int tolua_set_basic_large_var33(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var33'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var33 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var34 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var34
static int tolua_get_basic_large_var34(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var34'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var34);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var34 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var34
static int tolua_set_basic_large_var34(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var34'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var34 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var35 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var35
static int tolua_get_basic_large_var35(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var35'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var35);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var35 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var35
static int tolua_set_basic_large_var35(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var35'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var35 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var36 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var36
static int tolua_get_basic_large_var36(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var36'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var36);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var36 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var36
static int tolua_set_basic_large_var36(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var36'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var36 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var37 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var37
static int tolua_get_basic_large_var37(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var37'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var37);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var37 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var37
static int tolua_set_basic_large_var37(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var37'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var37 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var38 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var38
static int tolua_get_basic_large_var38(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var38'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var38);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var38 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var38
static int tolua_set_basic_large_var38(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var38'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var38 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var39 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var39
static int tolua_get_basic_large_var39(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var39'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var39);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var39 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var39
static int tolua_set_basic_large_var39(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var39'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var39 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var40 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var40
static int tolua_get_basic_large_var40(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var40'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var40);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var40 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var40
static int tolua_set_basic_large_var40(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var40'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var40 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var41 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var41
static int tolua_get_basic_large_var41(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var41'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var41);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var41 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var41
static int tolua_set_basic_large_var41(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var41'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var41 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var42 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var42
static int tolua_get_basic_large_var42(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var42'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var42);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var42 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var42
static int tolua_set_basic_large_var42(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var42'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var42 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var43 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var43
static int tolua_get_basic_large_var43(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var43'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var43);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var43 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var43
static int tolua_set_basic_large_var43(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var43'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var43 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var44 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var44
static int tolua_get_basic_large_var44(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var44'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var44);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var44 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var44
static int tolua_set_basic_large_var44(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var44'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var44 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var45 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var45
static int tolua_get_basic_large_var45(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var45'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var45);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var45 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var45
static int tolua_set_basic_large_var45(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var45'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var45 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var46 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var46
static int tolua_get_basic_large_var46(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var46'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var46);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var46 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var46
static int tolua_set_basic_large_var46(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var46'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var46 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var47 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var47
static int tolua_get_basic_large_var47(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var47'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var47);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var47 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var47
static int tolua_set_basic_large_var47(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var47'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var47 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var48 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var48
static int tolua_get_basic_large_var48(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var48'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->var48);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var48 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var48
static int tolua_set_basic_large_var48(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var48'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var48 = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: var49 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_get_basic_large_var49
static int tolua_get_basic_large_var49(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var49'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->var49,"int64_t");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: var49 of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_set_basic_large_var49
static int tolua_set_basic_large_var49(lua_State* tolua_S)
{
  basic_large* self = (basic_large*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'var49'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"int64_t",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->var49 = *((int64_t*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cl_new00
static int tolua_toluapp_lib_cl_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic_large",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   basic_large* tolua_ret = (basic_large*)  Mtolua_new((basic_large)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic_large");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  basic_large */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cl_new00_local
static int tolua_toluapp_lib_cl_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"basic_large",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   basic_large* tolua_ret = (basic_large*)  Mtolua_new((basic_large)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"basic_large");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  complex_base_a */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cba_new00
static int tolua_toluapp_lib_cba_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_base_a",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_base_a* tolua_ret = (complex_base_a*)  Mtolua_new((complex_base_a)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_base_a");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  complex_base_a */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cba_new00_local
static int tolua_toluapp_lib_cba_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_base_a",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_base_a* tolua_ret = (complex_base_a*)  Mtolua_new((complex_base_a)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_base_a");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: a_func of class  complex_base_a */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cba_a_func00
static int tolua_toluapp_lib_cba_a_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const complex_base_a",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const complex_base_a* self = (const complex_base_a*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'a_func'", NULL);
#endif
  {
   double tolua_ret = (double)  self->a_func();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'a_func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  complex_base_b */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cbb_new00
static int tolua_toluapp_lib_cbb_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_base_b",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_base_b* tolua_ret = (complex_base_b*)  Mtolua_new((complex_base_b)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_base_b");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  complex_base_b */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cbb_new00_local
static int tolua_toluapp_lib_cbb_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_base_b",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_base_b* tolua_ret = (complex_base_b*)  Mtolua_new((complex_base_b)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_base_b");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: b_func of class  complex_base_b */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cbb_b_func00
static int tolua_toluapp_lib_cbb_b_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const complex_base_b",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const complex_base_b* self = (const complex_base_b*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'b_func'", NULL);
#endif
  {
   double tolua_ret = (double)  self->b_func();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'b_func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cab_new00
static int tolua_toluapp_lib_cab_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_ab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_ab* tolua_ret = (complex_ab*)  Mtolua_new((complex_ab)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_ab");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cab_new00_local
static int tolua_toluapp_lib_cab_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"complex_ab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   complex_ab* tolua_ret = (complex_ab*)  Mtolua_new((complex_ab)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"complex_ab");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: a_func of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cab_a_func00
static int tolua_toluapp_lib_cab_a_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const complex_ab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const complex_ab* self = (const complex_ab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'a_func'", NULL);
#endif
  {
   double tolua_ret = (double)  self->a_func();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'a_func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: b_func of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cab_b_func00
static int tolua_toluapp_lib_cab_b_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const complex_ab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const complex_ab* self = (const complex_ab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'b_func'", NULL);
#endif
  {
   double tolua_ret = (double)  self->b_func();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'b_func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ab_func of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_cab_ab_func00
static int tolua_toluapp_lib_cab_ab_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const complex_ab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const complex_ab* self = (const complex_ab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ab_func'", NULL);
#endif
  {
   double tolua_ret = (double)  self->ab_func();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ab_func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __complex_base_b__ of class  complex_ab */
#ifndef TOLUA_DISABLE_tolua_get_complex_ab___complex_base_b__
static int tolua_get_complex_ab___complex_base_b__(lua_State* tolua_S)
{
  complex_ab* self = (complex_ab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__complex_base_b__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<complex_base_b*>(self), "complex_base_b");
#else
   tolua_pushusertype(tolua_S,(void*)((complex_base_b*)self), "complex_base_b");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* function: basic_call */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_basic_call00
static int tolua_toluapp_lib_basic_call00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double x = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   double tolua_ret = (double)  basic_call(x);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'basic_call'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: basic_return */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_basic_return00
static int tolua_toluapp_lib_basic_return00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double x = ((double)  tolua_tonumber(tolua_S,1,0));
  {
   basic tolua_ret = (basic)  basic_return(x);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((basic)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"basic");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(basic));
     tolua_pushusertype(tolua_S,tolua_obj,"basic");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'basic_return'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: basic_get_var */
#ifndef TOLUA_DISABLE_tolua_toluapp_lib_basic_get_var00
static int tolua_toluapp_lib_basic_get_var00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const basic",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const basic* b = ((const basic*)  tolua_tousertype(tolua_S,1,0));
  {
   double tolua_ret = (double)  basic_get_var(*b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'basic_get_var'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_toluapp_lib_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"c","basic","",tolua_collect_basic);
  #else
  tolua_cclass(tolua_S,"c","basic","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"c");
   tolua_variable(tolua_S,"var",tolua_get_basic_var,tolua_set_basic_var);
   tolua_variable(tolua_S,"var0",tolua_get_basic_var0,tolua_set_basic_var0);
   tolua_variable(tolua_S,"var1",tolua_get_basic_var1,tolua_set_basic_var1);
   tolua_variable(tolua_S,"var2",tolua_get_basic_var2,tolua_set_basic_var2);
   tolua_variable(tolua_S,"var3",tolua_get_basic_var3,tolua_set_basic_var3);
   tolua_variable(tolua_S,"var4",tolua_get_basic_var4,tolua_set_basic_var4);
   tolua_function(tolua_S,"new",tolua_toluapp_lib_c_new00);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_c_new00_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_c_new00_local);
   tolua_function(tolua_S,"new",tolua_toluapp_lib_c_new01);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_c_new01_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_c_new01_local);
   tolua_function(tolua_S,"get",tolua_toluapp_lib_c_get00);
   tolua_function(tolua_S,"set",tolua_toluapp_lib_c_set00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"cl","basic_large","",tolua_collect_basic_large);
  #else
  tolua_cclass(tolua_S,"cl","basic_large","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"cl");
   tolua_variable(tolua_S,"var",tolua_get_basic_large_var,tolua_set_basic_large_var);
   tolua_variable(tolua_S,"var0",tolua_get_basic_large_var0,tolua_set_basic_large_var0);
   tolua_variable(tolua_S,"var1",tolua_get_basic_large_var1,tolua_set_basic_large_var1);
   tolua_variable(tolua_S,"var2",tolua_get_basic_large_var2,tolua_set_basic_large_var2);
   tolua_variable(tolua_S,"var3",tolua_get_basic_large_var3,tolua_set_basic_large_var3);
   tolua_variable(tolua_S,"var4",tolua_get_basic_large_var4,tolua_set_basic_large_var4);
   tolua_variable(tolua_S,"var5",tolua_get_basic_large_var5,tolua_set_basic_large_var5);
   tolua_variable(tolua_S,"var6",tolua_get_basic_large_var6,tolua_set_basic_large_var6);
   tolua_variable(tolua_S,"var7",tolua_get_basic_large_var7,tolua_set_basic_large_var7);
   tolua_variable(tolua_S,"var8",tolua_get_basic_large_var8,tolua_set_basic_large_var8);
   tolua_variable(tolua_S,"var9",tolua_get_basic_large_var9,tolua_set_basic_large_var9);
   tolua_variable(tolua_S,"var10",tolua_get_basic_large_var10,tolua_set_basic_large_var10);
   tolua_variable(tolua_S,"var11",tolua_get_basic_large_var11,tolua_set_basic_large_var11);
   tolua_variable(tolua_S,"var12",tolua_get_basic_large_var12,tolua_set_basic_large_var12);
   tolua_variable(tolua_S,"var13",tolua_get_basic_large_var13,tolua_set_basic_large_var13);
   tolua_variable(tolua_S,"var14",tolua_get_basic_large_var14,tolua_set_basic_large_var14);
   tolua_variable(tolua_S,"var15",tolua_get_basic_large_var15,tolua_set_basic_large_var15);
   tolua_variable(tolua_S,"var16",tolua_get_basic_large_var16,tolua_set_basic_large_var16);
   tolua_variable(tolua_S,"var17",tolua_get_basic_large_var17,tolua_set_basic_large_var17);
   tolua_variable(tolua_S,"var18",tolua_get_basic_large_var18,tolua_set_basic_large_var18);
   tolua_variable(tolua_S,"var19",tolua_get_basic_large_var19,tolua_set_basic_large_var19);
   tolua_variable(tolua_S,"var20",tolua_get_basic_large_var20,tolua_set_basic_large_var20);
   tolua_variable(tolua_S,"var21",tolua_get_basic_large_var21,tolua_set_basic_large_var21);
   tolua_variable(tolua_S,"var22",tolua_get_basic_large_var22,tolua_set_basic_large_var22);
   tolua_variable(tolua_S,"var23",tolua_get_basic_large_var23,tolua_set_basic_large_var23);
   tolua_variable(tolua_S,"var24",tolua_get_basic_large_var24,tolua_set_basic_large_var24);
   tolua_variable(tolua_S,"var25",tolua_get_basic_large_var25,tolua_set_basic_large_var25);
   tolua_variable(tolua_S,"var26",tolua_get_basic_large_var26,tolua_set_basic_large_var26);
   tolua_variable(tolua_S,"var27",tolua_get_basic_large_var27,tolua_set_basic_large_var27);
   tolua_variable(tolua_S,"var28",tolua_get_basic_large_var28,tolua_set_basic_large_var28);
   tolua_variable(tolua_S,"var29",tolua_get_basic_large_var29,tolua_set_basic_large_var29);
   tolua_variable(tolua_S,"var30",tolua_get_basic_large_var30,tolua_set_basic_large_var30);
   tolua_variable(tolua_S,"var31",tolua_get_basic_large_var31,tolua_set_basic_large_var31);
   tolua_variable(tolua_S,"var32",tolua_get_basic_large_var32,tolua_set_basic_large_var32);
   tolua_variable(tolua_S,"var33",tolua_get_basic_large_var33,tolua_set_basic_large_var33);
   tolua_variable(tolua_S,"var34",tolua_get_basic_large_var34,tolua_set_basic_large_var34);
   tolua_variable(tolua_S,"var35",tolua_get_basic_large_var35,tolua_set_basic_large_var35);
   tolua_variable(tolua_S,"var36",tolua_get_basic_large_var36,tolua_set_basic_large_var36);
   tolua_variable(tolua_S,"var37",tolua_get_basic_large_var37,tolua_set_basic_large_var37);
   tolua_variable(tolua_S,"var38",tolua_get_basic_large_var38,tolua_set_basic_large_var38);
   tolua_variable(tolua_S,"var39",tolua_get_basic_large_var39,tolua_set_basic_large_var39);
   tolua_variable(tolua_S,"var40",tolua_get_basic_large_var40,tolua_set_basic_large_var40);
   tolua_variable(tolua_S,"var41",tolua_get_basic_large_var41,tolua_set_basic_large_var41);
   tolua_variable(tolua_S,"var42",tolua_get_basic_large_var42,tolua_set_basic_large_var42);
   tolua_variable(tolua_S,"var43",tolua_get_basic_large_var43,tolua_set_basic_large_var43);
   tolua_variable(tolua_S,"var44",tolua_get_basic_large_var44,tolua_set_basic_large_var44);
   tolua_variable(tolua_S,"var45",tolua_get_basic_large_var45,tolua_set_basic_large_var45);
   tolua_variable(tolua_S,"var46",tolua_get_basic_large_var46,tolua_set_basic_large_var46);
   tolua_variable(tolua_S,"var47",tolua_get_basic_large_var47,tolua_set_basic_large_var47);
   tolua_variable(tolua_S,"var48",tolua_get_basic_large_var48,tolua_set_basic_large_var48);
   tolua_variable(tolua_S,"var49",tolua_get_basic_large_var49,tolua_set_basic_large_var49);
   tolua_function(tolua_S,"new",tolua_toluapp_lib_cl_new00);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_cl_new00_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_cl_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"cba","complex_base_a","",tolua_collect_complex_base_a);
  #else
  tolua_cclass(tolua_S,"cba","complex_base_a","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"cba");
   tolua_function(tolua_S,"new",tolua_toluapp_lib_cba_new00);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_cba_new00_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_cba_new00_local);
   tolua_function(tolua_S,"a_func",tolua_toluapp_lib_cba_a_func00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"cbb","complex_base_b","",tolua_collect_complex_base_b);
  #else
  tolua_cclass(tolua_S,"cbb","complex_base_b","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"cbb");
   tolua_function(tolua_S,"new",tolua_toluapp_lib_cbb_new00);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_cbb_new00_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_cbb_new00_local);
   tolua_function(tolua_S,"b_func",tolua_toluapp_lib_cbb_b_func00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"cab","complex_ab","complex_base_a",tolua_collect_complex_ab);
  #else
  tolua_cclass(tolua_S,"cab","complex_ab","complex_base_a",NULL);
  #endif
  tolua_beginmodule(tolua_S,"cab");
   tolua_function(tolua_S,"new",tolua_toluapp_lib_cab_new00);
   tolua_function(tolua_S,"new_local",tolua_toluapp_lib_cab_new00_local);
   tolua_function(tolua_S,".call",tolua_toluapp_lib_cab_new00_local);
   tolua_function(tolua_S,"a_func",tolua_toluapp_lib_cab_a_func00);
   tolua_function(tolua_S,"b_func",tolua_toluapp_lib_cab_b_func00);
   tolua_function(tolua_S,"ab_func",tolua_toluapp_lib_cab_ab_func00);
   tolua_variable(tolua_S,"__complex_base_b__",tolua_get_complex_ab___complex_base_b__,NULL);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"basic_call",tolua_toluapp_lib_basic_call00);
  tolua_function(tolua_S,"basic_return",tolua_toluapp_lib_basic_return00);
  tolua_function(tolua_S,"basic_get_var",tolua_toluapp_lib_basic_get_var00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_toluapp_lib (lua_State* tolua_S) {
 return tolua_toluapp_lib_open(tolua_S);
};
#endif

