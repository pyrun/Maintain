#include "input.h"

input::input() {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            p_keyIsDown[i] = false;
}

input::~input()
{
    //dtor
}
