#ifndef    __sound__
#define    __sound__

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <memory>

class sound{
public:
    bool initSounds();
    void setSoundLoop(int soundNumber, bool yes);
    void playSound(const int thatSound);
    void setSoundVolume(const float volume);

private:
    bool loadFileSounds();
    void assignSoundsToBuffers();

    std::array<sf::SoundBuffer, 10> m_soundBuffer;
    std::array<sf::Sound, 10> m_sound;
};
#endif
