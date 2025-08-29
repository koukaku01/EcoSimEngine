#pragma once

#include "EcoSimEngine/scene/Scene.hpp"

#include <map>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

// --- Enum for static scenes ---
enum class SceneID {
	Menu,
	Options
};


class SceneManager {
	using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;
	SceneMap m_staticScenes;		// fixed scenes like Menu, Options
	SceneMap m_simulationScenes;	// user-created or loadable simulations

	std::string m_currentSceneKey;

	// Helper: convert enum to string for static scenes
	static std::string sceneIDtoString(SceneID id) {
		switch (id) {
		case SceneID::Menu: return "MENU";
		case SceneID::Options: return "OPTIONS";
		default: return "UNKNOWN";
		}
	}

public:
	SceneManager() = default;

	// Change to a static scene
	void changeScene(SceneID id, std::shared_ptr<Scene> scene, bool endCurrentScene = false) {
		changeScene(sceneIDtoString(id), std::move(scene), endCurrentScene, true);
	}

	// Chnage to a simulation scene
	void changeSimulationScene(const std::string& simKey, std::shared_ptr<Scene> scene, bool endCurrentScene = false) {
		changeScene(simKey, std::move(scene), endCurrentScene, false);
	}

	// Get current scene
	std::shared_ptr<Scene> getCurrentScene() {
		if (m_currentSceneKey.empty())
			throw std::runtime_error("Current scene not set");

		auto it = m_staticScenes.find(m_currentSceneKey);
		if (it != m_staticScenes.end()) return it->second;

		it = m_simulationScenes.find(m_currentSceneKey);
		if (it != m_simulationScenes.end()) return it->second;

		throw std::runtime_error("Current scene not found: " + m_currentSceneKey);
	}

	std::shared_ptr<Scene> getMenuScene() {
		auto it = m_staticScenes.find(sceneIDtoString(SceneID::Menu));
		if (it != m_staticScenes.end()) return it->second;
		return nullptr;
	}

	// ------------------------
	// --- Scene Queries ---
	// ------------------------

	bool hasScene(const std::string& key) const {
		return m_staticScenes.find(key) != m_staticScenes.end() ||
			m_simulationScenes.find(key) != m_simulationScenes.end();
	}

	std::vector<std::string> getAllSimulationKeys() const {
		std::vector<std::string> keys;
		for (const auto& [key, _] : m_simulationScenes) keys.push_back(key);
		return keys;
	}


	// ------------------------
	// --- Scene Management ---
	// ------------------------
	void removeScene(const std::string& key) {
		if (m_currentSceneKey == key) m_currentSceneKey.clear();
		m_staticScenes.erase(key);
		m_simulationScenes.erase(key);
	}

	void renameSimulation(const std::string& oldKey, const std::string& newKey) {
		auto it = m_simulationScenes.find(oldKey);
		if (it != m_simulationScenes.end()) {
			m_simulationScenes[newKey] = std::move(it->second);
			m_simulationScenes.erase(it);
			if (m_currentSceneKey == oldKey) m_currentSceneKey = newKey;
		}
	}

private:
	// Core internal changeScene
	void changeScene(const std::string& key, std::shared_ptr<Scene> scene, bool endCurrentScene, bool isStatic) {
		if (endCurrentScene && !m_currentSceneKey.empty()) {
			removeScene(m_currentSceneKey);
		}
		m_currentSceneKey = key;
		if (isStatic) m_staticScenes[key] = std::move(scene);
		else m_simulationScenes[key] = std::move(scene);
	}
};
