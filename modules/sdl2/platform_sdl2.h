#pragma once

#include <rockit/platform/window.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_syswm.h>

#include <memory>
namespace Rockit
{
    class SDL2Window : public Window
    {
    protected:
        SDL_Window* windowPtr;
    public:
        SDL2Window(int32_t width, int32_t height, const char* title)
        {
            auto windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
            windowPtr = SDL_CreateWindow(
                            title,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            windowFlags);
        }
        virtual ~SDL2Window() override
        {
            if(windowPtr)
            {
                SDL_DestroyWindow(windowPtr);
            }
        }
    };
}