#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <switch.h>

#include "script_init.hpp"

int scriptLength = 47;
std::vector<struct controlMsg> scriptA(scriptLength);
std::vector<struct controlMsg> scriptS(scriptLength);

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

void getScriptLines(std::string fileName, std::vector<struct controlMsg> &script)
{
    std::ifstream ifs(fileName);

    if(ifs.good())
    {
        std::string frameStr, keyStr, lStickStr, rStickStr;
        while(ifs >> frameStr >> keyStr >> lStickStr >> rStickStr)
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

            //get left stick
            std::size_t foundL = lStickStr.find(";");
            std::string l_x_pos = lStickStr.substr(0,foundL);
            s32 joy_l_x = static_cast<s32>(std::stoi(l_x_pos));
            std::string l_y_pos = lStickStr.substr(foundL+1);
            s32 joy_l_y = static_cast<s32>(std::stoi(l_y_pos));

            //get right stick
            std::size_t foundR = rStickStr.find(";");
            std::string r_x_pos = rStickStr.substr(0,foundR);
            s32 joy_r_x = static_cast<s32>(std::stoi(r_x_pos));
            std::string r_y_pos = rStickStr.substr(foundR+1);
            s32 joy_r_y = static_cast<s32>(std::stoi(r_y_pos));


            //deposit found values into the script
            int activeFrame = std::stoi(frameStr);
            script[activeFrame].keys = keys;
            script[activeFrame].joy_l_x = joy_l_x;
            script[activeFrame].joy_l_y = joy_l_y;
            script[activeFrame].joy_r_x = joy_r_x;
            script[activeFrame].joy_r_y = joy_r_y;
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
    {
        scriptA[i].keys = 0;
        scriptA[i].joy_l_x = 0;
        scriptA[i].joy_l_y = 0;
        scriptA[i].joy_r_x = 0;
        scriptA[i].joy_r_y = 0;
    }

    for(int i = 0; i < scriptLength; ++i)
    {
        scriptS[i].keys = 0;
        scriptS[i].joy_l_x = 0;
        scriptS[i].joy_l_y = 0;
        scriptS[i].joy_r_x = 0;
        scriptS[i].joy_r_y = 0;
    }

    //std::ifstream ifs("sdmc:/script.txt");
    getScriptLines("sdmc:/scriptA.txt", scriptA);
    getScriptLines("sdmc:/scriptS.txt", scriptS);
}