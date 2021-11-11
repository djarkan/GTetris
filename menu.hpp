#ifndef    __menu__
#define    __menu__

#include <SFML/Graphics.hpp>
#include <SFML/Window/mouse.hpp>
#include "json\json.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include<clocale>
#include "button.h"
#include "screenmanagement.h"
#include "mouseevent.hpp"
#include "setup.hpp"
#include "timer.h"
#include "game.h"

class menu{

public:
    menu();
    bool loadJsonFiles(const std::string fileName1, const std::string fileName2);
    void loadButtons(std::string buttonConfig);
    void drawAllButtons(manageScreen& screen);
    int  checkButtonsAction(sf::RenderWindow &window);
    bool launchAction(int buttonID, manageScreen& screen);
    void setPlayMenu(manageScreen& screen);
    void parametersMenu(manageScreen& screen);
    void saveSetUp();
    void savePseudo();
    void playMenu(manageScreen& screen);

    setup m_setup;
    game game;
    manageScreen screen;
    std::vector<std::unique_ptr<button>> m_buttonList;

private:
    void saveJsonSetup(const std::string fileName);
    void setSetUp();
    void printLabels(manageScreen& screen);
    void printParameters(manageScreen& screen);
    int setxParam(int labelSize);
    void setLocale(int language);

    Json::Value m_configRoot;
    Json::Value m_setupRoot;
    mouseEvent mouseEvent;

};
#endif





