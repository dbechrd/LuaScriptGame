#ifndef TILESHEET_H_INCLUDED
#define TILESHEET_H_INCLUDED

#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "AnimationData.h"
#include "RenderEngine.h"

class RenderEngine;

class Tilesheet{
    private:
        RenderEngine *renderer;
        SDL_Surface *surface;
        SDL_Rect rect;
        int tileSprites;
        int tileFrames;
        std::vector<SDL_Rect*> tileRects;
        std::map<int, bool> tileCol;
        std::map<int, bool>::iterator iterCol;
        std::map<int, AnimationData*> tileAnims;
        std::map<int, AnimationData*>::iterator iterAnims;
    public:
        Tilesheet();
        ~Tilesheet();
        int Load( const std::string &filename, int frameWidth, int frameHeight );
        SDL_Surface *GetSurface();
        SDL_Rect *GetRect( int currentFrame );
        bool GetCollide( int tileType );
        AnimationData *GetAnimData( int tileType );
        //int GetStartFrame( int sprite );
        //int GetNextFrame( int sprite, int currentFrame );
};

#endif // TILESHEET_H_INCLUDED
