#pragma once

#include "Vec2.hpp"

enum class Sex { Male, Female };
enum class BehaviorState { Idle, Wander, SeekFood, Flee, Reproduce };

class Component
{
public:
    bool exists{ false };
};

class CTransform : public Component
{
public:
    Vec2f pos{};
    Vec2f velocity{};
    Vec2f acceleration{};
    float scale{ 1.0f };

    CTransform() = default;

    CTransform(const Vec2f& p, const Vec2f& v, float s)
        : pos(p), velocity(v), scale(s) { }
    CTransform(const Vec2f &pos)
        : CTransform(pos, {}, scale) { }
};

class CSpecies : public Component
{
public:
    std::string speciesName{"Unknown"};
    int age{ 0 };

    bool canSwim{};
    bool canFly{};

    CSpecies() = default;
    CSpecies(const std::string &speciesName,int age)
        : speciesName(speciesName), age(age) {}
};

class CHealth : public Component
{
public:
    float health{ 100.0f };
    float maxHealth{ 100.0f };

	CHealth() = default;
    explicit CHealth(float max) : health(max), maxHealth(max) {}
};

class CEnergy : public Component
{
public:
    float current{ 100.0f };       // current energy/hunger level
    float max{ 100.0f };           // maximum energy
    float consumptionRate{ 1.0f }; // per second or tick

    CEnergy() = default;
};


class CReproductive : public Component
{
public:
    Sex sex{ Sex::Male };

    bool canReproduce{ false };
    bool isPregnant{ false };

    float reproductionCooldown{ 0.0f };     // time until next reproduction
    float pregnancyDuration{ 0.0f };        // time spent pregnant
    float timePregnant{ 0.0f };             // elapsed pregnancy time

    float reproductionCooldownMax{ 10.0f }; // max cooldown
    float pregnancyDurationMax{ 10.0f };    // max pregnancy duration

    CReproductive() = default;
};

class CBehavior : public Component {
public:
    BehaviorState current{ BehaviorState::Idle };
    float stateTimer{ 0.0f }; // how long to stay in current state

    CBehavior() = default;
};
