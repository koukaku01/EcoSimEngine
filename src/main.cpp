// Project: Ecosystem Simulation
// SFML version 3.0.0
// C++ version C++20
// 
// external libraries used:
// - SFML 3.0.0
// - nlohmann/json 3.12.0
// - ImGui-SFML 3.0

#include <SFML/Graphics.hpp>
#include "EcoSimEngine/SimulationEngine.hpp"
#include "EcoSimEngine/math/Vec2.hpp"

int main(void) {
	SimulationEngine sim("config/config.json");
	sim.run();

    return 0;
}