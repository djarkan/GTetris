#ifndef    __music__
#define    __music__

#include <SFML/Audio.hpp>
#include <string>

class music{
public:
    bool initMusic();
    void setMusicVolume(const float volume);
    void playSong();
    void stopSong();

    sf::Music m_music;

private:
    bool loadSong(std::string title);
    void setMusicLoop(bool loop);


};
#endif
