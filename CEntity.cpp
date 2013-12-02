// Implementation file for CEntitys
//
// Andrew Michaud
// 12/02/13

#include "CEntity.h"

// List of all our entities.
std::vector<CEntity*> CEntity::EntityList;

// CEntity constructor.
CEntity::CEntity() {
    Surf_Entity = NULL;

    X = Y = 0.0f;

    Width = Height = 0;

    AnimState = 0;
}

CEntity::~CEntity() {
}

// What to do on load.
bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    
    // Error checking
    if ((Surf_Entity = CSurface::OnLoad(File)) == NULL) {
        return false;
    }

    // Creating a transparent surface.
    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    // Set width and height
    this->Width = Width;
    this->Height = Height;

    // Set MaxFrames
    Anim_Control.MaxFrames = MaxFrames;

    // Loading worked
    return true;
}

// On looping, animate.
void CEntity::OnLoop() {
    Anim_Control.OnAnimate();
}

// On Rendering
void CEntity::OnRender(SDL_Surface* Surf_Display) {
    
    // Detect errors
    if (Surf_Entity == NULL || Surf_Display == NULL) {
        return;
    }

    // Call OnDraw
    CSurface::OnDraw(Surf_Display, Surf_Entity, X, Y, 
                     AnimState * Width, 
                     Anim_Control.GetCurrentFrame() * Height, 
                     Width,
                     Height);
}

void CEntity::OnCleanup() {
    
    // Free Surf_Entity if non-null
    if (Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}

