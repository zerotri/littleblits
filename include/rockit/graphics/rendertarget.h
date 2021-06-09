#pragma once

#include <rockit/core/resource.h>
#include <rockit/graphics/texture.h>

namespace Rockit
{
    class RenderTarget : public Resource
    {
    protected:
        SharedPointer<Texture> BaseTexture;

    public:
        enum class ClearMask
        {
            None = 0,
            Color = 1,
            Depth = 2,
            Stencil = 4,
            All = Color | Depth | Stencil
        };


        RenderTarget() = delete;
        RenderTarget(const RenderTarget&) = delete;
        RenderTarget& operator=(const RenderTarget&) = delete;
        RenderTarget& operator=(RenderTarget&&) = delete;
        virtual ~RenderTarget() {};

        virtual int32_t GetWidth() const = 0;
        virtual int32_t GetHeight() const = 0;
        virtual void Clear() = 0;

        SharedPointer<Texture> GetTexture() { return BaseTexture; };

    };
}