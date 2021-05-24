#pragma once
#include <cstddef>
#include <assert.h>

namespace Rockit
{
    // Todo(Wynter): Array should be changed to represent an immutable array type
    // Todo(Wynter): Design + Implement MutableArray
    template<typename DataType>
    class Array
    {
    private:
        DataType *Data = nullptr;

        // Size of array in memory
        size_t ArraySize = 0;

    public:
        Array()
        {
        }

        bool Allocate(size_t Size)
        {
            size_t BufferSizeInBytes = Size * sizeof(DataType);
            bool bSuccess = false;
            if (!Data && BufferSizeInBytes > 0)
            {
                Data = static_cast<DataType *>(malloc(BufferSizeInBytes));
                if (Data) bSuccess = true;
                ArraySize = Size;
            }
            return bSuccess;
        }

        bool Resize(size_t NewSize)
        {
            size_t BufferSizeInBytes = NewSize * sizeof(DataType);
            bool bSuccess = false;
            if (!Data && BufferSizeInBytes > 0)
            {
                Data = static_cast<DataType *>(realloc(Data, BufferSizeInBytes));
                if (Data) bSuccess = true;
                ArraySize = NewSize;
            }
            return bSuccess;
        }

        DataType &operator[](size_t Index)
        {
            assert(Index < ArraySize);
            return Data[Index];
        }

        const DataType &operator[](uintptr_t Index) const
        {
            assert(Index < ArraySize);
            return Data[Index];
        }
    };
}