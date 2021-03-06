// Andrew Michaud
// Camera header file
// 12/05/13

#ifndef CCAMERA_HPP
#define CCAMERA_HPP 1

#include <SDL/SDL.h>

#include "Define.hpp"

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

        float* TargetX;
        float* TargetY;

    public:
        int TargetMode;

        CCamera();

        void OnMove(int MoveX, int MoveY);
        
        int GetX();
        int GetY();

        void SetPos(int posX, int posY);
        
        void SetTarget(float* targetX, float* targetY);
};

#endif // CCAMERA_HPP defined

