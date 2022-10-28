#include "statistics.hpp"

statistics::statistics()
{

}

bool statistics::loadPlayerStats(const std::string title)
{
    bool flag = m_playerStatsFile.loadJsonFile(title);
    m_singleline = m_playerStatsFile.m_Root["stats"].get("singlelines",0).asInt();
    m_tetris = m_playerStatsFile.m_Root["stats"].get("tetris",0).asInt();
    m_Tspin = m_playerStatsFile.m_Root["stats"].get("Tspin",0).asInt();
    m_Tspinsingle = m_playerStatsFile.m_Root["stats"].get("Tspinsingle",0).asInt();
    m_Tspindouble = m_playerStatsFile.m_Root["stats"].get("Tspindouble",0).asInt();
    m_Tspintriple =  m_playerStatsFile.m_Root["stats"].get("Tspintriple",0).asInt();
    m_miniTspin = m_playerStatsFile.m_Root["stats"].get("miniTspin",0).asInt();
    m_miniTspinsingle = m_playerStatsFile.m_Root["stats"].get("miniTspinsingle",0).asInt();
    m_miniTspindouble = m_playerStatsFile.m_Root["stats"].get("miniTspindouble",0).asInt();
    m_clearBoard = m_playerStatsFile.m_Root["stats"].get("clearBoard",0).asInt();
    m_backToBack = m_playerStatsFile.m_Root["stats"].get("backtoback",0).asInt();
    return flag;
}

void statistics::savePlayerStats(const std::string title)
{
    m_playerStatsFile.m_Root["stats"]["singlelines"] = m_singleline;
    m_playerStatsFile.m_Root["stats"]["tetris"] = m_tetris;
    m_playerStatsFile.m_Root["stats"]["Tspin"] = m_Tspin;
    m_playerStatsFile.m_Root["stats"]["Tspinsingle"] = m_Tspinsingle;
    m_playerStatsFile.m_Root["stats"]["Tspindouble"] = m_Tspindouble;
    m_playerStatsFile.m_Root["stats"]["Tspintriple"] = m_Tspintriple;
    m_playerStatsFile.m_Root["stats"]["miniTspin"] = m_miniTspin;
    m_playerStatsFile.m_Root["stats"]["miniTspinsingle"] = m_miniTspinsingle;
    m_playerStatsFile.m_Root["stats"]["miniTspindouble"] = m_miniTspindouble;
    m_playerStatsFile.m_Root["stats"]["clearBoard"]= m_clearBoard;
    m_playerStatsFile.m_Root["stats"]["backtoback"] = m_backToBack;
    m_playerStatsFile.saveJsonFile(title);
}

void statistics::createPlayerStats(const std::string title)
{
    std::ofstream file(title, std::ios::app);
    file << m_emptyStats;
    file.flush();
}

void statistics::addPatternsToStats(const pattern& pattern)
{
    if(pattern.singleLine) { m_singleline+=1; }
    else if(pattern.doubleLine) { m_singleline+=2; }
         else if(pattern.tripleLine) { m_singleline+=3; }
              else if(pattern.tetris) { ++m_tetris; }
                   else if(pattern.miniTspin) { ++m_miniTspin; }
                        else if(pattern.miniTspinSingle) { ++m_miniTspinsingle; }
                             else if(pattern.miniTspinDouble) { ++m_miniTspindouble; }
                                  else if(pattern.Tspin) { ++m_Tspin; }
                                       else if(pattern.TspinSingle) { ++m_Tspinsingle; }
                                            else if(pattern.TspinDouble) { ++m_Tspindouble; }
                                                 else if(pattern.TspinTriple) { ++m_Tspintriple; }
                                                      else if(pattern.ClearBoard) { ++m_clearBoard; }
    if(pattern.backToBackFlag) { ++m_backToBack; }
}
