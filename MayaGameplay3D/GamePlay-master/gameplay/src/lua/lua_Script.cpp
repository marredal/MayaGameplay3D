// Autogenerated by gameplay-luagen
#include "Base.h"
#include "ScriptController.h"
#include "lua_Script.h"
#include "Base.h"
#include "Game.h"
#include "Ref.h"
#include "Script.h"
#include "ScriptController.h"
#include "Ref.h"

namespace gameplay
{

extern void luaGlobal_Register_Conversion_Function(const char* className, void*(*func)(void*, const char*));

static Script* getInstance(lua_State* state)
{
    void* userdata = luaL_checkudata(state, 1, "Script");
    luaL_argcheck(state, userdata != NULL, 1, "'Script' expected.");
    return (Script*)((gameplay::ScriptUtil::LuaObject*)userdata)->instance;
}

static int lua_Script__gc(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                void* userdata = luaL_checkudata(state, 1, "Script");
                luaL_argcheck(state, userdata != NULL, 1, "'Script' expected.");
                gameplay::ScriptUtil::LuaObject* object = (gameplay::ScriptUtil::LuaObject*)userdata;
                if (object->owns)
                {
                    Script* instance = (Script*)object->instance;
                    SAFE_RELEASE(instance);
                }
                
                return 0;
            }

            lua_pushstring(state, "lua_Script__gc - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_addRef(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                instance->addRef();
                
                return 0;
            }

            lua_pushstring(state, "lua_Script_addRef - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_functionExists(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 2:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA) &&
                (lua_type(state, 2) == LUA_TSTRING || lua_type(state, 2) == LUA_TNIL))
            {
                // Get parameter 1 off the stack.
                const char* param1 = gameplay::ScriptUtil::getString(2, false);

                Script* instance = getInstance(state);
                bool result = instance->functionExists(param1);

                // Push the return value onto the stack.
                lua_pushboolean(state, result);

                return 1;
            }

            lua_pushstring(state, "lua_Script_functionExists - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 2).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_getPath(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                const char* result = instance->getPath();

                // Push the return value onto the stack.
                lua_pushstring(state, result);

                return 1;
            }

            lua_pushstring(state, "lua_Script_getPath - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_getRefCount(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                unsigned int result = instance->getRefCount();

                // Push the return value onto the stack.
                lua_pushunsigned(state, result);

                return 1;
            }

            lua_pushstring(state, "lua_Script_getRefCount - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_getScope(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                Script::Scope result = instance->getScope();

                // Push the return value onto the stack.
                lua_pushnumber(state, (int)result);

                return 1;
            }

            lua_pushstring(state, "lua_Script_getScope - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_release(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                instance->release();
                
                return 0;
            }

            lua_pushstring(state, "lua_Script_release - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

static int lua_Script_reload(lua_State* state)
{
    // Get the number of parameters.
    int paramCount = lua_gettop(state);

    // Attempt to match the parameters to a valid binding.
    switch (paramCount)
    {
        case 1:
        {
            if ((lua_type(state, 1) == LUA_TUSERDATA))
            {
                Script* instance = getInstance(state);
                bool result = instance->reload();

                // Push the return value onto the stack.
                lua_pushboolean(state, result);

                return 1;
            }

            lua_pushstring(state, "lua_Script_reload - Failed to match the given parameters to a valid function signature.");
            lua_error(state);
            break;
        }
        default:
        {
            lua_pushstring(state, "Invalid number of parameters (expected 1).");
            lua_error(state);
            break;
        }
    }
    return 0;
}

// Provides support for conversion to all known relative types of Script
static void* __convertTo(void* ptr, const char* typeName)
{
    Script* ptrObject = reinterpret_cast<Script*>(ptr);

    if (strcmp(typeName, "Ref") == 0)
    {
        return reinterpret_cast<void*>(static_cast<Ref*>(ptrObject));
    }

    // No conversion available for 'typeName'
    return NULL;
}

static int lua_Script_to(lua_State* state)
{
    // There should be only a single parameter (this instance)
    if (lua_gettop(state) != 2 || lua_type(state, 1) != LUA_TUSERDATA || lua_type(state, 2) != LUA_TSTRING)
    {
        lua_pushstring(state, "lua_Script_to - Invalid number of parameters (expected 2).");
        lua_error(state);
        return 0;
    }

    Script* instance = getInstance(state);
    const char* typeName = gameplay::ScriptUtil::getString(2, false);
    void* result = __convertTo((void*)instance, typeName);

    if (result)
    {
        gameplay::ScriptUtil::LuaObject* object = (gameplay::ScriptUtil::LuaObject*)lua_newuserdata(state, sizeof(gameplay::ScriptUtil::LuaObject));
        object->instance = (void*)result;
        object->owns = false;
        luaL_getmetatable(state, typeName);
        lua_setmetatable(state, -2);
    }
    else
    {
        lua_pushnil(state);
    }

    return 1;
}

void luaRegister_Script()
{
    const luaL_Reg lua_members[] = 
    {
        {"addRef", lua_Script_addRef},
        {"functionExists", lua_Script_functionExists},
        {"getPath", lua_Script_getPath},
        {"getRefCount", lua_Script_getRefCount},
        {"getScope", lua_Script_getScope},
        {"release", lua_Script_release},
        {"reload", lua_Script_reload},
        {"to", lua_Script_to},
        {NULL, NULL}
    };
    const luaL_Reg* lua_statics = NULL;
    std::vector<std::string> scopePath;

    gameplay::ScriptUtil::registerClass("Script", lua_members, NULL, lua_Script__gc, lua_statics, scopePath);

    luaGlobal_Register_Conversion_Function("Script", __convertTo);
}

}