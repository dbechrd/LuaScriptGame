#include "AnimationData.h"
#include <iostream>
#include "SDL/SDL.h"

AnimationData::AnimationData( int new_startFrame, int new_totalFrames, int new_delay, int new_flag )
{
    startFrame = new_startFrame;
    currentFrame = new_startFrame;
    totalFrames = new_totalFrames;
    endFrame = startFrame + (totalFrames - 1);
    delay = new_delay;
    delayOld = SDL_GetTicks();
    flag = new_flag;
    flagChanged = false;
    animForward = true;
}

void AnimationData::Reset()
{
    flag = FREEZE;
    currentFrame = startFrame;
}

void AnimationData::SetFlag( int new_Flag )
{
    flag = new_Flag;
    flagChanged = true;
}

int AnimationData::Update()
{
    if( flag != FREEZE ){
        int delayNew = SDL_GetTicks();

        if( flagChanged ){
            delayOld = delayNew;
            flagChanged = false;
        }

        if( delayNew - delayOld >= delay )
        {
            delayOld = delayNew;

            switch( flag )
            {
                //No animation
                case FREEZE:
                    break;
                //Loop Normally
                case LOOP:
                    if( currentFrame < endFrame )
                    {
                        currentFrame += 1;
                    }else if( currentFrame == endFrame ){
                        currentFrame = startFrame;
                    }
                    break;
                //Oscillate
                case OSC:
                    if( currentFrame > startFrame && currentFrame < endFrame )
                    {
                        if( animForward == true )
                        {
                            currentFrame += 1;
                        }else{
                            currentFrame -= 1;
                        }
                    }else if( currentFrame == startFrame ){
                        currentFrame += 1;
                        animForward = true;
                    }else if( currentFrame == endFrame ){
                        currentFrame -= 1;
                        animForward = false;
                    }
                    break;
            }
            return 1;
        }else{
            return 0;
        }
    }else{
        if( flagChanged ){
            int delayNew = SDL_GetTicks();

            if( delayNew - delayOld >= 200 )
            {
                Reset();
                flagChanged = false;
            }
        }
    }
}
