#pragma once

#include <set>
#include <cstddef>

using EntityId = std::size_t;

class System {
public:
	std::set<EntityId> mEntities; // unique entity IDs this system acts on
	virtual ~System() = default;
};