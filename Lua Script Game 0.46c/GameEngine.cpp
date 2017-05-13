#include <iostream>
#include <fstream>
#include "SDL/SDL.h"
#include "GameEngine.h"
#include "RenderEngine.h"
#include "TextEngine.h"

using namespace std;

GameEngine* GameEngine::pinstance = NULL;
bool GameEngine::quit = false;
GameEngine* GameEngine::Instance( const std::string &filename )
{
    if (pinstance == NULL)
    {
        pinstance = new GameEngine( filename.c_str() );
    }
    return pinstance;
}

GameEngine::GameEngine( const std::string &filename )
{
    renderer = NULL;
    text = NULL;
    level = NULL;
    renderer = RenderEngine::Instance();
    text = TextEngine::Instance();

    //Delete old log file
    remove( "whoa.txt" );

    //Initialize engine variables
    fps = 30;
    oldTime = SDL_GetTicks();
    mousex = 0;
    mousey = 0;
    mouseLeft = false;
    mouseRight = false;
    level = NULL;

    //Configuration file
    std::ifstream configStream( filename.c_str() );

    if( configStream == NULL )
    {
        cout << "Config Stream is NULL\n";
    }

    //Read in map filename
    std::string mapname = "";
    configStream >> mapname;

    configStream.close();
}

GameEngine::~GameEngine()
{
    if( level != NULL ){
        delete level;
        level = NULL;
        cout << "Level Deleted\n";
        cout.flush();
    }

    cout << "Terminating Game Engine\n";
    cout.flush();
}

