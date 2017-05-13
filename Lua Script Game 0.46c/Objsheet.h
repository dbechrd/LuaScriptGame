#ifndef OBJSHEET_H_INCLUDED
#define OBJSHEET_H_INCLUDED

#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "AnimationData.h"
#include "RenderEngine.h"

class RenderEngine;

class Objsheet{
    private:
        RenderEngine *renderer;
        SDL_Surface *surface;
        SDL_Rect rect;
        int objSprites;
        int objFrames;
        std::vector<SDL_Rect*> objs;
    public:
        //Tile animations
        std::vector<AnimationData*> objAnims;

        Objsheet();
        ~Objsheet();
        int Load( const std::string &filename, int frameWidth, int frameHeight );
        SDL_Surface *GetSurface();
        SDL_Rect *GetRect( int currentFrame );
        //int GetStartFrame( int sprite );
        //int GetNextFrame( int sprite, int currentFrame );
};

#endif // OBJSHEET_H_INCLUDED
