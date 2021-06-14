#pragma once

#include <rockit/core/resource.h>

namespace Rockit
{
    class Uniform : public Resource
    {
    public:
        Uniform() = delete;
        Uniform(const Uniform&) = delete;
        Uniform& operator=(const Uniform&) = delete;
        Uniform& operator=(Uniform&&) = delete;
        virtual ~Uniform() {};
    };

    class Shader : public Resource
    {
    public:
        enum class Type
        {
            Vertex,
            Geometry,
            // todo(Wynter): Someday we can add Tesselation/Evaluation shaders
            Fragment,
            Compute
        };
    public:
        Shader() = delete;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;
        virtual ~Shader() {};
    };
}