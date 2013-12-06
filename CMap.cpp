// Andrew Michaud
// CMap implementation file
// 12/05/13

#include "CMap.h"
#include <iostream>

CMap::CMap() {
    Surf_Tileset = NULL;
}

// Map loading functions.
// Populates Tile List

bool CMap::OnLoad(char* File) {
    TileList.clear();

    // Load file
    FILE* FileHandle = fopen(File, "r");

    // Error out if loading failed.
    if(FileHandle == NULL) {
        return false;
    }

    // Fill tileList
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        for (int X = 0; X < MAP_WIDTH; X++) {
            CTile tempTile;

            // Read in one tile
            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            // Add tile to list
            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "/n");
    }

    // Close file
    fclose(FileHandle);

    // We loaded properly, so return true
    return true;
}

// Render map
void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {

    // Error check
    if (Surf_Tileset == NULL) {
        return;
    }

    // Store tileset width and height
    int TilesetWidth = Surf_Tileset->w / TILE_SIZE;
    int TilesetHeight = Surf_Tileset->h / TILE_SIZE;
    //std::cout << "Got tileset dims" << std::endl;
    int ID = 0;

    // Draw tiles
    for (int Y = 0; Y < MAP_HEIGHT; Y++) {
        for (int X = 0; X < MAP_WIDTH; X++) {

            // Skip tiles that don't need to be rendered.
            if (TileList[ID].TypeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }

            // Set position
            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);

            int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

            // Draw
            CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, 
                             TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

            ID++;
        }
    }
    //std::cout << "Map rendering done" << std::endl;
}

// Get Tile from coordinates
CTile* CMap::GetTile(int X, int Y) {

    int ID = X / TILE_SIZE;
    ID += (MAP_WIDTH * (Y / TILE_SIZE));

    // Bounds checking
    if (ID < 0 && ID >= TileList.size()) {
        return NULL;
    }

    return &TileList[ID];
}

