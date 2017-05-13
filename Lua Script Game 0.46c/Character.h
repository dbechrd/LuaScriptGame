#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "SDL/SDL.h"
#include "AnimationData.h"
#include "RenderEngine.h"
#include "Object.h"
#include <string>
#include <vector>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

class RenderEngine;
class Object;

//#define CHAR_DEBUG

//#define ORIGCOL

enum direction{ UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Character{
    private:

        //All Characters
        static std::vector<Character*> characters;

        //Next available UID
        static int nextUID;

        //This character's UID
        int UID;

        RenderEngine *renderer;
        lua_State *L;

        //Displayed Name
        std::string name;

        SDL_Surface *surface;
        SDL_Rect rect;
        int mapX;
        int mapY;

        int sprite;
        int charSprites;
        int charFrames;
        int frameWidth;
        int frameHeight;
        int tileWidth;
        int tileHeight;

        //possibly debug vars
        int oldTime;
        bool colliding;

        #ifdef ORIGCOL
        Object *objCol;
        #else
        //Object colliding with most
        Object *objColMain;
        //All objects colliding with
        Object *objCol[4];
        #endif

        //Character colliding with
        Character *charCol;

        int walkWidth;
        int walkHeight;
        int walkSpeed;
        bool walking;
        int facing;

        std::vector<SDL_Rect*> sprites;
        std::vector<AnimationData*> spriteAnims;

    public:

        Character( std::string filename, int new_x, int new_y );
        ~Character();

        int GetUID(){ return UID; }
        std::string GetName(){ return name; }
        int Speed();
        SDL_Rect *Rect(){ return &rect; }

        #ifdef ORIGCOL
        Object *CollidingWith(){ return objCol; }
        #else
        Object *CollidingWith(){ return objColMain; }
        #endif

        void Walk( std::string direction );
        void Action();
        bool Collision();
        void Update();
        int Draw();

};

#endif // CHARACTER_H_INCLUDED
