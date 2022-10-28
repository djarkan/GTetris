#include "sound.hpp"
#include <array>
#include <iostream>

bool sound::loadFileSounds()
{
    bool flag = m_soundBuffer[0].loadFromFile("sound\\harddrop.ogg");

    flag &= m_soundBuffer[1].loadFromFile("sound\\rotation.ogg");
    flag &= m_soundBuffer[2].loadFromFile("sound\\softdrop.ogg");
    flag &= m_soundBuffer[3].loadFromFile("sound\\ouverturemenu.ogg");
    flag &= m_soundBuffer[4].loadFromFile("sound\\levelchgt.ogg");
    flag &= m_soundBuffer[5].loadFromFile("sound\\complitedlines.ogg");
    flag &= m_soundBuffer[6].loadFromFile("sound\\departfinpartie.ogg");
    flag &= m_soundBuffer[7].loadFromFile("sound\\savequitparam.ogg");
    flag &= m_soundBuffer[8].loadFromFile("sound\\decomptetimer.ogg");
    flag &= m_soundBuffer[9].loadFromFile("sound\\startparty.ogg");
    return flag;
}

void sound::assignSoundsToBuffers()
{
    for(auto i = 0; i < 10; ++i){
        m_sound[i].setBuffer(m_soundBuffer[i]);
    }
}

bool sound::initSounds()
{
    if(loadFileSounds()) {
        assignSoundsToBuffers();
        return true;
    }
    else { return false; }
}

void sound::setSoundLoop(int soundNumber, bool yes)
{
    m_sound[soundNumber].setLoop(yes);
}

void sound::setSoundVolume(const float volume)
{
    for(auto i = 0; i < 15; ++i){
        m_sound[i].setVolume(volume);
    }
}

void sound::playSound(const int thatSound)
{
    m_sound[thatSound].play();
}
