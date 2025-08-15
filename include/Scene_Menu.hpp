#pragma once

#include "Scene.hpp"
#include "Action.hpp"
#include <SFML/Graphics.hpp>

class Scene_Menu : public Scene {
public:
    explicit Scene_Menu(SimulationEngine* simulationEngine = nullptr);

    void update() override;
    void sDoAction(const Action& action) override;
    void onEnd() override;
    void sRender() override;

protected:
    // No text or sound for prototype
};
