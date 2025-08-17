#include "Scene_Menu.hpp"
#include "SimulationEngine.hpp"
#include "Vec2.hpp"
#include "Assets.hpp"
#include "Action.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Scene_Menu::Scene_Menu(SimulationEngine* simulationEngine)
    : Scene(simulationEngine)
{
    init();
}

void Scene_Menu::init() {
	// Set the view to the center of the window
    sf::View view = m_simulation->window().getView();
    view.setCenter({
        static_cast<float>(m_simulation->window().getSize().x) / 2.0f,
        static_cast<float>(m_simulation->window().getSize().y) / 2.0f }
    );
    m_simulation->window().setView(view);

	// Register actions for the menu
    registerAction(sf::Keyboard::Key::W, "UP");
    registerAction(sf::Keyboard::Key::S, "DOWN");
    registerAction(sf::Keyboard::Key::Enter, "SELECT");
    registerAction(sf::Keyboard::Key::Escape, "BACK");

    // Load sound
    sf::Sound& m_titleMusic = m_simulation->assets().getSound("Foo");
    m_titleMusic.play();


    const sf::Font& font = m_simulation->assets().getFont("Main");

	// Create title text
    m_titleText = std::make_unique<sf::Text>(font, sf::String(m_title), 48);
    m_titleText->setFillColor(sf::Color::White);
    //    // Center origin
    sf::FloatRect textRect = m_titleText->getLocalBounds();
    m_titleText->setOrigin({ textRect.size.x / 2.f, textRect.size.y / 2.f });
    m_titleText->setPosition({
        m_simulation->window().getSize().x / 2.f,
        50.f }
    );


    // Create main menu texts
    for (size_t i = 0; i < m_mainItems.size(); ++i)
    {
        m_mainTexts.emplace_back(font, sf::String(m_mainItems[i]), 24);
        m_mainTexts.back().setFillColor((i == m_selectedMainIndex) ? sf::Color::Yellow : sf::Color::White);
        m_mainTexts.back().setPosition({ 100.f, 100.f + i * 40.f });
    }

    // Create sub menu texts
    for (size_t i = 0; i < m_subItems.size(); ++i) {
        m_subTexts.emplace_back(font, sf::String(m_subItems[i]), 24);
        m_subTexts.back().setFillColor(sf::Color::White);
        m_subTexts.back().setPosition({ 150.f, 150.f + i * 40.f });
    }
}




void Scene_Menu::sDoAction(const Action& action) {
    if (action.type() != "START") return; // <-- ignore auto-repeat and END events

    if (m_menuState == MenuState::Main)
    {
        if (action.name() == "UP") {
            if (m_selectedMainIndex == 0)
                m_selectedMainIndex = m_mainItems.size() - 1;
            else
                --m_selectedMainIndex;
        }
        if (action.name() == "DOWN") {
            m_selectedMainIndex = (m_selectedMainIndex + 1) % m_mainItems.size();
        }
        if (action.name() == "SELECT") {
            if (m_selectedMainIndex == 1) { // Load -> switch to sub-menu
                m_menuState = MenuState::SubMenu;
                m_selectedSubIndex = 0;
            }
            else if (m_selectedMainIndex == 3) { // Quit
                onEnd();
            }
        }

        // Update colours
		for (size_t i = 0; i < m_mainTexts.size(); ++i) {
			m_mainTexts[i].setFillColor((i == m_selectedMainIndex) ? sf::Color::Yellow : sf::Color::White);
		}

    }
    else if (m_menuState == MenuState::SubMenu) {
        if (action.name() == "UP") {
            if (m_selectedSubIndex == 0)
                m_selectedSubIndex = m_subItems.size() - 1;
            else
                --m_selectedSubIndex;
        }
        if (action.name() == "DOWN") {
            m_selectedSubIndex = (m_selectedSubIndex + 1) % m_subItems.size();
        }
        if (action.name() == "BACK") {
            m_menuState = MenuState::Main;
        }
        else if (action.name() == "SELECT") {
            // TODO: Handle Sub-menu selection
            // something like
            //      //   m_game->changeScene("PLAY", std::make_shared<Scene_Simulation>(m_game, __SIMULATION_FILE_HERE__));

        }

        for (size_t i = 0; i < m_subTexts.size(); ++i)
            m_subTexts[i].setFillColor(i == m_selectedSubIndex ? sf::Color::Yellow : sf::Color::White);
    }
}



void Scene_Menu::sRender() {
    sf::RenderWindow& window = m_simulation->window();

    // Clear window with charcoal background
    window.clear(sf::Color(31, 31, 31));

	// Draw title text
    if (m_titleText) window.draw(*m_titleText);


    // Draw rectangle in the center
    sf::RectangleShape rect;
    rect.setSize({ 200.f, 100.f });
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(Vec2f(
        (window.getSize().x - rect.getSize().x) / 2.f,
        (window.getSize().y - rect.getSize().y) / 2.f)
    );
    window.draw(rect);

    // draw menu texts depends on the MenuState
    if (m_menuState == MenuState::Main) {
        for (auto& text : m_mainTexts) {
            window.draw(text);
        }
    }
    else if (m_menuState == MenuState::SubMenu) {
        for (auto& text : m_subTexts) {
            window.draw(text);
        }
    }
}



void Scene_Menu::onEnd() {
    m_simulation->quit();
}

void Scene_Menu::update() {
    sRender();
}