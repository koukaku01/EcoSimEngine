#pragma once

#include <string>
#include <tuple>

#include "Components.hpp"

class EntityManager;

typedef std::tuple<
	CTransform,
	CSpecies,
	CHealth,
	CReproductive
> ComponentTuple;

class Entity {
    friend class EntityManager;

    bool m_active = true;
    const size_t m_id = 0;
    const std::string m_tag = "default";
    ComponentTuple m_components;

    // constructor is private, so we can never create entities
    // outside the EntityManager which had friend access
    Entity(size_t id, std::string tag)
		: m_id(id), m_tag(std::move(tag)){
	}

public:
    void destroy()
    {
        m_active = false;
    }

    [[nodiscard]] size_t id() const
    {
		return m_id;
    }

    [[nodiscard]] bool isActive() const
    {
		return m_active;
    }

    [[nodiscard]] const std::string& tag() const
    {
		return m_tag;
    }

    template<class T>
    bool has() const {
        return get<T>().has;
    }

    template<class T, typename... TArgs>
    T& add(TArgs &&... mArgs) {
        auto& component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
        return component;
    }

    template<class T>
    T& get() {
        return std::get<T>(m_components);
    }

    template<class T>
    const T& get() const {
        return std::get<T>(m_components);
    }

    template<class T>
    void remove() {
        get<T>() = T();
    }
};