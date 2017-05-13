/*
** Lua binding: GameEngine
** Generated automatically by tolua++-1.0.7 on 08/10/09 13:15:07.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "GameEngine.h"

/* Exported function */
TOLUA_API int  tolua_GameEngine_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_GameEngine (lua_State* tolua_S)
{
 GameEngine* self = (GameEngine*) tolua_tousertype(tolua_S,1,0);
	delete self;
	self = NULL;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"GameEngine");
 tolua_usertype(tolua_S,"Level");
}

/* method: SetQuit of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_SetQuit00
static int tolua_GameEngine_GameEngine_SetQuit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameEngine::SetQuit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetQuit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Quit of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Quit00
static int tolua_GameEngine_GameEngine_Quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  GameEngine::Quit();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Quit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Instance00
static int tolua_GameEngine_GameEngine_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameEngine* tolua_ret = (GameEngine*)  GameEngine::Instance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameEngine");
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

/* method: Instance of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Instance01
static int tolua_GameEngine_GameEngine_Instance01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   GameEngine* tolua_ret = (GameEngine*)  GameEngine::Instance(filename);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameEngine");
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
tolua_lerror:
 return tolua_GameEngine_GameEngine_Instance00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_delete00
static int tolua_GameEngine_GameEngine_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  if( self != NULL ){
      delete self;
      self = NULL;
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HandleInput of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_HandleInput00
static int tolua_GameEngine_GameEngine_HandleInput00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HandleInput'",NULL);
#endif
  {
   self->HandleInput();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HandleInput'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: KeyDown of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_KeyDown00
static int tolua_GameEngine_GameEngine_KeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
  std::string key = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->KeyDown(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: KeyUp of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_KeyUp00
static int tolua_GameEngine_GameEngine_KeyUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
  std::string key = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'KeyUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->KeyUp(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'KeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Collision of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Collision00
static int tolua_GameEngine_GameEngine_Collision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Collision'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Collision();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Collision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Sleep of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Sleep00
static int tolua_GameEngine_GameEngine_Sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
  int duration = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Sleep'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Sleep(duration);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sleep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_Update00
static int tolua_GameEngine_GameEngine_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
  {
   self->Update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadLevel of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_LoadLevel00
static int tolua_GameEngine_GameEngine_LoadLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
  std::string mapname = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadLevel'",NULL);
#endif
  {
   Level* tolua_ret = (Level*)  self->LoadLevel(mapname);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Level");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  GameEngine */
#ifndef TOLUA_DISABLE_tolua_GameEngine_GameEngine_GetLevel00
static int tolua_GameEngine_GameEngine_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameEngine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameEngine* self = (GameEngine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'",NULL);
#endif
  {
   Level* tolua_ret = (Level*)  self->GetLevel();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Level");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_GameEngine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
  tolua_cclass(tolua_S,"GameEngine","GameEngine","",tolua_collect_GameEngine);
#else
  tolua_cclass(tolua_S,"GameEngine","GameEngine","",NULL);
#endif
  tolua_beginmodule(tolua_S,"GameEngine");
   tolua_function(tolua_S,"SetQuit",tolua_GameEngine_GameEngine_SetQuit00);
   tolua_function(tolua_S,"Quit",tolua_GameEngine_GameEngine_Quit00);
   tolua_function(tolua_S,"Instance",tolua_GameEngine_GameEngine_Instance00);
   tolua_function(tolua_S,"Instance",tolua_GameEngine_GameEngine_Instance01);
   tolua_function(tolua_S,"delete",tolua_GameEngine_GameEngine_delete00);
   tolua_function(tolua_S,"HandleInput",tolua_GameEngine_GameEngine_HandleInput00);
   tolua_function(tolua_S,"KeyDown",tolua_GameEngine_GameEngine_KeyDown00);
   tolua_function(tolua_S,"KeyUp",tolua_GameEngine_GameEngine_KeyUp00);
   tolua_function(tolua_S,"Collision",tolua_GameEngine_GameEngine_Collision00);
   tolua_function(tolua_S,"Sleep",tolua_GameEngine_GameEngine_Sleep00);
   tolua_function(tolua_S,"Update",tolua_GameEngine_GameEngine_Update00);
   tolua_function(tolua_S,"LoadLevel",tolua_GameEngine_GameEngine_LoadLevel00);
   tolua_function(tolua_S,"GetLevel",tolua_GameEngine_GameEngine_GetLevel00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
