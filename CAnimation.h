// Animation header file
// Andrew Michaud
// 11/29/13

#ifndef CANIMATION_H
#define CANIMATION_H 1

#include <SDL/SDL.h>

class CAnimation {
    private:
        unsigned int CurrentFrame;

        int FrameInc;

    private:
        unsigned int FrameRate; // in milliseconds

        unsigned long OldTime;

    public:
        unsigned int MaxFrames;

        bool Oscillate;

    public:
        CAnimation();

        void OnAnimate();

    public:
        void SetFrameRate(unsigned int Rate);

        void SetCurrentFrame(unsigned int Frame);

        unsigned int GetCurrentFrame();
};

#endif // CANIMATION_H defined
