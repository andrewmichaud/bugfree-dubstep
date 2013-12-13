#ifndef CENTITY_H
#define CENTITY_H 1

// Header file for CEntity
// Andrew Michaud
// 12/02/13

#include <vector>
#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"

// Indicate whether entity is player or not
enum {
    ENTITY_TYPE_GENERIC =0,

    ENTITY_TYPE_PLAYER
};

// Flags for gravity, ghost, etc.
enum {
    ENTITY_FLAG_NONE    = 0,

    ENTITY_FLAG_GRAVITY = 0x00000001,
    ENTITY_FLAG_GHOST   = 0x00000002,
    ENTITY_FLAG_MAPONLY = 0x00000004
};

class CEntity {
    public:
        static std::vector<CEntity*> EntityList;

    protected:
        CAnimation      Anim_Control;

        SDL_Surface*    Surf_Entity;

    public:

        // Position
        float           X;
        float           Y;

        // Size
        int             Width;
        int             Height;

        // Whether entity is moving
        bool            MoveLeft;
        bool            MoveRight;
        bool            MoveUp;
        bool            MoveDown;

        // Flags for player
        int             Type;

        bool            Dead;
        int             Flags;

    protected:

        // Speed
        float           SpeedX;
        float           SpeedY;

        // Acceleration
        float           AccelX;
        float           AccelY;

    public:

        float           MaxSpeedX;
        float           MaxSpeedY;

    protected:

        int             CurrentFrameCol;
        int             CurrentFrameRow;

        int             Col_X;
        int             Col_Y;
        int             Col_Width;
        int             Col_Height;

    protected:
        bool            CanJump;

    public: 
        bool            Jump();

    // Constructors, destructors
    public:
        CEntity();

        virtual ~CEntity();

    // Other methods
    public:
        virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        virtual void OnLoop();

        virtual void OnRender(SDL_Surface* Surf_Display);

        virtual void OnCleanup();

        virtual void OnAnimate();

        virtual bool OnCollision(CEntity* Entity);

        void         OnMove(float MoveX, float MoveY);

        void         StopMove();

        bool         Collides(int oX, int oY, int oW, int oH);

    private:
        bool         PosValid(int NewX, int NewY);

        bool         PosValidTile(CTile* Tile);

        bool         PosValidEntity(CEntity* Entity, int NewX, int NewY);

};

class CEntityCol {
    public:
        static std::vector<CEntityCol>  EntityColList;
    public:
        CEntity* EntityA;
        CEntity* EntityB;

    public:
        CEntityCol();

};

#endif // CENTITY_H defined.

