#pragma once

#include <rockit/core/resource.h>

namespace Rockit
{
    class Shader : public Resource
    {
    public:
        Shader() = delete;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;
        virtual ~Shader() {};
    };
}