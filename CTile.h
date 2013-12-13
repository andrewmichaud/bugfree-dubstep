// Andrew Michaud
// CTile header file
// 12/02/13

#ifndef CTILE_H
#define CTILE_H 1

#include "Define.h"

enum {
    TILE_TYPE_NONE = 0,

    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class CTile {
    public:
        int     TileID;
        int     TypeID;


    public:
        CTile();
};

#endif

