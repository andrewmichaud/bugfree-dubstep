#include "CApp.h"

CApp::CApp() {
    
    // Keep things tidy by initializing this pointer to null
    Surf_Display = NULL;

    Surf_Test = NULL;
    
    // We are running
    Running = true;
}
 
bool CApp::OnInit() {
    
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

    if ((Surf_Test = CSurface::OnLoad("smile.bmp")) == NULL) {
        return false;
    }

    return true;
}

// What to do with events.
void CApp::OnEvent(SDL_Event* Event) {
    
    // Handle quitting.
    // Look for this thing and end program if we see it.
    if (Event->type == SDL_QUIT) {
        Running = false;
    }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {

    // Draw
    CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);

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
