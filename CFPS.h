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
        unsigned    OldTime;
        unsigned    LastTime;

        float	    SpeedFactor;

        unsigned    NumFrames;
        unsigned    Frames;

    public:
        CFPS();

        void	    OnLoop();

    public:
        unsigned    GetFPS();

        float	    GetSpeedFactor();
};

#endif // CFPS_H defined

