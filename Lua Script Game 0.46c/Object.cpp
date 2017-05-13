#include "Object.h"
#include "ObjectEngine.h"
#include <iostream>

Object::Object( int objType, int objTile, bool newcol, std::string newname, int x, int y, int w, int h )
{
    type = objType;
    tile = objTile;
    name = newname;
    collide = newcol;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    std::cout << "OBJNAME: " << name << std::endl;
}

std::string Object::GetName()
{
    return name;
}

void Object::SetName( std::string newname )
{
    name = newname;
}

int Object::GetType()
{
    return type;
}

void Object::SetType( int objType )
{
    type = objType;
}

int Object::GetTile()
{
    return tile;
}

void Object::SetTile( int objTile )
{
    tile = objTile;
}

bool Object::GetCollide()
{
    return collide;
}

void Object::SetCollide( bool newcol )
{
    collide = newcol;
}

int Object::GetFlags()
{
    return flags;
}

void Object::SetFlags( int newflags )
{
    flags = newflags;
}

void Object::Update( Tilesheet *tileSheet )
{
    AnimationData *tempAnimData = tileSheet->GetAnimData( tile );
    if( tempAnimData != NULL ){
        tempAnimData->Update();
    }
}

void Object::Draw( Tilesheet *tileSheet )
{
    if( tile > -1 )
    {
        SDL_Surface *tileSheetSurface = tileSheet->GetSurface();
        SDL_Rect *tileSheetRect = NULL;

        AnimationData *tempAnimData = tileSheet->GetAnimData( tile );
        if( tempAnimData != NULL ){
            tileSheetRect = tileSheet->GetRect( tempAnimData->CurrentFrame() );
        }

        if( tileSheetRect != NULL ){
            RenderEngine::Instance()->Draw( (rect.x * rect.w), (rect.y * rect.h), tileSheetSurface, NULL, tileSheetRect );
        }
    }
}
