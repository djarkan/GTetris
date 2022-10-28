#include "help.hpp"

help::help()
{

}

void help::displayHelpPage(manageScreen &screen,  int pageIndex, int language)
{
    std::string label;
    switch(pageIndex) {
        case 0:
             label = m_helpText.m_Root["gameControl"][language].asString();
             screen.displayText(label, 32,sf::Color::White, 10, 10);
            break;
        case 1 : {
            sf::IntRect source(0, 1600, 850, 500);
            sf::Vector2f destination(155, 100);
            screen.rawRenderCopy(source, destination, 255);
            label = "[c25][u]JOYSTICK[/u][/c]";
            screen.displayText(label, 48,sf::Color::White, 490  - ((static_cast<float>(label.size() - 16) * 16) / 2.f), 20);
            label = m_helpText.m_Root["hold"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 390  - ((static_cast<float>(label.size()) * 12) / 2.f), 130);
            screen.displayText(label, 32,sf::Color::White, 620  - ((static_cast<float>(label.size()) * 12) / 2.f), 130);
            label = m_helpText.m_Root["escape"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 800  - ((static_cast<float>(label.size()) * 12) / 2.f), 210);
            label = m_helpText.m_Root["pause"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 500  - ((static_cast<float>(label.size()) * 12) / 2.f), 220);
            label = m_helpText.m_Root["rotationleft"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 820  - ((static_cast<float>(label.size()) * 12) / 2.f), 320);
            label = m_helpText.m_Root["rotationright"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 820  - ((static_cast<float>(label.size()) * 12) / 2.f), 440);
            label = m_helpText.m_Root["space"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 640  - ((static_cast<float>(label.size()) * 12) / 2.f), 520);
            label = m_helpText.m_Root["moveright"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 350  - ((static_cast<float>(label.size()) * 12) / 2.f), 555);
            label = m_helpText.m_Root["softdrop"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 160  - ((static_cast<float>(label.size()) * 12) / 2.f), 470);
            label = m_helpText.m_Root["moveleft"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 130  - ((static_cast<float>(label.size()) * 12) / 2.f), 360);
            label = m_helpText.m_Root["harddrop"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 160  - ((static_cast<float>(label.size()) * 12) / 2.f), 260);

            break;
        }
        case 2:
            label = m_helpText.m_Root["gameMode"][language].asString();
            screen.displayText(label, 32,sf::Color::White, 10, 10);
            break;
        case 3:
             label = m_helpText.m_Root["parameters1"][language].asString();
             screen.displayText(label, 32,sf::Color::White, 10, 10);
            break;
        case 4:
             label = m_helpText.m_Root["parameters2"][language].asString();
             screen.displayText(label, 32,sf::Color::White, 10, 10);
            break;
        case 5:
             label = m_helpText.m_Root["parameters3"][language].asString();
             screen.displayText(label, 32,sf::Color::White, 10, 10);
            break;
    }
}

bool help::loadHelpText()
{
    return m_helpText.loadJsonFile("language\\help.json");
}
