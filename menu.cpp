#include "menu.hpp"
#include "scorelist.hpp"
menu::menu()
{

}

bool menu::initMenu()
{
    bool flag1 = m_jsonConfig.loadJsonFile("config.json");
    bool flag2 = m_jsonSetup.loadJsonFile("setup.json");
    gameSound.initSounds();
    gameMusic.initMusic();
    setSetUp();
    setSoundVolume(m_setup.soundVolume);
    setMusicVolume(m_setup.musicVolume);
    return flag1 | flag2;
}

void menu::saveJsonSetup(const std::string fileName)
{
    m_jsonSetup.saveJsonFile(fileName);
}

void menu::loadButtons(std::string buttonConfig)
{
    m_buttonList.resize(0);
    for(auto buttonMember : m_jsonConfig.m_Root[buttonConfig]) {
        m_buttonList.push_back(std::make_unique<button>(buttonMember.get("x",0).asInt(),
                                                        buttonMember.get("y",0).asInt(),
                                                        buttonMember.get("width",0).asInt(),
                                                        buttonMember.get("higth",0).asInt(),
                                                        static_cast<button::buttonType>(buttonMember.get("buttonType",0).asInt()),
                                                        buttonMember.get("buttonId",0).asInt(),
                                                        buttonMember.get("textureNumber",0).asInt(),
                                                        buttonMember.get("state",0).asInt()));
    }
}

void menu::drawAllButtons()
{
    for(unsigned int i = 0; i < m_buttonList.size(); i++){
        screen.drawButton(m_buttonList[i]->m_x,
                          m_buttonList[i]->m_y,
                          m_buttonList[i]->m_width,
                          m_buttonList[i]->m_higth,
                          m_buttonList[i]->m_textureNumber,
                          m_buttonList[i]->m_state);
    }
}

int menu::checkButtonsAction()
{
    for(unsigned int i = 0; i < m_buttonList.size(); i++){
        button::buttonState action = m_buttonList[i]->whatButtonState(screen.m_window);
        switch (action) {
            case button::buttonState::buttonPressed:
                if(m_buttonList[i]->m_buttonType == button::buttonType::pushedButton) {
                    return m_buttonList[i]->m_buttonId;
                }
                break;
            case button::buttonState::buttonHeld :
                if(m_buttonList[i]->m_buttonType == button::buttonType::heldButton) {
                    return m_buttonList[i]->m_buttonId;
                }
                break;
            case button::buttonState::buttonReleased:
                if(m_buttonList[i]->m_buttonType == button::buttonType::releasedButton) {
                    return m_buttonList[i]->m_buttonId;
                }
                break;
            case button::buttonState::mouseOver:
            case button::buttonState::noAction:
            default:
                break;
        }
    }
    return -1;
}

