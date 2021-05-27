#pragma once
#include <cstddef>
#include <assert.h>

namespace Rockit
{
    template<typename DataType>
    class MutableArray;

    template<typename DataType>
    class ImmutableArray;

    // Todo(Wynter): Array should be changed to represent an immutable array type
    // Todo(Wynter): Design + Implement MutableArray
    template<typename DataType>
    class MutableArray
    {
    protected:
        DataType *elements = nullptr;
        size_t elementCount = 0;
        size_t allocatedSize = 0;
    public:
        friend class ImmutableArray<DataType>;

        MutableArray() = default;
        MutableArray(size_t allocatedSize)
        {
            Resize(allocatedSize);
        }
        MutableArray(const MutableArray<DataType>& Other)
        : elementCount(Other.elementCount), allocatedSize(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        };

        MutableArray(MutableArray<DataType>&& Other)
        : elementCount(Other.elementCount), allocatedSize(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        };

        MutableArray<DataType>& operator =(MutableArray<DataType> const& Other)
        {
            elementCount = Other.elementCount;
            allocatedSize = Other.elementCount;
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        }

        MutableArray<DataType>& operator =(MutableArray<DataType> && Other)
        {
            elementCount = Other.elementCount;
            allocatedSize = Other.elementCount;
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        }

        explicit MutableArray(const ImmutableArray<DataType>& Other)
        : elementCount(Other.elementCount), allocatedSize(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        };

        explicit MutableArray(const ImmutableArray<DataType>&& Other)
                : elementCount(Other.elementCount), allocatedSize(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType(newElement);
            }
        };

        ~MutableArray() = default;

        DataType& Get(size_t index)
        {
            return elements[index];
        }

        const DataType& Get(size_t index) const
        {
            return elements[index];
        }

        DataType& operator[](size_t index) {
            return Get(index);
        };
        const DataType operator[](size_t index) const {
            return Get(index);
        };

        void Resize(size_t newCount)
        {
            if(newCount == allocatedSize) return;

            allocatedSize = newCount;

            if(elements)
            {
                elements = static_cast<DataType *>(realloc(elements, newCount * sizeof(DataType)));

                if (elementCount > newCount)
                {
                    elementCount = newCount;
                }
            }
            else
            {
                elements = static_cast<DataType *>(malloc(newCount * sizeof(DataType)));
                for(size_t index; index < newCount; index++)
                {
                    new (elements + index) DataType();
                }
            }
        }

        size_t Add(const DataType& item)
        {
            if(elementCount == allocatedSize)
            {
                Resize(((double)allocatedSize+1) * 1.4);
            }
            elements[elementCount++] = DataType(item);
            return elementCount;
        }

        DataType Remove(size_t index)
        {
            if(elementCount > 1)
            {
                elementCount-=1;
                DataType item = elements[elementCount];
                elements[elementCount] = DataType{};
                return item;
                // Todo(Wynter): shrink array at a certain ratio
            }
            return DataType{};
        }

        size_t Count() const { return elementCount; };
        size_t AllocatedSize() const { return allocatedSize; };
    };

    template<typename DataType>
    class ImmutableArray
    {
    protected:
        DataType *Data = nullptr;
        DataType *elements = nullptr;
        size_t elementCount = 0;

    public:
        friend class MutableArray<DataType>;

        ImmutableArray() = delete;
        explicit ImmutableArray(const MutableArray<DataType>& Other)
        : elementCount(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType();
            }
        };

        explicit ImmutableArray(const ImmutableArray<DataType>& Other)
        : elementCount(Other.elementCount)
        {
            elements = static_cast<DataType *>(malloc(sizeof(DataType) * Other.elementCount));
            for(size_t index = 0; index < elementCount; index++)
            {
                DataType newElement = Other.Get(index);
                new (elements + index) DataType();
            }
        };
        ~ImmutableArray() {};

        DataType &operator[](size_t Index) const {};
    };

    template<typename DataType>
    class Array
    {
    private:
        DataType *Data = nullptr;

        // Size of array in memory
        size_t ArraySize = 0;

    public:
        Array() = default;

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