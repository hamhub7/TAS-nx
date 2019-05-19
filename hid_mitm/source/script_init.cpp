#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <switch.h>

#include "script_init.hpp"

int scriptLength = 47;
std::vector<struct controlMsg> script(scriptLength);

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

    nutClip();
}