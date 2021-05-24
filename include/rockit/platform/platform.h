#pragma once
#include <rockit/core/application.h>
#include <rockit/core/pointer.h>
#include <rockit/platform/window.h>

namespace Rockit
{
    namespace Platform
    {
        bool Init();
        bool Shutdown();
        bool PumpEvents(Application& application);

        SharedPointer<Window> CreateWindow(Application::Description &description);
        double Sleep(double secondsToSleep);
    };
}