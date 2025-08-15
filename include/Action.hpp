#pragma once

#include <string>
#include <sstream>

#include "Vec2.hpp"


class Action {
    std::string m_name;
    std::string m_type;
    Vec2f m_pos = Vec2f(0.0f, 0.0f);

public:
    Action() = default;

    Action(std::string name, std::string type)
        : m_name(std::move(name)), m_type(std::move(type)) {
    };

    Action(std::string name, Vec2f pos)
        : m_name(std::move(name)), m_pos(pos) {
    };

    Action(std::string name, std::string type, Vec2f pos)
        : m_name(std::move(name)), m_type(std::move(type)), m_pos(pos) {
    };

    [[nodiscard]] const std::string& name() const
    {
        return m_name;
    };

    [[nodiscard]] const std::string& type() const
    {
        return m_type;
    };

    [[nodiscard]] const Vec2f& pos() const
    {
        return m_pos;
    };

    [[nodiscard]] std::string toString() const
    {
        std::stringstream ss;
        ss << name() << " " << type() << " "
            << static_cast<int>(pos().x) << " "
            << static_cast<int>(pos().y);
        return ss.str();
    };

};