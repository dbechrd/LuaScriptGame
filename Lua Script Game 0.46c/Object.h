#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "RenderEngine.h"
#include "Tilesheet.h"

class Tilesheet;

enum {
    WALK = 1,
    TALK = 2,
    TAKE = 4
    //STYLE4  =   8,
    //STYLE5  =  16,
    //STYLE6  =  32,
    //STYLE7  =  64,
    //STYLE8  = 128
};

class Object{
    private:
        SDL_Rect rect;
        int type;
        int tile;
        std::string name;
        bool collide;
        int flags;
    public:
        Object( int objType, int objTile, bool newcol, std::string newname, int x, int y, int w, int h );

        SDL_Rect *Rect(){ return &rect; }
        std::string GetName();
        void SetName( std::string newname );
        int GetType();
        void SetType( int objType );
        int GetTile();
        void SetTile( int objTile );
        bool GetCollide();
        void SetCollide( bool newcol );
        int GetFlags();
        void SetFlags( int newflags );

        void Update( Tilesheet *tileSheet = NULL );
        void Draw( Tilesheet *tileSheet = NULL );
};

#endif // OBJECT_H_INCLUDED
