#ifndef    __sound__
#define    __sound__

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <memory>

class sound{
public:
 //   sound();
    void initSounds();
    void setSoundLoop(int soundNumber, bool yes);
    void playSound(const int thatSound);
    void setSoundVolume(const float volume);

private:
    bool loadFileSounds();
    void assignSoundsToBuffers();

    std::array<sf::SoundBuffer, 15> m_soundBuffer;
    std::array<sf::Sound, 15> m_sound;
};
#endif
