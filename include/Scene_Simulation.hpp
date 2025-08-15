#include <memory>
#include "SFML/Graphics/Text.hpp"

#include "Components.hpp"
#include "Scene.hpp"


class Scene_Simulation : public Scene {
    struct PlayerConfig {
        float X, Y, CX, CY, SPEED, HEALTH;
    };

protected:
    std::string m_levelPath;
    PlayerConfig m_playerConfig{};

    bool m_drawTextures = true;
    bool m_drawCollision = false;
    bool m_drawGrid = false;
    bool m_follow = false;

    const Vec2f m_gridSize = { 64, 64 };
    sf::Text m_gridText;

    Vec2f m_mousePos;

    void init(const std::string& levelPath);

    void loadLevel(const std::string& levelPath);

    void onEnd() override;

    void spawnPlayer();

    void spawnSword(const std::shared_ptr<Entity>& entity);

    Vec2f getPosition(int rx, int ry, int tx, int ty) const;

    std::shared_ptr<Entity> player();

    void sDoAction(const Action& action) override;

    void sMovement();

    void sAI();

    void sStatus();

    void sAnimation();

    void sCollision();

    void sCamera();

    void sGUI();

    void sRender() override;

    void sDrag();

    void changePlayerStateTo(const std::string& state, const Vec2f& facing);

    Vec2f windowToWorld(const Vec2f& pos);

    Vec2f getRoomXY(const Vec2f& pos);

    void movementStart(const std::string& actionName);

    void animatePlayer();

public:

    Scene_Simulation(SimulationEngine* simulationEngine, std::string& levelPath);

    void update() override;
};
