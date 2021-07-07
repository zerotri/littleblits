#include <rockit/graphics/pipeline.h>

namespace Rockit {
    Pipeline::Pipeline(Pipeline::Description description)
            : Resource(true), name(description.name), shaders(description.shaders)
    {

    }
    Pipeline::~Pipeline()
    {

    }
}