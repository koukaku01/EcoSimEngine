#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"

// #include "imgui.h"
// #include "imgui-SFML.h"

#include "Components.hpp"
#include "SimulationEngine.hpp"
#include "Scene_Menu.hpp"
#include "Scene_Simulation.hpp"
#include "Vec2.hpp"


Scene_Simulation::Scene_Simulation(SimulationEngine* simulation, std::string& simKey)
    : Scene(simulation), m_simKey(simKey){
    init(simKey);
}

void Scene_Simulation::init(std::string& simulationKey) {
    // MAYDELETE
   // m_gridText.setCharacterSize(12);
   // m_gridText.setFont(m_simulation->assets().getFont("Main"));

    registerAction(sf::Keyboard::Key::Escape, ActionName::QUIT_AND_SAVE);
    registerAction(sf::Keyboard::Key::P, ActionName::PAUSE);
    registerAction(sf::Keyboard::Key::Y, ActionName::TOGGLE_FOLLOW);    // toggle follow camera
    registerAction(sf::Keyboard::Key::T, ActionName::TOGGLE_TEXTURE);   // toggle drawing (T)extures
    registerAction(sf::Keyboard::Key::C, ActionName::TOGGLE_COLLISION); // toggle drawing (C)ollision Box
    registerAction(sf::Keyboard::Key::G, ActionName::TOGGLE_GRID);      // toggle drawing (G)rid

    // Register the actions required to simulation control
    registerAction(sf::Keyboard::Key::W, ActionName::UP);
    registerAction(sf::Keyboard::Key::S, ActionName::DOWN);
    registerAction(sf::Keyboard::Key::A, ActionName::LEFT);
    registerAction(sf::Keyboard::Key::D, ActionName::RIGHT);
}

void Scene_Simulation::sDoAction(const Action& action) {
    if (action.type() != ActionType::START) return;

    if (action.name() == ActionName::QUIT_AND_SAVE) 
    {
        onEnd();
    }

}


void Scene_Simulation::update() {
    m_entityManager.update();

    // Implement pause functionality
    if (!m_paused) {
		//sDrag(); // MAYDELETE
        //sAI();
        //sMovement();
        //sStatus();
        //sCollision();
        //sAnimation();
        //sCamera();
        m_currentFrame++;
    }

    //sGUI();
    sRender();
}

void Scene_Simulation::onEnd() {
    // When the scene ends, change back to the MENU scene

    // Important: pass m_simulation (the SimulationEngine context) to Scene_Menu,
    // not "this". Scenes should always receive the engine that owns them so they
    // can access window, assets, input, etc. Passing "this" (the current scene)
    // would be wrong because Scene_Menu is not constructed from another scene.
    m_simulation->sceneManager().changeScene(SceneID::Menu, std::make_shared<Scene_Menu>(m_simulation));
}


void Scene_Simulation::sRender() {
    m_simulation->window().clear(sf::Color(255, 192, 122));
    sf::RectangleShape tick({ 1.0f, 6.0f });
    tick.setFillColor(sf::Color::Black);
}
