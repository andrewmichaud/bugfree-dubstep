// Implementation file for events
// Andrew Michaud
// 11/28/13

#include "CEvent.hpp"

CEvent::CEvent() {
}

CEvent::~CEvent() {
    // Do nothing
}

// Handle events
void CEvent::OnEvent(SDL_Event* Event) {
    
    // Switch on event type
    switch(Event->type) {

        // If event is an active event
        case SDL_ACTIVEEVENT: {
            // Switch on event active state
            switch(Event->active.state) {

                // If event is mouse focus
                case SDL_APPMOUSEFOCUS: {
                    
                    // Do OnMouseFocus if we gained mouse focus                        
                    if ( Event->active.gain ) {
                        OnMouseFocus();

                    // Otherwise do this event
                    } else {
                        OnMouseBlur();
                    }

                    break;
                }

                // If App gained focus
                case SDL_APPINPUTFOCUS: {

                    // Do OnInputFocus if we gained focus
                    if ( Event->active.gain ) {
                        OnInputFocus();
                    
                    // Otherwise do OnInputBlur
                    } else {
                        OnInputBlur();
                    }
 
                    break;
                }

                // If the App just became active or not
                case SDL_APPACTIVE:    {

                    // Do OnRestore if we were restored.
                    if ( Event->active.gain ) {
                        OnRestore();
                    
                    // Otherwise do OnMinimize if we were minimized.
                    } else {
                        OnMinimize();
                    }
 
                    break;
                }
            }
            break;
        }
 
        // If a key was pressed, do the appropriate thing.
        case SDL_KEYDOWN: {

            // Call OnKeyDown with the keysym, the mod, and the unicode value
            OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod,
                      Event->key.keysym.unicode);
            break;
        }
 
        // Same for key unpress
        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod,
                    Event->key.keysym.unicode);
            break;
        }
 
        // Handle mouse motion
        case SDL_MOUSEMOTION: {

            // Pass through motion and whether or not buttons are clicked
            OnMouseMove(Event->motion.x, Event->motion.y, 
                        Event->motion.xrel,Event->motion.yrel,
                        (Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
                        (Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
                        (Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;
        }
 
        // Handle mouse button presses
        case SDL_MOUSEBUTTONDOWN: {
            
            // Switch on which button was pressed
            switch(Event->button.button) {

                // Do left things if left button was pressed
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }

                // Do right things if right button was pressed
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }

                // Middle things
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        // Do the same thing for right button presses
        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        // Handle joystick axis motion
        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
            break;
        }
 
        // Handle joystick ball motion
        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which, Event->jball.ball, 
                      Event->jball.xrel,Event->jball.yrel);
            break;
        }
 
        // Handle joystick hat motion
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }

        // Handle joystick button press
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        // Handle joystick button unpress
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        // Handle quitting
        case SDL_QUIT: {
            OnExit();
            break;
        }
 
        // Handle window manager event?
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
 
        // Handle resize events
        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }
 
        // Handle expose events.
        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }
 
        // Handle anything else
        default: {
            OnUser(Event->user.type, Event->user.code, 
                   Event->user.data1,Event->user.data2);
            break;
        }
    }
}
 
// What to do on input focus.
void CEvent::OnInputFocus() {
    //Pure virtual, do nothing
}
 
// What to do on input blur
void CEvent::OnInputBlur() {
    //Pure virtual, do nothing
}
 
// What to do on keypress
void CEvent::OnKeyDown(SDLKey, SDLMod, Uint16) {
    //Pure virtual, do nothing
}
 
// What to do on key unpress
void CEvent::OnKeyUp(SDLKey, SDLMod, Uint16) {
    //Pure virtual, do nothing
}
 
// What to do on mouse focus
void CEvent::OnMouseFocus() {
    //Pure virtual, do nothing
}
 
// What to do on mouse blur
void CEvent::OnMouseBlur() {
    //Pure virtual, do nothing
}
 
// What to do on mouse movement
void CEvent::OnMouseMove(int, int, int, int, 
                         bool, bool, bool) {
    //Pure virtual, do nothing
}
 
// Mouse wheel movement
void CEvent::OnMouseWheel(bool, bool) {
    //Pure virtual, do nothing
}
 
// L button press
void CEvent::OnLButtonDown(int, int) {
    //Pure virtual, do nothing
}
 
// L button unpress
void CEvent::OnLButtonUp(int, int) {
    //Pure virtual, do nothing
}
 
// R Button press
void CEvent::OnRButtonDown(int, int) {
    //Pure virtual, do nothing
}
 
// R Button unpress
void CEvent::OnRButtonUp(int, int) {
    //Pure virtual, do nothing
}
 
// M Button press
void CEvent::OnMButtonDown(int, int) {
    //Pure virtual, do nothing
}
 
// M Button unpress
void CEvent::OnMButtonUp(int, int) {
    //Pure virtual, do nothing
}
 
// Joystick axis movement
void CEvent::OnJoyAxis(Uint8, Uint8, Sint16) {
    //Pure virtual, do nothing
}
 
// Handle joystick button press
void CEvent::OnJoyButtonDown(Uint8, Uint8) {
    //Pure virtual, do nothing
}
 
// Handle joystick button unpress
void CEvent::OnJoyButtonUp(Uint8, Uint8) {
    //Pure virtual, do nothing
}
 
// Handle joystick hat press
void CEvent::OnJoyHat(Uint8, Uint8, Uint8) {
    //Pure virtual, do nothing
}
 
// Handle joystick ball movement
void CEvent::OnJoyBall(Uint8, Uint8, Sint16, Sint16) {
    //Pure virtual, do nothing
}
 
// Handle minimize
void CEvent::OnMinimize() {
    //Pure virtual, do nothing
}
 
// Handle restore
void CEvent::OnRestore() {
    //Pure virtual, do nothing
}
 
// Handle resize
void CEvent::OnResize(int, int) {
    //Pure virtual, do nothing
}
 
// Handle expose
void CEvent::OnExpose() {
    //Pure virtual, do nothing
}
 
// Handle exit
void CEvent::OnExit() {
    //Pure virtual, do nothing
}
 
// Handle other stuff
void CEvent::OnUser(Uint8, int, void*, void*) {
    //Pure virtual, do nothing
}
