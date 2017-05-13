#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <string>
#include "RenderEngine.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

class RenderEngine;

class ScriptEngine{
    private:
        static ScriptEngine* pinstance;
        lua_State* L;
        RenderEngine *renderer;
    protected:
        ScriptEngine();
        ScriptEngine(const ScriptEngine&);
        ScriptEngine& operator= (const ScriptEngine&);
    public:
        static ScriptEngine* Instance();
        ~ScriptEngine();
        lua_State* GetLuaState();
        void Register();
        void RegisterScript(std::string filename);
};

#endif // SCRIPT_H_INCLUDED
