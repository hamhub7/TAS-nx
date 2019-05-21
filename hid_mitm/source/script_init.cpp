#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <switch.h>

#include "script_init.hpp"

int scriptLength = 47;
std::vector<struct controlMsg> script(scriptLength);

extern FILE *file;

std::string keyDef[] = {"KEY_A", "KEY_B", "KEY_X", "KEY_Y", "KEY_LSTICK", "KEY_RSTICK", "KEY_L", "KEY_R", "KEY_ZL", "KEY_ZR", "KEY_PLUS", "KEY_MINUS", "KEY_DLEFT", "KEY_DUP", "KEY_DRIGHT", "KEY_DDOWN"};

u64 translateKey(std::string str)
{  
    for (u64 i = 0; i < sizeof(keyDef) / sizeof(char *); i++)
    {
        if (str == keyDef[i])
        {
            return BIT(i);
        }
    }
    return static_cast<u64>(0);
}

void getScriptLines()
{
    std::ifstream ifs("sdmc:/script.txt");

    if(ifs.good())
    {
        std::string frameStr, keyStr;
        while(ifs >> frameStr >> keyStr)
        {
            //get keys
            u64 keys = 0;
            while(keyStr.find_last_of(";") != std::string::npos)
            {
                std::size_t found = keyStr.find_last_of(";");
                std::string latestKey = keyStr.substr(found+1);
                keys |= translateKey(latestKey);
                keyStr.resize(found);
            }
            keys |= translateKey(keyStr);

            //deposit found values into the script
            int activeFrame = std::stoi(frameStr);
            script[activeFrame].keys = keys;
        }
        ifs.close();

    }
    else
    {
        fatalSimple(0x000f);
    }
}

void initScript()
{
    for(int i = 0; i < scriptLength; ++i)
        script[i].keys = 0;

    for(int i = 0; i < scriptLength; ++i)
        script[i].joy_l_x = 0;

    for(int i = 0; i < scriptLength; ++i)
        script[i].joy_l_y = 0;

    for(int i = 0; i < scriptLength; ++i)
        script[i].joy_r_x = 0;

    for(int i = 0; i < scriptLength; ++i)
        script[i].joy_r_y = 0;

    getScriptLines();
}