#include <iostream>
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "RenderEngine.h"

using namespace std;

RenderEngine* RenderEngine::pinstance = NULL;
RenderEngine* RenderEngine::Instance()
{
    if (pinstance == NULL)
    {
        pinstance = new RenderEngine;
    }
    return pinstance;
}

RenderEngine::RenderEngine()
{
    camera = NULL;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        cout << "SDL_Init Error\n";
    }

    if( TTF_Init() == -1 )
    {
        cout << "TTF_Init Error\n";
    }

    SDL_Surface *screen;

    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT );

    if( screen == NULL )
    {
        cout << "SDL_SetVideoMode Error\n";
    }

    fullScreen = false;
    worldCoords = true;
    resetCoords = false;

    surfaces["screen"] = screen;

    SDL_WM_SetCaption( "Lua Script Game", NULL );

    camera = Camera::Instance();
}

RenderEngine::~RenderEngine()
{
    for( iter = surfaces.begin(); iter != surfaces.end(); iter++ )
    {
        SDL_FreeSurface( iter->second );
    }
    surfaces.clear();

    SDL_Quit();

    cout << "Terminating Render Engine\n";
}

void RenderEngine::ToggleFullScreen()
{
    if (fullScreen == false){
        SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_FULLSCREEN );
    }else{
        SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT );
    }

    fullScreen = !fullScreen;
}

SDL_Surface *RenderEngine::LoadSurface( std::string filename )
{
    for( iter = surfaces.begin(); iter != surfaces.end(); iter++ )
    {
        if( filename == iter->first )
        {
            std::cout << "Existing Surface - Not loaded again (Yay Success!)\n";
            return iter->second;
        }
    }

    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF ) );
        }
    }else{
        return NULL;
    }

    surfaces[filename] = optimizedImage;

    return optimizedImage;
}

void RenderEngine::UnloadSurface( std::string surface )
{
    iter = surfaces.find( surface );
    SDL_FreeSurface( iter->second );
    surfaces.erase( iter );
}

SDL_Rect RenderEngine::GetSurfaceRect( std::string surface )
{
    return surfaces[surface]->clip_rect;
}

void RenderEngine::EnableWorldCoords()
{
    worldCoords = true;
}

void RenderEngine::DisableWorldCoords( bool permanant )
{
    worldCoords = false;
    if( !permanant ){
        resetCoords = true;
    }
}

void RenderEngine::Draw( int x, int y, SDL_Surface *surfacesource, SDL_Surface *surfacedest, SDL_Rect* clip )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //World coords as opposed to screen coords (which disregard camera position)
    if( worldCoords ){
        offset.x -= camera->Rect()->x;
        offset.y -= camera->Rect()->y;
    }else if( resetCoords ){
        worldCoords = true;
        resetCoords = false;
    }

    if( surfacedest == NULL )
    {
        SDL_BlitSurface( surfacesource, clip, surfaces["screen"], &offset );
    }else{
        SDL_BlitSurface( surfacesource, clip, surfacedest, &offset );
    }
}

void RenderEngine::Update( SDL_Surface *surface )
{
    if( surface == NULL )
    {
        SDL_Flip(surfaces["screen"]);
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
    }else{
        SDL_Flip(surface);
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
    }
}
