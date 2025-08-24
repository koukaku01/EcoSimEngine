#include <memory>
#include "SFML/Graphics/Text.hpp"

#include "EcoSimEngine/ecs/Components.hpp"
#include "EcoSimEngine/scene/Scene.hpp"
#include "EcoSimEngine/Utils/SpatialHash.hpp"


class Scene_Simulation : public Scene {
    std::string m_simKey;
	std::string m_defaultSimulationPath{ "resources/defaults/default_simulation.json" };

    std::unordered_map<std::string, sf::Color> m_speciesColors;

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

    void init(std::string& simulationKey);
	void loadSimulation(std::string& simulationKey);
    void loadDefaultSimulation(std::string & defaultSimulationPath);

    void onEnd() override;

    // Systems
    void sDoAction(const Action& action) override;
    void sAI(float dt);
    void sMovement(float dt);
    void sRender() override;
    //void sGUI();

public:
    Scene_Simulation(SimulationEngine* simulationEngine, std::string& name); // Constructor takes in specific simulation name

    void update() override;
};
