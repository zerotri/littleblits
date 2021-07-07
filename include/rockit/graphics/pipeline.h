#pragma once

#include <rockit/core/array.h>
#include <rockit/core/pointer.h>
#include <rockit/core/resource.h>
#include <rockit/graphics/shader.h>

namespace Rockit
{
    enum class PrimitiveType
    {
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip
    };

    class Pipeline : public Resource
    {
    public:
        using ShaderPtr = SharedPointer<Shader>;

        struct Description
        {
            const char* name = "";
            const ImmutableArray<ShaderPtr> shaders;
        };

    protected:
        const char* name = "";
        const ImmutableArray<ShaderPtr> shaders;

    public:
        Pipeline() = delete;
        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;
        Pipeline& operator=(Pipeline&&) = delete;

        Pipeline(Pipeline::Description description);
        virtual ~Pipeline();
    };
}