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
            // Todo(Wynter): I'm not happy with the dependency on knowing graphics API here but coming up with a
            // solution that will actually make me happy isn't productive right now.
            auto windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

            auto applicationInstance = Application::GetApplicationInstance();
            if(applicationInstance->GetRendererBackendType() == Renderer::OpenGL)
            {
                windowFlags |= SDL_WINDOW_OPENGL;
            }

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