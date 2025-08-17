#pragma once

#include "Scene.hpp"
#include "Action.hpp"
#include "Assets.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

enum class MenuState {
    Main,
    SubMenu
};

class Scene_Menu : public Scene {
protected:
    MenuState m_menuState{ MenuState::Main };

    std::unique_ptr<sf::Text> m_titleText;
    std::string m_title{ "Main Menu" };

    std::vector<std::string> m_mainItems{ "New", "Load", "Options", "Quit" };
    std::vector<std::string> m_subItems{ "Simulation1", "Simulation2", "Simulation3" };

    std::vector<sf::Text> m_mainTexts;
    std::vector<sf::Text> m_subTexts;

    size_t m_selectedMainIndex{ 0 };
    size_t m_selectedSubIndex{ 0 };

    void init();
    void update() override;
    void sDoAction(const Action& action) override;
    void onEnd() override;

public:
    explicit Scene_Menu(SimulationEngine* simulationEngine = nullptr);

    void sRender() override;
};
