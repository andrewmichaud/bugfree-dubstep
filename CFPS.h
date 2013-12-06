// Andrew Michaud
// FPS header file
// 12/05/13

#ifndef CFPS_H
#define CFPS_H 1

#include <SDL/SDL.h>

class CFPS {
    public:
        static CFPS FPSControl;

    private:
        int     OldTime;
        int     LastTime;

        float   SpeedFactor;

        int     NumFrames;
        int     Frames;

    public:
        CFPS();

        void    OnLoop();

    public:
        int     GetFPS();

        float   GetSpeedFactor();
};

#endif // CFPS_H defined

