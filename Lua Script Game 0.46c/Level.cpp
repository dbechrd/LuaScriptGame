#include "Level.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "SDL/SDL.h"

#include "Level.h"
#include "Tile.h"
#include "RenderEngine.h"
#include "ObjectEngine.h"

using namespace std;

Level::Level( const std::string &file_map )
{
    camera = NULL;
    objEngine = NULL;

    camera = Camera::Instance()->Rect();

    //The tile offsets
    int x = 0, y = 0;
    int t;

    //Open the map
    std::ifstream mapStream( file_map.c_str() );

    //If the map couldn't be loaded
    if( mapStream == NULL )
    {
        std::cout << "Map Load Error" << std::endl;
    }

    mapFileName = file_map;

    mapStream >> animDataFileName;
    mapStream >> objDataFileName;

    objEngine = new ObjectEngine( objDataFileName );

    int MapParams[10];

    for( int j = 0; j < 10; j++ )
    {
        MapParams[j] = -1;
    }

    for( int i = 0; i < 10; i++ )
    {
        int val = -1;

        mapStream >> val;

        if( val == -1 )
        {
            break;
        }

        MapParams[i] = val;

        if( mapStream.fail() == true )
        {
            mapStream.close();
            std::cout << "Parameter error" << std::endl << "Expected Format: [levelWidth levelHeight numberOfLayers tileWidth tileHeight numberOfTiles -1]" << std::endl;
        }
    }

    levelWidth = MapParams[0];
    std::cout << "Level Width: " << levelWidth << "     ";
    levelHeight = MapParams[1];
    std::cout << "Level Height: " << levelHeight << std::endl;
    levelLayers = MapParams[2];
    std::cout << "levelLayers: " << levelLayers << std::endl;
    tileWidth = MapParams[3];
    std::cout << "Tile Width: " << tileWidth << "     ";
    tileHeight = MapParams[4];
    std::cout << "Tile Height: " << tileHeight << std::endl;

    //Load the tilesheet and get the number of sprites
    tileSprites = tileSheet.Load( animDataFileName, tileWidth, tileHeight );
    std::cout << "Tile Sprites: " << tileSprites << std::endl;

    tileColumn = levelHeight / tileHeight;
    tileRow = levelWidth / tileWidth;
    totalTiles = tileColumn * tileRow;

    //load tile layers
    for( int l = 0; l < levelLayers; l++ )
    {
        layerData.push_back( new Layer( levelWidth, levelHeight, tileWidth, tileHeight ) );
        for( t = 0; t < totalTiles; t++ )
        {
            int tileType = -1;

            mapStream >> tileType;

            if( mapStream.fail() == true )
            {
                mapStream.close();
                std::cout << "Map Tile Read Error" << std::endl;
            }

            if( ( tileType >= -1 ) && ( tileType < tileSprites ) )
            {
                layerData[l]->AddTile( x, y, new Tile(&tileSheet, x, y, tileWidth, tileHeight, tileType) );
            }

            x += 1;

            if( x >= tileRow )
            {
                x = 0;
                y += 1;
            }
        }
        x = 0;
        y = 0;
    }

    //Create NULL 2D object vector
    for( int objx = 0; objx < (levelWidth / tileWidth); objx++ )
    {
        objData.push_back( std::vector<Object*>() );
        for( int objy = 0; objy < (levelHeight / tileHeight); objy++ )
        {
            objData[objx].push_back( NULL );
        }
    }

    //Load objects
    x = 0;
    y = 0;

    cout << "Loading Objects\n";
    for( t = 0; t < totalTiles; t++ )
    {
        int objType = -1;

        mapStream >> objType;

        if( mapStream.fail() == true )
        {
            mapStream.close();
            std::cout << "Map Object Read Error" << std::endl;
        }

        if( ( objType > -1 ) && ( objType < tileSprites ) )
        {
            Object *newobj = objEngine->AddObject( objType, x, y );
            objData[x][y] = newobj;
        }

        x += 1;

        if( x >= tileRow )
        {
            x = 0;
            y += 1;
        }
    }

    //Close the file
    mapStream.close();

    activeLayer = 0;

    cout << "Level Created\n";
}

Level::~Level()
{
    for( int i = layerData.size() - 1; i >= 0; i-- )
    {
        if( layerData[i] != NULL ){
            delete layerData[i];
            layerData[i] = NULL;
        }
    }
    layerData.clear();

    cout << "Level: Layers Deleted\n";
    cout.flush();

    for( int j = objData.size() - 1; j >= 0; j-- )
    {
        for( int k = objData[j].size() - 1; k >= 0; k-- )
        {
            if( objData[j][k] != NULL ){
                delete objData[j][k];
                objData[j][k] = NULL;
            }
        }
        objData[j].clear();
    }
    objData.clear();

    cout << "Level: Objects Deleted\n";
    cout.flush();
}

