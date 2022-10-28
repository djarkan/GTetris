#ifndef    __help__
#define    __help__

#include <string>
#include "screenmanagement.hpp"
#include "jsonfile.hpp"
#include "sound.hpp"

class help{
    public:
            help();
            void displayHelpPage(manageScreen &screen, int pageIndex, int language);
            bool loadHelpText();

    private:
        jsonFile m_helpText;

};

#endif
