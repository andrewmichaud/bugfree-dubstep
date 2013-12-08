// Andrew Michaud
// Implementation file for CPlayer
// 12/06/13

#include "CPlayer.h"

CPlayer::CPlayer() {
    Surf_Entity = NULL;

    X = 0;
    Y = 0;

    Width = Height = 0;
    
    // Entities are not moving by default
    MoveLeft = false;
    MoveRight = false;
    MoveUp = false;
    MoveDown= false;

    // Entities default to generic, not dead, and affected by gravity.
    Type = ENTITY_TYPE_GENERIC;
    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;

    // Speed and acceleration are zero.
    SpeedX = 0;
    SpeedY = 0;

    AccelX = 0;
    AccelY = 0;

    MaxSpeedX = 10;
    MaxSpeedY = 10;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

    Col_X = 7;
    Col_Y = 0;

    Col_Width = 10;
    Col_Height = 0;

    CanJump = false;

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
bool CPlayer::OnCollision(CEntity* ) { //Entity) {
    return true;
}

