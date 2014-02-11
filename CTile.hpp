// Andrew Michaud
// CTile header file
// 12/02/13

#ifndef CTILE_HPP
#define CTILE_HPP 1

#include "Define.hpp"

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

#endif // CTILE_HPP defined.

