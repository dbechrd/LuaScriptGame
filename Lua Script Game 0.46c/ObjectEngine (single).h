#ifndef OBJECTENGINE_H_INCLUDED
#define OBJECTENGINE_H_INCLUDED

#include "Object.h"
#include <vector>
#include <map>

class ObjectEngine{
    private:
        static ObjectEngine* pinstance;

        int tileObjects;
        int objWidth;
        int objHeight;

        //Object type, tile
        std::map<int, int> objTileData;

        //Object type, name
        std::map<int, std::string> objNameData;
        std::map<int, std::string>::iterator iterName;

        //Object type, name
        std::map<int, bool> objColData;
        std::map<int, bool>::iterator iterCol;

        std::vector<Object*> objects;
    protected:
        ObjectEngine( std::string filename );
        ObjectEngine(const ObjectEngine&);
        ObjectEngine& operator= (const ObjectEngine&);
    public:
        static ObjectEngine* Instance( std::string filename );
        static ObjectEngine* Instance();
        ~ObjectEngine();

        Object *AddObject( int objType, int x, int y );

        std::string GetObjectName( int objType );
        bool GetObjectCol( int objType );

        void DrawObjects( Tilesheet *tileSheet );
};

#endif // OBJECTENGINE_H_INCLUDED
