#ifndef OBJECTENGINE_H_INCLUDED
#define OBJECTENGINE_H_INCLUDED

#include "Object.h"
#include <vector>
#include <map>

class ObjectEngine{
    private:
        int totalObjects;
        int objWidth;
        int objHeight;

        //Object type, tile
        std::map<int, int> objTileData;
        std::map<int, int>::iterator iterTile;

        //Object type, collision
        std::map<int, bool> objColData;
        std::map<int, bool>::iterator iterCol;

        //Object type, name
        std::map<int, std::string> objNameData;
        std::map<int, std::string>::iterator iterName;

        std::vector<Object*> objects;
    public:
        ObjectEngine( std::string filename );
        ~ObjectEngine();

        Object *AddObject( int objType, int x, int y );

        int GetObjectWidth( int objType );
        int GetObjectHeight( int objType );
        int GetObjectTile( int objType );
        bool GetObjectCol( int objType );
        std::string GetObjectName( int objType );

        void UpdateObjects( Tilesheet *tileSheet = NULL );
        void DrawObjects( Tilesheet *tileSheet = NULL );
};

#endif // OBJECTENGINE_H_INCLUDED
