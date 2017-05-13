#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include <vector>
#include <string>

#include "SDL/SDL.h"

#include "Tile.h"
#include "Tilesheet.h"

class Layer{
    private:
        int levelWidth;
        int levelHeight;

        int tileWidth;
        int tileHeight;

        std::vector< std::vector<Tile*> > tileData;
        SDL_Rect *camera;
    public:
		bool visible;

        Layer( int lWidth, int lHeight, int tWidth, int tHeight );
        ~Layer();

        int AddTile( int x, int y, Tile *tile = NULL );

        int GetSprite( int x, int y );
        void SetSprite( int x, int y, int tileSprite );
        int GetX( int x, int y );
        int GetY( int x, int y );

        void Update();
        int DrawSprite( int x, int y );
        int Draw();
};

#endif // LAYER_H_INCLUDED
