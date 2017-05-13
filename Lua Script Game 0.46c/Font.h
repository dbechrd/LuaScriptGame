#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

class Font{
    private:
        TTF_Font *font;
        SDL_Color color;
    public:
        Font( std::string filename, int size = 16 );
        ~Font();
        SDL_Surface *Font::Draw( std::string text );
};

#endif // FONT_H_INCLUDED
