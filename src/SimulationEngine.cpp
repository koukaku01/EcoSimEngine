#include <iostream>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"

//#include "imgui.h"
//#include "imgui-SFML.h"
#include "SFML/Window/Event.hpp"

#include "Assets.hpp"
#include "SimulationEngine.hpp"
#include "Scene_Menu.hpp"


SimulationEngine::SimulationEngine(const std::string& path) {
    init(path);
}

void SimulationEngine::init(const std::string& path) {
    // Load JSON config
	std::ifstream ifs(path);
    if (!ifs) {
        throw std::runtime_error("Could not open config file: " + path + "(SimulationEngine)");
    }
    nlohmann::json json;
    ifs >> json;

    // Parse window config
	auto w = json["window"];
    m_windowConfig.width = w["width"];
	m_windowConfig.height = w["height"];
    m_windowConfig.frameRate = w["frameRate"];
	m_windowConfig.vsync = w["vsync"];

    // Apply window config
    m_window.create(sf::VideoMode({ m_windowConfig.width, m_windowConfig.height })
        , "Ecosystem Simulation");
	m_window.setFramerateLimit(m_windowConfig.frameRate);
	m_window.setVerticalSyncEnabled(m_windowConfig.vsync);

	// Load assets
    m_assets.loadFromFile(json);

    /*
    if (!ImGui::SFML::Init(m_window)) {
        std::cerr << "Failed ImGui initialization\n";
    }
    */

    changeScene("MENU", std::make_shared<Scene_Menu>(this));
}

std::shared_ptr<Scene> SimulationEngine::currentScene() {
    return m_sceneMap[m_currentScene];
}

bool SimulationEngine::isRunning() {
    return m_running & m_window.isOpen(); // maybe '&&' instead of '&'?
}

sf::RenderWindow& SimulationEngine::window() {
    return m_window;
}

void SimulationEngine::run() {
    while (isRunning()) {
        sUserInput();
     //   ImGui::SFML::Update(m_window, m_deltaClock.restart());
        update();
     //   ImGui::SFML::Render(m_window);
        m_window.display();
    }
}

void SimulationEngine::sUserInput() {
    while (auto eventOpt = m_window.pollEvent()) {
		auto& event = *eventOpt;
     ///ImGui::SFML::ProcessEvent(m_window, event); // need refactor

		// Handle window closed
        if (event.is<sf::Event::Closed>()) {
            quit();
            continue;
        }

        /* TODO
        // Screenshot on 'X' key press
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::X) {
                std::cout << "Save screenshot to " << "test.png" << std::endl;
                sf::Texture texture;
                texture.create(m_window.getSize().x, m_window.getSize().y);
                texture.update(m_window);
                if (texture.copyToImage().saveToFile("test.png")) {
                    std::cout << "Screenshot saved to " << "test.png" << std::endl;
                }
            }
        }
        */


        if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            int keyInt = static_cast<int>(keyEvent->code);
            auto it = currentScene()->getActionMap().find(keyInt);
            if (it != currentScene()->getActionMap().end()) {
                currentScene()->doAction(Action(it->second, "START"));
            }
        }
        else if (auto keyEvent = event.getIf<sf::Event::KeyReleased>()) {
            int keyInt = static_cast<int>(keyEvent->code);
            auto it = currentScene()->getActionMap().find(keyInt);
            if (it != currentScene()->getActionMap().end()) {
                currentScene()->doAction(Action(it->second, "END"));
            }
        }


        // this line ignores mouse events if ImGui is the thing clicked
        //   if (ImGui::GetIO().WantCaptureMouse) { continue; }


        // --- Mouse buttons ---
        auto mousePos = sf::Mouse::getPosition(m_window);
        Vec2f pos = Vec2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        if (auto mb = event.getIf<sf::Event::MouseButtonPressed>()) {
            switch (mb->button) {
            case sf::Mouse::Button::Left:
                currentScene()->doAction(Action("LEFT_CLICK", "START", pos));
                break;
            case sf::Mouse::Button::Middle:
                currentScene()->doAction(Action("MIDDLE_CLICK", "START", pos));
                break;
            case sf::Mouse::Button::Right:
                currentScene()->doAction(Action("RIGHT_CLICK", "START", pos));
                break;
            default:
                break;
            }
        }

        if (auto mb = event.getIf<sf::Event::MouseButtonReleased>()) {
            switch (mb->button) {
            case sf::Mouse::Button::Left:
                currentScene()->doAction(Action("LEFT_CLICK", "END", pos));
                break;
            case sf::Mouse::Button::Middle:
                currentScene()->doAction(Action("MIDDLE_CLICK", "END", pos));
                break;
            case sf::Mouse::Button::Right:
                currentScene()->doAction(Action("RIGHT_CLICK", "END", pos));
                break;
            default:
                break;
            }
        }

        // --- Mouse Move ---
        if (auto mm = event.getIf<sf::Event::MouseMoved>()) {
            currentScene()->doAction(Action("MOUSE_MOVE", Vec2f(static_cast<float>(mm->position.x), static_cast<float>(mm->position.y))));
        }
    }
}

void SimulationEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene) {
    m_currentScene = sceneName;
    m_sceneMap[sceneName] = std::move(scene);
}

void SimulationEngine::quit() {
    m_running = false;
    m_window.close();
}

void SimulationEngine::update() {
    currentScene()->update();
}

Assets& SimulationEngine::assets() {
    return m_assets;
}
