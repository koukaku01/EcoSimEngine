#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Entity.hpp"


using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

/**
 * @brief EntityManager class for managing game entities.
 *
 * Responsibilities:
 * - Store all active entities and those pending addition.
 * - Index entities by tag for efficient retrieval.
 * - Remove inactive (destroyed) entities during updates.
 *
 * Entities are managed via std::shared_ptr to allow multiple references
 * without ownership issues. Updates should be called once per simulation tick.
 */
class EntityManager {
    EntityVec m_entities;       // all entities
    EntityVec m_entitiesToAdd;  // entities to add next update
    EntityMap m_entityMap;      // map from entity tag to vectors
    size_t m_totalEntities{ 0 }; // total entities created

    /**
     * @brief Removes all inactive entities from the given vector.
     *
     * This helper function ensures that only active entities remain in the container.
     * Uses std::erase_if (C++20) to remove elements where the entity's isActive() returns false.
     * 
     * @param vec Reference to a vector of shared pointers to Entity objects.
     *            The vector is modified directly; inactive entities are removed.
     */
    inline void removeDeadEntities(EntityVec& vec) noexcept
    {
        // Erase elements from the vector where the lambda predicate returns true.
        // Lambda returns true if the entity is inactive, causing its removal.
        std::erase_if(vec,
            [](const std::shared_ptr<Entity>& entity) {
                return !entity->isActive();
            });
    }

public:
	EntityManager() = default;

    void update() {
        // Add entities from m_entitiesToAdd to:
        // 1. The main entity vector (m_entities)
        // 2. The tag-indexed map (m_entityMap)
        for (const auto& entity : m_entitiesToAdd) {
            m_entities.push_back(entity);
            m_entityMap[entity->tag()].push_back(entity);
        }
        m_entitiesToAdd.clear();

        // remove dead entities from the vector of all entities
        removeDeadEntities(m_entities);

        // remove dead entities from each vector in the entity map
        for (auto& [tag, entityVec] : m_entityMap) {
            removeDeadEntities(entityVec);
        }
    }

    std::shared_ptr<Entity> addEntity(const std::string& tag) {
        auto entity = std::make_shared<Entity>(m_totalEntities++, tag);
        m_entitiesToAdd.push_back(entity);
        return entity;
    }

    EntityVec& getEntities() {
		return m_entities;
    }

	EntityVec& getEntities(const std::string& tag) {
		return m_entityMap[tag];
	}

	const EntityMap& getEntityMap() const noexcept
    {
		return m_entityMap;
    }
};