#ifndef _CAPP_H_
    #define _CAPP_H_

// Header file for main app
// Andrew Michaud
// 11/28/13

#include <string>

#include <SDL/SDL.h>
#include "CAnimation.hpp"
#include "CEvent.hpp"
#include "CSurface.hpp"
#include "CEntity.hpp"
#include "CArea.hpp"
#include "CCamera.hpp"
#include "CPlayer.hpp"

#include "Define.hpp"

class CApp : public CEvent {

    private:
        bool            Running;
        
        SDL_Surface*    Surf_Display;
        
        SDL_Surface*    Surf_Test;
    
        CAnimation      Anim_Player;

        CEntity         Entity1;
        CEntity         Entity2;

        CPlayer         Player;
        CPlayer         Player2;

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

        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
};
 
#endif
