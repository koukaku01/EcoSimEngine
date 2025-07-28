#pragma once

#include <cmath>
#include <algorithm>
#include <stdexcept>

///; #include <SFML/System/Vector2.hpp>

template <typename T>
class Vec2
{
public:
    T x{0}, y{0};

    constexpr Vec2() = default;

    constexpr Vec2(T x, T y)
        : x(x), y(y) {}

    // constructor from a single value, x and y will be the same
    // explicit usage to avoid accidental conversions
    constexpr explicit Vec2(T value)
        : x(value), y(value) {}

    // allow automatic conversion to sf::Vector2<T>
    // this lets us pass Vec2 to functions that expect sf::Vector2<T>
    constexpr operator sf::Vector2<T>() const noexcept
    {
        return sf::Vector2<T>(x, y);
    }

    // unary negation
    constexpr Vec2 operator-() const noexcept
    {
        return Vec2(-x, -y);
    }

    // Comparison operators

    constexpr bool operator==(const Vec2 &other) const
    {
        return x == other.x && y == other.y;
    }
    constexpr bool operator!=(const Vec2 &other) const
    {
        return !(*this == other);
    }

    // Arithmetic operations

    constexpr Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }
    constexpr Vec2 operator-(const Vec2 &other) const
    {
        return Vec2(x - other.x, y - other.y);
    }
    constexpr Vec2 operator*(T scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }
    Vec2 operator/(T scalar) const
    {
        if (scalar == 0)
        {
            throw std::runtime_error("Division by zero in Vec2 division");
        }
        return Vec2(x / scalar, y / scalar);
    }

    // Compound assignment operators

    constexpr Vec2 &operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Vec2 &operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    constexpr Vec2 &operator*=(T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vec2 &operator/=(T scalar)
    {
        if (scalar == 0)
        {
            throw std::runtime_error("Division by zero in Vec2 division");
        }
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Length and normalization

    double distSq(const Vec2 &other) const
    {
        double dx = static_cast<double>(x) - static_cast<double>(other.x);
        double dy = static_cast<double>(y) - static_cast<double>(other.y);
        return dx * dx + dy * dy;
    }

    double dist(const Vec2 &other) const
    {
        return std::sqrt(distSq(other));
    }

    double length() const
    {
        return std::sqrt(static_cast<double>(x * x + y * y));
    }

    Vec2 normalized() const
    {
        double len = length();
        if (len == 0)
        {
            throw std::runtime_error("Cannot normalize a zero-length vector");
        }
        return Vec2(x / len, y / len);
        // Note: Fast Inverse Square Root not implemented here due to precision needs.
    }

    Vec2 abs() const
    {
        return Vec2(std::abs(x), std::abs(y));
    }

    // Dot product
    double dot(const Vec2 &other) const
    {
        return static_cast<double>(x) * other.x + static_cast<double>(y) * other.y;
    }

    // 2d scalar cross product
    double cross(const Vec2 &other) const
    {
        return static_cast<double>(x) * other.y - static_cast<double>(y) * other.x;
    }

    // Angle between two vectors in radians
    double angleBetween(const Vec2 &other) const
    {
        double dotPod = dot(other);
        double lengths = length() * other.length();
        if (lengths == 0)
            throw std::runtime_error("Zero length vector in angleBetween calculation");

        // Clamp the value to the range [-1, 1] to avoid NaN due to floating point precision issues
        double cosTheta = std::clamp(dotPod / lengths, -1.0, 1.0);
        return std::acos(cosTheta);
    }

    // Rotation by an angle in radians around the origin
    Vec2 rotated(double radians) const noexcept
    {
        double cosTheta = std::cos(radians);
        double sinTheta = std::sin(radians);
        return Vec2(
            static_cast<T>(x * cosTheta - y * sinTheta),
            static_cast<T>(x * sinTheta + y * cosTheta));
    }

    // Rotation by an angle in radians around a specific point
    inline Vec2 rotatedAround(double radians, const Vec2 &point) const noexcept
    {
        // translate -> rotate -> translate back
        return ((*this - point).rotated(radians) + point);
    }

    // Static utility functions

    // Create from angle in radians
    static Vec2 fromAngle(double radians) noexcept
    {
        return Vec2(
            static_cast<T>(std::cos(radians)),
            static_cast<T>(std::sin(radians)));
    }

    // Create from angle in radians with a specific magnitude
    static Vec2 fromAngle(double radians, T magnitude) noexcept
    {
        return Vec2(
            static_cast<T>(std::cos(radians) * magnitude),
            static_cast<T>(std::sin(radians) * magnitude));
    }


};

// Left side arithmetic operations
template <typename T>
inline Vec2<T> operator*(T scalar, const Vec2<T> &vec) noexcept
{
    return Vec2<T>(vec.x * scalar, vec.y * scalar);
}

// Type aliases for convenience

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;