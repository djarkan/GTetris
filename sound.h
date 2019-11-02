#ifndef    __sound__
#define    __sound__

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <memory>

class sound{
public:
    sound();
    ~sound();
    void loadSoundInVector(std::string title);
    void loadMusicInVector(std::string title);
    void playSoundInVector(int soundNB);
    void playMusicInVector(int soundNB);

private:
    std::vector<std::unique_ptr<Mix_Chunk>> soundVector;
    std::vector<std::unique_ptr<Mix_Music>> MusicVector;
};
#endif
