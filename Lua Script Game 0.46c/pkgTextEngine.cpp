/*
** Lua binding: TextEngine
** Generated automatically by tolua++-1.0.7 on 08/20/09 21:05:58.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "TextEngine.h"

/* Exported function */
TOLUA_API int  tolua_TextEngine_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_TextEngine (lua_State* tolua_S)
{
 TextEngine* self = (TextEngine*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"TextEngine");
}

/* method: Instance of class  TextEngine */
#ifndef TOLUA_DISABLE_tolua_TextEngine_TextEngine_Instance00
static int tolua_TextEngine_TextEngine_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextEngine* tolua_ret = (TextEngine*)  TextEngine::Instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextEngine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  TextEngine */
#ifndef TOLUA_DISABLE_tolua_TextEngine_TextEngine_delete00
static int tolua_TextEngine_TextEngine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextEngine* self = (TextEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TextEngine::DebugString of class  TextEngine */
#ifndef TOLUA_DISABLE_tolua_TextEngine_TextEngine_TextEngine__DebugString00
static int tolua_TextEngine_TextEngine_TextEngine__DebugString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextEngine* self = (TextEngine*)  tolua_tousertype(tolua_S,1,0);
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  bool screenCoords = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TextEngine::DebugString'",NULL);
#endif
  {
   self->TextEngine::DebugString(message,x,y,screenCoords);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TextEngine__DebugString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Textbox of class  TextEngine */
#ifndef TOLUA_DISABLE_tolua_TextEngine_TextEngine_Textbox00
static int tolua_TextEngine_TextEngine_Textbox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TextEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextEngine* self = (TextEngine*)  tolua_tousertype(tolua_S,1,0);
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  int delay = ((int)  tolua_tonumber(tolua_S,4,0));
  int x = ((int)  tolua_tonumber(tolua_S,5,0));
  int y = ((int)  tolua_tonumber(tolua_S,6,0));
  bool screenCoords = ((bool)  tolua_toboolean(tolua_S,7,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Textbox'",NULL);
#endif
  {
   self->Textbox(title,message,delay,x,y,screenCoords);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Textbox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_TextEngine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
  tolua_cclass(tolua_S,"TextEngine","TextEngine","",tolua_collect_TextEngine);
#else
  tolua_cclass(tolua_S,"TextEngine","TextEngine","",NULL);
#endif
  tolua_beginmodule(tolua_S,"TextEngine");
   tolua_function(tolua_S,"Instance",tolua_TextEngine_TextEngine_Instance00);
   tolua_function(tolua_S,"delete",tolua_TextEngine_TextEngine_delete00);
   tolua_function(tolua_S,"TextEngine__DebugString",tolua_TextEngine_TextEngine_TextEngine__DebugString00);
   tolua_function(tolua_S,"Textbox",tolua_TextEngine_TextEngine_Textbox00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
