#pragma once

#include <SFML/Graphics/Color.hpp>

#include <cmath>


sf::Color hslToRgb(float h, float s, float l) {
    float c = (1 - std::fabs(2 * l - 1)) * s;
    float x = c * (1 - std::fabs(fmod(h / 60.0f, 2) - 1));
    float m = l - c / 2;
    float r = 0, g = 0, b = 0;

    if (h < 60) { r = c; g = x; }
    else if (h < 120) { r = x; g = c; }
    else if (h < 180) { g = c; b = x; }
    else if (h < 240) { g = x; b = c; }
    else if (h < 300) { r = x; b = c; }
    else { r = c; b = x; }

    return sf::Color(
        static_cast<std::uint8_t>((r + m) * 255),
        static_cast<std::uint8_t>((g + m) * 255),
        static_cast<std::uint8_t>((b + m) * 255)
    );
}