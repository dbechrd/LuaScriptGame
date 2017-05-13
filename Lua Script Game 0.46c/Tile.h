#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "SDL/SDL.h"
#include "Tilesheet.h"
#include "RenderEngine.h"
#include <vector>

class RenderEngine;

class Tile{
    private:
        RenderEngine *renderer;
        SDL_Rect rect;
        int sprite;
        Tilesheet *tileSheet;
    public:
        Tile(Tilesheet *new_tileSheet, int x, int y, int tileWidth, int tileHeight, int new_sprite);

        int X(){ return rect.x; }
        int Y(){ return rect.y; }

        int Sprite(){ return sprite; }
        void SetSprite( int tileSprite ){ sprite = tileSprite; }

        int CurrentFrame();

        int Delay();
        void SetDelay( int new_delay );

        int AnimFlag();
        void SetAnimFlag( int new_animFlag );

        void Update();
        int Draw();
};

#endif // TILE_H_INCLUDED
