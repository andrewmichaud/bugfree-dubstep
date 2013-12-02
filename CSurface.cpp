#include "CSurface.h"

// Surface handling code, implementation file
// Andrew Michaud
// 11/28/13

CSurface::CSurface() {
}

SDL_Surface* CSurface::OnLoad(char* File) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    // Load surface
    if ((Surf_Temp = IMG_Load(File)) == NULL) {
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

// Second draw function, used to draw only part of an image.
// Do this
// Take:
// Destination surface
// Source surface (surface we use to draw on destinatino)
// X and Y position we are drawing to
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y,
                      int X2, int Y2, int W, int H) {
    
    // Is our surface valid?
    if (Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    // Assign coordinates to destination surface
    DestR.x = X;
    DestR.y = Y;

    // Draw rectangle specifying which part of the source image we are drawing
    SDL_Rect SrcR;

    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    // Draw image on.
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}

// Transparent surface.  We can make any color transparent.
bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
    
    // Error check
    if (Surf_Dest == NULL) {
        return false;
    }

    // Apply color key.
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY |SDL_RLEACCEL, 
                    SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}
