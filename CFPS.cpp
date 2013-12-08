// Andrew Michaud
// CFPS implementation file
// 12/05/13

#include "CFPS.h"

CFPS CFPS::FPSControl;

CFPS::CFPS() {
    OldTime     = 0;
    LastTime    = 0;

    SpeedFactor = 0;

    Frames      = 0;
    NumFrames   = 0;
}


// Function that does stuff in loop
void CFPS::OnLoop() {

    // Check if a second has passed
    if (OldTime + 1000 < SDL_GetTicks()) {
        OldTime = SDL_GetTicks();

        NumFrames = Frames;

        Frames = 0;
    }

    SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;

    LastTime = SDL_GetTicks();

    Frames++;
}

// Get FPS
unsigned CFPS::GetFPS() { 
    return NumFrames;
}

// Get SpeedFactor
float CFPS::GetSpeedFactor() {
    return SpeedFactor;
}

