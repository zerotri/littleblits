#include <rockit/graphics/shader.h>

namespace Rockit {
    Shader::Shader(Shader::Description description)
    : Resource(true), name(description.name), source(description.source), type(description.type)
    {

    }
    Shader::~Shader()
    {

    }
}