#pragma once

#include <map>
#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"

#include "Scene.hpp"
#include "Assets.hpp"

struct WindowConfig {
    unsigned int width;
    unsigned int height;
    unsigned int frameRate;
    bool vsync;
};

using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

class SimulationEngine {
protected:
	WindowConfig m_windowConfig;
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock; // for imgui
    Assets m_assets;
    std::string m_currentScene;
    SceneMap m_sceneMap;
    size_t m_simulationSpeed{ 1 };
    bool m_running{ true };

    void init(const std::string& path);

    void update();

    void sUserInput();

    std::shared_ptr<Scene> currentScene();

public:
    explicit SimulationEngine(const std::string& path);

    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

    void quit();

    void run();

    void playSound(const std::string& soundName);

    void stopSound(const std::string& soundName);

    sf::RenderWindow& window();

    Assets& assets();

    bool isRunning() const;
};
