#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <cstdint>
#include <cmath>
#include <algorithm>


// Forward declaration
class Entity;


class SpatialHash {

public:
	using EntityPtr = std::shared_ptr<Entity>;
private:
	float m_cellSize;
	std::unordered_map<std::uint64_t, std::vector<EntityPtr>> m_grid;

	static int64_t keyFor(int gx, int gy) {
		// pack two 32-bit ints into 64-bit key
		return (static_cast<int64_t>(gx) << 32) ^ (static_cast<int64_t>(gy) & 0xffffffffLL);
	}

public:

	explicit SpatialHash(float cellSize = 100.0f)
		: m_cellSize(cellSize) {
	}

	void clear() {
		m_grid.clear();
	}

	void insert(const EntityPtr& e, float x, float y) {
		int gx = static_cast<int>(std::floor(x / m_cellSize));
		int gy = static_cast<int>(std::floor(y / m_cellSize));
		m_grid[keyFor(gx, gy)].push_back(e);
	}

	// Query neighbos within radius (return unique set)
	std::vector<EntityPtr> query(float x, float y, float radius) const {
		std::vector<EntityPtr> result;
		int gx0 = static_cast<int>(std::floor((x - radius) / m_cellSize));
		int gy0 = static_cast<int>(std::floor((y - radius) / m_cellSize));
		int gx1 = static_cast<int>(std::floor((x + radius) / m_cellSize));
		int gy1 = static_cast<int>(std::floor((y + radius) / m_cellSize));

		float r2 = radius * radius;
		result.reserve(64); // reserve space for 64 entities

		for (int gx = gx0; gx <= gx1; ++gx) {
			for (int gy = gy0; gy <= gy1; ++gy) {
				int64_t key = keyFor(gx, gy);
				auto it = m_grid.find(key);
				if (it == m_grid.end()) continue;
				for (const auto& e : it->second) {
					if (!e) continue;
					// cheap distance check using component later (caller may re-filter)
					result.push_back(e);
				}
			}
		}

		// Remove duplicates (same entity can be in multiple buckets if you inserted multiple times)
		std::sort(result.begin(), result.end());
		result.erase(std::unique(result.begin(), result.end()), result.end());
		return result;
	}

	float cellSize() const {
		return m_cellSize;
	}
};