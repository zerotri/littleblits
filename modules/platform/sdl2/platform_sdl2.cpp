#include <rockit/core/pointer.h>
#include <rockit/platform/platform.h>
#include <renderer/opengl/renderer_opengl.h>
#include "platform_sdl2.h"

#include <stdarg.h>

#if defined(_WIN32)
#include <windows.h>
#undef CreateWindow
#endif

#include <ctime>
#include <cerrno>
#include <chrono>
#include <thread>


#if defined(_WIN32)
extern int main(int, char**);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    return main(0, nullptr);
}
#endif

namespace Rockit
{
    namespace Platform
    {
        static LogLevel globalLogLevel = LogLevel::Info;
        static double startingTime = Time();

        bool Init()
        {
            SDL_SetMainReady();

            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
            {
                // SDL_GetError()
                return false;
            }
            return true;
        }

        SharedPointer<Window> CreateWindow(Application::Description &description)
        {
            SharedPointer<Window> window = MakeSharedPointer<SDL2Window>(description.width, description.height, description.name);
            return window;
        }

        SharedPointer<Renderer> CreateRenderer(Application::Description &description, SharedPointer<Window> window)
        {
            auto windowPtr = dynamic_cast<SDL2Window*>(window.Get());
            SharedPointer<Renderer> renderer;

#if ROCKIT_RENDERER_OPENGL == 1
            renderer = MakeSharedPointer<OpenGLRenderer>();

#endif
            return renderer;
        }


        bool Shutdown()
        {
            SDL_Quit();
            return true;
        }

        bool PumpEvents(Application& application)
        {
            SDL_Event event;
            while( SDL_PollEvent( &event ) != 0 )
            {
                if( event.type == SDL_QUIT )
                {
                    application.Quit();
                }
            }
            return true;
        }

        double Sleep(double secondsToSleep)
        {
            double remainingTime = 0.0;
#if defined(_WIN32)
            std::chrono::duration<double> durationToSleep(secondsToSleep);
            std::this_thread::sleep_for(durationToSleep);

#else
            struct timespec timeToSleep, timeRemaining;
            timeToSleep.tv_sec = (time_t) secondsToSleep;
            timeToSleep.tv_nsec = (time_t) ((secondsToSleep - timeToSleep.tv_sec) * 1000000000.0);
            auto result = nanosleep(&timeToSleep, &timeRemaining);

            if(result < 0 && errno == EINTR)
            {
                remainingTime = timeRemaining.tv_sec + (timeRemaining.tv_nsec / 1000000000.0);
            }
#endif

            return remainingTime;
        }

        double Time()
        {
#if defined(_WIN32)
            static LARGE_INTEGER frequency;
            static double frequencyInverse = 0.0;

            if( frequencyInverse == 0.0 )
            {
                QueryPerformanceFrequency(&frequency);

                frequencyInverse = 1.0 / double(frequency.QuadPart);
            }

            LARGE_INTEGER counterValue;
            QueryPerformanceCounter(&counterValue);

            double time = double(counterValue.QuadPart) / double(frequency.QuadPart);
            return time;

#else
            struct timespec currentTime;

            if(clock_gettime(CLOCK_MONOTONIC, &currentTime) == 0)
            {
                double time = (double)currentTime.tv_sec + ((double)currentTime.tv_nsec / 1000000000.0);
                return time;
            }
#endif
            return 0.0;
        }

        LogLevel SetLogLevel(LogLevel newLevel)
        {
            auto oldLevel = globalLogLevel;
            globalLogLevel = newLevel;
            return oldLevel;
        }

        static int LogOut(LogLevel level, const char* tag, const char* format, va_list args)
        {
            const char *LogLevelNames[] = {
                "Fatal",
                "Error",
                "Warning",
                "Info",
                "Debug",
                "Verbose",
                "All"
            };

            if(globalLogLevel < level) return 0;
            const auto logFormat = "%16f [%24s|%-8s]: %s\n";
            const auto logStringBufferSize = 4* 1024;
            static thread_local char logStringBuffer[logStringBufferSize];

            double deltaTime = Time() - startingTime;
            char formatBuffer[256];
            snprintf(formatBuffer, 256, logFormat, deltaTime, tag, LogLevelNames[(int)level], format);

            auto count = vsnprintf(logStringBuffer, logStringBufferSize, formatBuffer, args);

#if WIN32
            OutputDebugStringA(logStringBuffer);
#else
            fputs(logStringBuffer, stdout);
#endif

            return count;
        }

        int LogInfo(const char* tag, const char* format, ...)
        {
            va_list varArgList;
            va_start(varArgList, format);
            auto count = LogOut(LogLevel::Info, tag, format, varArgList);
            va_end(varArgList);
            return count;
        }

        int LogDebug(const char* tag, const char* format, ...)
        {
            va_list varArgList;
            va_start(varArgList, format);
            auto count = LogOut(LogLevel::Debug, tag, format, varArgList);
            va_end(varArgList);
            return count;
        }

        int LogError(const char* tag, const char* format, ...)
        {
            va_list varArgList;
            va_start(varArgList, format);
            auto count = LogOut(LogLevel::Error, tag, format, varArgList);
            va_end(varArgList);
            return count;
        }
    };
}
