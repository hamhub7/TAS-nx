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

void nutClip()
{
    //Length 47
    script[0].keys = KEY_ZL;
    script[1].keys = KEY_B;
    script[28].keys = KEY_ZL;
    script[29].keys = KEY_B;
    script[46].keys = KEY_Y;
}

/*void spinPound()
{
    //Length 34
    script[0].joy_l_x = 30000;
    script[1].joy_l_x = 30000;
    script[1].joy_l_y = 30000;
    script[2].joy_l_y = 30000;
    script[3].joy_l_x = -30000;
    script[3].joy_l_y = 30000;
    script[4].joy_l_x = -30000;
    script[5].joy_l_x = -30000;
    script[5].joy_l_y = -30000;
    script[6].joy_l_y = -30000;
    script[7].joy_l_x = 30000;
    script[7].joy_l_y = -30000;

    script[8].joy_l_x = 30000;
    script[9].joy_l_x = 30000;
    script[9].joy_l_y = 30000;
    script[10].joy_l_y = 30000;
    script[10].joy_l_x = -30000;
    script[11].joy_l_y = 30000;
    script[12].joy_l_x = -30000;
    script[13].joy_l_x = -30000;
    script[13].joy_l_y = -30000;
    script[14].joy_l_y = -30000;
    script[15].joy_l_x = 30000;
    script[15].joy_l_y = -30000;

    script[16].joy_l_x = 30000;
    script[17].joy_l_x = 30000;
    script[17].joy_l_y = 30000;
    script[18].joy_l_y = 30000;
    script[19].joy_l_x = -30000;
    script[19].joy_l_y = 30000;
    script[20].joy_l_x = -30000;
    script[21].joy_l_x = -30000;
    script[21].joy_l_y = -30000;
    script[22].joy_l_y = -30000;
    script[23].joy_l_x = 30000;
    script[23].joy_l_y = -30000;

    script[24].joy_l_x = 30000;
    script[25].joy_l_x = 30000;
    script[26].joy_l_x = 30000;
    script[27].joy_l_x = 30000;
    script[28].joy_l_x = 30000;
    script[29].joy_l_x = 30000;
    script[30].joy_l_x = 30000;
    script[31].joy_l_x = 30000;
    script[32].keys = KEY_B;
    script[33].keys = KEY_ZL;
}*/

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
    return 0;
}

void getScriptLines()
{
    std::ifstream ifs("sdmc:/script.txt");

    if(ifs.good())
    {
        int index = 0;
        std::string templine;
        while(std::getline(ifs, templine))
        {
            templine.pop_back();
            std::string frameStr;
            std::string keyStr;

            if(templine != "\n")
            {
                for(long unsigned i = 0;i < templine.length();++i)
                {
                    if(templine[i] == ' ')
                    {
                        frameStr = templine.substr(0,i);
                        keyStr = templine.substr(i+1);
                    }
                }

                u64 keys = 0;
                long unsigned int prev = 0;

                for(long unsigned i = 0;i < keyStr.length();++i)
                {
                    if((templine[i] == '&'))
                    {
                        keys |= translateKey(templine.substr(prev,i));
                        prev = i+1;
                    }

                    keys |= translateKey(templine.substr(i+1));
                }

                //u64 keys = translateKey(keyStr);
                int activeFrame = std::stoi(frameStr);
                script[activeFrame].keys = keys;
            }

            ++index;
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