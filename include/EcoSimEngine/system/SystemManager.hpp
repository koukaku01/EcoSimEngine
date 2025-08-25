// File: include/EcoSimEngine/system/SystemManager.hpp
#pragma once

#include "EcoSimEngine/system/System.hpp"
#include "EcoSimEngine/ecs/ComponentIndices.hpp"

#include <typeindex>
#include <unordered_map>
#include <memory>
#include <cassert>

class SystemManager {
    std::unordered_map<std::type_index, Signature> m_signatures{};
    std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems{};
public:
    // Register a system and return a shared_ptr to it
    template<typename T, typename... Args>
    std::shared_ptr<T> RegisterSystem(Args&&... args) {
        std::type_index ti(typeid(T));
        assert(m_systems.find(ti) == m_systems.end() && "Registering system more than once.");
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        m_systems.emplace(ti, system);
        return std::static_pointer_cast<T>(system);
    }

    // Set the signature (component bitset) for a system type
    template<typename T>
    void SetSignature(const Signature& signature) {
        std::type_index ti(typeid(T));
        assert(m_systems.find(ti) != m_systems.end() && "SetSignature on unregistered system.");
        m_signatures[ti] = signature;
    }

    // Remove entity from all systems when destroyed
    void EntityDestroyed(EntityId id) {
        for (auto& [_, system] : m_systems) {
            if (system) system->mEntities.erase(id);
        }
    }

    // Called when an entity's signature changed (add/remove component)
    void EntitySignatureChanged(EntityId id, const Signature& entitySignature) {
        for (auto& [type, system] : m_systems) {
            const Signature& sSig = m_signatures[type];
            if ((entitySignature & sSig) == sSig) system->mEntities.insert(id);
            else system->mEntities.erase(id);
        }
    }

    // Get the registered system of type T (or nullptr if none)
    template<typename T>
    std::shared_ptr<T> GetSystem() {
        std::type_index ti(typeid(T));
        auto it = m_systems.find(ti);
        if (it == m_systems.end()) return nullptr;
        return std::static_pointer_cast<T>(it->second);
    }
};
