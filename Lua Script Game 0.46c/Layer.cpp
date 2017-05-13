#include "Layer.h"
#include <iostream>
#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "RenderEngine.h"

using namespace std;

Layer::Layer( int lWidth, int lHeight, int tWidth, int tHeight )
{
    camera = NULL;

    levelWidth = lWidth;
    levelHeight = lHeight;
    tileWidth = tWidth;
    tileHeight = tHeight;

    for( int j = 0; j < (levelWidth / tileWidth); j++ )
    {
        tileData.push_back( std::vector<Tile*>() );
        for( int k = 0; k < (levelHeight / tileHeight); k++ )
        {
            tileData[j].push_back( NULL );
        }
    }

    camera = Camera::Instance()->Rect();

    visible = true;

    cout << "Layer Created\n";
}

Layer::~Layer()
{
    for( int j = tileData.size() - 1; j >= 0; j-- )
    {
        for( int k = tileData[j].size() - 1; k >= 0; k-- )
        {
            if( tileData[j][k] != NULL ){
                delete tileData[j][k];
                tileData[j][k] = NULL;
            }
        }
        tileData[j].clear();
    }
    tileData.clear();

    cout << "Layer Deleted\n";
}

int Layer::AddTile( int x, int y, Tile *tile )
{
    tileData[x][y] = tile;
}

int Layer::GetSprite( int x, int y )
{
    if( tileData[x][y] != NULL ){
        return tileData[x][y]->Sprite();
    }
    return -1;
}

void Layer::SetSprite( int x, int y, int tileSprite )
{
    if( tileData[x][y] != NULL ){
        tileData[x][y]->SetSprite( tileSprite );
    }
}

int Layer::GetX( int x, int y )
{
    if( tileData[x][y] != NULL ){
        return tileData[x][y]->X();
    }
    return -1;
}

int Layer::GetY( int x, int y )
{
    if( tileData[x][y] != NULL ){
        return tileData[x][y]->Y();
    }
    return -1;
}

void Layer::Update()
{
    for( int j = 0; j < (levelWidth / tileWidth); j++ )
    {
        for( int k = 0; k < (levelHeight / tileHeight); k++ )
        {
            if( tileData[j][k] != NULL ){
                tileData[j][k]->Update();
            }
        }
    }
}

int Layer::DrawSprite( int x, int y )
{
    if( tileData[x][y] != NULL ){
        tileData[x][y]->Draw();
    }
}

int Layer::Draw()
{
    int xAdd = (camera->x) / tileWidth;                   //-150 / 32 = -4
    int yAdd = (camera->y) / tileHeight;                  //-200 / 32 = -6
    int xMax = ((camera->x + camera->w) / tileWidth) + 1;  //-150 + 640 / 32 = 16
    int yMax = ((camera->y + camera->h) / tileHeight) + 1; //-150 + 480 / 32 = 11

    for( int j = 0; j < (camera->w / tileWidth) + 1; j++ ) // 20
    {
        for( int k = 0; k < (camera->h / tileHeight) + 1; k++ ) // 15
        {
            if( j + xAdd >= 0 && j + xAdd < xMax && j + xAdd < levelWidth / tileWidth && k + yAdd >= 0 && k + yAdd < yMax && k + yAdd < levelHeight / tileHeight ){
                if( tileData[j + xAdd][k + yAdd] != NULL ){
                    tileData[j + xAdd][k + yAdd]->Draw();
                }
            }
        }
    }
}
