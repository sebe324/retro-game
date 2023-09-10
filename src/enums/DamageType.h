#ifndef DAMAGETYPE_H
#define DAMAGETYPE_H

enum DamageType{
    LIGHT,
    DARKNESS,
    EARTH,
    AIR,
    FIRE,
    WATER,
    PHYSIC,
    TRUE
};

const unsigned int DamageTypeColors[]=
{0xf6e58dff, 0x535c68ff, 0xa77b06ff, 0xc7eceeff, 0xeb4d4bff, 0x22a6b3ff,
0xffbe76ff, 0xffffffff
};
#endif // DAMAGETYPE_H
