#pragma once
#include <rockit/core/array.h>
#include <rockit/core/function.h>
#include <rockit/core/pointer.h>

namespace Rockit
{

    class Actor;
    class ActorBehaviour;

    class Actor
    {
    public:
        using BehaviourPointer = SharedPointer<ActorBehaviour>;

    protected:
        MutableArray<BehaviourPointer> behaviours;

    public:
        virtual ~Actor();

        template<typename BehaviourType>
        bool AddBehaviour()
        {
            SharedPointer<BehaviourType> behaviour = MakeSharedPointer<BehaviourType>();
            behaviours.Add(behaviour);
            return true;
        }

        template<typename BehaviourType, typename... Args>
        bool AddBehaviour(Args&&... args)
        {
            SharedPointer<BehaviourType> behaviour = MakeSharedPointer<BehaviourType>(args...);
            behaviours.Add(behaviour);
            return true;
        }

        bool AddBehaviour(ActorBehaviour* behaviour)
        {
            behaviours.Add(SharedPointer<ActorBehaviour>(behaviour));
            return true;
        }
        bool AddBehaviour(SharedPointer<ActorBehaviour> behaviour)
        {
            behaviours.Add(behaviour);
            return true;
        }

        void Update(double deltaTime);
    };


    class ActorBehaviour
    {
    protected:
        using OnCreateMethod = TFunction<void()>;
        using OnDestroyMethod = TFunction<void()>;
        using OnUpdateMethod = TFunction<void(double deltaTime)>;

        OnCreateMethod onCreate;
        OnDestroyMethod onDestroy;
        OnUpdateMethod onUpdate;

    public:
        struct Description
        {
            OnCreateMethod onCreate;
            OnDestroyMethod onDestroy;
            OnUpdateMethod onUpdate;
        };

        ActorBehaviour() = default;
        ActorBehaviour(const ActorBehaviour&) = delete;
        ActorBehaviour& operator=(const ActorBehaviour&) = delete;
        ActorBehaviour& operator=(ActorBehaviour&&) = delete;

        explicit ActorBehaviour(Description description)
        : onCreate(description.onCreate),
          onDestroy(description.onDestroy),
          onUpdate(description.onUpdate)
        {

        };

        virtual ~ActorBehaviour();
        virtual void OnCreate()
        {
            if(onCreate)
                onCreate();
        }

        virtual void OnDestroy()
        {
            if(onDestroy)
                onDestroy();
        }

        virtual void OnUpdate(double deltaTime)
        {
            if(onUpdate)
                onUpdate(deltaTime);
        }
    };
}