// Andrew Michaud
// Camera header file
// 12/05/13

#ifndef CCAMERA_H
#define CCAMERA_H 1

#include <SDL/SDL.h>

#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera {
    public:
        static CCamera CameraControl;

    private:
        int X;
        int Y;

        int* TargetX;
        int* TargetY;

    public:
        int TargetMode;

        CCamera();

        void OnMove(int MoveX, int MoveY);
        
        int GetX();
        int GetY();

        void SetPos(int posX, int posY);
        
        void SetTarget(int* targetX, int* targetY);
};

#endif // CCAMERA_H defined

