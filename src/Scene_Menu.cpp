#include "Scene_Menu.hpp"
#include "SimulationEngine.hpp"
#include "Vec2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

Scene_Menu::Scene_Menu(SimulationEngine* simulationEngine)
    : Scene(simulationEngine)
{
    // Nothing special for prototype
}

void Scene_Menu::update() {
    sRender();
}

void Scene_Menu::sDoAction(const Action&) {
    // No actions needed for prototype
}

void Scene_Menu::onEnd() {
    m_simulation->quit();
}

void Scene_Menu::sRender() {
    // Clear window with blue background
    m_simulation->window().clear(sf::Color(100, 100, 255));

    // Draw a simple rectangle in the center
    sf::RectangleShape rect;
    rect.setSize({ 200.f, 100.f });
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(Vec2f(
        (m_simulation->window().getSize().x - rect.getSize().x) / 2.f,
        (m_simulation->window().getSize().y - rect.getSize().y) / 2.f)
    );
    m_simulation->window().draw(rect);

}
