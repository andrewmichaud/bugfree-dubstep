// Andrew Michaud
// Header file for map class
// 12/05/13

#ifndef CMAP_HPP
#define CMAP_HPP 1

#include <SDL/SDL.h>
#include <vector>

#include "CTile.hpp"
#include "CSurface.hpp"

class CMap {
    public:
        SDL_Surface* Surf_Tileset;

    private:
        std::vector<CTile> TileList;

    public:
        CMap();

    public:
        bool OnLoad(char* File);

        void OnRender(SDL_Surface* Surf_Display,
                      int MapX, int MapY);

        CTile* GetTile(int X, int Y);
};
#endif // CMAP_HPP defined

