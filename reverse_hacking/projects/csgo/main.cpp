#include "csgo.h"


int main(int, char**)
{
    CSGO csgo;
    if (!csgo.init())
    {
        return 1;
    }

    csgo.run();
    return 0;
}

