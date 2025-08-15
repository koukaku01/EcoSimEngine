#include <cassert>
#include <fstream>
#include <iostream>

#include <SFML/Audio/SoundBuffer.hpp>

#include <nlohmann/json.hpp>

#include "Assets.hpp"

Assets::Assets() = default;
Assets::~Assets() = default;

using json = nlohmann::json;
namespace fs = std::filesystem;

void Assets::loadFromFile(const json& j) {
    // -- Textures --
    if (j.contains("textures") && j["textures"].is_object()) {
        for (auto& it : j["textures"].items()) {
            const std::string name = it.key();
            const std::string texPath = it.value().get<std::string>();
            addTexture(name, texPath);      
        }
    }

    // -- Fonts --
    if (j.contains("fonts") && j["fonts"].is_object()) {
        for (auto& it : j["fonts"].items()) {
            addFont(it.key(), it.value().get<std::string>());
        }
    }

    // -- Sounds --
    if (j.contains("sounds") && j["sounds"].is_object()) {
        for (auto& it : j["sounds"].items()) {
            addSound(it.key(), it.value().get<std::string>());
        }
    }
}

// Add asset methods

void Assets::addTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Could not load image: " << path << "!\n";
        exit(-1);
    }
    m_textureMap[name] = texture;
}

void Assets::addFont(const std::string& name, const std::string& path) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        std::cerr << "Could not load font: " << path << "\n";
        exit(-1);
    }
    m_fontMap[name] = font;
}

void Assets::addSound(const std::string& name, const std::string& path) {
    sf::SoundBuffer sb;
    if (!sb.loadFromFile(path)) {
        std::cerr << "Could not load sound: " << path << "\n";
        exit(-1);
    }
    m_soundBuffers[name] = sb;

    // create sf::Sound dynamically
    auto sound = std::make_unique<sf::Sound>(m_soundBuffers.at(name));
    m_sounds[name] = std::move(sound);
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
    assert(m_sounds.find(name) != m_sounds.end());
    return *(m_sounds.at(name));
}

// getters for maps

const std::map<std::string, sf::Texture>& Assets::getTextures() const {
    return m_textureMap;
}

std::map<std::string, std::unique_ptr<sf::Sound>>& Assets::getSounds() {
    return m_sounds;
}
