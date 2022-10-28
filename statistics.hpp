#ifndef __STATISTICS__
#define __STATISTICS__

#include <fstream>
#include <string>
#include "jsonfile.hpp"
#include "pattern.hpp"

class statistics
{
    public:
        statistics();

        bool loadPlayerStats(const std::string title);
        void savePlayerStats(const std::string title);
        void createPlayerStats(const std::string title);
        void addPatternsToStats(const pattern& pattern);

        jsonFile m_playerStatsFile;
        unsigned int m_singleline;
        unsigned int m_tetris;
        unsigned int m_Tspin;
        unsigned int m_Tspinsingle;
        unsigned int m_Tspindouble;
        unsigned int m_Tspintriple;
        unsigned int m_miniTspin;
        unsigned int m_miniTspinsingle;
        unsigned int m_miniTspindouble;
        unsigned int m_clearBoard;
        unsigned int m_backToBack;

    private:
        std::string m_emptyStats{ "{ \"stats\" : { \"singlelines\" : 0, \"tetris\" : 0, \"Tspin\" : 0, \"Tspinsingle\" : 0, \"Tspindouble\" : 0, \"Tspintriple\" : 0, \"miniTspin\" : 0, \"miniTspinsingle\" : 0, \"miniTspindouble\" : 0, \"clear\" : 0, \"backtoback\" : 0  } }"  };

};

#endif
