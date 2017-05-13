#ifndef ANIMATIONDATA_H_INCLUDED
#define ANIMATIONDATA_H_INCLUDED

#include <vector>

enum animFlag{ FREEZE = 0, LOOP = 1, OSC = 2 };

class AnimationData{
    private:
        int startFrame;
        int currentFrame;
        int totalFrames;
        int endFrame;
        int delay;
        int delayOld;
        int flag;
        bool flagChanged;
        bool animForward;
    public:
        AnimationData( int new_startFrame, int new_totalFrames, int new_delay, int new_flag );

        int StartFrame(){ return startFrame; }
        int TotalFrames(){ return totalFrames; }
        int CurrentFrame(){ return currentFrame; }
        void Reset();
        int Delay(){ return delay; }
        void SetDelay( int new_delay ){ delay = new_delay; }
        int Flag(){ return flag; }
        void SetFlag( int new_Flag );
        int Update();
};

#endif // ANIMATIONDATA_H_INCLUDED
