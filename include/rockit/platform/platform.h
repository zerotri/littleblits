#pragma once
#include <rockit/core/application.h>
#include <rockit/core/pointer.h>
#include <rockit/graphics/renderer.h>
#include <rockit/platform/window.h>

namespace Rockit
{
    namespace Platform
    {
        bool Init();
        bool Shutdown();
        bool PumpEvents(Application& application);

        SharedPointer<Window> CreateWindow(Application::Description &description);
        SharedPointer<Renderer> CreateRenderer(Application::Description &description, SharedPointer<Window> window);
        double Sleep(double secondsToSleep);
        double Time();

        // Logging
        enum class LogLevel {
            Fatal,
            Error,
            Warning,
            Info,
            Debug,
            Verbose,
            All
        };

        LogLevel SetLogLevel(LogLevel newLevel);
        int LogInfo(const char* tag, const char* format, ...);
        int LogDebug(const char* tag, const char* format, ...);
        int LogError(const char* tag, const char* format, ...);
//        int LogException();
    };
}