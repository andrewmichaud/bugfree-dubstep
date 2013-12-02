// Implementation code for animation
// Andrew Michaud
// 11/29/13

#include "CAnimation.h"

// Constructor
CAnimation::CAnimation() {
    CurrentFrame  = 0;
    MaxFrames     = 0;
    FrameInc      = 1;

    FrameRate     = 100; // Milliseconds
    OldTime       = 0;

    Oscillate     = false;
}

// What to do on animate
void CAnimation::OnAnimate() {
    
    // Use this to check if one second has passed yet.
    // If it has, we increment the frame.
    if (OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    // Set OldTime
    OldTime = SDL_GetTicks();

    // Increment currentFrame
    CurrentFrame += FrameInc;

    // If oscillate is set, we animate to the highest frame and then back again
    if (Oscillate) {

        // If frameInc is positive we can just change frameInc
        if (FrameInc > 0) {

            // If we're past MaxFrames, reverse FrameInc
            if (CurrentFrame >= MaxFrames) {
                FrameInc = -FrameInc;
            }
        } else {

            // Negate FrameInc again if we've gone to or below the 0th frame.
            if (CurrentFrame <= 0) {
                FrameInc = -FrameInc;
            }
        }
    
    // If we aren't oscillating, return to zero when we hit the max frame
    } else {
        
        if (CurrentFrame >= MaxFrames) {
            CurrentFrame = 0;
        }
    }
}

// Simple setter
void CAnimation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}

// Simple setter
void CAnimation::SetCurrentFrame(int Frame) {
    
    // Bounds checking
    if (Frame < 0 || Frame >= MaxFrames) {
        return;
    }

    CurrentFrame = Frame;
}

// Simple getter
int CAnimation::GetCurrentFrame() {
    return CurrentFrame;
}

