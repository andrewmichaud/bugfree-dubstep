#ifndef CSURFACE_H
#define CSURFACE_H 1

#include <SDL/SDL.h>

class CSurface {
    public:
        CSurface();

    public:
        static SDL_Surface* OnLoad(char* File);
        
        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, 
                           int X, int Y);
};

#endif // CSURFACE_H defined
