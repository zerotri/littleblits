#include <rockit/core/actor.h>

namespace Rockit {
    Actor::~Actor()
    {

    }

    void Actor::Update(double deltaTime)
    {
        for(size_t behaviourIndex = 0; behaviourIndex < behaviours.Count(); behaviourIndex++)
        {
            auto behaviour = behaviours[behaviourIndex];
            behaviour->OnUpdate(deltaTime);
        }
    }

    ActorBehaviour::~ActorBehaviour()
    {

    }
}