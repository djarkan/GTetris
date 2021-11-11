#include <iostream>
#include "menu.hpp"


int main()
{
    menu menu;
    if(!menu.loadJsonFiles("config.json", "setup.json")) {
        std::cout << "pb lecture fichiers json.\n";
        return -1;
    }

    menu.screen.loadBitmapFile("graphics\\graphics.png");
    menu.screen.loadFontFile("oneslot.ttf");

    menu.playMenu(menu.screen);
    return 0;
}
