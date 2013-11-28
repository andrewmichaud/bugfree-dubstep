#ifndef CSURFACE_H
#define CSURFACE_H 1

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// Header file for surface handling code
// Andrew Michaud
// 11/28/13

class CSurface {
    public:
        CSurface();

    public:
        static SDL_Surface* OnLoad(char* File);
        
        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, 
                           int X, int Y);

        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, 
                           int X, int Y, int X2, int Y2, int W, int H);
};

#endif // CSURFACE_H defined
