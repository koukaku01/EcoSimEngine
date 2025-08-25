#pragma once

#include <memory>

#include "SFML/Graphics/Text.hpp"

#include "EcoSimEngine/ecs/Components.hpp"
#include "EcoSimEngine/scene/Scene.hpp"
#include "EcoSimEngine/Utils/SpatialHash.hpp"
#include "EcoSimEngine/external/nlohmann/json.hpp"


class Scene_Simulation : public Scene {
private:
    std::string m_simKey;
	const std::string m_defaultSimulationPath{ "resources/defaults/default_simulation.json" };

    // simple species -> color map for rendering
    std::unordered_map<std::string, sf::Color> m_speciesColors;

    // spatial accel structure + timers
	SpatialHash m_spatialHash{ 120.0f }; // default cell size (tweakable)
	sf::Clock m_clock; // for timing updates

protected:
    bool m_drawTextures{ true };
    bool m_drawCollision{};
    bool m_drawGrid{};
    bool m_follow{};

    const Vec2f m_gridSize = { 64, 64 };
    //sf::Text m_gridText;

    Vec2f m_mousePos;

	// lifecycle
    void init(const std::string& simulationKey);
	void loadSimulation(const std::string& simulationKey); // load a named/save simulation (TODO: implement file loading)
    void loadDefaultSimulation(const std::string & defaultSimulationPath); // load default config
    void spawnFromJson(const nlohmann::json& simJson);                        // shared spawn logic 

    // scene callbacks
    void onEnd() override;
    void sDoAction(const Action& action) override;
    void sRender() override;
    //void sGUI();

public:
    // simKey = empty -> create new simulation from default config
    Scene_Simulation(SimulationEngine* simulationEngine, const std::string& simKey = {}); // Constructor takes in specific simulation name

    void update() override;
};
