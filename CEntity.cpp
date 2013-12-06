// Implementation file for CEntitys
//
// Andrew Michaud
// 12/02/13

#include "CEntity.h"

// List of all our entities.
std::vector<CEntity*> CEntity::EntityList;

std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() {
    this->EntityA = NULL;
    this->EntityB = NULL;
}

// CEntity constructor.
CEntity::CEntity() {
    Surf_Entity = NULL;

    X = 0;
    Y = 0;

    Width = Height = 0;
    
    // Entities are not moving by default
    MoveLeft = false;
    MoveRight = false;

    // Entities default to generic, not dead, and affected by gravity.
    Type = ENTITY_TYPE_GENERIC;
    Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;

    // Speed and acceleration are zero.
    SpeedX = 0;
    SpeedY = 0;

    AccelX = 0;
    AccelY = 0;

    MaxSpeedX = 5;
    MaxSpeedY = 5;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

    Col_X = 0;
    Col_Y = 0;

    Col_Width = 0;
    Col_Height = 0;

    CanJump = false;

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
    
    // Moving left
    if (MoveLeft) {
        AccelX = -0.5;
    
    // Moving Right
    } else if (MoveRight) {
        AccelX = 0.5;
    
    // Not moving
    } else { 
        StopMove();
    }

    // Check gravity
    if (Flags & ENTITY_FLAG_GRAVITY) {
        AccelY = 0.75f;
    }

    // Apply speed changes.
    SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
    SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

    // Bounds checking on speed.
    if (SpeedX >  MaxSpeedX) SpeedX =  MaxSpeedX;
    if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
    if (SpeedY >  MaxSpeedY) SpeedY =  MaxSpeedY;
    if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

    // Animate
    OnAnimate();

    // Move
    OnMove(SpeedX, SpeedY);
}

