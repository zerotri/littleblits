#pragma once

namespace Rockit
{
    struct Vec2
    {
        float x;
        float y;

        Vec2() = default;

        Vec2 operator+(const Vec2& other) const;
        Vec2 operator-(const Vec2& other) const;
        Vec2 operator*(const Vec2& other) const;
        Vec2 operator/(const Vec2& other) const;
        Vec2 operator*(float other) const;
        Vec2 operator/(float other) const;

        Vec2& operator +=(const Vec2& other);
        Vec2& operator -=(const Vec2& other);
        Vec2& operator *=(const Vec2& other);
        Vec2& operator /=(const Vec2& other);
        Vec2& operator *=(float other);
        Vec2& operator /=(float other);

        bool operator ==(const Vec2& other) const;

        Vec2 Absolute() const;
        Vec2 Normalized() const;
        float Length() const;
        float Dot(const Vec2& other) const;
        float Angle() const;

        static Vec2 Up;
        static Vec2 Down;
        static Vec2 Left;
        static Vec2 Right;
        static Vec2 Zero;
        static Vec2 One;
    };
};