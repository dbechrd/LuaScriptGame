#include <string>
#include <iostream>
#include <fstream>
#include "SDL/SDL.h"
#include "Objsheet.h"
#include "RenderEngine.h"
#include "AnimationData.h"

Objsheet::Objsheet()
{
    renderer = RenderEngine::Instance();

}

Objsheet::~Objsheet()
{
    for( int i = objs.size(); i >= 0; i-- )
    {
        delete objs[i];
    }
    objs.clear();

    for( int j = objAnims.size(); j >= 0; j-- )
    {
        delete objAnims[j];
    }
    objAnims.clear();
}

int Objsheet::Load( const std::string &filename, int frameWidth, int frameHeight )
{
    ////////////////////////////////////////////////////////////////////////////////////
    //Load Animation Data Stream

    std::string objSheetFilename;

    std::ifstream animDataStream( filename.c_str() );

    if( animDataStream == NULL )
    {
        std::cout << "Object Animation Data Error" << std::endl;
    }
    animDataStream >> objSheetFilename;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load objsheet surface

    surface = renderer->LoadSurface( objSheetFilename );
    rect = surface->clip_rect;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Animation Data

    animDataStream >> objSprites;
    animDataStream >> objFrames;

    int spriteNumber;
    int startFrame;
    int totalFrames;
    int delay;
    int animFlag;
    std::string name;

    for( int i = 0; i < objSprites; i++ )
    {
        animDataStream >> spriteNumber;
        animDataStream >> startFrame;
        animDataStream >> totalFrames;
        animDataStream >> delay;
        animDataStream >> animFlag;
        animDataStream >> name;
        objAnims.push_back( new AnimationData( spriteNumber, startFrame, totalFrames, delay, animFlag ) );
    }
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Rects

    int objNumber = 0;

    for( int j = 0; j < (rect.h / frameHeight); j++ )
    {
        for( int k = 0; k < (rect.w / frameWidth); k++ )
        {
            objs.push_back( new SDL_Rect );
            objs[objNumber]->x = k * frameWidth;
            objs[objNumber]->y = j * frameHeight;
            objs[objNumber]->w = frameWidth;
            objs[objNumber]->h = frameHeight;
            objNumber++;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////

    return objSprites;
}

SDL_Surface *Objsheet::GetSurface()
{
    return surface;
}

SDL_Rect *Objsheet::GetRect( int currentFrame )
{
    return objs[currentFrame];
}

/*int Tilesheet::GetStartFrame( int sprite )
{
    int startFrame = tileAnims[sprite]->StartFrame();
    return startFrame;
}

int Tilesheet::GetNextFrame( int sprite, int currentFrame )
{
    int nextFrame = tileAnims[sprite]->NextFrame( currentFrame );
    return nextFrame;
}*/
