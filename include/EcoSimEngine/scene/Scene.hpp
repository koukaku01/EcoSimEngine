#pragma once

#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "EcoSimEngine/ecs/Action.hpp"
#include "EcoSimEngine/ecs/EntityManager.hpp"

// Forward declaration to break circular include
class SimulationEngine;

using ActionMap = std::map<sf::Keyboard::Key, ActionName>;

class Scene {
protected:
    SimulationEngine* m_simulation{ nullptr };
    EntityManager m_entityManager;
    ActionMap m_actionMap;
    bool m_paused{ false };
    bool m_hasEnded{ false };
    size_t m_currentFrame{ 0 };

    virtual void onEnd() = 0;

    void setPaused(bool paused);

public:
    Scene() = default;
    explicit Scene(SimulationEngine* simulationEngine);
    virtual ~Scene() = default;

    virtual void update() = 0;
    virtual void sDoAction(const Action& action);
    virtual void sRender() = 0;
    virtual void doAction(const Action& action);

    void simulate(size_t frames);
    void registerAction(sf::Keyboard::Key inputKey, const ActionName actionName);

    [[nodiscard]] float width() const;
    [[nodiscard]] float height() const;
    [[nodiscard]] size_t currentFrame() const;
    [[nodiscard]] bool hasEnded() const;
    [[nodiscard]] const ActionMap& getActionMap() const;

    void drawLine(const Vec2f& p1, const Vec2f& p2);
};
