#include <string>
#include <iostream>
#include <fstream>
#include "SDL/SDL.h"
#include "Tilesheet.h"
#include "RenderEngine.h"
#include "AnimationData.h"

Tilesheet::Tilesheet()
{
    renderer = NULL;
    surface = NULL;

    renderer = RenderEngine::Instance();
}

Tilesheet::~Tilesheet()
{
    for( int i = tileRects.size(); i >= 0; i-- )
    {
        if( tileRects[i] != NULL ){
            delete tileRects[i];
            tileRects[i] = NULL;
        }
    }
    tileRects.clear();

    for( int j = tileAnims.size(); j >= 0; j-- )
    {
        if( tileAnims[j] != NULL ){
            delete tileAnims[j];
            tileAnims[j] = NULL;
        }
    }
    tileAnims.clear();
}

int Tilesheet::Load( const std::string &filename, int frameWidth, int frameHeight )
{
    ////////////////////////////////////////////////////////////////////////////////////
    //Load Animation Data Stream

    std::string tileSheetFilename;

    std::ifstream animDataStream( filename.c_str() );

    if( animDataStream == NULL )
    {
        std::cout << "Tile Animation Data Error" << std::endl;
    }
    animDataStream >> tileSheetFilename;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load tilesheet surface

    surface = renderer->LoadSurface( tileSheetFilename );
    rect = surface->clip_rect;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Animation Data

    animDataStream >> tileSprites;
    animDataStream >> tileFrames;

    int spriteNumber;
    int spriteCol;
    int startFrame;
    int totalFrames;
    int delay;
    int animFlag;

    for( int i = 0; i < tileSprites; i++ )
    {
        animDataStream >> spriteNumber;
        animDataStream >> spriteCol;
        animDataStream >> startFrame;
        animDataStream >> totalFrames;
        animDataStream >> delay;
        animDataStream >> animFlag;
        //tileAnims.push_back( new AnimationData( spriteNumber, startFrame, totalFrames, delay, animFlag ) );
        tileAnims[spriteNumber] = new AnimationData( startFrame, totalFrames, delay, animFlag );
        if( spriteCol == 1 ){
            tileCol[spriteNumber] = true;
        }else{
            tileCol[spriteNumber] = false;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Rects

    int tileNumber = 0;

    for( int j = 0; j < (rect.h / frameHeight); j++ )
    {
        for( int k = 0; k < (rect.w / frameWidth); k++ )
        {
            tileRects.push_back( new SDL_Rect );
            tileRects[tileNumber]->x = k * frameWidth;
            tileRects[tileNumber]->y = j * frameHeight;
            tileRects[tileNumber]->w = frameWidth;
            tileRects[tileNumber]->h = frameHeight;
            tileNumber++;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////

    return tileSprites;
}

SDL_Surface *Tilesheet::GetSurface()
{
    return surface;
}

SDL_Rect *Tilesheet::GetRect( int currentFrame )
{
    return tileRects[currentFrame];
}

bool Tilesheet::GetCollide( int tileType )
{
    iterCol = tileCol.find( tileType );
    if( iterCol != tileCol.end() )
    {
        return iterCol->second;
    }
    return false;
}


AnimationData *Tilesheet::GetAnimData( int tileType )
{
    if( tileType > -1 ){
        iterAnims = tileAnims.find( tileType );
        if( iterAnims != tileAnims.end() )
        {
            return iterAnims->second;
        }
    }
    return NULL;
}


/*int Tilesheet::GetStartFrame( int sprite )
{
    //std::cout << "GetNextFrame: " << sprite << ", " << currentFrame << std::endl;
    int startFrame = tileAnims[sprite]->StartFrame();
    return startFrame;
}

int Tilesheet::GetNextFrame( int sprite, int currentFrame )
{
    //std::cout << "GetNextFrame: " << sprite << ", " << currentFrame << std::endl;
    std::cout << "1";
    int nextFrame = tileAnims[sprite]->NextFrame( currentFrame );
    std::cout << "5";
    return nextFrame;
}*/
