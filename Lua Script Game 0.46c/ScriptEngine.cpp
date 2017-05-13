#include <iostream>
#include <string>
#include "ScriptEngine.h"
//#include "ScriptFuncs.h"
#include "pkgCharacter.h"
#include "pkgGameEngine.h"
#include "pkgLevel.h"
#include "pkgCamera.h"
#include "pkgTextEngine.h"
#include "pkgObject.h"
#include "RenderEngine.h"

using namespace std;

ScriptEngine* ScriptEngine::pinstance = NULL;
ScriptEngine* ScriptEngine::Instance()
{
    if (pinstance == NULL)
    {
        pinstance = new ScriptEngine;
    }
    return pinstance;
}

ScriptEngine::ScriptEngine()
{
    L = NULL;
    renderer = NULL;

    //Initialize Lua
	L = lua_open();

	//Load Lua base libraries
	luaL_openlibs(L);

	renderer = RenderEngine::Instance();
}

ScriptEngine::~ScriptEngine()
{
    //Clean up Lua
    lua_close(L);
}

lua_State* ScriptEngine::GetLuaState()
{
    return L;
}

void ScriptEngine::Register()
{
    //Register functions with lua
	tolua_Character_open(L);
	tolua_GameEngine_open(L);
	tolua_Level_open(L);
	tolua_Camera_open(L);
	tolua_TextEngine_open(L);
	tolua_Object_open(L);

	//luaL_dofile(L, "scripts\\objects.lua");
}

void ScriptEngine::RegisterScript(string filename)
{
    /* run the script */
	luaL_dofile(L, filename.c_str());
}
