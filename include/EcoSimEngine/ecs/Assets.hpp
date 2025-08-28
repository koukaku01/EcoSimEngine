#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>


class Assets {
	std::unordered_map<std::string, sf::Texture> m_textureMap;
	std::unordered_map<std::string, sf::Font> m_fontMap;
	std::unordered_map<std::string, std::string> m_fontPathMap;
	std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::unordered_map<std::string, std::unique_ptr<sf::Sound>> m_soundMap; // store sounds as unique_ptr

	void addTexture(const std::string& name, const std::string& path);
	void addFont(const std::string& name, const std::string& path); // for both sf::Font and std::string FontPath
	void addSound(const std::string& name, const std::string& path);

public:
    Assets();
    ~Assets();

	void loadFromFile(const std::string &path);

	[[nodiscard]] const sf::Texture& getTexture(const std::string& name) const;
	[[nodiscard]] const sf::Font& getFont(const std::string& name) const;
	[[bodiscard]] const std::string& getFontPath(const std::string& name) const;
	[[nodiscard]] sf::Sound& getSound(const std::string& name);

    [[nodiscard]] const std::unordered_map<std::string, sf::Texture>& getTextureMap() const;
	[[nodiscard]] std::unordered_map<std::string, std::unique_ptr<sf::Sound>>& getSoundMap();
};
