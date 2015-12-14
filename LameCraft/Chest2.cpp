#include "Chest2.h"


Chest::Chest(int x, int y,  int z)
{
    for(char i = 0; i < 27; i++)
    {
        chestSlotId[i] = -1;
        chestSlotAm[i] = -1;
        chestSlotSt[i] = 0;
    }

    chestAddress = x + y * 176 + z * 176 * 112;
}

Chest::~Chest()
{

}

