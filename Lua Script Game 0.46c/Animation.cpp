#include "Animation.h"

int Animation::GetCurrentFrame()
{
    return currentFrame;
}

void Animation::SetCurrentFrame( int frame )
{
    currentFrame = frame;
}

int Animation::GetDelay()
{
    return delay;
}

void Animation::SetDelay( int newdelay )
{
    delay = newdelay;
}

bool Animation::GetAnimate()
{
    return animate;
}

void Animation::SetAnimate( bool state )
{
    animate = state;
}

bool Animation::GetOscillate()
{
    return oscillate;
}

void Animation::SetOscillate( bool state )
{
    oscillate = state;
}

int Animation::Draw()
{
    //Draw
}
