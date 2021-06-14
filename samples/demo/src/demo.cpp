#include <iostream>
#include <rockit/core/application.h>
#include <rockit/core/coroutine.h>
#include <rockit/core/pointer.h>
#include <rockit/core/array.h>
#include <rockit/platform/platform.h>
#include <rockit/core/actor.h>

using namespace Rockit;

int main(int argc, char **argv)
{
    MutableArray<std::string> stringArray(10);
    stringArray.Add("This is a string from main");

    std::cout << "Called from main function" << std::endl;
    std::cout << stringArray[0] << std::endl;

    Coroutine coroutine(Coroutine::StackSize::Large,
        [stringArray](Coroutine &co, Coroutine::UserData userData) -> void *
        {
            std::cout << "Called from within coroutine" << std::endl;
            std::cout << stringArray[0] << std::endl;

            int i = 0;
            while (++i < 10)
            {
                printf(".");

                Yield(nullptr);
                // co.Wait(0.5, nullptr);
            }
            return nullptr;
        });

    double timer = 0.0;
    Actor testActor;

    testActor.AddBehaviour({
        .onUpdate = [&coroutine, &timer](double deltaTime){
            timer += deltaTime;

            if(timer > 1)
            {
                std::cout << "Time: " << Platform::Time() << std::endl;

                if (coroutine.IsRunning())
                {
                    coroutine.Resume(nullptr);
                    fflush(nullptr);
                }
                timer -= 1;
            }
        }
    });

    Application application({
        .name = "Rockit Demo",
        .width = 1280,
        .height = 720,
        .onUpdate = [&testActor](double deltaTime)
        {
            testActor.Update(deltaTime);
        },
    });

    application.Run();

    return 0;
}