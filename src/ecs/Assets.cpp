#include <cassert>
#include <fstream>
#include <iostream>

#include <SFML/Audio/SoundBuffer.hpp>

#include <nlohmann/json.hpp>

#include "EcoSimEngine/ecs/Assets.hpp"

Assets::Assets() = default;
Assets::~Assets() = default;

void Assets::loadFromFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) {
        throw std::runtime_error("Could not open file: " + path);
    }

    nlohmann::json j;
    ifs >> j;

    
    // -- Textures --
    if (j.contains("textures") && j["textures"].is_object()) {
        for (const auto& [name, texPath] : j["textures"].items()) {
            addTexture(name, texPath.get<std::string>());
        }
    }

    // -- Fonts --
    if (j.contains("fonts") && j["fonts"].is_object()) {
        for (const auto& [name, fontPath] : j["fonts"].items()) {
            addFont(name, fontPath.get<std::string>());
        }
    }

    // -- Sounds --
    if (j.contains("sounds") && j["sounds"].is_object()) {
        for (const auto& [name, soundPath] : j["sounds"].items()) {
            addSound(name, soundPath.get<std::string>());
        }
    }
}

// Add asset methods

void Assets::addTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Could not load texture: " + path);
    }
    m_textureMap[name] = texture;
}

void Assets::addFont(const std::string& name, const std::string& path) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        throw std::runtime_error("Could not load font: " + path);
    }
    m_fontMap[name] = font;
}

void Assets::addSound(const std::string& name, const std::string& path) {
    sf::SoundBuffer sb;
    if (!sb.loadFromFile(path)) {
        throw std::runtime_error("Could not load sound: " + path);
    }
    m_soundBuffers[name] = sb;

    // SFML 3.0.0
    // Create sf::Sound dynamically and store as unique_ptr
    m_soundMap[name] = std::make_unique<sf::Sound>(m_soundBuffers.at(name));
}


// getters for asset

const sf::Texture& Assets::getTexture(const std::string& name) const {
    assert(m_textureMap.find(name) != m_textureMap.end());
    return m_textureMap.at(name);
}

const sf::Font& Assets::getFont(const std::string& name) const {
    assert(m_fontMap.find(name) != m_fontMap.end());
    return m_fontMap.at(name);
}

sf::Sound& Assets::getSound(const std::string& name) {
    auto it = m_soundMap.find(name);
    if (it != m_soundMap.end()) {
        return *(it->second); // return the stored unique_ptr as reference
    }

    // If not found, create it using the buffer
    auto bufferIt = m_soundBuffers.find(name);
    if (bufferIt == m_soundBuffers.end()) {
        throw std::runtime_error("SoundBuffer not loaded: " + name);
    }

    // Create sf::Sound with buffer
    std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>(bufferIt->second);
    sf::Sound& ref = *sound;
    m_soundMap[name] = std::move(sound); // store in map
    return ref;
}


// getters for maps

const std::unordered_map<std::string, sf::Texture>& Assets::getTextureMap() const {
    return m_textureMap;
}

std::unordered_map<std::string, std::unique_ptr<sf::Sound>>& Assets::getSoundMap() {
    return m_soundMap;
}
