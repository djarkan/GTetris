#ifndef    __menu__
#define    __menu__

#include <iostream>
#include <vector>
#include "button.h"
#include "screenmanagement.h"

class menu{
private:
    std::vector <std::string> setupToPrint;
    std::vector <button> buttonList;

public:
    menu();
    ~menu();
    void pause(manageScreen &screen);

};
#endif
