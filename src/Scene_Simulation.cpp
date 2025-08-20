#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <random>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"

#include "nlohmann/json.hpp"

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
	loadSimulation(simulationKey);

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

void Scene_Simulation::loadSimulation(std::string& simulationKey) {
    // reset the entity manager every time we load a level
    m_entityManager = EntityManager();
	// Load the simulation data from a file or database
	// For now, we will just print the simulation key
	std::cout << "Loading simulation with key: " << simulationKey << std::endl;
	// Here you would typically load entities, components, and other simulation data
	// For example:
	// m_entityManager.loadEntitiesFromFile(simulationKey + ".entities");
	// m_componentManager.loadComponentsFromFile(simulationKey + ".components");

    // Load default simulation
	loadDefaultSimulation(m_defaultSimulationPath);
}

void Scene_Simulation::loadDefaultSimulation(std::string& defaultSimulationPath) {
	// Load default entities and components for the simulation from default JSON
    
    // reset the entity manager every time we load a level
    m_entityManager = EntityManager();

	std::cout << "Loading default simulation from: " << defaultSimulationPath << std::endl;

	std::ifstream file(defaultSimulationPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open default simulation file: " << defaultSimulationPath << std::endl;
        return;
    }

	nlohmann::json sim;
	file >> sim;

    // read population counts
    auto populations = sim["simulation"]["initialPopulation"];

    // --- set up RNG once per load ---
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(
        0, sim["simulation"]["world"]["size"]["width"].get<int>());
    std::uniform_real_distribution<float> distY(
        0, sim["simulation"]["world"]["size"]["height"].get<int>());

    for (auto& [speciesName, popData] : populations.items()) {
        int total = popData["total"];
		int males = popData["male"];
		int females = popData["female"];

	    // load species data JSON (per-species data)
	    std::string speciesFile = "resources/data/species/" + speciesName + ".json";
	    std::ifstream sf(speciesFile);
        if (!sf.is_open()) {
            std::cerr << "Could not open species file: " << speciesFile << "\n";
            continue;
        }
        nlohmann::json speciesJson;
	    sf >> speciesJson;

        // create entities
        for (int i = 0; i < total; i++) {
            auto entity = m_entityManager.addEntity(speciesName);

            // --- add Compoennts ---
			entity->add<CSpecies>(speciesName, 0); // default age is 0
            entity->add<CHealth>(100.0f);
            entity->add<CEnergy>(100.0f);

            // proper random position
            float x = distX(gen);
            float y = distY(gen);
            entity->add<CTransform>(Vec2f(x, y));

            // reproductive component
			auto& repro = entity->add<CReproductive>();
            repro.sex = (i < males ? Sex::Male : Sex::Female);
            repro.canReproduce = true;

            // TODO
            // default AI 
            entity->add<CBehavior>();
        }
        std::cout << "Loaded " << total << " " << speciesName << " entities.\n";
    }

    	
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
    m_simulation->sceneManager()
        .changeScene(SceneID::Menu, std::make_shared<Scene_Menu>(m_simulation));
}


void Scene_Simulation::sRender() {
    sf::RenderWindow& win = m_simulation->window();
    win.clear(sf::Color(15, 15, 20));

    for (const auto& entity : m_entityManager.getEntities()) {
        if (!entity->isActive()) continue;

        if (entity->has<CTransform>()) {
            const auto& transform = entity->get<CTransform>();
            sf::CircleShape circle(5.0f);
            circle.setFillColor(sf::Color::White);
            circle.setOrigin({ circle.getRadius(), circle.getRadius() }); // center on pos
            circle.setPosition(transform.pos);

            win.draw(circle);
        }
    }
}
