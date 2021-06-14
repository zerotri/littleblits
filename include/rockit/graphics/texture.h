#pragma once

#include <rockit/core/resource.h>

namespace Rockit
{
    class Texture : public Resource
    {
    public:
        enum class Format
        {
            None = 0,
            Default = 1,
            Backbuffer = 2,
            R8U,
            R32F,
            RGB8U,
            RGB8S,
            RGBA8U,
            RGBA8S,
            RGBA32F,
            SRGB8,
            SRGBA8,
        };

        enum class Filter
        {
            None,
            NearestNeighbor,
            Linear
            // todo(Wynter): Do we want to include the Mipmap filters here too?
        };

        enum class Wrap
        {
            Repeat,
            RepeatMirrored,
            Clamp,
            ClampToBorder
        };

        enum class Sampler
        {

        };

    protected:
        Format format;
        uint32_t width;
        uint32_t height;

    public:
        Texture(uint32_t width, uint32_t height, Texture::Format format)
        : width(width), height(height), format(format), Resource(false) {};
        Texture() = delete;
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = delete;
        virtual ~Texture() {};

        virtual int32_t GetWidth() const { return width; };
        virtual int32_t GetHeight() const { return height; };
        Texture::Format GetFormat() const { return format; };

    };
}