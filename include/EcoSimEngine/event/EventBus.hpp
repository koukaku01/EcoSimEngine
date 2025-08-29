#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <utility>

/// header-only EventBus
/// - stores subscribers as unique_ptr<BaseWrapper>
/// - avoids copying unique_ptrs when publishing by copying callable objects
class EventBus {
    // base type stored in container (non-templated)
    struct BaseWrapper {
        size_t m_id;
        explicit BaseWrapper(size_t id) : m_id(id) {}
        virtual ~BaseWrapper() = default;
    };

    // per-event-type wrapper storing the typed callback
    template <typename Event>
    struct Wrapper : BaseWrapper {
        std::function<void(const Event&)> fn;
        Wrapper(size_t id, std::function<void(const Event&)> f)
            : BaseWrapper(id), fn(std::move(f)) {
        }
    };

    // mapping: event type -> list of subscriptions
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<BaseWrapper>>> m_listeners;
    size_t m_nextId{ 0 };

public:
    struct Subscription {
        std::type_index m_type;
        size_t m_id;
    };

    EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    /// Subscribe: returns token you can later pass to unsubscribe()
    template <typename Event>
    Subscription subscribe(std::function<void(const Event&)> listener) {
        auto& vec = m_listeners[std::type_index(typeid(Event))];
        size_t id = m_nextId++;
        vec.push_back(std::make_unique<Wrapper<Event>>(id, std::move(listener)));
        return { std::type_index(typeid(Event)), id };
    }

    /// Unsubscribe using token
    void unsubscribe(const Subscription& sub) {
        auto it = m_listeners.find(sub.m_type);
        if (it == m_listeners.end()) return;

        auto& vec = it->second;
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [&](auto& ptr) { return ptr->m_id == sub.m_id; }),
            vec.end());
    }

    /// Publish: safe against subscribers adding/removing during iteration.
    template <typename Event>
    void publish(const Event& event) {
        auto it = m_listeners.find(std::type_index(typeid(Event)));
        if (it == m_listeners.end()) return;

        // Build a list of callables (copyable) to avoid copying unique_ptrs.
        std::vector<std::function<void(const Event&)>> callbacks;
        callbacks.reserve(it->second.size());

        for (auto& uptr : it->second) {
            // cast to concrete wrapper and copy the stored std::function
            auto* w = static_cast<Wrapper<Event>*>(uptr.get());
            callbacks.push_back(w->fn); // copies the std::function
        }

        // invoke callbacks from the copied list
        for (auto& cb : callbacks) {
            if (cb) cb(event);
        }
    }
};
