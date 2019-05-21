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
        std::string templine;
        while(std::getline(ifs, templine))
        {
            templine.pop_back(); //remove newline
            std::string frameStr;
            std::string keyStr;
            //std::string lStickStr;
            //std::string rStickStr;

            if(templine != "")
            {

                //separate right joy
                /*std:: size_t foundR = keyStr.find_last_of(" ");
                rStickStr = templine.substr(foundR+1);
                templine.resize(foundR);

                //separate left joy
                std:: size_t foundL = keyStr.find_last_of(" ");
                lStickStr = templine.substr(foundL+1);
                templine.resize(foundL);*/

                //separate keys and frame
                std:: size_t foundK = keyStr.find_last_of("+");
                keyStr = templine.substr(foundK+1);
                //fprintf(file, keyStr.c_str());
                templine.resize(foundK);
                frameStr = templine;
                //fprintf(file, frameStr.c_str());

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
                /*s32 joy_l_x = 0;
                s32 joy_l_y = 0;
                while(lStickStr.find(";") != std::string::npos)
                {
                    std::size_t found = lStickStr.find(";");
                    std::string l_x_pos = lStickStr.substr(0,found);
                    joy_l_x = static_cast<s32>(std::stoi(l_x_pos));
                    std::string l_y_pos = lStickStr.substr(found+1);
                    joy_l_y = static_cast<s32>(std::stoi(l_y_pos));
                }*/

                //get right stick
                /*s32 joy_r_x = 0;
                s32 joy_r_y = 0;
                while(rStickStr.find(";") != std::string::npos)
                {
                    std::size_t found = rStickStr.find(";");
                    std::string r_x_pos = rStickStr.substr(0,found);
                    joy_r_x = static_cast<s32>(std::stoi(r_x_pos));
                    std::string r_y_pos = rStickStr.substr(found+1);
                    joy_r_y = static_cast<s32>(std::stoi(r_y_pos));
                }*/

                //deposit found values into the script
                int activeFrame = std::stoi(frameStr);
                script[activeFrame].keys = keys;
                //script[activeFrame].joy_l_x = joy_l_x;
                //script[activeFrame].joy_l_y = joy_l_y;
                //script[activeFrame].joy_r_x = joy_r_x;
                //script[activeFrame].joy_r_y = joy_r_y;
            }
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