// Andrew Michaud
// Camera implementation file
// 12/05/13

#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
    
    // Reset camera position
    X = Y = 0;

    // Reset camera target

    TargetX = TargetY = NULL;

    // Targetting mode.
    TargetMode = TARGET_MODE_NORMAL;
}

// Move camera
void CCamera::OnMove(int MoveX, int MoveY) {
   
    // Shift camera position
    X += MoveX;
    Y += MoveY;
}

// Get camera X pos
int CCamera::GetX() {

    // Return target X if camera is targetting
    if (TargetX != NULL) {
        
        // 
        if (TargetMode == TARGET_MODE_CENTER) {
            return *TargetX - (WWIDTH / 2);
        }

        return *TargetX;
    }

    return X;
}

// Get camera Y pos
int CCamera::GetY() {

    // Return target Y if camera is targetting
    if (TargetY != NULL) {
        
        // 
        if (TargetMode == TARGET_MODE_CENTER) {
            return *TargetY - (WHEIGHT / 2);
        }

        return *TargetY;
    }

    return Y;
}

// Set camera position
void CCamera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}

// Set camera target
void CCamera::SetTarget(int* X, int* Y) {
    TargetX = X;
    TargetY = Y;
}

