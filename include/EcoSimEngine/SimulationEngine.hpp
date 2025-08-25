#pragma once

#include <map>
#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"

#include "EcoSimEngine/scene/Scene.hpp"
#include "EcoSimEngine/scene/SceneManager.hpp"
#include "EcoSimEngine/ecs/Assets.hpp"
#include "EcoSimEngine/system/SystemManager.hpp"

struct WindowConfig {
    unsigned int width;
    unsigned int height;
    unsigned int frameRate;
    bool vsync;
};

class SimulationEngine {
protected:
    WindowConfig m_windowConfig;
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock; // for imgui
    Assets m_assets;
    SceneManager m_sceneManager;
	SystemManager m_systemManager;
    size_t m_simulationSpeed{ 1 };
    bool m_running{ true };
    std::shared_ptr<Scene> currentScene();

     ComponentManager m_componentManager; // REFACTORING ADD
     EntityManager m_entityManager;


    void init(const std::string& path);

    void update();

    void sUserInput();

    

public:
    explicit SimulationEngine(const std::string& path);

    void quit();

    void run();

    void playSound(const std::string& soundName);
    void stopSound(const std::string& soundName);

    sf::RenderWindow& window();

    Assets& assets();

    bool isRunning() const;

    SceneManager& sceneManager() noexcept { return m_sceneManager; }
    SystemManager& systemManager() noexcept { return m_systemManager; }
    EntityManager& entityManager() noexcept { return m_entityManager; }
    ComponentManager& componentManager() noexcept { return m_componentManager; }
};