// On Rendering
void CEntity::OnRender(SDL_Surface* Surf_Display) {
    
    // Detect errors
    if (Surf_Entity == NULL || Surf_Display == NULL) {
        return;
    }

    float drawX = X - CCamera::CameraControl.GetX();
    float drawY = Y - CCamera::CameraControl.GetY();
    float drawW = CurrentFrameCol * Width;
    float drawH = (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height;
    
    // Call OnDraw
    // Take into account where the camera is.
    CSurface::OnDraw(Surf_Display, Surf_Entity, 
                     drawX, drawY, drawW, drawH,
                     Width, Height);
}

void CEntity::OnCleanup() {
    
    // Free Surf_Entity if non-null
    if (Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}

// Handle animation
void CEntity::OnAnimate() {

    // Left
    if (MoveLeft) {
        CurrentFrameCol = 0;
    
    // Right
    } else if (MoveRight) {
        CurrentFrameCol = 1;
    }

    // Let Anim_Control do its thing
    Anim_Control.OnAnimate();
}

// Handle collisions.
// Overridden on a per-entity basis
bool CEntity::OnCollision(CEntity* Entity) {
}

// Handle movement
void CEntity::OnMove(float MoveX, float MoveY) {

    CanJump = false;

    // Not moving is pretty simple
    if (MoveX == 0 && MoveY == 0) {
        return;
    }

    // Otherwise moving is complicated. Prepare variables.
    double NewX = 0;
    double NewY = 0;

    // Take speed factor into account.
    MoveX *= CFPS::FPSControl.GetSpeedFactor();
    MoveY *= CFPS::FPSControl.GetSpeedFactor();

    // Handle X movement
    if (MoveX != 0) {
        
        // Move right or none.
        if (MoveX >= 0) {
            NewX =  CFPS::FPSControl.GetSpeedFactor();
        // Move left
        } else {
            NewX = -CFPS::FPSControl.GetSpeedFactor();
        }
    }

    // Handle Y movement
    if (MoveY != 0) {
        
        // Move right or none.
        if (MoveY >= 0) {
            NewY =  CFPS::FPSControl.GetSpeedFactor();
        // Move left
        } else {
            NewY = -CFPS::FPSControl.GetSpeedFactor();
        }
    }

    // Actually move.
    while (true) {

        // Ghosts don't need to worry about collisions.
        if (Flags & ENTITY_FLAG_GHOST) {
            int checkX = (int) (X + NewX);
            int checkY = (int) (Y + NewY);
            
            // We still need to tell other entities we are moving.
            PosValid(checkX, checkY);

            // Move
            X += NewX;
            Y += NewY;

        // Otherwise we need to check collisions.
        } else {
            
            // Check X
            // Move if we can.
            if (PosValid((int)(X + NewX), (int)(Y))) {
                X += NewX;
            
            // Stop if we can't.
            } else {
                SpeedX = 0;
            }

            // Check Y
            // Move if we can.
            if (PosValid((int)(X), (int)(Y + NewY))) {
                Y += NewY;
            
            // Stop if we can't.
            } else {

                // Jumping
                if (MoveY > 0) {
                    CanJump = true;
                }

                SpeedY = 0;
            }
        }

        // Take away however far we moved from the total distance we were
        // supposed to move.
        MoveX -= NewX;
        MoveY -= NewY;

        // Bounds checking
        if ((NewX > 0 && MoveX <= 0) ||
            (NewX < 0 && MoveX >= 0)) {
            NewX = 0;
        }

        if ((NewY > 0 && MoveY <= 0) ||
            (NewY < 0 && MoveY >= 0)) {
            NewY = 0;
        }

        // We don't need to move any farther if we moved how far we were
        // supposed to move.
        if (MoveX == 0) {
            NewX = 0;
        }

        if (MoveY == 0) {
            NewY = 0;
        }

        // Break if we moved as far as we needed to or if we aren't going to
        // move any farther.
        if ((MoveX == 0 && MoveY == 0) ||
            (NewX  == 0 && NewY  == 0)) {
            break;
        }
    }
}

// Cause player to jump
bool CEntity::Jump() {

    // Only jump if we can
    if (!CanJump) {
        return false;
    }

    SpeedY = -MaxSpeedY;

    return true;
}

// Stop movement
void CEntity::StopMove() {
    
    // If speed is positive, apply negative acceleration.
    if (SpeedX > 0) {
        AccelX = -1;
    }

    // If speed is negative, apply positive acceleration.
    if (SpeedX < 0) {
        AccelX =  1;
    }

    // Bounds checkng of how slow we should be going until we stop.
    if (SpeedX < 2.0f && SpeedX > -2.0f) {
        AccelX = 0;
        SpeedX = 0;
    }
}

// Check if this entity is colliding with another entity.
bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    
    // Variables for the sides of the two bounding boxes of our two entities
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    // Our X and Y position, with the offset taken into account
    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;

    // Left sides of bounding boxes
    left1 = tX;
    left2 = oX;

    // Right sides
    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;

    // Top sides
    top1 = tY;
    top2 = oY;

    // Bottom sides
    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;

    // NOTE: Y increases downward in this coordinate system.
    // Do checks to see if we could possibly be colliding.  Check if any sides
    // are positioned such that the boxes can't be overlapping.
    if ((bottom1 < top2) ||
        (top1 > bottom2) ||
        (right1 < left2) ||
        (left1 > right2)) {
        return false;
    }

    // Return true if we can't rule out a collision.
    return true;
}

// Determines whether a collision has occured, and whether the position an
// entity wants to move to is valid.
bool CEntity::PosValid(int NewX, int NewY) {
    bool Return = true;

    // Start position
    int StartX      = (NewX + Col_X) / TILE_SIZE;
    int StartY      = (NewY + Col_Y) / TILE_SIZE;

    // End position (intended)
    int EndX        = ((NewX + Col_X) + Width - Col_Width - 1) / TILE_SIZE;
    int EndY        = ((NewY + Col_Y) + Height - Col_Height - 1) / TILE_SIZE;

    // Check all tiles between our start and end positions.
    for (int iY = StartY; iY <= EndY; iY++) {
        for (int iX = StartX; iX <= EndX; iX++) {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE,
                                                     iY * TILE_SIZE);
            // Return false if any tile is invalid
            if (!PosValidTile(Tile)) { 
                Return = false;
            }
        }
    }

    // Check collisions with entities, if we collide with entities.
    if (Flags & ENTITY_FLAG_MAPONLY) {
        // Do nothing
    } else {
        
        // Check all entities
        for (int i = 0; i != EntityList.size(); i++) {
            if (PosValidEntity(EntityList[i], NewX, NewY) == false) {
                Return = false;
            }
        }
    }

    return Return;
}

// Can a tile be moved over?
bool CEntity::PosValidTile(CTile* Tile) {

    // We can move over a null tile
    if (Tile == NULL) {
        return true;
    }

    // We cannot move over tiles of type TILE_TYPE_BLOCK
    if (Tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }

    return true;
}

// Are we colliding with any entity?
bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    
    // Check if the entity is us, null, or dead
    // Also check that we don't have the MAPONLY flag on.
    // If all checks pass, see if we're colliding.
    if (this != Entity && Entity != NULL && Entity->Dead == false &&
        Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->Collides(NewX + Col_X,
                         NewY + Col_Y,
                         Width - Col_Width - 1,
                         Height - Col_Height - 1)) {

        // Create entity collision queue
        CEntityCol EntityCol;

        // Push ourselves and the other Entity
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;

        // Position not valid
        return false;
    }

    // Position valid.
    return true;
}









