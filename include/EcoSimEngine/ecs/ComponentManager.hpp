#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>

class ComponentManager {
	struct IStore { virtual ~IStore() = default; };
	template<typename T> struct Store : IStore {
		std::unordered_map<size_t, T> data;
	};

	std::unordered_map<std::type_index, std::unique_ptr<IStore>> stores;

	template<typename T> Store<T>& ensure() {
		auto ti = std::type_index(typeid(T));
		auto it = stores.find(ti);
		if (it == stores.end()) {
			stores[ti] = std::make_unique<Store<T>>();
		}
		return *static_cast<Store<T>*>(stores[ti].get());
	}

public:
	template<typename T, typename... Args>
	T& add(std::size_t id, Args&&... args) {
		auto& store = ensure<T>();
		auto [it, _] = store.data.emplace(id, T(std::forward<Args>(args)...));
		return it->second;
	}

	template<typename T>
	bool has(std::size_t id) const {
		auto ti = std::type_index(typeid(T));
		auto it = stores.find(ti);
		if (it == stores.end()) return false;
		auto* s = static_cast<const Store<T>*>(it->second.get());
		return s->data.find(id) != s->data.end();
	}

	template<typename T> T& get(std::size_t id) {
		auto& s = ensure<T>();
		return s.data.at(id);
	}

	template<typename T> void remove(std::size_t id) {
		auto& s = ensure<T>();
		s.data.erase(id);
	}

	void clear() { stores.clear(); }
};