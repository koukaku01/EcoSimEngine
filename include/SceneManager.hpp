#pragma once

#include "Scene.hpp"

class SceneManager {
	using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;

	SceneMap m_scenes;
	std::string m_currentScene;

public:
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false) {
		if (endCurrentScene && !m_currentScene.empty())
		{
			m_scenes.erase(m_currentScene);
		}
		m_currentScene = sceneName;
		m_scenes[sceneName] = std::move(scene);
	}

	std::shared_ptr<Scene> getCurrentScene() {
		return m_scenes.at(m_currentScene);
	}

	bool hasScene(const std::string& sceneName) const {
		return m_scenes.find(sceneName) != m_scenes.end();
	}

	void removeScene(const std::string& sceneName) {
		m_scenes.erase(sceneName);
	}
};