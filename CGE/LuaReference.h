#ifndef LUAREFERENCE_H
#define LUAREFERENCE_H

#include <lua.hpp>

namespace CGE
{
    class LuaReference
    {
        public:
            LuaReference(lua_State* inState = NULL);
            ~LuaReference();

            inline bool isSet() const { return mReference != LUA_NOREF; }

            void unset();
            void set(lua_State* inState);
            void get() const;

        protected:
        private:
            lua_State* mState;
            int mReference;
    };
}

#endif
