#include "TextEngine.h"
#include "RenderEngine.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

TextEngine* TextEngine::pinstance = 0;
TextEngine* TextEngine::Instance( std::string filename )
{
	//Create single instance if it doesn't already exist (singleton pattern)
    if (pinstance == 0) 
    {
        pinstance = new TextEngine( filename );
    }
    return pinstance;
}

TextEngine* TextEngine::Instance()
{
    if (pinstance == 0)
    {
        return NULL;
    }
    return pinstance;
}

TextEngine::TextEngine( std::string filename )
{
    renderer = RenderEngine::Instance();

    filename = "resources\\" + filename;
    font = new Font( filename );

    curData = NULL;
    oldTime = SDL_GetTicks();
}

TextEngine::~TextEngine()
{
    delete font;
    std::cout << "Terminating Text Engine\n";
}

void TextEngine::DebugString( std::string message, int x, int y, bool screenCoords )
{
    //Generate surface from message and render it
    SDL_Surface *msgSurface = font->Draw( message );

    if( screenCoords ){
        renderer->DisableWorldCoords();
    }
    renderer->Draw( x, y, msgSurface );
}

void TextEngine::Textbox( std::string title, std::string message, int delay, int x, int y, bool screenCoords )
{
    //Generate surface from message
    SDL_Surface *titleSurface = font->Draw( title );
    SDL_Surface *msgSurface = font->Draw( message );

    //Create new textbox data object and queue it
    textboxes.push( new TextData( titleSurface, msgSurface, delay, x, y, screenCoords ) );
}

void TextEngine::Update()
{
    //No textboxes being shown but at least one in queue
    if( curData == NULL && !textboxes.empty() ){
        std::cout.flush();
        curData = textboxes.front();
        oldTime = SDL_GetTicks();
    //Textbox being shown
    }else if( curData != NULL ){
        std::cout.flush();
        //Time since last successful update
        int deltaTime = SDL_GetTicks() - oldTime;

        //Time to update again
        if( deltaTime >= curData->delay ){
            textboxes.pop();
            delete curData;
            curData = NULL;
        }
    }

    if( curData != NULL ){
        if( curData->screenCoords ){
            renderer->DisableWorldCoords();
        }
        renderer->Draw( curData->x, curData->y - 20, curData->title );
        if( curData->screenCoords ){
            renderer->DisableWorldCoords();
        }
        renderer->Draw( curData->x, curData->y, curData->text );
    }
}
