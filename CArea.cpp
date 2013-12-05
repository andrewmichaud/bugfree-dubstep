// Andrew Michaud
// CArea implementation file
// 12/05/13

#include "CArea.h"

CArea CArea::AreaControl;

// Constructor
CArea::CArea() {
    AreaSize = 0;
}

// Loading function
bool CArea::OnLoad(char* File) {
    
    // Clear MapList before we load.
    MapList.clear();

    // Open area file
    FILE* FileHandle = fopen(File, "r");

    // Error check
    if (FileHandle == NULL) {
        return false;
    }

    // Allocate space for TileSet
    char TilesetFile[255];

    fscanf(FileHandle, "%s\n", TilesetFile);

    // Attempt to file tileset.  Error out if this fails.
    if ((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
        fclose(FileHandle);

        return false;
    }

    // Load area
    fscanf(FileHandle, "%d\n", &AreaSize);

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

        scanf(FileHandle, "\n");

    }

    // Close file and successfully return.
    fclose(FileHandle);

    return true;
}

// Rendering function
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
    
    // Set map width and height
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    // Set first ID
    int FirstID = -CameraX / MapWidth;
    FirstID += (-CameraY / MapHeight) * AreaSize;

    // Render maps
    // TODO: get rid of magic numbers sometime.
    for (int i = 0; i < 4; i++) {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        // Error checking
        if (ID < 0 || ID >= MapList.size()) {
            continue;
        }

        // Set position
        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

        // Render map
        MapList[ID].OnRender(Surf_Display, X, Y);
    }
}

// Cleanup function
void CArea::OnCleanup() { 

    //Free surfaces
    if (Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    }

    MapList.clear();
}

