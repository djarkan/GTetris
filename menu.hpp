#ifndef    __menu__
#define    __menu__

#include <SFML/Graphics.hpp>
#include <SFML/Window/mouse.hpp>
#include "json\json.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include<clocale>
#include "button.hpp"
#include "screenmanagement.hpp"
#include "mouseevent.hpp"
#include "setup.hpp"
#include "timer.hpp"
#include "game.hpp"
#include "jsonfile.hpp"
#include "eventreader.hpp"
#include "sound.hpp"
#include "music.hpp"
#include "statistics.hpp"
#include "help.hpp"

class menu{

public:

    menu();
    menu(sf::Uint32 style);
    bool initMenu();
    void loadButtons(std::string buttonConfig);
    void drawAllButtons();
    int  checkButtonsAction();
    bool launchAction(int buttonID);
    void setPlayMenu();
    void parametersMenu();
    void saveSetUp();
    void savePseudo();
    void playMenu();
    void displayPlayerStats();
    void helpMenu();
    void errorMessage();

    setup m_setup;
    sf::Uint32 m_style;
    manageScreen screen;//(sf::Uint32 style);
    sound gameSound;
    music gameMusic;
    statistics playerStats;
    help help;
    int helpPage{0};
    jsonFile m_gameTtranslation;
    std::vector<std::unique_ptr<button>> m_buttonList;

private:
    void saveJsonSetup(const std::string fileName);
    void setSetUp();
    void printLabels();
    void printParameters();
    void setLocale(int language);
    void setSoundVolume(float soundVolume);
    void setMusicVolume(float musicVolume);

    jsonFile m_jsonConfig;
    jsonFile m_menuLabels;
    jsonFile m_jsonSetup;
    mouseEvent mouseEvent;
    eventReader eventReader;
    sf::Cursor myCursor;

};
#endif
