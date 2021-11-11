#include "menu.hpp"

menu::menu()
{

}

bool menu::loadJsonFiles(const std::string fileName1, const std::string fileName2)
{
    std::ifstream jsonFile1(fileName1, std::ifstream::in);
    std::ifstream jsonFile2(fileName2, std::ifstream::in);
    Json::CharReaderBuilder reader;
    reader["collectComments"] = true;
    JSONCPP_STRING errs;
    bool flag1 = Json::parseFromStream(reader, jsonFile1, &m_configRoot, &errs);
    bool flag2 = Json::parseFromStream(reader, jsonFile2, &m_setupRoot, &errs);
    setSetUp();
    return flag1 & flag2;
}

void menu::saveJsonSetup(const std::string fileName)
{
    std::ofstream jsonFile(fileName, std::ofstream::out);
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(m_setupRoot, &jsonFile);

}
void menu::loadButtons(std::string buttonConfig)
{
    Json::Value buttonList = m_configRoot[buttonConfig];
    m_buttonList.resize(0);
    for(auto buttonMember: buttonList) {
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

void menu::drawAllButtons(manageScreen& screen)
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

int menu::checkButtonsAction(sf::RenderWindow &window)
{
    mouseEvent.checkButtons(window);
    for(unsigned int i = 0; i < m_buttonList.size(); i++){
        button::buttonState action = m_buttonList[i]->whatButtonState(mouseEvent);
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

bool menu::launchAction(int buttonID, manageScreen& screen)
{
    switch(buttonID){
            case 0:
                static inGameFlags inGameFlags;
                game.launchParty(screen, m_setup, inGameFlags);
                game.clearInGameFlags(inGameFlags);
                break;
            case 1:
                parametersMenu(screen);
                break;
            case 2:
                return false;
                break;
            case 3:
                if(m_setup.language == 0) { m_setup.language = m_configRoot["maxValue"]["maxLanguage"].asInt() -1; }
                else { --m_setup.language; }

                break;
            case 4:
                if(m_setup.language == m_configRoot["maxValue"]["maxLanguage"].asInt() -1) { m_setup.language = 0; }
                else { ++m_setup.language; }
                break;
            case 5:
                if(m_setup.pieceGraphic == 0) { m_setup.pieceGraphic = m_configRoot["maxValue"]["maxPieceGraphic"].asInt() -1; }
                else {--m_setup.pieceGraphic; }
                break;
            case 6:
                if(m_setup.pieceGraphic == m_configRoot["maxValue"]["maxPieceGraphic"].asInt() -1) { m_setup.pieceGraphic = 0; }
                else { ++m_setup.pieceGraphic; }
                break;
            case 7:
                if(m_setup.gameType == 0) { m_setup.gameType = m_configRoot["maxValue"]["maxGameType"].asInt() -1; }
                else {--m_setup.gameType; }
                break;
            case 8:
                if(m_setup.gameType == m_configRoot["maxValue"]["maxGameType"].asInt() -1) { m_setup.gameType = 0; }
                else { ++m_setup.gameType; }
                break;
            case 9:
            case 10:
                m_setup.enhanced = !m_setup.enhanced;
                break;
            case 11:
            case 12:
                m_setup.superRotationSystem = !m_setup.superRotationSystem;
                break;
            case 13:
            case 14:
                m_setup.shadow = !m_setup.shadow;
                break;
            case 15:
            case 16:
                m_setup.hold = !m_setup.hold;
                break;
            case 17:
            case 18:
                m_setup.lockout = !m_setup.lockout;
                break;
            case 19:
            case 20:
                m_setup.sevenBag = !m_setup.sevenBag;
                break;
            case 21:
            case 22:
                m_setup.nextPiece = !m_setup.nextPiece;
                break;
            case 23:
                if(m_setup.nextPiecesNumber == 0) { m_setup.nextPiecesNumber = m_configRoot["maxValue"]["MaxNextPieces"].asInt(); }
                else { --m_setup.nextPiecesNumber; }
                break;
            case 24:
                if(m_setup.nextPiecesNumber == m_configRoot["maxValue"]["MaxNextPieces"].asInt()) { m_setup.nextPiecesNumber = 0; }
                else { ++m_setup.nextPiecesNumber; }
                break;
            case 25:
            case 26:
                m_setup.music = !m_setup.music;
                break;
            case 27:
                if(m_setup.musicVolume > 0) { --m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                break;
            case 28:
                if(m_setup.musicVolume < 100) { ++m_setup.musicVolume; }
                sf::sleep(sf::milliseconds(40));
                break;
            case 29:
            case 30:
                m_setup.sound = !m_setup.sound;
                break;
            case 31:
                if(m_setup.soundVolume > 0) { --m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                break;
            case 32:
                if(m_setup.soundVolume < 100) { ++m_setup.soundVolume; }
                sf::sleep(sf::milliseconds(40));
                break;
            case 33:
                return false;
                break;
            case 34:
                saveSetUp();
                break;
            case 35:
                static std::string oldPseudo = m_setup.pseudo;
                static eventReader eventReader;
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
                    setPlayMenu(screen);
                    drawAllButtons(screen);
                    std::string label = m_configRoot["pseudobutton"][m_setup.language].asString();
                    screen.displayText(label, 24, sf::Color::White, 250 - ((label.size() * 14) / 2), 677);
                    label = m_configRoot["welcome"][m_setup.language].asString() + m_setup.pseudo;
                    screen.displayText(label, 32, sf::Color::White, 115, 625);
                    if(cursorTimer.isTimeElapsed()){
                        if(cursorColor == sf::Color::White)
                            { cursorColor = sf::Color::Black; }
                        else { cursorColor = sf::Color::White; }
                        cursorTimer.startTimer();
                    }
                    screen.drawRectangle(115 + ((label.size() + 1) * 13.2), 628 , 3, 32, cursorColor);
                    screen.render();
                }
                if(m_setup.pseudo == "") { m_setup.pseudo = oldPseudo; }
                m_setupRoot["setUp"]["pseudo"] = m_setup.pseudo;
                savePseudo();
                break;
            default:
                break;
        }
    return true;
}

void menu::setPlayMenu(manageScreen& screen)
{
    screen.drawGameName();
    loadButtons("playButton");
    drawAllButtons(screen);

}

void menu::playMenu(manageScreen& screen)
{
    bool iPlay{true};
    while(iPlay){
        screen.clear();
        setPlayMenu(screen);
        iPlay = launchAction(checkButtonsAction(screen.m_window), screen);
        drawAllButtons(screen);
        std::string label = m_configRoot["pseudobutton"][m_setup.language].asString();
        screen.displayText(label, 24, sf::Color::White, 250 - ((label.size() * 14) / 2), 677);
        label = m_configRoot["welcome"][m_setup.language].asString() + m_setup.pseudo;
        screen.displayText(label, 32, sf::Color::White, 115, 625);
        screen.render();
    }
}

void menu::setSetUp()
{
    m_setup.enhanced = m_setupRoot["setUp"].get("enhanced",1).asBool();
    m_setup.gameType = m_setupRoot["setUp"].get("gameType",0).asInt();
    m_setup.hold = m_setupRoot["setUp"].get("hold",1).asBool();
    m_setup.language = m_setupRoot["setUp"].get("language",1).asInt();
    m_setup.lockout = m_setupRoot["setUp"].get("lockout",1).asBool();
    m_setup.music = m_setupRoot["setUp"].get("music",1).asBool();
    m_setup.musicVolume = m_setupRoot["setUp"].get("musicVolume",100).asInt();
    m_setup.nextPiece = m_setupRoot["setUp"].get("nextPiece",1).asBool();
    m_setup.nextPiecesNumber = m_setupRoot["setUp"].get("nextPiecesNumber",5).asInt();
    m_setup.pieceGraphic = m_setupRoot["setUp"].get("pieceGraphic",0).asInt();
    m_setup.sevenBag = m_setupRoot["setUp"].get("sevenBag",1).asBool();
    m_setup.shadow = m_setupRoot["setUp"].get("shadow",1).asBool();
    m_setup.sound = m_setupRoot["setUp"].get("sound",1).asBool();
    m_setup.soundVolume = m_setupRoot["setUp"].get("soundVolume",100).asInt();
    m_setup.superRotationSystem = m_setupRoot["setUp"].get("superRotationSystem",1).asBool();
    setLocale(m_setup.language);
    m_setup.pseudo = m_setupRoot["setUp"].get("pseudo","").asString();
}

void menu::savePseudo()
{
    setLocale(m_setup.language);
    m_setupRoot["setUp"].get("pseudo","").asString() = m_setup.pseudo;
    saveJsonSetup("setup.json");
}

void menu::saveSetUp()
{
    m_setupRoot["setUp"]["enhanced"] = m_setup.enhanced;
    m_setupRoot["setUp"]["gameType"] = m_setup.gameType;
    m_setupRoot["setUp"]["hold"] = m_setup.hold;
    m_setupRoot["setUp"]["language"] = m_setup.language;
    m_setupRoot["setUp"]["lockout"] = m_setup.lockout;
    m_setupRoot["setUp"]["music"] = m_setup.music;
    m_setupRoot["setUp"]["musicVolume"] = m_setup.musicVolume;
    m_setupRoot["setUp"]["nextPiece"] = m_setup.nextPiece;
    m_setupRoot["setUp"]["nextPiecesNumber"] = m_setup.nextPiecesNumber;
    m_setupRoot["setUp"]["pieceGraphic"] = m_setup.pieceGraphic;
    m_setupRoot["setUp"]["sevenBag"] = m_setup.sevenBag;
    m_setupRoot["setUp"]["shadow"] = m_setup.shadow;
    m_setupRoot["setUp"]["sound"] = m_setup.sound;
    m_setupRoot["setUp"]["soundVolume"] = m_setup.soundVolume;
    m_setupRoot["setUp"]["superRotationSystem"] = m_setup.superRotationSystem;
    saveJsonSetup("setup.json");
}

void menu::printParameters(manageScreen& screen)
{
    std::string label = m_configRoot["setupSelector"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 102);
    label = m_configRoot["setupSelector"]["gameType"][m_setup.language][m_setup.gameType].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 182);
    label = m_configRoot["setupSelector"]["enhanced"][m_setup.language][m_setup.enhanced].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 222);
    label = m_configRoot["setupSelector"]["superRotationSystem"][m_setup.language][m_setup.superRotationSystem].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 262);
    label = m_configRoot["setupSelector"]["shadow"][m_setup.language][m_setup.shadow].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 302);
    label = m_configRoot["setupSelector"]["hold"][m_setup.language][m_setup.hold].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 342);
    label = m_configRoot["setupSelector"]["lockout"][m_setup.language][m_setup.lockout].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 382);
    label = m_configRoot["setupSelector"]["sevenBag"][m_setup.language][m_setup.sevenBag].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 422);
    label = m_configRoot["setupSelector"]["nextPiece"][m_setup.language][m_setup.nextPiece].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 462);
    label = std::to_string(m_setup.nextPiecesNumber);
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 502);
    label = m_configRoot["setupSelector"]["music"][m_setup.language][m_setup.music].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 542);
    label = std::to_string(m_setup.musicVolume);
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 582);
    label = m_configRoot["setupSelector"]["sound"][m_setup.language][m_setup.sound].asString();
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 622);
    label = std::to_string(m_setup.soundVolume);
    screen.displayText(label, 32, sf::Color::White, 770 - ((label.size() * 14) / 2), 662);
    screen.drawBlock(m_setup.pieceGraphic);
}

