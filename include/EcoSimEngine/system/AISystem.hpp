#pragma once

#include "EcoSimEngine/system/System.hpp"
#include "EcoSimEngine/ecs/Entity.hpp"
#include "EcoSimEngine/ecs/EntityManager.hpp"
#include "EcoSimEngine/math/Vec2.hpp"
#include "EcoSimEngine/utils/Utils.hpp"


class AISystem : public System {
public:
    void update(EntityManager& em, ComponentManager& cm, float dt)
    {
        for (EntityId id : mEntities)
        {
            auto e = em.getEntityById(id);
            if (!e || !e->isActive()) continue;
            if (!cm.has<CBehavior>(id) || !cm.has<CTransform>(id)) continue;
            
            auto& behavior = cm.get<CBehavior>(id);
            auto& t = cm.get<CTransform>(id);

            behavior.stateTimer -= dt;
            if (behavior.stateTimer <= 0.0f) {
                behavior.stateTimer = randomFloat(1.0f, 5.0f);
                behavior.current = BehaviorState::Wander;
            }

            if (behavior.current == BehaviorState::Wander && t.velocity.length() < 0.1f) {
                Vec2f dir = randomUnitVector();
                t.velocity = dir * behavior.movementSpeed;
            }
        }
    }
};