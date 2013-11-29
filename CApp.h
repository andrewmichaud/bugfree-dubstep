#ifndef _CAPP_H_
    #define _CAPP_H_

// Header file for main app
// Andrew Michaud
// 11/28/13

#include <SDL/SDL.h>
#include "CAnimation.h"
#include "CEvent.h"
#include "CSurface.h"

class CApp : public CEvent {

    private:
        bool            Running;
        
        SDL_Surface*    Surf_Display;
        
        SDL_Surface*    Surf_Test;
    
        CAnimation      Anim_Yoshi;

    public:
 
        CApp();
 
        int OnExecute();
 
    public:

        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();

};
 
#endif
