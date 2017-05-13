#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <vector>
#include <string>
#include "Tile.h"
#include "Layer.h"
#include "Tilesheet.h"
#include "Object.h"
#include "Camera.h"
#include "ObjectEngine.h"

class Tilesheet;

enum { layer_Floor, layer_Walls, layer_Roof, layer_Objects };

class Level{
    private:
        int levelWidth;
        int levelHeight;
        int levelLayers;
		std::vector<Layer*> layerData;

        int tileWidth;
        int tileHeight;
        int tileSprites;
        int tileColumn;
        int tileRow;
        int totalTiles;
        Tilesheet tileSheet;

        SDL_Rect *camera;

        ObjectEngine *objEngine;
        std::vector< std::vector<Object*> > objData;

        std::string mapFileName;
        std::string animDataFileName;
        std::string objDataFileName;

        int activeLayer;
    public:
        Level( const std::string &file_map );
        ~Level();

		int LevelWidth();
        int LevelHeight();
		int ToggleLayer( int layer );

        int TileWidth();
        int TileHeight();
        SDL_Surface *GetTileSheet();
        int GetTileNumber( int x, int y );
        SDL_Rect GetTileCoords( int x, int y );
        int SetTileSprite( int x, int y, int sprite );
        int GetTileSprite( int x, int y );
		int GetTileSprites(){ return tileSprites; }

        Object *GetObject( int x, int y );
        bool IsCollision( int x, int y );

        int Save();
		void Update();
        int Draw( int drawCode = 0 );
};

#endif // LEVEL_H_INCLUDED
