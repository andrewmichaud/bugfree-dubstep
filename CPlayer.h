// Andrew Michaud
// Header file for player - special kind of entity
// 12/06/13

#ifndef CPLAYER_H
#define CPLAYER_H 1

#include "CEntity.h"

class CPlayer : public CEntity {
    public:
        CPlayer();

        bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        void OnCollision(CEntity* Entity);
};


#endif // CPLAYER_H defined

