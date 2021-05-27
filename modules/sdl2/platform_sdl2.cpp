#include <rockit/core/pointer.h>
#include <rockit/platform/platform.h>
#include "platform_sdl2.h"

#include <time.h>

namespace Rockit
{
    namespace Platform
    {
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
            struct timespec timeToSleep, timeRemaining;
            timeToSleep.tv_sec = (time_t) secondsToSleep;
            timeToSleep.tv_nsec = (time_t) ((secondsToSleep - timeToSleep.tv_sec) * 1000000000.0);
            nanosleep(&timeToSleep, &timeRemaining);

            // Todo(Wynter): handle timeRemaining
            return 0.0;
        }

        double Time()
        {
            struct timespec currentTime;

            if(clock_gettime(CLOCK_MONOTONIC, &currentTime) == 0)
            {
                double time = (double)currentTime.tv_sec + ((double)currentTime.tv_nsec / 1000000000.0);
                return time;
            }
            return 0.0;
        }
    };
}