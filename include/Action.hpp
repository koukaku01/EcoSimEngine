#pragma once

#include <string>
#include <format>

#include "Vec2.hpp"

enum class ActionName {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
    BACK,
	LEFT_CLICK,
	MIDDLE_CLICK,
	RIGHT_CLICK,
	MOUSE_MOVE,
    NONE
};

enum class ActionType {
	START,
	END,
    NONE
};

class Action {
    ActionName m_name;
    ActionType m_type;
    Vec2f m_pos{}; // default to (0,0)

public:
    Action() = default;

    /// Constructs an Action with a name, type, and position.
    Action(ActionName name, ActionType type, Vec2f pos)
        : m_name{ name }, m_type{ type }, m_pos{ pos } {
    }

    /// Constructs an Action with name and type, position defaults to (0,0).
    Action(ActionName name, ActionType type)
        : Action{ name, type, Vec2f{} } {
    }

    /// Constructs an Action with name and position, type defaults to NONE.
    Action(ActionName name, Vec2f pos)
        : Action{ name, ActionType::NONE, pos } {
    }

    [[nodiscard]] const ActionName name() const  noexcept { return m_name; }
    [[nodiscard]] const ActionType type() const noexcept { return m_type; }
    [[nodiscard]] const Vec2f& pos() const noexcept { return m_pos; }

    [[nodiscard]] std::string toString() const noexcept {
        static constexpr const char* NameStrings[] = {
            "UP", "DOWN", "LEFT", "RIGHT", "SELECT", "BACK", "NONE", 
            "LEFT_CLICK","MIDDLE_CLICK","RIGHT_CLICK","MOUSE_MOVE",
        };
        static constexpr const char* TypeStrings[] = {
            "START", "END", "NONE"
        };

        return std::format("{} {} {} {}",
            NameStrings[static_cast<int>(m_name)],
            TypeStrings[static_cast<int>(m_type)],
            static_cast<int>(m_pos.x),
            static_cast<int>(m_pos.y));
    }
};