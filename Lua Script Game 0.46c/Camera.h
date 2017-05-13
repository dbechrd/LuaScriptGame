#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Character.h"

class Character;
enum cameramodes { CAM_FREEZE = 0, CAM_FOLLOW_CHARACTER = 1, CAM_SCRIPT_DRIVEN = 2 };

class Camera{
    private:
        static Camera* pinstance;
        SDL_Rect rect;
        int speed;
        int mode;
        Character *charToFollow;
    protected:
        Camera();
        Camera(const Camera&);
        Camera& operator= (const Camera&);
    public:
        static Camera* Instance();

        int X(){ return rect.x; }
        void SetX( int newx ){ rect.x = newx; }

        int Y(){ return rect.y; }
        void SetY( int newy ){ rect.y = newy; }

        int W(){ return rect.w; }
        void SetW( int neww ){ rect.w = neww; }

        int H(){ return rect.h; }
        void SetH( int newh ){ rect.h = newh; }

        void SetPos( int newx, int newy ){ rect.x = newx; rect.y = newy; }
        void SetSize( int neww, int newh ){ rect.w = neww; rect.h = newh; }

        SDL_Rect *Rect(){ return &rect; }
        void SetRect( SDL_Rect *newrect = NULL ){ rect.x = newrect->x; rect.y = newrect->y; rect.w = newrect->w; rect.h = newrect->h; }

        int Speed(){ return speed; }
        void SetSpeed( int newspeed ){ speed = newspeed; }

        void SetChar( Character *follow = NULL );

        int Mode(){ return mode; }
        void SetMode( int newmode ){ mode = newmode; }

        void Update();
};

#endif // CAMERA_H_INCLUDED
