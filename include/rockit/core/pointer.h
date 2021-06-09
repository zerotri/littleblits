#pragma once

#include <cstddef>
#include <cstdint>
#include <malloc.h>
#include <rockit/core/referencecounter.h>

namespace Rockit
{
    template<typename Type>
    struct DefaultDeleter
    {
        void operator()(Type *Object) const
        {
            delete Object;
        }
    };

    template<typename Type, typename DeleterType = DefaultDeleter<Type>>
    class ReferenceCountedPointerController :
            public ReferenceCounterControlledBase,
            public DeleterType
    {
    private:
        Type *DataPointer = nullptr;

    public:
        explicit ReferenceCountedPointerController(Type *DataPointer)
                : DataPointer(DataPointer)
        {
        }

        ~ReferenceCountedPointerController() override = default;

        void Delete() override
        {
            if(DataPointer != nullptr)
            {
                (*static_cast<DeleterType *>(this))(DataPointer);
            }
        }
    };

    template<typename Type>
    class SharedPointer
    {
    protected:
        Type *DataPointer = nullptr;
        ReferenceCounterControlledBase *ReferenceCounter = nullptr;
    public:

        template<class OtherType> friend
        class SharedPointer;

        SharedPointer() = default;

        SharedPointer(Type *PointerToObject)
                : DataPointer(PointerToObject), ReferenceCounter(new ReferenceCountedPointerController<Type>(PointerToObject))
        {
            ReferenceCounter->Increment();
        }

        SharedPointer(const SharedPointer<Type> &Other)
                : DataPointer(Other.DataPointer), ReferenceCounter(Other.ReferenceCounter)
        {
            ReferenceCounter->Increment();
        }

        SharedPointer(Type *PointerToObject, ReferenceCounterControlledBase *NewReferenceCounter)
                : DataPointer(PointerToObject), ReferenceCounter(NewReferenceCounter)
        {
            ReferenceCounter->Increment();
        }

        template<typename OtherType>
        SharedPointer(const SharedPointer<OtherType> &Other)
                : DataPointer(Other.DataPointer), ReferenceCounter(Other.ReferenceCounter)
        {
            ReferenceCounter->Increment();
        }

        ~SharedPointer()
        {
            if (ReferenceCounter != nullptr)
            {
                ReferenceCounter->Decrement();
                if (ReferenceCounter->GetCount() == 0)
                {
                    ReferenceCounter->Delete();
                    delete ReferenceCounter;
                }
            }
        }

        SharedPointer<Type> &operator=(const SharedPointer<Type> &Other)
        {
            if (this != &Other)
            {
                if (ReferenceCounter && ReferenceCounter->GetCount() == 0)
                {
                    ReferenceCounter->Delete();
                    delete ReferenceCounter;
                }
                DataPointer = Other.DataPointer;
                ReferenceCounter = Other.ReferenceCounter;
                ReferenceCounter->Increment();
            }
            return *this;
        }

        SharedPointer<Type> &operator=(Type *Other)
        {
            if ((DataPointer != Other) && (Other != nullptr))
            {
                if (DataPointer != nullptr)
                {
                    if (ReferenceCounter != nullptr)
                    {
                        ReferenceCounter->Decrement();
                        if (ReferenceCounter->GetCount() == 0)
                        {
                            ReferenceCounter->Delete();
                            delete ReferenceCounter;
                        }
                    }
                }
                DataPointer = Other;
                ReferenceCounter = new ReferenceCountedPointerController<Type>(Other);
                ReferenceCounter->Increment();
            }
            return *this;
        }

        template<typename OtherType>
        SharedPointer<Type> &operator=(SharedPointer<OtherType> &Other)
        {
            if (this != &Other)
            {
                if (ReferenceCounter != nullptr)
                {
                    ReferenceCounter->Decrement();
                    if (ReferenceCounter->GetCount() == 0)
                    {
                        ReferenceCounter->Delete();
                        delete ReferenceCounter;
                    }
                }
                DataPointer = Other.DataPointer;
                ReferenceCounter = Other.ReferenceCounter;
                ReferenceCounter->Increment();
            }
            return *this;
        }

        template<typename OtherType>
        SharedPointer<Type> &operator=(OtherType *Other)
        {
            if ((DataPointer != Other) && (Other != nullptr))
            {
                if (DataPointer != nullptr)
                {
                    if (ReferenceCounter != nullptr)
                    {
                        ReferenceCounter->Decrement();
                        if (ReferenceCounter->GetCount() == 0)
                        {
                            ReferenceCounter->Delete();
                            delete ReferenceCounter;
                        }
                    }
                }
                DataPointer = Other;
                ReferenceCounter = new ReferenceCountedPointerController<OtherType>(Other);
                ReferenceCounter->Increment();
            }
            return *this;
        }

        Type *Get() const
        {
            return DataPointer;
        }

        Type &operator*() const
        {
            return *Get();
        }

        Type *operator->() const
        {
            return Get();
        }

        explicit operator bool()
        {
            return DataPointer != nullptr;
        }

        bool operator==(const SharedPointer<Type> &Other)
        {
            return (DataPointer == Other.DataPointer);
        }

        bool operator==(const Type &Other)
        {
            return (DataPointer == Other.DataPointer);
        }

        template<typename OtherType>
        bool operator==(const SharedPointer<OtherType> &Other)
        {
            return (DataPointer == Other.DataPointer);
        }

        template<typename OtherType>
        bool operator==(const OtherType &Other)
        {
            return (DataPointer == Other.DataPointer);
        }


    };

    template<typename Type>
    [[maybe_unused]] SharedPointer<Type> MakeSharedPointer(Type *DataPointer)
    {
        return SharedPointer<Type>(DataPointer, new ReferenceCountedPointerController<Type>(DataPointer));
    }

    template<typename Type>
    [[maybe_unused]] SharedPointer<Type> MakeSharedPointer()
    {
        Type *DataPointer = new Type();
        return SharedPointer<Type>(DataPointer, new ReferenceCountedPointerController<Type>(DataPointer));
    }

    template<typename Type, typename... Args>
    [[maybe_unused]] SharedPointer<Type> MakeSharedPointer(Args... args)
    {
        Type *DataPointer = new Type(args...);
        return SharedPointer<Type>(DataPointer, new ReferenceCountedPointerController<Type>(DataPointer));
    }

    template<typename Type, typename DeleterType>
    [[maybe_unused]] SharedPointer<Type> MakeSharedPointer(Type *DataPointer, DeleterType &&Deleter)
    {
        return SharedPointer<Type>(DataPointer, Deleter);
    }
}