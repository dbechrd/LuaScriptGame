#include "Font.h"
#include <iostream>
#include <string>

using namespace std;

Font::Font( std::string filename, int size )
{
    font = NULL;
    font = TTF_OpenFont( filename.c_str(), size );

    if( font == NULL )
    {
        cout << "Error loading font: " << filename << endl;
    }

    color.r = 255;
    color.g = 255;
    color.b = 255;
}

Font::~Font()
{
	delete font;
    cout << "Font Freed\n";
}

SDL_Surface *Font::Draw( std::string text )
{
    SDL_Surface *fontSurface = TTF_RenderText_Solid( font, text.c_str(), color );
    return fontSurface;
}
