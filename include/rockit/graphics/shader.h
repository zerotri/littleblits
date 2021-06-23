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

        struct Description
        {
            Type type = Type::Vertex;
            const char* name = "";
            const char* source = "";
        };

        struct Error
        {
            bool isValid = false;
            const char* message = "";
        };

    protected:
        const char* name = "";
        const char* source = "";

        Type type;

    public:
        Shader() = delete;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;

        Shader(Shader::Description description);
        virtual ~Shader();

        virtual Error GetLastError() { return Error{}; };
    };
}