void GameEngine::HandleInput()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            SetQuit();
        }
        if ( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_a:
                    keys["a"] = true;
                    break;
                case SDLK_b:
                    keys["b"] = true;
                    break;
                case SDLK_c:
                    keys["c"] = true;
                    break;
                case SDLK_d:
                    keys["d"] = true;
                    break;
                case SDLK_e:
                    keys["e"] = true;
                    break;
                case SDLK_f:
                    keys["f"] = true;
                    break;
                case SDLK_g:
                    keys["g"] = true;
                    break;
                case SDLK_h:
                    keys["h"] = true;
                    break;
                case SDLK_i:
                    keys["i"] = true;
                    break;
                case SDLK_j:
                    keys["j"] = true;
                    break;
                case SDLK_k:
                    keys["k"] = true;
                    break;
                case SDLK_l:
                    keys["l"] = true;
                    break;
                case SDLK_m:
                    keys["m"] = true;
                    break;
                case SDLK_n:
                    keys["n"] = true;
                    break;
                case SDLK_o:
                    keys["o"] = true;
                    break;
                case SDLK_p:
                    keys["p"] = true;
                    break;
                case SDLK_q:
                    keys["q"] = true;
                    break;
                case SDLK_r:
                    keys["r"] = true;
                    break;
                case SDLK_s:
                    keys["s"] = true;
                    break;
                case SDLK_t:
                    keys["t"] = true;
                    break;
                case SDLK_u:
                    keys["u"] = true;
                    break;
                case SDLK_v:
                    keys["v"] = true;
                    break;
                case SDLK_w:
                    keys["w"] = true;
                    break;
                case SDLK_x:
                    keys["x"] = true;
                    break;
                case SDLK_y:
                    keys["y"] = true;
                    break;
                case SDLK_z:
                    keys["z"] = true;
                    break;
                case SDLK_0:
                    keys["0"] = true;
                    break;
                case SDLK_1:
                    keys["1"] = true;
                    break;
                case SDLK_2:
                    keys["2"] = true;
                    break;
                case SDLK_3:
                    keys["3"] = true;
                    break;
                case SDLK_4:
                    keys["4"] = true;
                    break;
                case SDLK_5:
                    keys["5"] = true;
                    break;
                case SDLK_6:
                    keys["6"] = true;
                    break;
                case SDLK_7:
                    keys["7"] = true;
                    break;
                case SDLK_8:
                    keys["8"] = true;
                    break;
                case SDLK_9:
                    keys["9"] = true;
                    break;
                case SDLK_UP:
                    keys["up"] = true;
                    break;
                case SDLK_DOWN:
                    keys["down"] = true;
                    break;
                case SDLK_LEFT:
                    keys["left"] = true;
                    break;
                case SDLK_RIGHT:
                    keys["right"] = true;
                    break;
                case SDLK_RETURN:
                    keys["return"] = true;
                    break;
                case SDLK_BACKSPACE:
                    keys["backspace"] = true;
                    break;
                case SDLK_LSHIFT:
                    keys["lshift"] = true;
                    break;
                case SDLK_RSHIFT:
                    keys["rshift"] = true;
                    break;
                case SDLK_LALT:
                    keys["lalt"] = true;
                    break;
                case SDLK_RALT:
                    keys["ralt"] = true;
                    break;
                case SDLK_LCTRL:
                    keys["lctrl"] = true;
                    break;
                case SDLK_RCTRL:
                    keys["rctrl"] = true;
                    break;
                case SDLK_F1:
                    keys["F1"] = true;
                    break;
                case SDLK_F2:
                    keys["F2"] = true;
                    break;
                case SDLK_F3:
                    keys["F3"] = true;
                    break;
                case SDLK_F4:
                    renderer->ToggleFullScreen();
                    break;
                case SDLK_F5:
                    keys["F5"] = true;
                    break;
                case SDLK_F6:
                    keys["F6"] = true;
                    break;
                case SDLK_F7:
                    keys["F7"] = true;
                    break;
                case SDLK_F8:
                    keys["F8"] = true;
                    break;
                case SDLK_F9:
                    keys["F9"] = true;
                    break;
                case SDLK_F10:
                    keys["F10"] = true;
                    break;
                case SDLK_F11:
                    keys["F11"] = true;
                    break;
                case SDLK_F12:
                    keys["F12"] = true;
                    break;
                case SDLK_ESCAPE:
                    keys["esc"] = true;
                    break;
            }
        }
        if ( event.type == SDL_KEYUP )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_a:
                    keys["a"] = false;
                    break;
                case SDLK_b:
                    keys["b"] = false;
                    break;
                case SDLK_c:
                    keys["c"] = false;
                    break;
                case SDLK_d:
                    keys["d"] = false;
                    break;
                case SDLK_e:
                    keys["e"] = false;
                    break;
                case SDLK_f:
                    keys["f"] = false;
                    break;
                case SDLK_g:
                    keys["g"] = false;
                    break;
                case SDLK_h:
                    keys["h"] = false;
                    break;
                case SDLK_i:
                    keys["i"] = false;
                    break;
                case SDLK_j:
                    keys["j"] = false;
                    break;
                case SDLK_k:
                    keys["k"] = false;
                    break;
                case SDLK_l:
                    keys["l"] = false;
                    break;
                case SDLK_m:
                    keys["m"] = false;
                    break;
                case SDLK_n:
                    keys["n"] = false;
                    break;
                case SDLK_o:
                    keys["o"] = false;
                    break;
                case SDLK_p:
                    keys["p"] = false;
                    break;
                case SDLK_q:
                    keys["q"] = false;
                    break;
                case SDLK_r:
                    keys["r"] = false;
                    break;
                case SDLK_s:
                    keys["s"] = false;
                    break;
                case SDLK_t:
                    keys["t"] = false;
                    break;
                case SDLK_u:
                    keys["u"] = false;
                    break;
                case SDLK_v:
                    keys["v"] = false;
                    break;
                case SDLK_w:
                    keys["w"] = false;
                    break;
                case SDLK_x:
                    keys["x"] = false;
                    break;
                case SDLK_y:
                    keys["y"] = false;
                    break;
                case SDLK_z:
                    keys["z"] = false;
                    break;
                case SDLK_0:
                    keys["0"] = false;
                    break;
                case SDLK_1:
                    keys["1"] = false;
                    break;
                case SDLK_2:
                    keys["2"] = false;
                    break;
                case SDLK_3:
                    keys["3"] = false;
                    break;
                case SDLK_4:
                    keys["4"] = false;
                    break;
                case SDLK_5:
                    keys["5"] = false;
                    break;
                case SDLK_6:
                    keys["6"] = false;
                    break;
                case SDLK_7:
                    keys["7"] = false;
                    break;
                case SDLK_8:
                    keys["8"] = false;
                    break;
                case SDLK_9:
                    keys["9"] = false;
                    break;
                case SDLK_UP:
                    keys["up"] = false;
                    break;
                case SDLK_DOWN:
                    keys["down"] = false;
                    break;
                case SDLK_LEFT:
                    keys["left"] = false;
                    break;
                case SDLK_RIGHT:
                    keys["right"] = false;
                    break;
                case SDLK_RETURN:
                    keys["return"] = false;
                    break;
                case SDLK_BACKSPACE:
                    keys["backspace"] = false;
                    break;
                case SDLK_LSHIFT:
                    keys["lshift"] = false;
                    break;
                case SDLK_RSHIFT:
                    keys["rshift"] = false;
                    break;
                case SDLK_LALT:
                    keys["lalt"] = false;
                    break;
                case SDLK_RALT:
                    keys["ralt"] = false;
                    break;
                case SDLK_LCTRL:
                    keys["lctrl"] = false;
                    break;
                case SDLK_RCTRL:
                    keys["rctrl"] = false;
                    break;
                case SDLK_F1:
                    keys["F1"] = false;
                    break;
                case SDLK_F2:
                    keys["F2"] = false;
                    break;
                case SDLK_F3:
                    keys["F3"] = false;
                    break;
                case SDLK_F4:
                    keys["F4"] = false;
                    break;
                case SDLK_F5:
                    keys["F5"] = false;
                    break;
                case SDLK_F6:
                    keys["F6"] = false;
                    break;
                case SDLK_F7:
                    keys["F7"] = false;
                    break;
                case SDLK_F8:
                    keys["F8"] = false;
                    break;
                case SDLK_F9:
                    keys["F9"] = false;
                    break;
                case SDLK_F10:
                    keys["F10"] = false;
                    break;
                case SDLK_F11:
                    keys["F11"] = false;
                    break;
                case SDLK_F12:
                    keys["F12"] = false;
                    break;
                case SDLK_ESCAPE:
                    keys["esc"] = false;
                    break;
            }
        }
        if( event.type == SDL_MOUSEBUTTONUP )
        {
            switch( event.button.button )
            {
                case SDL_BUTTON_LEFT:
                    mouseLeft = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseRight = false;
                    break;
            }
        }
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            mousex = event.button.x;
            mousey = event.button.y;
            switch( event.button.button )
            {
                case SDL_BUTTON_LEFT:
                    mouseRight = false;
                    mouseLeft = true;
                    //Do Something On Mouse Button Left
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseLeft = false;
                    mouseRight = true;
                    //Do Something On Mouse Button Right
                    break;
                case SDL_BUTTON_MIDDLE:
                    //Do Something On Mouse Button Middle
                    break;
                case SDL_BUTTON_WHEELUP:
                    //Do Something On Mouse Wheel Up
                    break;
                case SDL_BUTTON_WHEELDOWN:
                    //Do Something On Mouse Wheel Down
                    break;
                default:
                    break;
            }
        }
        if( event.type == SDL_MOUSEMOTION )
        {
            SDL_GetMouseState(&mousex, &mousey);
            //Do Something On Mouse Move
        }
    }
}

bool GameEngine::KeyDown( std::string key )
{
    iter = keys.find( key );
    if( iter != keys.end() )
    {
        return iter->second;
    }else{
        return false;
    }
}

bool GameEngine::KeyUp( std::string key )
{
    iter = keys.find( key );
    if( iter != keys.end() )
    {
        return !iter->second;
    }else{
        return true;
    }
}

int GameEngine::Collision()
{

}

int GameEngine::Sleep( int duration )
{
    if( duration == -1 ){
        int newTime = SDL_GetTicks();
        int deltaTime = newTime - oldTime;
        if( deltaTime < 1000 / fps )
        {
            SDL_Delay( ( 1000 / fps ) - deltaTime );
            oldTime = newTime;
        }
    }else{
        SDL_Delay( duration );
    }
    return 0;
}

void GameEngine::Update()
{
    level->Update();
    text->Update();
    renderer->Update();
}

Level *GameEngine::LoadLevel( std::string mapname )
{
    cout << mapname << endl;
    level = new Level( mapname );
    return level;
}

Level *GameEngine::GetLevel()
{
    return level;
}

void GameEngine::SetQuit()
{
    quit = true;
}

bool GameEngine::Quit()
{
    return quit;
}
