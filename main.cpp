#include "menu.hpp"
#include <SFML/Window/WindowStyle.hpp>
#include "jsonfile.hpp"

int main()
{
    jsonFile setupFile;
    if(setupFile.loadJsonFile("setup.json")) {
        sf::Uint32 style;
        if(setupFile.m_Root["setUp"].get("windowed",1).asBool()) { style = sf::Style::Close; }
        else { style = sf::Style::Fullscreen; }
        menu menu(style);
        if(!menu.initMenu()) {
            menu.errorMessage();
            return -1;
        }
        menu.playMenu();
        return 0;
    }
}
