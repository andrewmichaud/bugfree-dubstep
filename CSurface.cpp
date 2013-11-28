#include "CSurface.h"

CSurface::CSurface() {
}

SDL_Surface* CSurface::OnLoad(char* File) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    // Load surface
    if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }

    // Get a new surface.
    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    
    // Free old one.
    SDL_FreeSurface(Surf_Temp);

    // Return
    return Surf_Return;
}

// On draw, do this.
// Take:
// Destination surface
// Source surface (surface we use to draw on destinatino)
// X and Y position we are drawing to
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    
    // Is our surface valid?
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    // Assign coordinates to destinatino surface
    DestR.x = X;
    DestR.y = Y;

    // Draw image on.
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

