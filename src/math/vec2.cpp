#include <rockit/math/vec2.h>

#include <cmath>

namespace Rockit {
    Vec2 Vec2::operator+(const Vec2& other) const
    {
        return Vec2 { x + other.x, y + other.y };
    }
    Vec2 Vec2::operator-(const Vec2& other) const
    {
        return Vec2 { x - other.x, y - other.y };
    }
    Vec2 Vec2::operator*(const Vec2& other) const
    {
        return Vec2 { x * other.x, y * other.y };
    }
    Vec2 Vec2::operator/(const Vec2& other) const
    {
        return Vec2 { x / other.x, y / other.y };
    }
    Vec2 Vec2::operator*(float other) const
    {
        return Vec2 { x * other, y * other };
    }
    Vec2 Vec2::operator/(float other) const
    {
        return Vec2 { x / other, y / other };
    }
    Vec2& Vec2::operator +=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2& Vec2::operator -=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2& Vec2::operator *=(const Vec2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vec2& Vec2::operator /=(const Vec2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    Vec2& Vec2::operator *=(float other)
    {
        x *= other;
        y *= other;
        return *this;
    }
    Vec2& Vec2::operator /=(float other)
    {
        x /= other;
        y /= other;
        return *this;
    }

    bool Vec2::operator ==(const Vec2& other) const
    {
        return ((x == other.x) && (y == other.y));
    }

    Vec2 Vec2::Absolute() const
    {
        return Vec2 { fabsf(x), fabsf(y) };
    }
    Vec2 Vec2::Normalized() const
    {
        if(*this == Vec2::Zero)
            return Vec2::Zero;
        
        float length = Length();
        return Vec2 { x / length, y / length };
        
    }
    float Vec2::Length() const
    {
        return sqrtf(LengthSq());
    }
    float Vec2::LengthSq() const
    {
        return x * x + y * y;
    }
    float Vec2::Dot(const Vec2& other) const
    {
        return (x * other.x + y * other.y);
    }
    float Vec2::Angle() const
    {
        return atan2f(y, x);
    }
    float Vec2::Distance(const Vec2& other) const
    {
        return sqrtf(DistanceSq(other));
    }
    float Vec2::DistanceSq(const Vec2& other) const
    {
        float a = other.x - x;
        float b = other.y - y;
        return a * a + b * b;
    }

    Vec2 Vec2::Up       = { 0.0f,  1.0f};
    Vec2 Vec2::Down     = { 0.0f, -1.0f};
    Vec2 Vec2::Left     = {-1.0f,  0.0f};
    Vec2 Vec2::Right    = { 1.0f,  0.0f};
    Vec2 Vec2::Zero     = { 0.0f,  0.0f};
    Vec2 Vec2::One      = { 1.0f,  1.0f};
}