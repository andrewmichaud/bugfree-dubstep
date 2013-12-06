// Andrew Michaud
// Implementation file for CPlayer
// 12/06/13

#include "CPlayer.h"

CPlayer::CPlayer() {
}

// Load function
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames) {

    // Error check
    if (!CEntity::OnLoad(File, Width, Height, MaxFrames)) {
        return false;
    }

    return true;
}

// Looping
void CPlayer::OnLoop() {
    
    // Just call Entity function
    CEntity::OnLoop();
}

// Rendering
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    
    // Just call Entity function
    CEntity::OnRender(Surf_Display);
}

// Cleaning up
void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
}

// Animation
void CPlayer::OnAnimate() {

    //Define animations here

    // Walking
    if (SpeedX != 0) {
        Anim_Control.MaxFrames = 8;

    // Standing still
    } else {
        Anim_Control.MaxFrames = 0;
    }

    CEntity::OnAnimate();
}

// Collisions
bool CPlayer::OnCollision(CEntity* Entity) {
    Jump();

    return true;
}