int menu::setxParam(int labelSize)
{
    if(labelSize % 2 > 0) { return 735; }
    else {return 755; }
}

void menu::printLabels(manageScreen& screen)
{
    screen.displayText(m_configRoot["paramtersTitles"]["title"][m_setup.language].asString(), 64, sf::Color::White, 350, 5);
    std::string label = m_configRoot["paramtersTitles"]["language"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 102);
    label = m_configRoot["paramtersTitles"]["pieceGraphic"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 142);
    label = m_configRoot["paramtersTitles"]["gameType"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 182);
    label = m_configRoot["paramtersTitles"]["enhanced"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 222);
    label = m_configRoot["paramtersTitles"]["superRotationSystem"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 262);
    label = m_configRoot["paramtersTitles"]["shadow"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 302);
    label = m_configRoot["paramtersTitles"]["hold"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 342);
    label = m_configRoot["paramtersTitles"]["lockout"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 17), 382);
    label = m_configRoot["paramtersTitles"]["sevenBag"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 422);
    label = m_configRoot["paramtersTitles"]["nextPiece"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 462);
    label = m_configRoot["paramtersTitles"]["nextPiecesNumber"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 502);
    label = m_configRoot["paramtersTitles"]["music"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 542);
    label = m_configRoot["paramtersTitles"]["musicVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 582);
    label = m_configRoot["paramtersTitles"]["sound"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 622);
    label = m_configRoot["paramtersTitles"]["soundVolume"][m_setup.language].asString();
    screen.displayText(label, 32, sf::Color::White, 275 - ((label.size() / 2) * 14), 662);
}
void menu::parametersMenu(manageScreen& screen)
{
    bool stayInMenu{true};
    while(stayInMenu == true) {
        screen.clear();
        printLabels(screen);
        printParameters(screen);
        loadButtons("setUpButtons");
        stayInMenu = launchAction(checkButtonsAction(screen.m_window), screen);
        drawAllButtons(screen);
        std::string label = m_configRoot["quit"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black,  135 - ((label.size() / 2) * 12), 26);
        label = m_configRoot["save"][m_setup.language].asString();
        screen.displayText(label, 28, sf::Color::Black, 875 - ((label.size() / 2) * 12), 26);
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
