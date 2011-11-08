#ifndef LUAMACHINE_H
#define LUAMACHINE_H

#include <lua.hpp>
#include <string>

namespace CGE
{
    class LuaMachine
    {
        public:
            LuaMachine();
            virtual ~LuaMachine();

            void reset();
            void loadFile(const char* inFile);
            void runCommand(const char* inCommand);
            void addFunction(const char* inName, lua_CFunction inFunction);

            inline lua_State* getState() { return mLuaState; }

        private:
            void execute();
            void reportErrors();

            lua_State* mLuaState;
            int mStatus;
            std::string mError;
    };
}

#endif
