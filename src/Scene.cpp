#include "Scene.hpp"
#include "SimulationEngine.hpp" // full definition needed here

// ===== Protected methods =====
void Scene::setPaused(bool paused) {
    m_paused = paused;
}

// ===== Constructors =====
Scene::Scene(SimulationEngine* simulationEngine)
    : m_simulation(simulationEngine) {
}

// ===== Public methods =====
void Scene::sDoAction(const Action& action) {
    // Default empty implementation
}

void Scene::doAction(const Action& action) {
    sDoAction(action);
}

void Scene::simulate(size_t frames) {
    // Default empty implementation
}

void Scene::registerAction(sf::Keyboard::Key inputKey, const std::string& actionName) {
    m_actionMap[inputKey] = actionName;
}

float Scene::width() const {
    return static_cast<float>(m_simulation->window().getSize().x);
}

float Scene::height() const {
    return static_cast<float>(m_simulation->window().getSize().y);
}

size_t Scene::currentFrame() const {
    return m_currentFrame;
}

bool Scene::hasEnded() const {
    return m_hasEnded;
}

const ActionMap& Scene::getActionMap() const {
    return m_actionMap;
}

void Scene::drawLine(const Vec2f& p1, const Vec2f& p2) {
    sf::Vertex line[] = {
        sf::Vertex{sf::Vector2f{p1.x, p1.y}},
        sf::Vertex{sf::Vector2f{p2.x, p2.y}}
    };
    m_simulation->window().draw(line, 2, sf::PrimitiveType::Lines);
}
