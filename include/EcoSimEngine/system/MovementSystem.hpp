#pragma once

#include "EcoSimEngine/system/System.hpp"
#include "EcoSimEngine/ecs/ComponentIndices.hpp"
#include "EcoSimEngine/ecs/Entity.hpp"
#include "EcoSimEngine/ecs/EntityManager.hpp"


class MovementSystem : public System {
public:
    // EntityManager must implement getEntityById(size_t)
    void update(EntityManager& em, float dt)
    {
        if (dt <= 0.0f) return; // avoid division by zero

        for (EntityId id : mEntities) {
            auto e = em.getEntityById(id);
            if (!e || !e->isActive()) continue;
            if (!em.hasComponent<CTransform>(e)) continue; // has position and velocity

            auto& t = em.getComponent<CTransform>(e);

            // clamp speed using behavior if present
            float maxSpeed = 10.0f;
            if (em.hasComponent<CBehavior>(e)) maxSpeed = em.getComponent<CBehavior>(e).maxSpeed;

            float sp = t.velocity.length();
            if (sp > maxSpeed) t.velocity = t.velocity * (maxSpeed / sp);

            // integrate
            t.pos += t.velocity * dt;

            // damping
            t.velocity = t.velocity * 0.98f;
        }
    }
};