bool menu::launchAction(int buttonID)
{
    switch(buttonID){
            case 0:
                game.launchParty(screen, m_setup, gameSound);
                loadButtons("playButton");
                break;
            case 1:
                gameSound.playSound(3);
                parametersMenu();
                loadButtons("playButton");
                break;
            case 2:
                gameMusic.stopSong();
                return false;
                break;
            case 3:
                if(m_setup.language == 0) { m_setup.language = m_jsonConfig.m_Root["maxValue"]["maxLanguage"].asInt() -1; }
                else { --m_setup.language; }
                gameSound.playSound(1);
                break;
            case 4:
                if(m_setup.language == m_jsonConfig.m_Root["maxValue"]["maxLanguage"].asInt() -1) { m_setup.language = 0; }
                else { ++m_setup.language; }
                gameSound.playSound(1);
                break;
            case 5:
                if(m_setup.pieceGraphic == 0) { m_setup.pieceGraphic = m_jsonConfig.m_Root["maxValue"]["maxPieceGraphic"].asInt() -1; }
                else {--m_setup.pieceGraphic; }
                gameSound.playSound(1);
                break;
            case 6:
                if(m_setup.pieceGraphic == m_jsonConfig.m_Root["maxValue"]["maxPieceGraphic"].asInt() -1) { m_setup.pieceGraphic = 0; }
                else { ++m_setup.pieceGraphic; }
                gameSound.playSound(1);
                break;
            case 7:
                if(m_setup.gameType == 0) { m_setup.gameType = m_jsonConfig.m_Root["maxValue"]["maxGameType"].asInt() -1; }
                else {--m_setup.gameType; }
                gameSound.playSound(1);
                break;
            case 8:
                if(m_setup.gameType == m_jsonConfig.m_Root["maxValue"]["maxGameType"].asInt() -1) { m_setup.gameType = 0; }
                else { ++m_setup.gameType; }
                gameSound.playSound(1);
                break;
            case 9:
            case 10:
                m_setup.enhanced = !m_setup.enhanced;
                gameSound.playSound(1);
                break;
            case 11:
            case 12:
                m_setup.superRotationSystem = !m_setup.superRotationSystem;
                gameSound.playSound(1);
                break;
            case 13:
            case 14:
                m_setup.shadow = !m_setup.shadow;
                gameSound.playSound(1);
                break;
            case 15:
            case 16:
                m_setup.hold = !m_setup.hold;
                gameSound.playSound(1);
                break;
            case 17:
            case 18:
                m_setup.lockout = !m_setup.lockout;
                gameSound.playSound(1);
                break;
            case 19:
            case 20:
                m_setup.sevenBag = !m_setup.sevenBag;
                gameSound.playSound(1);
                break;
            case 21:
            case 22:
                m_setup.nextPiece = !m_setup.nextPiece;
                gameSound.playSound(1);
                break;
            case 23:
                if(m_setup.nextPiecesNumber == 0) { m_setup.nextPiecesNumber = m_jsonConfig.m_Root["maxValue"]["MaxNextPieces"].asInt(); }
                else { --m_setup.nextPiecesNumber; }
                gameSound.playSound(1);
                break;
            case 24:
                if(m_setup.nextPiecesNumber == m_jsonConfig.m_Root["maxValue"]["MaxNextPieces"].asInt()) { m_setup.nextPiecesNumber = 0; }
                else { ++m_setup.nextPiecesNumber; }
                gameSound.playSound(1);
                break;
            case 25:
            case 26:
                m_setup.music = !m_setup.music;
                if(m_setup.music) { gameMusic.playSong(); }
                else { gameMusic.stopSong(); }
                gameSound.playSound(1);
                break;
            case 27:
                if(m_setup.musicVolume > 0) { --m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                gameMusic.setMusicVolume(m_setup.musicVolume);
                gameSound.playSound(1);
                break;
            case 28:
                if(m_setup.musicVolume < 100) { ++m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                gameMusic.setMusicVolume(m_setup.musicVolume);
                gameSound.playSound(1);
                break;
            case 29:
            case 30:
                m_setup.sound = !m_setup.sound;
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 31:
                if(m_setup.soundVolume > 0) { --m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 32:
                if(m_setup.soundVolume < 100) { ++m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 33:
                gameSound.playSound(2);
                return false;
                break;
            case 34:
                saveSetUp();
                gameSound.playSound(2);
                break;
            case 35:
                gameSound.playSound(2);
                static std::string oldPseudo = m_setup.pseudo;
                static timer cursorTimer(500);
                cursorTimer.startTimer();
                static sf::Color cursorColor{sf::Color::White};
                bool readingPseudoChar;
                readingPseudoChar = true;
                m_setup.pseudo = "";
                while(readingPseudoChar)
                {
                    readingPseudoChar = eventReader.pseudoChar(screen.m_window, m_setup.pseudo, m_setup.language);
                    screen.clear();
                    setPlayMenu();
                    drawAllButtons();
                    std::string label = m_jsonConfig.m_Root["pseudobutton"][m_setup.language].asString();
                    screen.displayText(label, 24, sf::Color::White, 250 - ((static_cast<float>(label.size()) * 14) / 2), 677);
                    label = m_jsonConfig.m_Root["welcome"][m_setup.language].asString() + m_setup.pseudo;
                    screen.displayText(label, 32, sf::Color::White, 115, 625);
                    if(cursorTimer.isTimeElapsed()){
                        if(cursorColor == sf::Color::White)
                            { cursorColor = sf::Color::Black; }
                        else { cursorColor = sf::Color::White; }
                        cursorTimer.startTimer();
                    }
                    screen.drawRectangle(115 + ((static_cast<float>(label.size()) + 1) * 13.2f), 628 , 3, 32, cursorColor);
                    screen.render();
                }
                if(m_setup.pseudo == "") { m_setup.pseudo = oldPseudo; }
                m_jsonSetup.m_Root["setUp"]["pseudo"] = m_setup.pseudo;
                savePseudo();
                break;
            case 36:
                if(m_setup.startLevel > 1) { --m_setup.startLevel; }
                else { m_setup.startLevel = 15; }
                sf::sleep(sf::milliseconds(40));
                gameSound.playSound(1);
                break;
            case 37:
                if(m_setup.startLevel < 15) { ++m_setup.startLevel; }
                else { m_setup.startLevel = 1; }
                sf::sleep(sf::milliseconds(40));
                gameSound.playSound(1);
                break;
            case 38:
                scoreList scoreList;
                scoreList.buildScoreList(m_setup.gameType, m_setup.enhanced);
                screen.drawScoreList(scoreList.m_scoreArray, 0, m_setup.gameType);
                while(!eventReader.getSpace(screen.m_window)) {}
                break;
//            default:
//                break;
        }
    return true;
}

void menu::setPlayMenu()
{
    screen.drawGameName();
    drawAllButtons();

}

void menu::setSoundVolume(float soundVolume)
{
    if(!m_setup.sound) { soundVolume = 0.f; }
    gameSound.setSoundVolume(soundVolume);
}

void menu::setMusicVolume(float musicVolume)
{
    gameMusic.setMusicVolume(musicVolume);
}

void menu::playMenu()
{
    bool iPlay{true};
    loadButtons("playButton");
    if(m_setup.music) { gameMusic.playSong(); }
    while(iPlay){
        screen.clear();
        iPlay = launchAction(checkButtonsAction());
        setPlayMenu();
        std::string label = m_jsonConfig.m_Root["pseudobutton"][m_setup.language].asString();
        screen.displayText(label, 24, sf::Color::White, 250 - ((static_cast<float>(label.size()) * 14) / 2), 677);
        label = m_jsonConfig.m_Root["welcome"][m_setup.language].asString() + m_setup.pseudo;
        screen.displayText(label, 32, sf::Color::White, 115, 625);
        screen.render();
    }
}

void menu::setSetUp()
{
    m_setup.enhanced = m_jsonSetup.m_Root["setUp"].get("enhanced",1).asBool();
    m_setup.gameType = m_jsonSetup.m_Root["setUp"].get("gameType",0).asInt();
    m_setup.hold = m_jsonSetup.m_Root["setUp"].get("hold",1).asBool();
    m_setup.language = m_jsonSetup.m_Root["setUp"].get("language",1).asInt();
    m_setup.lockout = m_jsonSetup.m_Root["setUp"].get("lockout",1).asBool();
    m_setup.music = m_jsonSetup.m_Root["setUp"].get("music",1).asBool();
    m_setup.musicVolume = m_jsonSetup.m_Root["setUp"].get("musicVolume",100).asFloat();
    m_setup.nextPiece = m_jsonSetup.m_Root["setUp"].get("nextPiece",1).asBool();
    m_setup.nextPiecesNumber = m_jsonSetup.m_Root["setUp"].get("nextPiecesNumber",5).asInt();
    m_setup.pieceGraphic = m_jsonSetup.m_Root["setUp"].get("pieceGraphic",0).asInt();
    m_setup.sevenBag = m_jsonSetup.m_Root["setUp"].get("sevenBag",1).asBool();
    m_setup.shadow = m_jsonSetup.m_Root["setUp"].get("shadow",1).asBool();
    m_setup.sound = m_jsonSetup.m_Root["setUp"].get("sound",1).asBool();
    m_setup.soundVolume = m_jsonSetup.m_Root["setUp"].get("soundVolume",100).asFloat();
    m_setup.superRotationSystem = m_jsonSetup.m_Root["setUp"].get("superRotationSystem",1).asBool();
    setLocale(m_setup.language);
    m_setup.pseudo = m_jsonSetup.m_Root["setUp"].get("pseudo","").asString();
    m_setup.startLevel = m_jsonSetup.m_Root["setUp"].get("startLevel",1).asInt();
}

void menu::savePseudo()
{
    setLocale(m_setup.language);
    m_jsonSetup.m_Root["setUp"].get("pseudo","").asString() = m_setup.pseudo;
    saveJsonSetup("setup.json");
}

void menu::saveSetUp()
{
    m_jsonSetup.m_Root["setUp"]["enhanced"] = m_setup.enhanced;
    m_jsonSetup.m_Root["setUp"]["gameType"] = m_setup.gameType;
    m_jsonSetup.m_Root["setUp"]["hold"] = m_setup.hold;
    m_jsonSetup.m_Root["setUp"]["language"] = m_setup.language;
    m_jsonSetup.m_Root["setUp"]["lockout"] = m_setup.lockout;
    m_jsonSetup.m_Root["setUp"]["music"] = m_setup.music;
    m_jsonSetup.m_Root["setUp"]["musicVolume"] = m_setup.musicVolume;
    m_jsonSetup.m_Root["setUp"]["nextPiece"] = m_setup.nextPiece;
    m_jsonSetup.m_Root["setUp"]["nextPiecesNumber"] = m_setup.nextPiecesNumber;
    m_jsonSetup.m_Root["setUp"]["pieceGraphic"] = m_setup.pieceGraphic;
    m_jsonSetup.m_Root["setUp"]["sevenBag"] = m_setup.sevenBag;
    m_jsonSetup.m_Root["setUp"]["shadow"] = m_setup.shadow;
    m_jsonSetup.m_Root["setUp"]["sound"] = m_setup.sound;
    m_jsonSetup.m_Root["setUp"]["soundVolume"] = m_setup.soundVolume;
    m_jsonSetup.m_Root["setUp"]["superRotationSystem"] = m_setup.superRotationSystem;
    m_jsonSetup.m_Root["setUp"]["startLevel"] = m_setup.startLevel;
    saveJsonSetup("setup.json");
}

void menu::printParameters()
{
    std::string label = m_jsonConfig.m_Root["setupSelector"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 102);
    label = m_jsonConfig.m_Root["setupSelector"]["gameType"][m_setup.language][m_setup.gameType].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 182);
    label = std::to_string(m_setup.startLevel);
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 222);
    label = m_jsonConfig.m_Root["setupSelector"]["enhanced"][m_setup.language][m_setup.enhanced].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 262);
    label = m_jsonConfig.m_Root["setupSelector"]["superRotationSystem"][m_setup.language][m_setup.superRotationSystem].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 302);
    label = m_jsonConfig.m_Root["setupSelector"]["shadow"][m_setup.language][m_setup.shadow].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 342);
    label = m_jsonConfig.m_Root["setupSelector"]["hold"][m_setup.language][m_setup.hold].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 382);
    label = m_jsonConfig.m_Root["setupSelector"]["lockout"][m_setup.language][m_setup.lockout].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 422);
    label = m_jsonConfig.m_Root["setupSelector"]["sevenBag"][m_setup.language][m_setup.sevenBag].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 462);
    label = m_jsonConfig.m_Root["setupSelector"]["nextPiece"][m_setup.language][m_setup.nextPiece].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 502);
    label = std::to_string(m_setup.nextPiecesNumber);
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 542);
    label = m_jsonConfig.m_Root["setupSelector"]["music"][m_setup.language][m_setup.music].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 582);
    label = std::to_string(static_cast<int>(m_setup.musicVolume));
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 622);
    label = m_jsonConfig.m_Root["setupSelector"]["sound"][m_setup.language][m_setup.sound].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 662);
    label = std::to_string(static_cast<int>(m_setup.soundVolume));
    screen.displayText(label, 32, sf::Color::White, 770 - ((static_cast<float>(label.size()) * 14) / 2), 702);
    screen.drawBlock(m_setup.pieceGraphic);
}

