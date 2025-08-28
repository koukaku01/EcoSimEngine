#pragma once

#include "EcoSimEngine/component/ComponentIndices.hpp"
#include "EcoSimEngine/component/Components.hpp"

template<typename T> struct ComponentType; // primary template left undefined

// Specializations for each component type
template<> struct ComponentType<CTransform> { static constexpr std::size_t index = COMP_INDEX_CTransform; };
template<> struct ComponentType<CSpecies> { static constexpr std::size_t index = COMP_INDEX_CSpecies; };
template<> struct ComponentType<CHealth> { static constexpr std::size_t index = COMP_INDEX_CHealth; };
template<> struct ComponentType<CEnergy> { static constexpr std::size_t index = COMP_INDEX_CEnergy; };
template<> struct ComponentType<CReproductive> { static constexpr std::size_t index = COMP_INDEX_CReproductive; };
template<> struct ComponentType<CBehavior> { static constexpr std::size_t index = COMP_INDEX_CBehavior; };