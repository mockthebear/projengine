///         Projeej (Projengine)
///
///         Criado por Matheus Braga Almeida (Mock the bear)
///         Com auxilio de Gabriel Botelho
///         E professor Rodrigo Bonifácio
///
///         Materia Programação orientada a objetos 1/2013
///
///         Não redistribuir sem autorização de Matheus Braga
///

#include "sound.h"


Sound::Sound(char *s, int type){
      this->type = type;
    if (type == 1){

      chunk = Mix_LoadWAV(s);
      if (chunk == NULL)
            fail = true;
      else
            fail = false;

    }else{

      music = Mix_LoadMUS(s);
      if (music == NULL)
            fail = true;
      else
            fail = false;

    }
    volume = MIX_MAX_VOLUME;
    CTYPE = SOUND;
    distance = 0;
    angle = 0;
}

Sound::~Sound(){
    if (type != 1){
        Mix_FreeMusic(music);
    }else{
        Mix_FreeChunk(chunk);
    }
}

void Sound::play(){
    if (!fail){
        if (type == 1)
            channel = Mix_PlayChannel( -1, chunk, 0);
        else
            Mix_PlayMusic(music, -1);
    }
}

void Sound::play(int i){
    if (!fail){
        if (type == 1)
            channel = Mix_PlayChannel( i, chunk, 0 );
        else
            Mix_PlayMusic(music, 0);
    }
}

void Sound::play(int i,int loop){
    if (!fail){
        if (type == 1)
            channel = Mix_PlayChannel( i, chunk, loop);
        else
            Mix_PlayMusic(music, loop);
    }
}

void Sound::playFadeIn(int loop, int duration, int ticks){
      if(!fail){
            if(type == 1)
                  channel = Mix_FadeInChannelTimed(-1, chunk, loop, duration, ticks);
            else
                  Mix_FadeInMusic(music, loop, duration);
      }
}

void Sound::playFadeIn(int i, int loop, int duration, int ticks){
      if(!fail){
            if(type == 1)
                  channel = Mix_FadeInChannelTimed( i, chunk, loop, duration, ticks);
            else
                  Mix_FadeInMusic(music, loop, duration);
      }
}

void Sound::pauseAll(){
      if (!fail){
                  Mix_Pause(-1);
                  Mix_PauseMusic();
            }

}

void Sound::pause(){
      if (!fail){
            if(type == 1)
                  Mix_Pause(channel);
            else
                  Mix_PauseMusic();
      }
}

void Sound::resumeAll(){
      if (!fail){
                  Mix_Resume(-1);
                  Mix_ResumeMusic();
            }

}

void Sound::resume(){
      if (!fail){
            if(type == 1)
                  Mix_Resume(channel);
            else
                  Mix_ResumeMusic();
            }

}

void Sound::stopAll(){
      if (!fail){
            Mix_HaltChannel(-1);
            Mix_HaltMusic();
      }
}

void Sound::stopFadeOutAll(int duration){
      if (!fail){
            Mix_FadeOutChannel(-1, duration);
            Mix_FadeOutMusic(duration);
      }
}

void Sound::stop(){
      if (!fail){
            if(type == 1)
                  Mix_HaltChannel(channel);
            else
                  Mix_HaltMusic();
      }
}

void Sound::stopFadeOut(int duration){
      if (!fail){
            if(type == 1)
                  Mix_FadeOutChannel(channel, duration);
            else
                  Mix_FadeOutMusic(duration);
      }
}

int Sound::getVolume(){
      if (!fail){
            if (type == 1)
                  volume = Mix_Volume(channel, -1);
            else
                  volume = Mix_VolumeMusic(-1);
            return volume;
      }
      return 0;
};

void Sound::setVolume(int volume){
      if (!fail){
            this->volume = volume;
            if (type == 1)
                  Mix_Volume(channel, volume);
            else
                  Mix_VolumeMusic(volume);
            volume = getVolume();
      }
};

void Sound::increaseVolume(int amount){
      if (!fail){
            volume = getVolume() + amount;
            if (type == 1)
                  Mix_Volume(channel, volume);
            else
                  Mix_VolumeMusic(volume);
            volume = getVolume();
      }
};

void Sound::decreaseVolume(int amount){
      if (!fail){
            volume = getVolume() - amount;
            if (type == 1)
                  Mix_Volume(channel, volume);
            else
                  Mix_VolumeMusic(volume);
            volume = getVolume();
      }
};

void Sound::setAllVolumes(int volume){
      if (!fail){
            Mix_Volume(-1, volume);
            Mix_VolumeMusic(volume);
      }
};

void Sound::setPosition(int distance, int angle){
      if(distance<0) this->distance = 0;
      else if(distance>255) this->distance = 255;
      else this->distance = distance;
      this->angle = angle%360;
      Mix_SetPosition(channel, this->angle, this->distance);
}
