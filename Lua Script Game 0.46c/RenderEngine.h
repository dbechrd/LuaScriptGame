#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Camera.h"

class Camera;

class RenderEngine{
    private:

        static RenderEngine* pinstance;

        bool fullScreen;
        bool worldCoords;
        bool resetCoords;

        std::map<std::string, SDL_Surface*> surfaces;
        std::map<std::string, SDL_Surface*>::iterator iter;

        Camera *camera;

    protected:

        RenderEngine();
        RenderEngine(const RenderEngine&);
        RenderEngine& operator= (const RenderEngine&);

    public:

        static RenderEngine* Instance();
        ~RenderEngine();

        void ToggleFullScreen();

        SDL_Surface *LoadSurface( std::string filename );
        SDL_Rect GetSurfaceRect( std::string surface );
        void UnloadSurface( std::string surface );

        void EnableWorldCoords();
        void DisableWorldCoords( bool permanant = false );

        void Draw( int x, int y, SDL_Surface *surfacesource, SDL_Surface *surfacedest = NULL, SDL_Rect* clip = NULL );
        void Update( SDL_Surface *surface = NULL );
};

#endif // RENDER_H_INCLUDED
