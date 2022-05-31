#include <iostream>
#include "menu.hpp"


int main()
{
    menu menu;
    if(!menu.initMenu()) {
        std::cout << "pb lecture fichiers json.\n";
        return -1;
    }

    menu.screen.loadBitmapFile("graphics\\graphics.png");
    menu.screen.loadFontFile("font\\oneslot.ttf");

    menu.playMenu();
    return 0;
}
