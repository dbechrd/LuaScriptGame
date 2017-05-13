#include "ObjectEngine.h"
#include <fstream>
#include <iostream>

ObjectEngine* ObjectEngine::pinstance = 0;
ObjectEngine* ObjectEngine::Instance( std::string filename )
{
    if (pinstance == 0)
    {
        pinstance = new ObjectEngine( filename );
    }
    return pinstance;
}

ObjectEngine* ObjectEngine::Instance()
{
    if (pinstance == 0)
    {
        return NULL;
    }
    return pinstance;
}

ObjectEngine::ObjectEngine( std::string filename )
{
    std::ifstream objDataStream( filename.c_str() );

    if( objDataStream == NULL )
    {
        std::cout << "Object Data File Error" << std::endl;
    }

    objDataStream >> tileObjects;
    objDataStream >> objWidth;
    objDataStream >> objHeight;
    std::cout << "tileObjects: " << tileObjects << std::endl;
    std::cout << "tileObjects: " << objWidth << std::endl;
    std::cout << "tileObjects: " << objHeight << std::endl;

    int objNumber;
    int tileNumber;
    int objCol;
    std::string objName;

    for( int i = 0; i < tileObjects; i++ )
    {
        objDataStream >> objNumber;
        objDataStream >> tileNumber;
        objDataStream >> objCol;
        objDataStream >> objName;
        objTileData[objNumber] = tileNumber;
        objNameData[tileNumber] = objName;
        objColData[tileNumber] = objCol;
        std::cout << "objNumber: " << objNumber << std::endl;
        std::cout << "tileNumber: " << tileNumber << std::endl;
        std::cout << "objCol: " << objCol << std::endl;
        std::cout << "objName: " << objName << std::endl;
        std::cout << "objName[]: " << objNameData[tileNumber] << std::endl;
    }
}

ObjectEngine::~ObjectEngine()
{
    for( int i = objects.size() - 1; i >= 0; i-- )
    {
        delete objects[i];
    }
    objects.clear();
}

Object *ObjectEngine::AddObject( int objType, int x, int y )
{
    Object *newobj = new Object( objType, x, y, objWidth, objHeight );
    objects.push_back( newobj );
    return newobj;
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

bool ObjectEngine::GetObjectCol( int objType )
{
    iterCol = objColData.find( objType );
    if( iterCol != objColData.end() )
    {
        return iterCol->second;
    }
    return false;
}

void ObjectEngine::DrawObjects( Tilesheet *tileSheet )
{
    for( int i = 0; i < objects.size(); i++ )
    {
        objects[i]->Draw( tileSheet );
    }
}
