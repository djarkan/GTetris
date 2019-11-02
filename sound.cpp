/* #include "sound.h"

sound::sound()
{

}

sound::~sound()
{

}

void sound::loadSoundInVector(std::string title)
{
    soundVector.push_back(std::make_unique<Mix_Chunk>(Mix_LoadWAV("toto.wav")));
}

void sound::loadMusicInVector(std::string title)
{
    MusicVector.push_back(std::make_unique<Mix_Music>(Mix_LoadMUS("toto.mp3")));
}

void sound::playSoundInVector(int soundNB)
{
    Mix_PlayChannel( -1, &soundVector[soundNB], 0 );
}

void sound::playMusicInVector(int soundNB)
{
    Mix_PlayMusic( &MusicVector[soundNB], -1 );
}
*/
