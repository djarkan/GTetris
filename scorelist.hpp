#ifndef    __scoreList__
#define    __scoreList__

#include <array>
#include <string>
#include <utility>
#include <algorithm>
#include "json\json.h"
#include "jsonfile.hpp"

class scoreList{
public:
    scoreList();
    bool buildScoreList(const int gameMode, const bool enhanced);
    int enterScoreInList(std::string pseudo, int score, const int gameMode, const bool enhanced);
    bool isScoreEnterInScoreList(int score, const int gameMode);

    std::array<std::pair<std::string, int> , 20> m_scoreArray;

private:
    void saveScoreList();
    std::string getGameName(const int gameMode, const bool enhanced);

    std::string m_gameName;
    jsonFile m_jsonSocreList;
};
#endif
