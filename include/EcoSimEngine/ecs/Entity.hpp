#pragma once

#include <string>
#include <tuple>

#include "EcoSimEngine/ecs/Components.hpp"
#include "EcoSimEngine/ecs/ComponentIndices.hpp"
#include "EcoSimEngine/ecs/ComponentType.hpp"

class EntityManager;

using ComponentTuple = std::tuple<
	CTransform,
	CSpecies,
	CHealth,
	CEnergy,
	CReproductive,
	CBehavior
>;

class Entity {
    friend class EntityManager;

    bool m_active{ true };
    const size_t m_id{ 0 };
    const std::string m_tag{ "default" };
    ComponentTuple m_components;
	Signature m_signature; // bitset to track which components are present

    // constructor is private, so we can never create entities
    //   outside the EntityManager which had friend access
    Entity(size_t id, std::string tag)
        : m_id{ id }, m_tag{ std::move(tag) } {
	}

public:
    void destroy()
    {
        m_active = false;
    }

    [[nodiscard]] size_t id() const noexcept
    {
		return m_id;
    }

    [[nodiscard]] bool isActive() const noexcept
    {
		return m_active;
    }

    [[nodiscard]] const std::string& tag() const noexcept
    {
		return m_tag;
    }

    [[nodiscard]] const Signature& signature() const noexcept {
		return m_signature;
	}

    template<class T>
    bool has() const noexcept {
        return get<T>().has;
    }

    template<class T, typename... TArgs>
    T& add(TArgs &&... mArgs) {
        auto& component = get<T>();
        component = T(std::forward<TArgs>(mArgs)...);
        component.has = true;
		m_signature.set(ComponentType<T>::index, true); // mark component as present in signature (set bit ON)
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
        auto& comp = get<T>();
        comp = T();        // reset to default
        comp.has = false;  // explicitly mark as removed
		m_signature.set(ComponentType<T>::index, false); // mark component as absent in signature (set bit OFF)
    }
};
