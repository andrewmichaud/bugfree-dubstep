// Animation header file
// Andrew Michaud
// 11/29/13

#ifndef CANIMATION_H
#define CANIMATION_H 1

#include <SDL/SDL.h>

class CAnimation {
    private:
        int CurrentFrame;

        int FrameInc;

    private:
        int FrameRate; // in milliseconds

        long OldTime;

    public:
        int MaxFrames;

        bool Oscillate;

    public:
        CAnimation();

        void OnAnimate();

    public:
        void SetFrameRate(int Rate);

        void SetCurrentFrame(int Frame);

        int GetCurrentFrame();
};

#endif // CANIMATION_H defined
