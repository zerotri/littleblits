#pragma once

#include <cstdint>

namespace Rockit
{
    class ReferenceCounter
    {
    private:
        uint32_t ReferenceCount = 0;

    public:
        uint32_t Increment()
        {
            return ++ReferenceCount;
        }

        uint32_t Decrement()
        {
            return --ReferenceCount;
        }

        [[nodiscard]] uint32_t GetCount() const
        {
            return ReferenceCount;
        }
    };

    class ReferenceCounterControlledBase : public ReferenceCounter
    {
    private:
    public:
        virtual ~ReferenceCounterControlledBase();

        virtual void Delete() = 0;
    };
}