#ifndef TEXTENGINE_H_INCLUDED
#define TEXTENGINE_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Font.h"
#include "RenderEngine.h"
#include <queue>
#include <string>

struct TextData{
    public:

        //Title and message to display
        SDL_Surface *title;
        SDL_Surface *text;

        //How long (ms) to display text
        int delay;

        //Optional coords
        int x;
        int y;

        //If true coords are relative to the world not the screen
        bool screenCoords;

        //Set values
        TextData::TextData( SDL_Surface *ntitle, SDL_Surface *ntext, int ndelay, int nx, int ny, bool nscreenCoords )
        {
            title = ntitle;
            text = ntext;
            delay = ndelay;
            x = nx;
            y = ny;
            screenCoords = nscreenCoords;
        }

        //Free surface
        TextData::~TextData()
        {
            SDL_FreeSurface( text );
        }
};

class TextEngine{
    private:

        //Singleton instance
        static TextEngine* pinstance;

        //Renderer instance
        RenderEngine *renderer;

        //std::vector<Font*> fonts;
        Font *font;

        //Queue of textboxes to be shown
        std::queue<TextData*> textboxes;

        //Data for current textbox
        TextData *curData;

        //Time since last update
        int oldTime;

    protected:

        //Singleton constructor and assignment protection
        TextEngine( std::string filename );
        TextEngine(const TextEngine&);
        TextEngine& operator= (const TextEngine&);

    public:

        static TextEngine* Instance( std::string filename );
        static TextEngine* Instance();
        ~TextEngine();
        void TextEngine::DebugString( std::string message, int x = 0, int y = 0, bool screenCoords = true );
        void Textbox( std::string title, std::string message, int delay, int x = 0, int y = 0, bool screenCoords = true );
        void Update();

};

#endif // TEXTENGINE_H_INCLUDED
