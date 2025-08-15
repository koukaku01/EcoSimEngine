#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Entity.hpp"


typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;


class EntityManager {
    EntityVec m_entities;       // all entities
    EntityVec m_entitiesToAdd;  // entities to add next update
    EntityMap m_entityMap;      // map from entity tag to vectors
    size_t m_totalEntities = 0; // total entities created

    // helper function to avoid repeated code
    void removeDeadEntities(EntityVec& vec) {
        // remove all dead entities from the input vector
        // this is called by the update() function
        std::erase_if(
            vec,
            [](const std::shared_ptr<Entity>& entity) {
                return !entity->isActive();
            }
        );

    // alternative solution from the internet
    // 
    //    vec.erase(std::remove_if(vec.begin(),
    //                             vec.end(),
    //                             [](const Entity &e) { return !e.isActive(); }),
    //              vec.end());
}

public:
	EntityManager() = default;

    void update() {
        // Add entities from m_entitiesToAdd to the proper location(s):
        // - add them to the vector of all entities
        // - add them to the vector inside the map, with the tag as a key
        for (const auto& entity : m_entitiesToAdd) {
            m_entities.push_back(entity);
            m_entityMap[entity->tag()].push_back(entity);
        }
        m_entitiesToAdd.clear();

        // remove dead entities from the vector of all entities
        removeDeadEntities(m_entities);

        // remove dead entities from each vector in the entity map
        // C++20 way ot iterating through [key, value] pairs in a map
        for (auto& [tag, entityVec] : m_entityMap) {
            removeDeadEntities(entityVec);
        }
    }

    std::shared_ptr<Entity> addEntity(const std::string& tag) {
		auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
		m_entitiesToAdd.push_back(entity);
    }

    EntityVec& getEntities() {
		return m_entities;
    }

	EntityVec& getEntities(const std::string& tag) {
		return m_entityMap[tag];
	}

    const EntityMap& getEntityMap() 
    {
		return m_entityMap;
    }
};