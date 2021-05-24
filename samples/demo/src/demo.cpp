#include <iostream>
#include <rockit/core/application.h>
#include <rockit/core/coroutine.h>
#include <rockit/core/pointer.h>
#include <rockit/core/array.h>

using namespace Rockit;

int main(int argc, char **argv)
{
    Array<std::string> stringArray;
    stringArray.Allocate(10);
    stringArray[0] = "This is a string from main";

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

    Application application(
        {
            .name = "Rockit Demo",
            .width = 1280,
            .height = 720,
            .onUpdate = [&coroutine](float deltaTime)
            {
                if (coroutine.IsRunning())
                {
                    coroutine.Resume(nullptr);
                    fflush(nullptr);
                }
            },
        });

    application.Run();

    return 0;
}