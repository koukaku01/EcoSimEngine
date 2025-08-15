// Project: Ecosystem Simulation
// SFML version 3.0.0
// C++ version C++20
// 
// external libraries used:
// - SFML 3.0.0
// - nlohmann/json

#include <SFML/Graphics.hpp>
#include "SimulationEngine.hpp"
#include "Vec2.hpp"

int main(void) {
	SimulationEngine sim("config/config.json");
	sim.run();

    return 0;
}