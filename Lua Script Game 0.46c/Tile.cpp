#include <iostream>
#include "Tile.h"
#include "RenderEngine.h"
#include "Camera.h"
#include "AnimationData.h"

Tile::Tile( Tilesheet *new_tileSheet, int x, int y, int tileWidth, int tileHeight, int new_sprite )
{
    renderer = NULL;
    tileSheet = NULL;

    renderer = RenderEngine::Instance();
    tileSheet = new_tileSheet;

    rect.x = x;
    rect.y = y;
    rect.w = tileWidth;
    rect.h = tileHeight;

    sprite = new_sprite;
}

int Tile::CurrentFrame()
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        return tempAnimData->CurrentFrame();
    }
    return -1;
}

int Tile::Delay()
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        return tempAnimData->Delay();
    }
    return -1;
}

void Tile::SetDelay( int new_delay )
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        tempAnimData->SetDelay( new_delay );
    }
}

int Tile::AnimFlag()
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        return tempAnimData->Flag();
    }
    return -1;
}

void Tile::SetAnimFlag( int new_animFlag )
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        tempAnimData->SetFlag( new_animFlag );
    }
}

void Tile::Update()
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
    if( tempAnimData != NULL ){
        tempAnimData->Update();
    }
}

int Tile::Draw()
{
    if( sprite > -1 )
    {
        SDL_Surface *tileSheetSurface = tileSheet->GetSurface();
        SDL_Rect *tileSheetRect = NULL;

        AnimationData *tempAnimData = tileSheet->GetAnimData( sprite );
        if( tempAnimData != NULL ){
            tileSheetRect = tileSheet->GetRect( tempAnimData->CurrentFrame() );
        }

        if( tileSheetRect != NULL ){
            renderer->Draw( (rect.x * rect.w), (rect.y * rect.h), tileSheetSurface, NULL, tileSheetRect );
        }
    }
}
