#pragma once

#include "Vec2.hpp"

class Component
{
public:
    bool exists = false;
};

class CTransform : public Component
{
public:
    Vec2f pos = {0.0, 0.0};
    Vec2f velocity = {0.0, 0.0};
    float scale = 2;

    CTransform() = default;
    CTransform(const Vec2f &pos)
        : pos(pos) {}
    CTransform(const Vec2f &pos, const Vec2f &v, const float &scale)
        : pos(pos), velocity(v), scale(scale) {}
};

class CSpecies : public Component
{
public:
    std::string speciesName = "Unknown";
    int age = 0;

    bool can_swim = false;
    bool can_fly = false;

    CSpecies() = default;
    CSpecies(const std::string &speciesName,int age)
        : speciesName(speciesName), age(age) {}
};

class CHealth : public Component
{
public:
    float health = 100.0f;
    float maxHealth = 100.0f;
};

class CReproductive : public Component
{
public:
    int sex = 0; // 0 = Male, 1 = Female
    bool canReproduce = false;
    bool isPregnant = false;

    float reproductionCooldown = 0.0f;     // Time until next reproduction can occur
    float pregnancyDuration = 0.0f;        // Duration of pregnancy in seconds
    float timePregnant = 0.0f;             // Time already spent pregnant
    float reproductionCooldownMax = 10.0f; // Max time until next reproduction can occur
    float pregnancyDurationMax = 10.0f;    // Max duration of pregnancy in seconds
    CReproductive() = default;
    CReproductive(const int &sex, const float &reproductionCooldownMax, const float &pregnancyDurationMax, const bool &canReproduce, const bool &isPregnant)
        : sex(sex), reproductionCooldownMax(reproductionCooldownMax), pregnancyDurationMax(pregnancyDurationMax), canReproduce(canReproduce), isPregnant(isPregnant) {}
    CReproductive(const int &sex, const float &reproductionCooldownMax, const float &pregnancyDurationMax, const bool &canReproduce, const bool &isPregnant, const float &reproductionCooldown, const float &pregnancyDuration, const float &timePregnant)
        : sex(sex), reproductionCooldownMax(reproductionCooldownMax), pregnancyDurationMax(pregnancyDurationMax), canReproduce(canReproduce), isPregnant(isPregnant), reproductionCooldown(reproductionCooldown), pregnancyDuration(pregnancyDuration), timePregnant(timePregnant) {}
};
