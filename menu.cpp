#include "menu.hpp"
#include "scorelist.hpp"

menu::menu()
{

}

menu::menu(sf::Uint32 style) : m_style{style}, screen(m_style)
{
}

bool menu::initMenu()
{
    bool flag = m_jsonConfig.loadJsonFile("config.json");
    flag &= m_menuLabels.loadJsonFile("language\\menu.json");
    flag &= m_jsonSetup.loadJsonFile("setup.json");
    if(flag) { setSetUp(); }
//    style = sf::Style::Fullscreen;
//    manageScreen(style);
    flag &= screen.loadBitmapFile("graphics\\graphics.png");
    flag &= screen.loadBitmapCursor("graphics\\cursor.png");
    myCursor.loadFromPixels(screen.myCursor.getPixelsPtr(), {40,40}, {0,0});
    screen.m_window.setMouseCursor(myCursor);
    flag &= screen.loadFontFile("font\\oneslot.ttf");
    flag &= gameSound.initSounds();
    if(!flag) { setSoundVolume(m_setup.soundVolume); }
    flag &= gameMusic.initMusic();
    if(flag) { setMusicVolume(m_setup.musicVolume); }
    if(!playerStats.loadPlayerStats("statistics\\" + m_setup.pseudo + ".json")) {
        playerStats.createPlayerStats("statistics\\" + m_setup.pseudo + ".json");              ;
    }
    flag =  m_gameTtranslation.loadJsonFile("language\\play.json");
    return flag;
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
            case 0:                                                             // launch the game
                {
                game game;
                screen.m_window.setMouseCursorVisible(false);
                game.launchParty(screen, m_setup, gameSound, playerStats);
                playerStats.savePlayerStats("statistics\\" + m_setup.pseudo + ".json");
                loadButtons("playButton");
                screen.m_window.setMouseCursorVisible(true);
                }
                break;
            case 1:                                                             // launch parameters options
                gameSound.playSound(3);
                parametersMenu();
                loadButtons("playButton");
                break;
            case 2:                                                             // exit from the game
                gameMusic.stopSong();
                return false;
                break;
            case 3:                                                             //change language
                if(m_setup.language == 0) { m_setup.language = m_jsonConfig.m_Root["maxValue"]["maxLanguage"].asInt() -1; }
                else { --m_setup.language; }
                gameSound.playSound(1);
                break;
            case 4:                                                             //change language
                if(m_setup.language == m_jsonConfig.m_Root["maxValue"]["maxLanguage"].asInt() -1) { m_setup.language = 0; }
                else { ++m_setup.language; }
                gameSound.playSound(1);
                break;
            case 5:                                                             // choose piece texture
                if(m_setup.pieceGraphic == 0) { m_setup.pieceGraphic = m_jsonConfig.m_Root["maxValue"]["maxPieceGraphic"].asInt() -1; }
                else {--m_setup.pieceGraphic; }
                gameSound.playSound(1);
                break;
            case 6:                                                             // choose piece texture
                if(m_setup.pieceGraphic == m_jsonConfig.m_Root["maxValue"]["maxPieceGraphic"].asInt() -1) { m_setup.pieceGraphic = 0; }
                else { ++m_setup.pieceGraphic; }
                gameSound.playSound(1);
                break;
            case 7:                                                             // choose game mode
                if(m_setup.gameType == 0) { m_setup.gameType = m_jsonConfig.m_Root["maxValue"]["maxGameType"].asInt() -1; }
                else {--m_setup.gameType; }
                gameSound.playSound(1);
                break;
            case 8:                                                             // choose game mode
                if(m_setup.gameType == m_jsonConfig.m_Root["maxValue"]["maxGameType"].asInt() -1) { m_setup.gameType = 0; }
                else { ++m_setup.gameType; }
                gameSound.playSound(1);
                break;
            case 9:                                                             // choose pieces number
            case 10:
                m_setup.enhanced = !m_setup.enhanced;
                gameSound.playSound(1);
                break;
            case 11:                                                            // choose system rotation
            case 12:
                m_setup.superRotationSystem = !m_setup.superRotationSystem;
                gameSound.playSound(1);
                break;
            case 13:                                                            // choose shadow piece or not
            case 14:
                m_setup.shadow = !m_setup.shadow;
                gameSound.playSound(1);
                break;
            case 15:                                                            // enable hold 1 piece
            case 16:
                m_setup.hold = !m_setup.hold;
                gameSound.playSound(1);
                break;
            case 17:                                                            // choose if delay before locking the current piece
            case 18:
                m_setup.lockout = !m_setup.lockout;
                gameSound.playSound(1);
                break;
            case 19:                                                            // choose pieces randomization
            case 20:
                m_setup.sevenBag = !m_setup.sevenBag;
                gameSound.playSound(1);
                break;
            case 21:                                                            // choose to see next pieces or not
            case 22:
                m_setup.nextPiece = !m_setup.nextPiece;
                gameSound.playSound(1);
                break;
            case 23:                                                            // choose next piece number to see
                if(m_setup.nextPiecesNumber == 0) { m_setup.nextPiecesNumber = m_jsonConfig.m_Root["maxValue"]["MaxNextPieces"].asInt(); }
                else { --m_setup.nextPiecesNumber; }
                gameSound.playSound(1);
                break;
            case 24:                                                            // choose next piece number to see
                if(m_setup.nextPiecesNumber == m_jsonConfig.m_Root["maxValue"]["MaxNextPieces"].asInt()) { m_setup.nextPiecesNumber = 0; }
                else { ++m_setup.nextPiecesNumber; }
                gameSound.playSound(1);
                break;
            case 25:                                                            // enable music or not
            case 26:
                m_setup.music = !m_setup.music;
                if(m_setup.music) { gameMusic.playSong(); }
                else { gameMusic.stopSong(); }
                gameSound.playSound(1);
                break;
            case 27:                                                            // choose music volume
                if(m_setup.musicVolume > 0) { --m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                gameMusic.setMusicVolume(m_setup.musicVolume);
                gameSound.playSound(1);
                break;
            case 28:                                                            // choose music volume
                if(m_setup.musicVolume < 100) { ++m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                gameMusic.setMusicVolume(m_setup.musicVolume);
                gameSound.playSound(1);
                break;
            case 29:                                                            // enable sound or not
            case 30:
                m_setup.sound = !m_setup.sound;
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 31:                                                            // choose sound volume
                if(m_setup.soundVolume > 0) { --m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 32:                                                            // choose sound volume
                if(m_setup.soundVolume < 100) { ++m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                setSoundVolume(m_setup.soundVolume);
                gameSound.playSound(1);
                break;
            case 33:                                                            // exit from parameters option
                gameSound.playSound(7);
                return false;
                break;
            case 34:                                                            // save parameters
                saveSetUp();
                gameSound.playSound(7);
                break;
            case 35:                                                            // set player's name
                gameSound.playSound(7);
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
                    while (m_setup.pseudo.size() > 25) { m_setup.pseudo.pop_back(); }
                    screen.clear();
                    setPlayMenu();
                    drawAllButtons();
                    setPlayMenu();
                    std::string label = m_menuLabels.m_Root["quit"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black,  880 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
                    label = m_menuLabels.m_Root["playerstats"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black, 520 - ((static_cast<float>(label.size()) / 2.f) * 12), 650);
                    label = m_menuLabels.m_Root["play"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black,  145 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
                    label = m_menuLabels.m_Root["help"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black,  760 - ((static_cast<float>(label.size()) / 2.f) * 12), 650);
                    label = m_menuLabels.m_Root["score"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black, 635 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
                    label = m_menuLabels.m_Root["settings"][m_setup.language].asString();
                    screen.displayText(label, 28, sf::Color::Black, 390 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
                    label = m_menuLabels.m_Root["pseudobutton"][m_setup.language].asString();
                    screen.displayText(label, 26, sf::Color::Black, 280 - ((static_cast<float>(label.size()) / 2.f) * 11), 650);
                    label = m_menuLabels.m_Root["welcome"][m_setup.language].asString() + m_setup.pseudo;
                    screen.displayText(label, 32, sf::Color::White, 70, 490);
                    if(cursorTimer.isTimeElapsed()){
                        if(cursorColor == sf::Color::White)
                            { cursorColor = sf::Color::Black; }
                        else { cursorColor = sf::Color::White; }
                        cursorTimer.startTimer();
                    }
                    screen.drawRectangle(70 + (static_cast<float>(label.size() * 13.5)), 490 , 3, 32, cursorColor);
                    screen.render();
                }
                if(m_setup.pseudo == "") { m_setup.pseudo = oldPseudo; }
                m_jsonSetup.m_Root["setUp"]["pseudo"] = m_setup.pseudo;
                savePseudo();
                if(!playerStats.loadPlayerStats("statistics\\" + m_setup.pseudo + ".json")) {
                   playerStats.createPlayerStats("statistics\\" + m_setup.pseudo + ".json");              ;
                }
                break;
            case 36:                                                            // set start level
                if(m_setup.startLevel > 1) { --m_setup.startLevel; }
                else { m_setup.startLevel = 9; }
                sf::sleep(sf::milliseconds(40));
                gameSound.playSound(1);
                break;
            case 37: {                                                           // set start level
                if(m_setup.startLevel < 9) { ++m_setup.startLevel; }
                else { m_setup.startLevel = 1; }
                sf::sleep(sf::milliseconds(40));
                gameSound.playSound(1);
            }
                break;
            case 38:  {                                                          // display score list
                scoreList scoreList;
                scoreList.buildScoreList(m_setup.gameType, m_setup.enhanced);
                screen.drawScoreList(scoreList.m_scoreArray, 0, m_setup.gameType,
                                     m_menuLabels.m_Root["bestscore"][m_setup.language].asString(),
                                     m_menuLabels.m_Root["pressspace"][m_setup.language].asString());
                while(!eventReader.getSpace(screen.m_window)) {}
            }
                break;
            case 39:                                                              // display player's statistics
                displayPlayerStats();
                break;
            case 40:                                                              // display help menu
                if(help.loadHelpText()) {
                    gameSound.playSound(3);
                    helpMenu();
                    gameSound.playSound(3);
                }
                else { errorMessage(); }
                break;
            case 41:  {                                                            // help go left
                    --helpPage;
                    if(helpPage < 0) { helpPage = 5; }
                    gameSound.playSound(1);
                    help.displayHelpPage(screen, helpPage, m_setup.language); //gameSound);
                    drawAllButtons();
            }
                break;
            case 42: {                                                             // help go right
                    ++helpPage;
                    if(helpPage > 5) { helpPage = 0; }
                    gameSound.playSound(1);
                    help.displayHelpPage(screen, helpPage, m_setup.language); //gameSound);
                    drawAllButtons();
            }
                break;
            case 43:                                                              // quit help
                loadButtons("playButton");
                return false;
                break;
            case 44:                                                            // enable sound or not
            case 45:
                m_setup.windowed = !m_setup.windowed;
                gameSound.playSound(1);
            default: ;
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
        std::string label = m_menuLabels.m_Root["quit"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black,  880 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
        label = m_menuLabels.m_Root["playerstats"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black, 520 - ((static_cast<float>(label.size()) / 2.f) * 12), 650);
        label = m_menuLabels.m_Root["play"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black,  145 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
        label = m_menuLabels.m_Root["help"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black,  760 - ((static_cast<float>(label.size()) / 2.f) * 12), 650);
        label = m_menuLabels.m_Root["score"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black, 635 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
        label = m_menuLabels.m_Root["settings"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black, 390 - ((static_cast<float>(label.size()) / 2.f) * 12), 555);
        label = m_menuLabels.m_Root["pseudobutton"][m_setup.language].asString();
        screen.displayText(label, 26, sf::Color::Black, 280 - ((static_cast<float>(label.size()) / 2.f) * 11), 650);
        label = m_menuLabels.m_Root["welcome"][m_setup.language].asString() + m_setup.pseudo;
        screen.displayText(label, 32, sf::Color::White, 70, 490);
        screen.displayText("v1.0", 16, sf::Color::White, 980 , 745);
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
    m_setup.windowed = m_jsonSetup.m_Root["setUp"].get("windowed",1).asBool();
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
    m_jsonSetup.m_Root["setUp"]["windowed"] = m_setup.windowed;
    saveJsonSetup("setup.json");
}

void menu::printParameters()
{
    std::string label = m_menuLabels.m_Root["setupSelector"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 125);
    label = m_menuLabels.m_Root["setupSelector"]["gameType"][m_setup.language][m_setup.gameType].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 205);
    label = std::to_string(m_setup.startLevel);
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 245);
    label = m_menuLabels.m_Root["setupSelector"]["enhanced"][m_setup.language][m_setup.enhanced].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 285);
    label = m_menuLabels.m_Root["setupSelector"]["superRotationSystem"][m_setup.language][m_setup.superRotationSystem].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 325);
    label = m_menuLabels.m_Root["setupSelector"]["shadow"][m_setup.language][m_setup.shadow].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 365);
    label = m_menuLabels.m_Root["setupSelector"]["hold"][m_setup.language][m_setup.hold].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 405);
    label = m_menuLabels.m_Root["setupSelector"]["lockout"][m_setup.language][m_setup.lockout].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 445);
    label = m_menuLabels.m_Root["setupSelector"]["sevenBag"][m_setup.language][m_setup.sevenBag].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 485);
    label = m_menuLabels.m_Root["setupSelector"]["nextPiece"][m_setup.language][m_setup.nextPiece].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 525);
    label = std::to_string(m_setup.nextPiecesNumber);
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 565);
    label = m_menuLabels.m_Root["setupSelector"]["music"][m_setup.language][m_setup.music].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 605);
    label = std::to_string(static_cast<int>(m_setup.musicVolume));
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 645);
    label = m_menuLabels.m_Root["setupSelector"]["sound"][m_setup.language][m_setup.sound].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 685);
    label = std::to_string(static_cast<int>(m_setup.soundVolume));
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 725);
    label = m_menuLabels.m_Root["setupSelector"]["windowed"][m_setup.language][m_setup.windowed].asString();
    screen.displayText(label, 32, sf::Color::White, 750 - ((static_cast<float>(label.size()) * 14) / 2), 85);
    screen.drawBlock(m_setup.pieceGraphic);
}

