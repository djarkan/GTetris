#include "music.hpp"

bool music::loadSong(std::string title)
{
    return m_music.openFromFile(title);
}

void music::setMusicVolume(const float volume)
{
    m_music.setVolume(volume);
}

void music::setMusicLoop(bool loop)
{
    m_music.setLoop(loop);
}

bool music::initMusic()
{
    if(loadSong("music\\A Theme.flac")) {
        setMusicLoop(true);
        return true;
    }
    else { return false; }
}

void music::playSong()
{
    m_music.play();
}

void music::stopSong()
{
    m_music.stop();
}
