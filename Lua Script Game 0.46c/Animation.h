#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "SDL/SDL.h"

class Animation{
    protected:

        //current frame of animation
        int currentFrame;

        //delay in milliseconds between frames if animating
        int delay;

        //should the animation be playing
        bool animate;

        //oscillation pattern 0 1 2 3 4 3 2 1 0
        bool oscillate;

    public:

        virtual int GetCurrentFrame();
        virtual void SetCurrentFrame( int frame );
        virtual int GetDelay();
        virtual void SetDelay( int newdelay );
        virtual bool GetAnimate();
        virtual void SetAnimate( bool state );
        virtual bool GetOscillate();
        virtual void SetOscillate( bool state );
        virtual int Draw();
};

#endif // ANIMATION_H_INCLUDED