void menu::printLabels()
{
    std::string label = m_menuLabels.m_Root["paramtersTitles"]["title"][m_setup.language].asString();
    screen.displayText(label, 56, sf::Color::White, 512 - (((static_cast<float>(label.size()) - 7) * 22) / 2.f), 2);
    label = m_menuLabels.m_Root["paramtersTitles"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 125);
    label = m_menuLabels.m_Root["paramtersTitles"]["pieceGraphic"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 165);
    label = m_menuLabels.m_Root["paramtersTitles"]["gameType"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 205);
    label = m_menuLabels.m_Root["paramtersTitles"]["startLevel"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 245);
    label = m_menuLabels.m_Root["paramtersTitles"]["enhanced"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 285);
    label = m_menuLabels.m_Root["paramtersTitles"]["superRotationSystem"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 325);
    label = m_menuLabels.m_Root["paramtersTitles"]["shadow"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 365);
    label = m_menuLabels.m_Root["paramtersTitles"]["hold"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 405);
    label = m_menuLabels.m_Root["paramtersTitles"]["lockout"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 17), 445);
    label = m_menuLabels.m_Root["paramtersTitles"]["sevenBag"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 485);
    label = m_menuLabels.m_Root["paramtersTitles"]["nextPiece"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 525);
    label = m_menuLabels.m_Root["paramtersTitles"]["nextPiecesNumber"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 565);
    label = m_menuLabels.m_Root["paramtersTitles"]["music"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 605);
    label = m_menuLabels.m_Root["paramtersTitles"]["musicVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 645);
    label = m_menuLabels.m_Root["paramtersTitles"]["sound"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 685);
    label = m_menuLabels.m_Root["paramtersTitles"]["soundVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 725);
    label = m_menuLabels.m_Root["paramtersTitles"]["windowed"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((static_cast<float>(label.size()) / 2) * 14), 85);
}

void menu::displayPlayerStats()
{
    screen.clear();
    std::string label = m_menuLabels.m_Root["playerstats2"][m_setup.language].asString();
    screen.displayText(label, 40, sf::Color::White, 512 - (((label.size() -7)  * 16) / 2.f), 50);
    float y{120};
    for(auto i=0; i < 13; i++) {
        label = m_menuLabels.m_Root["pattern"][i][m_setup.language].asString();
        screen.displayText(label, 32, sf::Color::White, 260, y += 40);
    }
    y = 120;
    label = std::to_string(playerStats.m_singleline);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_tetris);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_Tspin);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_Tspinsingle);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_Tspindouble);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_Tspintriple);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 14), y += 40);
    label = std::to_string(playerStats.m_miniTspin);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_miniTspinsingle);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_miniTspindouble);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_clearBoard);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = std::to_string(playerStats.m_backToBack);
    screen.displayText(label, 32, sf::Color::White, 770 - (label.size() * 13), y += 40);
    label = m_menuLabels.m_Root["pressspace"][m_setup.language].asString();
    screen.displayText(label, 40, sf::Color::White, 512 - ((label.size() * 16) / 2.f), 650);
    screen.render();
    while(!eventReader.getSpace(screen.m_window)) {}
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
        screen.render();
    }
}

void menu::helpMenu()
{
    bool stayInHelp{true};
    loadButtons("helpButtons");
    helpPage = 0;
    while(stayInHelp == true) {
        screen.clear();
        help.displayHelpPage(screen, helpPage, m_setup.language); //gameSound);
        stayInHelp = launchAction(checkButtonsAction());
        drawAllButtons();
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

void menu::errorMessage()
{
    screen.errorMessage(m_menuLabels.m_Root["error"][m_setup.language].asString(), m_menuLabels.m_Root["reinstall"][m_setup.language].asString(), m_menuLabels.m_Root["pressspace"][m_setup.language].asString());
    while(!eventReader.getSpace(screen.m_window)) ;
}
