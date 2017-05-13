#include "Character.h"
#include "AnimationData.h"
#include "ScriptEngine.h"
#include "RenderEngine.h"
#include "TextEngine.h"
#include "GameEngine.h"
#include "Object.h"
#include "Level.h"
#include "SDL/SDL.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int Character::nextUID = 0000;
std::vector<Character*> Character::characters;

Character::Character( std::string filename, int new_x, int new_y )
{
    UID = Character::nextUID;
    Character::nextUID++;

    renderer = NULL;
    L = NULL;
    surface = NULL;
    #ifdef ORIGCOL
    objCol = NULL;
    #else
    objColMain = NULL;
    for( int i = 0; i < 4; i++ ){
        objCol[i] = NULL;
    }
    #endif
    charCol = NULL;

    renderer = RenderEngine::Instance();
    L = ScriptEngine::Instance()->GetLuaState();
    ////////////////////////////////////////////////////////////////////////////////////
    //Load Animation Data Stream

    std::string charScriptFilename;
    std::string charSheetFilename;

    std::ifstream animDataStream( filename.c_str() );

    if( animDataStream == NULL )
    {
        std::cout << "Character Data Error" << std::endl;
    }

    //Character name
    animDataStream >> name;

    //Load script
    animDataStream >> charScriptFilename;
    ScriptEngine::Instance()->RegisterScript( charScriptFilename );

    //Load sprite sheet
    animDataStream >> charSheetFilename;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load tilesheet surface

    surface = renderer->LoadSurface( charSheetFilename );
    rect = surface->clip_rect;
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Animation Data

    animDataStream >> frameWidth;
    animDataStream >> frameHeight;
    animDataStream >> charSprites;
    animDataStream >> charFrames;
    animDataStream >> walkWidth;
    animDataStream >> walkHeight;
    animDataStream >> walkSpeed;

    int spriteNumber;
    int startFrame;
    int totalFrames;
    int delay;
    int animFlag;

    for( int i = 0; i < charSprites; i++ )
    {
        animDataStream >> spriteNumber;
        animDataStream >> startFrame;
        animDataStream >> totalFrames;
        animDataStream >> delay;
        animDataStream >> animFlag;
        spriteAnims.push_back( new AnimationData( startFrame, totalFrames, delay, animFlag ) );
    }
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //Load Frame Rects

    int tempSpriteNumber = 0;

    for( int j = 0; j < (rect.h / frameHeight); j++ )
    {
        for( int k = 0; k < (rect.w / frameWidth); k++ )
        {
            sprites.push_back( new SDL_Rect );
            sprites[tempSpriteNumber]->x = k * frameWidth;
            sprites[tempSpriteNumber]->y = j * frameHeight;
            sprites[tempSpriteNumber]->w = frameWidth;
            sprites[tempSpriteNumber]->h = frameHeight;
            tempSpriteNumber++;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////

    sprite = DOWN;
    walking = false;

    //cameraDelta = 0;

    rect.x = new_x;
    rect.y = new_y;
    rect.w = frameWidth;
    rect.h = frameHeight;
    mapX = rect.x / 32;
    mapY = rect.y / 32;

    tileWidth = GameEngine::Instance()->GetLevel()->TileWidth();
    tileHeight = GameEngine::Instance()->GetLevel()->TileHeight();

    oldTime = SDL_GetTicks();
    colliding = false;

    bool walking = false;
    facing = DOWN;

    Character::characters.push_back( this );
    std::cout << "Character Created\n";
}

Character::~Character()
{
    for( int i = spriteAnims.size() - 1; i >= 0; i-- )
    {
        if( spriteAnims[i] != NULL ){
            delete spriteAnims[i];
            spriteAnims[i] = NULL;
        }
    }
    spriteAnims.clear();

    for( int j = sprites.size() - 1; j >= 0; j-- )
    {
        if( sprites[j] != NULL ){
            delete sprites[j];
            sprites[j] = NULL;
        }
    }
    sprites.clear();
}

int Character::Speed()
{
    return walkSpeed;
}

void Character::Walk( std::string direction )
{
    if( direction == "stop" ){
        spriteAnims[sprite]->SetFlag(0);
        walking = false;
        return;
    }

    if( direction == "up" && sprite != UP ){
        spriteAnims[sprite]->SetFlag(0);
        walking = false;
    }else if( direction == "down" && sprite != DOWN ){
        spriteAnims[sprite]->SetFlag(0);
        walking = false;
    }else if( direction == "left" && sprite != LEFT ){
        spriteAnims[sprite]->SetFlag(0);
        walking = false;
    }else if( direction == "right" && sprite != RIGHT ){
        spriteAnims[sprite]->SetFlag(0);
        walking = false;
    }

    if( walking == false )
    {
        if( direction == "up"){
            sprite = UP;
            facing = sprite;

            spriteAnims[sprite]->SetFlag(1);
            walking = true;
        }else if( direction == "down"){
            sprite = DOWN;
            facing = sprite;

            spriteAnims[sprite]->SetFlag(1);
            walking = true;
        }else if( direction == "left"){
            sprite = LEFT;
            facing = sprite;

            spriteAnims[sprite]->SetFlag(1);
            walking = true;
        }else if( direction == "right"){
            sprite = RIGHT;
            facing = sprite;

            spriteAnims[sprite]->SetFlag(1);
            walking = true;
        }else{
            std::cout << "Wtf happened?" << std::endl;
        }
    }
}

void Character::Action()
{
    if( charCol != NULL ){
        string command = charCol->GetName() + "_Talk";

        lua_getglobal(L, command.c_str());
        lua_pushnumber(L, facing);
        lua_pushstring(L, name.c_str());
        lua_call(L, 2, 0);

    }else{
        lua_getglobal(L, "ObjInspect");

        lua_pushnumber(L, facing);
        #ifdef ORIGCOL
        if( objCol != NULL ){
            lua_pushnumber(L, objCol->GetType());
        #else
        if( objColMain != NULL ){
            lua_pushnumber(L, objColMain->GetType());
        #endif
        }else{
            lua_pushnumber(L, -1);
        }

        #ifdef ORIGCOL
        if( objCol != NULL ){
            lua_pushstring(L, objCol->GetName().c_str());
        #else
        if( objColMain != NULL ){
            lua_pushstring(L, objColMain->GetName().c_str());
        #endif
        }else{
            lua_pushstring(L, "NULL");
        }

        lua_call(L, 3, 0);
    }
}

bool Character::Collision()
{
    bool collided = false;
    #ifndef ORIGCOL
    objColMain = NULL;
    Object *tempObj = NULL;

    SDL_Rect checkRec;
    checkRec.x = -1;
    checkRec.y = -1;
    checkRec.w = tileWidth;
    checkRec.h = tileHeight;
    #else
    objCol = NULL;
    #endif

    charCol = NULL;

    //Other characters exist
    if( !Character::characters.empty() ){
        //Iterate through them
        for( int j = 0; j < Character::characters.size(); j++ ){
            //Character is valid
            if( Character::characters[j] != NULL ){
                //Not me
                if( Character::characters[j]->GetUID() != UID ){
                    SDL_Rect *tempCharRect = Character::characters[j]->Rect();
                    //Check collision with other character
                    switch( facing ){
                        case UP:
                            if( rect.y - walkSpeed <= tempCharRect->y + tempCharRect->h && rect.y + rect.h > tempCharRect->y && rect.x < tempCharRect->x + tempCharRect->w && rect.x + rect.w > tempCharRect->x ){
                                //cout << "Colliding with valid char\n";
                                rect.y = tempCharRect->y + tempCharRect->h;
                                collided = true;
                                charCol = Character::characters[j];
                            //}else{
                            //    cout << "Valid Char not collided with\n";
                            }
                            break;
                        case DOWN:
                            if( rect.y < tempCharRect->y + tempCharRect->h && rect.y + rect.h + walkSpeed >= tempCharRect->y && rect.x < tempCharRect->x + tempCharRect->w && rect.x + rect.w > tempCharRect->x ){
                                //cout << "Colliding with valid char\n";
                                rect.y = tempCharRect->y - rect.h;
                                collided = true;
                                charCol = Character::characters[j];
                            //}else{
                            //    cout << "Valid Char not collided with\n";
                            }
                            break;
                        case LEFT:
                            if( rect.y < tempCharRect->y + tempCharRect->h && rect.y + rect.h > tempCharRect->y && rect.x - walkSpeed <= tempCharRect->x + tempCharRect->w && rect.x + rect.w > tempCharRect->x ){
                                //cout << "Colliding with valid char\n";
                                rect.x = tempCharRect->x + tempCharRect->w;
                                collided = true;
                                charCol = Character::characters[j];
                            //}else{
                            //    cout << "Valid Char not collided with\n";
                            }
                            break;
                        case RIGHT:
                            if( rect.y < tempCharRect->y + tempCharRect->h && rect.y + rect.h > tempCharRect->y && rect.x < tempCharRect->x + tempCharRect->w && rect.x + rect.w + walkSpeed >= tempCharRect->x ){
                                //cout << "Colliding with valid char\n";
                                rect.x = tempCharRect->x - rect.w;
                                collided = true;
                                charCol = Character::characters[j];
                            //}else{
                            //    cout << "Valid Char not collided with\n";
                            }
                            break;
                    }
                //}else{
                //    cout << "Valid Char is me\n";
                }
            //}else{
            //    cout << "Char is invalid (null)\n";
            }
        }
    //}else{
    //    cout << "No other chars exist\n";
    }

    switch( facing )
    {
        //CHECK FOR OBJECTS
        case UP:
            if( rect.y - walkSpeed > 0 )
            {
                #ifndef ORIGCOL
                int UpY = mapY - 1;
                int LeftX = mapX - 1;
                int RightX = mapX + 1;
                int MidX = mapX;

                bool tempCollided;

                for( int i = 0; i < 4; i++ ){

                    tempCollided = false;

                    switch( i ){
                        case 0:
                            if( rect.x < mapX * tileWidth ){
                                checkRec.x = LeftX;
                                checkRec.y = UpY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 1:
                            if( rect.x + rect.w > (mapX * tileWidth) + tileWidth ){
                                checkRec.x = RightX;
                                checkRec.y = UpY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 2:
                            checkRec.x = MidX;
                            checkRec.y = UpY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                        case 3:
                            checkRec.x = MidX;
                            checkRec.y = mapY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                    }

                    if( !collided && checkRec.x != -1 && checkRec.y != -1 ){
                        tempCollided = GameEngine::Instance()->GetLevel()->IsCollision( checkRec.x, checkRec.y );
                    }

                    if( rect.y - walkSpeed <= (checkRec.y * tileHeight) + checkRec.h ){
                        if( tempCollided == true ){
                            rect.y = (checkRec.y * tileHeight) + checkRec.h;
                            collided = true;
                            #ifdef CHAR_DEBUG
                            cout << "Character Collision [UP]: Tile\n";
                            #endif
                        }
                        if( tempObj != NULL ){
                            objCol[i] = tempObj;
                            objColMain = tempObj;
                            if( tempObj->GetCollide() ){
                                rect.y = (checkRec.y * tileHeight) + checkRec.h;
                                collided = true;
                                #ifdef CHAR_DEBUG
                                cout << "Character Collision [UP]: Object\n";
                                #endif
                            }
                        }else{
                            objCol[i] = NULL;
                        }
                    }else{
                        objCol[i] = NULL;
                    }

                    tempObj = NULL;
                    checkRec.x = -1;
                    checkRec.y = -1;
                }

                #else

                Object *tempObj = GameEngine::Instance()->GetLevel()->GetObject( mapX, mapY - 1 );
                if( tempObj != NULL ){
                    if( rect.y - speed <= (tempObj->Rect()->y * tileHeight) + tempObj->Rect()->h ){
                        objCol = tempObj;
                        if( tempObj->GetCollide() ){
                            rect.y = (tempObj->Rect()->y * tileHeight) + tempObj->Rect()->h;
                            collided = true;
                        }
                    }else{
                        objCol = NULL;
                    }
                }else{
                    objCol = NULL;
                }
                #endif

                #ifdef ORIGCOL
                return collided;
                #else
                return collided;
                #endif
            }else{
                #ifdef CHAR_DEBUG
                cout << "Character Collision [UP]: Out of bounds\n";
                #endif
                return true;
            }
            break;
        case DOWN:
            if( rect.y + rect.h + walkSpeed < GameEngine::Instance()->GetLevel()->LevelHeight() )
            {
                #ifndef ORIGCOL
                int DownY = mapY + 1;
                int LeftX = mapX - 1;
                int RightX = mapX + 1;
                int MidX = mapX;

                bool tempCollided;

                for( int i = 0; i < 4; i++ ){

                    tempCollided = false;

                    switch( i ){
                        case 0:
                            if( rect.x < mapX * tileWidth ){
                                checkRec.x = LeftX;
                                checkRec.y = DownY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 1:
                            if( rect.x + rect.w > (mapX * tileWidth) + tileWidth ){
                                checkRec.x = RightX;
                                checkRec.y = DownY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 2:
                            checkRec.x = MidX;
                            checkRec.y = DownY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                        case 3:
                            checkRec.x = MidX;
                            checkRec.y = mapY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                    }

                    if( !collided && checkRec.x != -1 && checkRec.y != -1 ){
                        tempCollided = GameEngine::Instance()->GetLevel()->IsCollision( checkRec.x, checkRec.y );
                    }

                    if( rect.y + rect.h + walkSpeed >= checkRec.y * tileHeight ){
                        if( tempCollided == true ){
                            rect.y = (checkRec.y * tileHeight) - rect.h;
                            collided = true;
                            #ifdef CHAR_DEBUG
                            cout << "Character Collision [DOWN]: Tile\n";
                            #endif
                        }
                        if( tempObj != NULL ){
                            objCol[i] = tempObj;
                            objColMain = tempObj;
                            if( tempObj->GetCollide() ){
                                rect.y = (checkRec.y * tileHeight) - rect.h;
                                collided = true;
                                #ifdef CHAR_DEBUG
                                cout << "Character Collision [DOWN]: Object\n";
                                #endif
                            }
                        }else{
                            objCol[i] = NULL;
                        }
                    }else{
                        objCol[i] = NULL;
                    }

                    tempObj = NULL;
                    checkRec.x = -1;
                    checkRec.y = -1;
                }

                #else
                Object *tempObj = GameEngine::Instance()->GetLevel()->GetObject( mapX, mapY + 1 );
                if( tempObj != NULL ){
                    if( rect.y + rect.h + speed >= tempObj->Rect()->y * tileHeight ){
                        objCol = tempObj;
                        if( tempObj->GetCollide() ){
                            rect.y = (tempObj->Rect()->y * tileHeight) - rect.h;
                            collided = true;
                        }
                    }else{
                        objCol = NULL;
                    }
                }else{
                    objCol = NULL;
                }
                #endif

                #ifdef ORIGCOL
                return collided;
                #else
                return collided;
                #endif
            }else{
                #ifdef CHAR_DEBUG
                cout << "Character Collision [DOWN]: Out of bounds\n";
                #endif
                return true;
            }
            break;
        case LEFT:
            if( rect.x - walkSpeed > 0 )
            {
                #ifndef ORIGCOL
                int LeftX = mapX - 1;
                int TopY = mapY - 1;
                int BotY = mapY + 1;
                int MidY = mapY;

                bool tempCollided;

                for( int i = 0; i < 4; i++ ){

                    tempCollided = false;

                    switch( i ){
                        case 0:
                            if( rect.y < mapY * tileHeight ){
                                checkRec.x = LeftX;
                                checkRec.y = TopY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 1:
                            if( rect.y + rect.h > (mapY * tileHeight) + tileHeight ){
                                checkRec.x = LeftX;
                                checkRec.y = BotY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 2:
                            checkRec.x = LeftX;
                            checkRec.y = MidY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                        case 3:
                            checkRec.x = mapX;
                            checkRec.y = MidY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                    }

                    if( !collided && checkRec.x != -1 && checkRec.y != -1 ){
                        tempCollided = GameEngine::Instance()->GetLevel()->IsCollision( checkRec.x, checkRec.y );
                    }

                    if( rect.x - walkSpeed <= (checkRec.x * tileWidth) + checkRec.w ){
                        if( tempCollided == true ){
                            rect.x = (checkRec.x * tileWidth) + checkRec.w;
                            collided = true;
                            #ifdef CHAR_DEBUG
                            cout << "Character Collision [LEFT]: Tile\n";
                            #endif
                        }
                        if( tempObj != NULL ){
                            objCol[i] = tempObj;
                            objColMain = tempObj;
                            if( tempObj->GetCollide() ){
                                rect.x = (checkRec.x * tileWidth) + checkRec.w;
                                collided = true;
                                #ifdef CHAR_DEBUG
                                cout << "Character Collision [LEFT]: Object\n";
                                #endif
                            }
                        }else{
                            objCol[i] = NULL;
                        }
                    }else{
                        objCol[i] = NULL;
                    }

                    tempObj = NULL;
                    checkRec.x = -1;
                    checkRec.y = -1;
                }

                #else
                Object *tempObj = GameEngine::Instance()->GetLevel()->GetObject( mapX - 1, mapY );
                if( tempObj != NULL ){
                    if( rect.x - speed <= (tempObj->Rect()->x * tileWidth) + tempObj->Rect()->w ){
                        objCol = tempObj;
                        if( tempObj->GetCollide() ){
                            rect.x = (tempObj->Rect()->x * tileWidth) + tempObj->Rect()->w;
                            collided = true;
                        }
                    }else{
                        objCol = NULL;
                    }
                }else{
                    objCol = NULL;
                }
                #endif

                #ifdef ORIGCOL
                return collided;
                #else
                return collided;
                #endif
            }else{
                #ifdef CHAR_DEBUG
                cout << "Character Collision [LEFT]: Out of bounds\n";
                #endif
                return true;
            }
            break;
        case RIGHT:
            if( rect.x + rect.w + walkSpeed < GameEngine::Instance()->GetLevel()->LevelWidth() )
            {
                #ifndef ORIGCOL
                int RightX = mapX + 1;
                int TopY = mapY - 1;
                int BotY = mapY + 1;
                int MidY = mapY;

                bool tempCollided;

                for( int i = 0; i < 4; i++ ){

                    tempCollided = false;

                    switch( i ){
                        case 0:
                            if( rect.y < mapY * tileHeight ){
                                checkRec.x = RightX;
                                checkRec.y = TopY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 1:
                            if( rect.y + rect.h > (mapY * tileHeight) + tileHeight ){
                                checkRec.x = RightX;
                                checkRec.y = BotY;
                                tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            }
                            break;
                        case 2:
                            checkRec.x = RightX;
                            checkRec.y = MidY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                        case 3:
                            checkRec.x = mapX;
                            checkRec.y = MidY;
                            tempObj = GameEngine::Instance()->GetLevel()->GetObject( checkRec.x, checkRec.y );
                            break;
                    }

                    if( !collided && checkRec.x != -1 && checkRec.y != -1 ){
                        tempCollided = GameEngine::Instance()->GetLevel()->IsCollision( checkRec.x, checkRec.y );
                    }

                    if( rect.x + rect.w + walkSpeed >= checkRec.x * tileWidth ){
                        if( tempCollided == true ){
                            rect.x = (checkRec.x * tileWidth) - rect.w;
                            collided = true;
                            #ifdef CHAR_DEBUG
                            cout << "Character Collision [RIGHT]: Tile\n";
                            #endif
                        }
                        if( tempObj != NULL ){
                            objCol[i] = tempObj;
                            objColMain = tempObj;
                            if( tempObj->GetCollide() ){
                                rect.x = (checkRec.x * tileWidth) - rect.w;
                                collided = true;
                                #ifdef CHAR_DEBUG
                                cout << "Character Collision [RIGHT]: Object\n";
                                #endif
                            }
                        }else{
                            objCol[i] = NULL;
                        }
                    }else{
                        objCol[i] = NULL;
                    }

                    tempObj = NULL;
                    checkRec.x = -1;
                    checkRec.y = -1;
                }

                #else
                Object *tempObj = GameEngine::Instance()->GetLevel()->GetObject( mapX + 1, mapY );
                if( tempObj != NULL ){
                    if( rect.x + rect.w + speed >= tempObj->Rect()->x * tileWidth ){
                        objCol = tempObj;
                        if( tempObj->GetCollide() ){
                            rect.x = (tempObj->Rect()->x * tileWidth) - rect.w;
                            collided = true;
                        }
                    }else{
                        objCol = NULL;
                    }
                }else{
                    objCol = NULL;
                }
                #endif

                #ifdef ORIGCOL
                return collided;
                #else
                return collided;
                #endif
            }else{
                #ifdef CHAR_DEBUG
                cout << "Character Collision [RIGHT]: Out of bounds\n";
                #endif
                return true;
            }
            break;
    }

    return false;
}

void Character::Update()
{
    int newTime = SDL_GetTicks();
    int deltaTime = newTime - oldTime;
    if( deltaTime >= 15 ){

        colliding = Collision();

        //Update Player Position
        if( walking == true ){
            if( colliding == false )
            {
                switch( sprite )
                {
                    case UP:
                        rect.y -= walkSpeed;
                        break;
                    case DOWN:
                        rect.y += walkSpeed;
                        break;
                    case LEFT:
                        rect.x -= walkSpeed;
                        break;
                    case RIGHT:
                        rect.x += walkSpeed;
                        break;
                }
            }else{
                spriteAnims[sprite]->SetFlag(0);
                walking = false;
            }

            mapX = (rect.x + rect.w/2) / tileWidth;
            mapY = (rect.y + rect.h/2) / tileHeight;
        }

        oldTime = newTime;
    }else{
        if( walking == true ){
            #ifdef CHAR_DEBUG
            cout << "Delay not met yet: " <<  deltaTime;
            #endif
        }
    }

    spriteAnims[sprite]->Update();
}

int Character::Draw()
{
    int curframe = spriteAnims[sprite]->CurrentFrame();
    SDL_Rect *temprect = sprites[curframe];

    renderer->Draw( rect.x, rect.y, surface, NULL, temprect );

    std::stringstream ssout;
    ssout  << mapX << "," << mapY;
    //World Coords textbox
    TextEngine::Instance()->DebugString( ssout.str(), rect.x - 8, rect.y - 22, false );

    #ifdef ORIGCOL
    if( objCol != NULL ){
        std::stringstream ssout2;
        ssout2  << "ObjTile: " << objCol->GetTile();
        TextEngine::Instance()->DebugString( ssout2.str(), 0, 0 );
    }

    if( objCol != NULL ){
        std::stringstream ssout3;
        ssout3  << "ObjType: " << objCol->GetType();
        TextEngine::Instance()->DebugString( ssout3.str(), 0, 20 );
    }
    #else
    if( objColMain != NULL ){
        std::stringstream ssout2;
        ssout2  << "ObjTile: " << objColMain->GetTile();
        TextEngine::Instance()->DebugString( ssout2.str(), 0, 0 );
    }

    if( objColMain != NULL ){
        std::stringstream ssout3;
        ssout3  << "ObjType: " << objColMain->GetType();
        TextEngine::Instance()->DebugString( ssout3.str(), 0, 20 );
    }
    #endif
}
