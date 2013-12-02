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
    if ((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | 
                                                       SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if ((Surf_Test = CSurface::OnLoad("femplayermap.png")) == NULL) {
        return false;
    }

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

void CApp::OnLoop() {
    // For animatino
    Anim_Yoshi.OnAnimate();
}

void CApp::OnRender() {

    int spriteheight = 128;
    // Draw
    //CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
    CSurface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, 
                     Anim_Yoshi.GetCurrentFrame() * spriteheight, 64, spriteheight);

    // Refresh the buffer.
    SDL_Flip(Surf_Display);

}



// Cleanup function
void CApp::OnCleanup() {
    
    // Free surfaces
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    
    
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

int main(int argc, char* argv[]) {
    CApp theApp;
 
    return theApp.OnExecute();
}
