#include "SDL.h"
#include "SDL/SDL_audio.h"
#include "base.h"
#include <SDL/SDL_mixer.h>
#ifndef _SOUNDH_

#define _SOUNDH_

class Sound : public Base{
        Mix_Chunk *chunk;
        Mix_Music *music;
        int channel,type, volume, distance, angle;
        bool fail;
    public:
        Sound(char *s,int type);
        ~Sound();
        void play();
        void play(int);
        void play(int,int);
        void playFadeIn(int, int, int);
        void playFadeIn(int, int, int, int);
        void pauseAll();
        void pause();
        void resumeAll();
        void resume();
        void stopAll();
        void stopFadeOutAll(int);
        void stop();
        void stopFadeOut(int);
        int getVolume();
        void setVolume(int);
        void increaseVolume(int);
        void decreaseVolume(int);
        void setAllVolumes(int);
        void setPosition(int, int);
};

    //Mix_Chunk *burr  = Mix_LoadWAV( "data/burr.wav" );
    //Mix_PlayChannel( -1, burr, 0 );
#endif // _SOUNDH_