int Level::ToggleLayer( int layer )
{
    if( layer <= layerData.size() )
    {
        if( layerData[layer]->visible == false )
        {
            layerData[layer]->visible = true;
            Draw();
        }
        else if( layerData[layer]->visible == true )
        {
            layerData[layer]->visible = false;
            Draw();
        }
    }
}

void Level::Update()
{
    for( int l = 0; l < levelLayers; l++ )
    {
        if( layerData[l]->visible == true )
        {
            layerData[l]->Update();
        }
    }

    objEngine->UpdateObjects( &tileSheet );
}

//OBJECT DRAW FUNCTION
int Level::Draw( int drawCode )
{
    if( drawCode == 0 || drawCode == 1 ){

        //Layer Floor Draw
        layerData[layer_Floor]->Draw();

        //Character Draw
        //NULL

        //Layer Walls Draw
        layerData[layer_Walls]->Draw();

        //Layer Objects Draw
        objEngine->DrawObjects( &tileSheet );

    }
    if( drawCode == 0 || drawCode == 2 ){

        //Layer Roof Draw
        layerData[layer_Roof]->Draw();

    }

    return 0;
}

int Level::TileWidth()
{
    return tileWidth;
}

int Level::TileHeight()
{
    return tileHeight;
}

int Level::LevelWidth()
{
    return levelWidth;
}

int Level::LevelHeight()
{
    return levelHeight;
}

SDL_Surface *Level::GetTileSheet()
{
    return tileSheet.GetSurface();
}

int Level::GetTileNumber( int x, int y )
{
    int tempa = x / tileWidth;
    int tempb = y / tileHeight;

    int tilenum = tempa + tempb * tileRow;
    return tilenum;
}

SDL_Rect Level::GetTileCoords( int x, int y )
{
    x = x / tileWidth;
    y = y / tileHeight;

    SDL_Rect coords;
    coords.x = layerData[activeLayer]->GetX( x, y ) * tileWidth;
    coords.y = layerData[activeLayer]->GetY( x, y ) * tileHeight;

    return coords;
}

int Level::SetTileSprite( int x, int y, int sprite )
{
    x = x / tileWidth;
    y = y / tileHeight;

    if( ( sprite >= -1 ) && ( sprite < tileSprites ) )
    {
        layerData[activeLayer]->SetSprite( x, y, sprite );
        layerData[activeLayer]->DrawSprite( x, y );
    }else{
        return 1;
    }

    return 0;
}

int Level::GetTileSprite( int x, int y )
{
    x = x / tileWidth;
    y = y / tileHeight;

    int sprite = layerData[activeLayer]->GetSprite( x, y );

    return sprite;
}

Object *Level::GetObject( int x, int y )
{
    if( x < 0 || y < 0 || x >= (levelWidth / tileWidth) || y >= (levelHeight / tileHeight) ){
        return NULL;
    }

    return objData[x][y];
}

bool Level::IsCollision( int x, int y )
{
    if( x < 0 || y < 0 || x >= (levelWidth / tileWidth) || y >= (levelHeight / tileHeight) ){
        return true;
    }
    if( tileSheet.GetCollide( layerData[layer_Floor]->GetSprite( x, y ) ) ){
        return true;
    }
    if( tileSheet.GetCollide( layerData[layer_Walls]->GetSprite( x, y ) ) ){
        return true;
    }
    if( objData[x][y] != NULL ){
        if( objData[x][y]->GetCollide() ){
            return true;
        }
    }
    return false;
}

int Level::Save()
{
    remove( mapFileName.c_str() );
    std::ofstream mapStream( mapFileName.c_str(), std::ios::app );

    //If the map couldn't be loaded
    if( mapStream == NULL )
    {
        cout << "Map Save Error";
        return 1;
    }

    //write tilesheet name and other attribute to map file
    mapStream << animDataFileName << std::endl;
    mapStream << levelWidth << " " << levelHeight << " " << levelLayers << " " << tileWidth << " " << tileHeight << " " << tileSprites << " -1\n";

    for( int i = 0; i < layerData.size(); i++ )
    {
        for( int j = 0; j < tileColumn; j++ )
        {
            for( int k = 0; k < tileRow; k++ )
            {
                int test = layerData[i]->GetSprite( k, j );
                if( test >= 0 && test < 10 )
                {
                    mapStream << "0" << test << " ";
                }else{
                    mapStream << test << " ";
                }
            }
            mapStream << std::endl;
        }
        mapStream << std::endl << std::endl;
    }
    mapStream.close();
}
