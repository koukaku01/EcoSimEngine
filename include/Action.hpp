#pragma once

#include <string>
#include <sstream>

#include "Vec2.hpp"


class Action {
    std::string m_name;
    std::string m_type;
    Vec2f m_pos{}; // default to (0,0)

public:
    Action() = default;

    /// Constructs an Action with a name, type, and position.
    Action(std::string name, std::string type, Vec2f pos)
        : m_name(std::move(name)), m_type(std::move(type)), m_pos(pos) {
    }

    /// Constructs an Action with name and type, position defaults to (0,0).
    Action(std::string name, std::string type)
        : Action(std::move(name), std::move(type), Vec2f{}) {
    }

    /// Constructs an Action with name and position, type defaults to "".
    Action(std::string name, Vec2f pos)
        : Action(std::move(name), "", pos) {
    }

    [[nodiscard]] const std::string& name() const  noexcept { return m_name; }
    [[nodiscard]] const std::string& type() const noexcept { return m_type; }
    [[nodiscard]] const Vec2f& pos() const noexcept { return m_pos; }

    [[nodiscard]] std::string toString() const
    {
        std::stringstream ss;
        ss << name() << " " << type() << " "
            << static_cast<int>(pos().x) << " "
            << static_cast<int>(pos().y);
        return ss.str();
    }
};