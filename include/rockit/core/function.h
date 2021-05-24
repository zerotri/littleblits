#pragma once

#include <functional>

// we're cheating a little bit here, aliasing from the STL instead of
// writing our own implementation. I'd like to change this later but it
// isn't a priority now. We only need a subset of the functionality.

namespace Rockit {
    template<typename T>
    using TFunction = std::function<T>;
}