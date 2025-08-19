#include <memory>
#include "SFML/Graphics/Text.hpp"

#include "Components.hpp"
#include "Scene.hpp"


class Scene_Simulation : public Scene {
    std::string m_simKey;
protected:
    bool m_drawTextures = true;
    bool m_drawCollision = false;
    bool m_drawGrid = false;
    bool m_follow = false;

    const Vec2f m_gridSize = { 64, 64 };
    //sf::Text m_gridText;

    Vec2f m_mousePos;

    void init(std::string& simulationKey);

    void onEnd() override;

    void sDoAction(const Action& action) override;

    void sRender() override;

    //void sGUI();

public:
    Scene_Simulation(SimulationEngine* simulationEngine, std::string& name);

    void update() override;
};
