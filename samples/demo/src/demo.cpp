#include <iostream>
#include <rockit/core/application.h>

using namespace Rockit;

int main(int argc, char** argv)
{
    Application::Description description = {
        .name = "Rockit Demo",
        .width = 1280,
        .height = 720,
    };

    Application::Create(description);
    Application::Run();
    Application::Destroy();

#if 0
    Coroutine co([]() -> int {
        std::cout << "This is a test" << std::endl;
        for(int i = 0; i < 5; i++) {
            int value = Coroutine::Yield(4);
        }

        return 5;
    });

    int retval = 0;
    Coroutine::Start(co);
    retval = Coroutine::Resume(co);
    retval = Coroutine::Resume(co, 3);
    retval = Coroutine::Resume(co);
    retval = Coroutine::Resume(co);
#endif

    return 0;
}