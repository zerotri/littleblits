#pragma once

#include <rockit/core/resource.h>
#include <rockit/graphics/rendertarget.h>
#include <rockit/graphics/shader.h>
#include <rockit/graphics/texture.h>

namespace Rockit
{
    class Renderer
    {
    public:
        enum Backend
        {
            None = 0,
            OpenGL = 1,
            Vulkan = 2
        };

    protected:
        Backend backendApi = None;

    public:
        Renderer() = default;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&&) = delete;
        virtual ~Renderer() {};

        virtual SharedPointer<Texture> CreateTexture(uint32_t width, uint32_t height, Texture::Format format) = 0;
        virtual SharedPointer<RenderTarget> CreateRenderTarget(uint32_t width, uint32_t height) = 0;
        virtual SharedPointer<Shader> CreateShader() = 0;

        Backend GetBackendApi() { return backendApi; };

    };
}