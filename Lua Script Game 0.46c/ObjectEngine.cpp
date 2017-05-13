#include "ObjectEngine.h"
#include "ScriptEngine.h"
#include <fstream>
#include <iostream>

ObjectEngine::ObjectEngine( std::string filename )
{
    std::ifstream objDataStream( filename.c_str() );

    if( objDataStream == NULL )
    {
        std::cout << "Object Data File Error" << std::endl;
    }

    std::string objScriptFilename;
    objDataStream >> objScriptFilename;
    ScriptEngine::Instance()->RegisterScript(objScriptFilename);

    objDataStream >> totalObjects;
    objDataStream >> objWidth;
    objDataStream >> objHeight;
    std::cout << "totalObjects: " << totalObjects << std::endl;
    std::cout << "objWidth: " << objWidth << std::endl;
    std::cout << "objHeight: " << objHeight << std::endl;

    int objNumber;
    int tileNumber;
    int objCol;
    std::string objName;
    char chrName[50];

    for( int i = 0; i < totalObjects; i++ )
    {
        objDataStream >> objNumber;
        objDataStream >> tileNumber;
        objDataStream >> objCol;
        objDataStream.ignore( 5, ' ' );
        objDataStream.getline( chrName, 50 );
        objName = chrName;
        objTileData[objNumber] = tileNumber;
        objColData[objNumber] = objCol;
        objNameData[objNumber] = objName;
        std::cout << "objNumber: " << objNumber << std::endl;
        std::cout << "tileNumber: " << tileNumber << std::endl;
        std::cout << "objCol: " << objCol << std::endl;
        std::cout << "objName: " << objName << std::endl;
    }
}

ObjectEngine::~ObjectEngine()
{
    for( int i = objects.size() - 1; i >= 0; i-- )
    {
        if( objects[i] != NULL ){
            delete objects[i];
            objects[i] = NULL;
        }
    }
    objects.clear();
}

Object *ObjectEngine::AddObject( int objType, int x, int y )
{
    int objTile = GetObjectTile( objType );
    bool collide = GetObjectCol( objType );
    std::string name = GetObjectName( objType );

    Object *newobj = new Object( objType, objTile, collide, name, x, y, objWidth, objHeight );
    objects.push_back( newobj );

    return newobj;
}

int ObjectEngine::GetObjectWidth( int objType )
{
    return objWidth;
}

int ObjectEngine::GetObjectHeight( int objType )
{
    return objHeight;
}

int ObjectEngine::GetObjectTile( int objType )
{
    iterTile = objTileData.find( objType );
    if( iterTile != objTileData.end() )
    {
        return iterTile->second;
    }
    return -1;
}

bool ObjectEngine::GetObjectCol( int objType )
{
    iterCol = objColData.find( objType );
    if( iterCol != objColData.end() )
    {
        return iterCol->second;
    }
    return false;
}

std::string ObjectEngine::GetObjectName( int objType )
{
    std::cout << "GetObjName: " << objType << std::endl;
    iterName = objNameData.find( objType );
    if( iterName != objNameData.end() )
    {
        std::cout << "iter->second: " << iterName->second << std::endl;
        return iterName->second;
    }
    return "GetObjectName Failed";
}

void ObjectEngine::UpdateObjects( Tilesheet *tileSheet )
{
    for( int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Update( tileSheet );
    }
}

void ObjectEngine::DrawObjects( Tilesheet *tileSheet )
{
    for( int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Draw( tileSheet );
    }
}
