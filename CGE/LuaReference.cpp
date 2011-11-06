#include "LuaReference.h"
#include <cassert>

LuaReference::LuaReference() : mState(NULL), mReference(LUA_NOREF)
{
}

LuaReference::~LuaReference()
{
    unset();
}

void LuaReference::set(lua_State* inState)
{
    assert(inState != NULL);
    unset();

    mState = inState;
    mReference = luaL_ref(mState, LUA_REGISTRYINDEX);

    if (mReference == LUA_REFNIL) unset();
}

void LuaReference::get()
{
    if (isSet()) lua_rawgeti(mState, LUA_REGISTRYINDEX, mReference);
}

void LuaReference::unset()
{
    if (isSet())
    {
        assert(mState != NULL);
        luaL_unref(mState, LUA_REGISTRYINDEX, mReference);
        mState = NULL;
        mReference = LUA_NOREF;
    }
}
