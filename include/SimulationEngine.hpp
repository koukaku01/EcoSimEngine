#pragma once

#include <map>
#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"

#include "Scene.hpp"
#include "Assets.hpp"
#include "SceneManager.hpp"

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
    size_t m_simulationSpeed{ 1 };
    bool m_running{ true };
    std::shared_ptr<Scene> currentScene();


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

    SceneManager& sceneManager();
};