void menu::printLabels()
{
    screen.displayText(m_jsonConfig.m_Root["paramtersTitles"]["title"][m_setup.language].asString(), 64, sf::Color::White, 350, 5);
    std::string label = m_jsonConfig.m_Root["paramtersTitles"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 102);
    label = m_jsonConfig.m_Root["paramtersTitles"]["pieceGraphic"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 142);
    label = m_jsonConfig.m_Root["paramtersTitles"]["gameType"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 182);
    label = m_jsonConfig.m_Root["paramtersTitles"]["startLevel"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 222);
    label = m_jsonConfig.m_Root["paramtersTitles"]["enhanced"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 262);
    label = m_jsonConfig.m_Root["paramtersTitles"]["superRotationSystem"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 302);
    label = m_jsonConfig.m_Root["paramtersTitles"]["shadow"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 342);
    label = m_jsonConfig.m_Root["paramtersTitles"]["hold"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 382);
    label = m_jsonConfig.m_Root["paramtersTitles"]["lockout"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 17), 422);
    label = m_jsonConfig.m_Root["paramtersTitles"]["sevenBag"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 462);
    label = m_jsonConfig.m_Root["paramtersTitles"]["nextPiece"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 502);
    label = m_jsonConfig.m_Root["paramtersTitles"]["nextPiecesNumber"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 542);
    label = m_jsonConfig.m_Root["paramtersTitles"]["music"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 582);
    label = m_jsonConfig.m_Root["paramtersTitles"]["musicVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 622);
    label = m_jsonConfig.m_Root["paramtersTitles"]["sound"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 662);
    label = m_jsonConfig.m_Root["paramtersTitles"]["soundVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 702);
}
void menu::parametersMenu()
{
    bool stayInMenu{true};
    loadButtons("setUpButtons");
    while(stayInMenu == true) {
        screen.clear();
        printLabels();
        printParameters();
        stayInMenu = launchAction(checkButtonsAction());
        drawAllButtons();
        std::string label = m_jsonConfig.m_Root["quit"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black,  135 - ((static_cast<float>(label.size()) / 2) * 12), 26);
        label = m_jsonConfig.m_Root["save"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black, 875 - ((static_cast<float>(label.size()) / 2) * 12), 26);
        screen.render();
    }
}

void menu::setLocale(int language)
{
    switch(language){
        case 0:
            std::setlocale(LC_ALL, "fr_FR.UTF-8");
            break;
        case 1:
            std::setlocale(LC_ALL, "us_US.UTF-8");
            break;
        case 2:
            std::setlocale(LC_ALL, "es_ES.UTF-8");
            break;
        case 3:
            std::setlocale(LC_ALL, "de_DE.UTF-8");
            break;
        default:
            break;
    }
}
