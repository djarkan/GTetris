#include "scorelist.hpp"
#include <iostream>
#include <algorithm>

scoreList::scoreList()
{
}

void scoreList::buildScoreList(const int gameMode, const bool enhanced)
{
    m_jsonSocreList.loadJsonFile("score.json");
    std::string gameName = getGameName(gameMode, enhanced);
    for(auto i = 0; i < 20; ++i){
     m_scoreArray[i].first = m_jsonSocreList.m_Root["score"][gameName]["pseudo"][i].asString();
     m_scoreArray[i].second = m_jsonSocreList.m_Root["score"][gameName]["score"][i].asInt();
    }
}

void scoreList::saveScoreList()
{
    /////////////////////////////////////////////////////////mettre l'array dans le json file avant la save
    m_jsonSocreList.saveJsonFile("score.json");
}

bool scoreList::isScoreEnterInScoreList(int score, const int gameMode)
{
    if(gameMode == 2) { return score < m_scoreArray[19].second; }
    else { return score > m_scoreArray[19].second; }
}

int scoreList::enterScoreInList(std::string pseudo, int score, const int gameMode, const bool enhanced )
{
    m_scoreArray[19].first = pseudo;
    m_scoreArray[19].second = score;
    int index = 19;
    if(gameMode == 2){
        while(m_scoreArray[index].second < m_scoreArray[index - 1].second && index > 0){
            m_scoreArray[index].swap(m_scoreArray[index - 1]);
            --index;
        }
    }
    else {
        while(m_scoreArray[index].second > m_scoreArray[index - 1].second && index > 0){
            m_scoreArray[index].swap(m_scoreArray[index - 1]);
            --index;
        }
    }
    std::string gameName = getGameName(gameMode, enhanced);
    for(auto i = 0; i < 20; ++i){
     m_jsonSocreList.m_Root["score"][gameName]["pseudo"][i] = m_scoreArray[i].first;
     m_jsonSocreList.m_Root["score"][gameName]["score"][i] = m_scoreArray[i].second;
    }
    saveScoreList();
    return index + 1;
}

std::string scoreList::getGameName(const int gameMode, const bool enhanced)
{
    std::string gameName{""};
    switch (gameMode){
    case 0:
        if(enhanced){ gameName = "marathonextended"; }
        else { gameName = "marathon"; }
        break;
    case 1:
        if(enhanced){ gameName = "sprintextended"; }
        else { gameName = "sprint"; }
        break;
    case 2:
        if(enhanced){ gameName = "30linesextended"; }
        else { gameName = "30lines"; }
        break;
    case 3:
        if(enhanced){ gameName = "phantomextended"; }
        else { gameName = "phantom"; }
        break;
    case 4:
        if(enhanced){ gameName = "inclusionextended"; }
        else { gameName = "inclusion"; }
        break;
    case 5:
        if(enhanced){ gameName = "underpreasureextended"; }
        else { gameName = "underpreasure"; }
        break;
    default :
        break;
    }
    return gameName;
}

void scoreList::viewScoreArray()
{
    for(auto i = 0; i < 20; ++i){
        std::cout << m_scoreArray[i].first << "  --------------   "  << m_scoreArray[i].second << std::endl;
    }
}
