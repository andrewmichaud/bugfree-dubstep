#include "CApp.h"

// Implementation file for main app
// Andrew Michaud
// 11/28/13

CApp::CApp() {
    
    // Keep things tidy by initializing this pointer to null
    Surf_Display = NULL;

    Surf_Test = NULL;
    
    // We are running
    Running = true;
}
 
bool CApp::OnInit() {
    
    // Animation stuff
    Anim_Yoshi.MaxFrames = 8;
    Anim_Yoshi.Oscillate = false;
    
    // Attempt to init SDL. If it fails, return false.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    // Create window and surface. 
    // Params:
    // Width
    // Height
    // Bit resolution
    // Display flags
    // First: Use hardware memory to store stuff.
    // Second: Use double buffering
    // Note: SDL_FULLSCREEN to force fullscreen
    if ((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | 
                                                       SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

#if 0
    if ((Surf_Test = CSurface::OnLoad("femplayermap.png")) == NULL) {
        return false;
    }
#endif

#if 0
    char* ent1 = "entity1.bmp".c_str();
    char* ent2 = "entity2.bmp".c_str();
    #endif

    // Load entities
        

    // std::cout << "Here" << std::endl;
    // Load two entities
    if (Entity1.OnLoad("entity1.bmp", 64, 64, 8) == false) {
        return false;
    }

    if (Entity2.OnLoad("entity2.bmp", 64, 64, 8) == false) {
        return false;
    }

    Entity2.X = 100;

    // Create players.
    if (!Player.OnLoad("yoshi.png", 64, 64, 8)) {
        return false;
    }

    if (!Player2.OnLoad("yoshi.png", 64, 64, 8)) {
        return false;
    }

    Player2.X = 100;

    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Player2);


    // Make cameras follow yoshi
    CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    //std::cout << "ssssss" << std::endl;
    //  Init area
    if (CArea::AreaControl.OnLoad("maps/1.area") == false) {
        //std::cout << "false" << std::endl;
        return false;
    }

    //std::cout << "asfas" << std::endl;

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    //std::cout << "init done" << std::endl;
    return true;
}

// What to do with events.
void CApp::OnEvent(SDL_Event* Event) {
    
    // Pass to CEvent class
    CEvent::OnEvent(Event);
#if 0
    // Handle quitting.
    // Look for this thing and end program if we see it.
    if (Event->type == SDL_QUIT) {
        Running = false;
    }
#endif
}

void CApp::OnExit() {
    Running = false;
}

// Handle keypresses
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch (sym) {
        // Camera follows player, this is unneeded when movement works.
        case SDLK_UP:       
            break;
        case SDLK_DOWN:
            break;
        case SDLK_LEFT:
            Player.MoveLeft = true; 
            break;
        case SDLK_RIGHT:
            Player.MoveRight = true;
            break;
        case SDLK_SPACE:
            Player.Jump();
            break;
        default:
            break;
    }
}

// Handle keyunpresses
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch (sym) {
        // Camera follows player, this is unneeded when movement works.
        case SDLK_UP:       
            break;
        case SDLK_DOWN:
            break;
        case SDLK_LEFT:
            Player.MoveLeft = false; 
            break;
        case SDLK_RIGHT:
            Player.MoveRight = false;
            break;
        default:
            break;
    }
}

void CApp::OnLoop() {
    // For animation
    Anim_Yoshi.OnAnimate();
    CFPS::FPSControl.OnLoop();
    // Animate all entities.
    for (unsigned i = 0; i < CEntity::EntityList.size(); i++) {

        if (!CEntity::EntityList[i]) {
            continue;
        }

        CEntity::EntityList[i]->OnLoop();
    }

    // Collision Events
    for (unsigned i = 0; i != CEntityCol::EntityColList.size(); i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

        // Check for null pointers
        if (EntityA == NULL || EntityB == NULL) {
            continue;
        }

        if (EntityA->OnCollision(EntityA)) {
            EntityB->OnCollision(EntityB);
        }
    }

    CEntityCol::EntityColList.clear();
}

void CApp::OnRender() {

    //int spriteheight = 64;
    // Draw
    //CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
#if 0
    CSurface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, 
                     Anim_Yoshi.GetCurrentFrame() * spriteheight, 64, spriteheight);

    std::cout << "sprite drawn" << std::endl;
#endif

#if 1
    // Draw all entities
    for (unsigned i = 0; i < CEntity::EntityList.size(); i++) {
     
        // Error checking
        if (!CEntity::EntityList[i]) {
            continue;
        }

        CEntity::EntityList[i]->OnRender(Surf_Display);
    }

    std::cout << "entities done" << std::endl;
#endif

    // Render area
    CArea::AreaControl.OnRender(Surf_Display,
                                -CCamera::CameraControl.GetX(),
                                -CCamera::CameraControl.GetY());

    //std::cout << "area done" << std::endl;
    // Refresh the buffer.
    SDL_Flip(Surf_Display);

    //std::cout << "render done" << std::endl;

}



// Cleanup function
void CApp::OnCleanup() {
    
    // Free surfaces
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    
    // Clean up Entities
    for (unsigned i = 0; i < CEntity::EntityList.size(); i++) {

        // Error checking
        if (!CEntity::EntityList[i]) {
            continue;
        }

        CEntity::EntityList[i]->OnCleanup();
    }

    CEntity::EntityList.clear();
    
    // Clean area
    CArea::AreaControl.OnCleanup();

    // Just quit
    SDL_Quit();
}
 
int CApp::OnExecute() {
    
    // Attempt to initialize. If this fails, return an error code and exit.
    if (!OnInit()) {
        return -1;
    }

    SDL_Event Event;

    // Game loop
    while (Running) {

        // Wait for events and pass them onto OnEvent
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        // Move on to moving data around.
        OnLoop();

        // Render game.
        OnRender();
    }

    // Cleanup before we exit.
    OnCleanup();

    return 0;
}

int main() {
    CApp theApp;
 
    return theApp.OnExecute();
}
