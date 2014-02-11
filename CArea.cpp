// Andrew Michaud
// CArea implementation file
// 12/05/13

#include "CArea.hpp"
#include <iostream>

CArea CArea::AreaControl;

// Constructor
CArea::CArea() {
    AreaSize = 0;
}

// Loading function
bool CArea::OnLoad(char* File) {
    
    //std::cout << "trying to load" << std::endl;
    // Clear MapList before we load.
    MapList.clear();

    // Open area file
    FILE* FileHandle = fopen(File, "r");

    // Error check
    if (FileHandle == NULL) {
        return false;
    }

    //std::cout << "ahve file" << std::endl;

    // Allocate space for TileSet
    char TilesetFile[255];

    fscanf(FileHandle, "%s\n", TilesetFile);

    // Attempt to load tileset.  Error out if this fails.
    if ((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
        //std::cout << TilesetFile << std::endl;
        fclose(FileHandle);

        return false;
    }

    //std::cout << "have tileset" << std::endl;

    // Load area
    fscanf(FileHandle, "%d\n", &AreaSize);

    //std::cout << "area loaede" << std::endl;
    // Fill MapList
    for (int X = 0; X < AreaSize; X++) {
        for (int Y = 0; Y < AreaSize; Y++) {
            char MapFile[255];

            fscanf(FileHandle, "%s ", MapFile);

            CMap tempMap;

            // Error check the map load
            if (tempMap.OnLoad(MapFile) == false) {
                fclose(FileHandle);

                return false;
            }

            tempMap.Surf_Tileset = Surf_Tileset;

            MapList.push_back(tempMap);
        }

        fscanf(FileHandle, "\n");

    }

    //std::cout << "tiles done" << std::endl;

    // Close file and successfully return.
    fclose(FileHandle);

    return true;
}

// Rendering function
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
    
    // Set map width and height
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    //std::cout << "CArea::OnRender:: vars done" << std::endl;
    // Set first ID
    int FirstID = -CameraX / MapWidth;
    FirstID += (-CameraY / MapHeight) * AreaSize;

    //std::cout << "areasize: " << AreaSize << std::endl;
    //std::cout << "CArea::OnRender:: first id" << std::endl;
    // Render maps
    // TODO: get rid of magic numbers sometime.
    for (int i = 0; i < 9; i++) {
        int ID = FirstID + ((i / 3) * AreaSize) + (i % 3);

        // Error checking
        if (ID < 0 || ID >= (int) MapList.size()) {
            continue;
        }

        // Set position
        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;
        //std::cout << "X: " << X << std::endl;
        //std::cout << "Y: " << Y << std::endl;
        // Render map
        MapList[ID].OnRender(Surf_Display, X, Y);
        //std::cout << "it: " << i << std::endl;
    }
    //std::cout << "CArea::OnRender:: maps done" << std::endl;
}

// Get Map by coordinates.
CMap* CArea::GetMap(int X, int Y) {
    
    // Get map height and width
    int MapWidth  = MAP_WIDTH  * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // Get ID
    int ID = X / MapWidth;
    ID += ((Y / MapHeight) * AreaSize);

    // Bounds checking
    if (ID < 0 || ID >= (int) MapList.size()) {
        return NULL;
    }

    return &MapList[ID];
}

// Get Tile by coordinates
CTile* CArea::GetTile(int X, int Y) {

    // Get map width and height
    int MapWidth  = MAP_WIDTH  * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // Map
    CMap* Map = GetMap(X, Y);

    // Error check
    if (Map == NULL) {
        return NULL;
    }

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

// Cleanup function
void CArea::OnCleanup() { 

    //Free surfaces
    if (Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    }

    MapList.clear();
}

