#pragma once

#include <map>
#include <string>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Assets {
	std::map<std::string, sf::Texture> m_textureMap;
	std::map<std::string, sf::Font> m_fontMap;

	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	//std::map<std::string, sf::Sound> m_sounds;
    std::map<std::string, std::unique_ptr<sf::Sound>> m_sounds; // store sounds as unique_ptr

	void addTexture(const std::string& name, const std::string& path);

	void addFont(const std::string& name, const std::string& path);

	void addSound(const std::string& name, const std::string& path);

public:
    Assets();
    ~Assets();

    void loadFromFile(const json&j);

    [[nodiscard]] const std::map<std::string, sf::Texture>& getTextures() const;

    [[nodiscard]] std::map<std::string, std::unique_ptr<sf::Sound>>& getSounds();

    [[nodiscard]] const sf::Texture& getTexture(const std::string& name) const;

    [[nodiscard]] const sf::Font& getFont(const std::string& name) const;

    [[nodiscard]] sf::Sound& getSound(const std::string& name);
};