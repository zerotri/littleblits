#pragma once

#include <rockit/platform/window.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_syswm.h>

#if ROCKIT_RENDERER_OPENGL == 1
#include <SDL2/SDL_opengl.h>
#endif

#include <memory>


namespace Rockit
{
    class SDL2Window : public Window
    {
    protected:
        SDL_Window* windowPtr = nullptr;
#if ROCKIT_RENDERER_OPENGL == 1
        SDL_GLContext glContext = nullptr;
#endif
    public:
        SDL2Window(int32_t width, int32_t height, const char* title)
        {
            // Todo(Wynter): I'm not happy with the dependency on knowing graphics API here but coming up with a
            // solution that will actually make me happy isn't productive right now.
            auto windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

//            auto applicationInstance = Application::GetApplicationInstance();
//            if(!applicationInstance)
//            {
//                // Todo(Wynter): Error handling
//            }

            // Todo(Wynter): we have to disable this code until we create a renderer object
//             auto renderer = applicationInstance->GetRenderer();
//             if(renderer->GetBackendApi() == Renderer::OpenGL)
//             {
//                 windowFlags |= SDL_WINDOW_OPENGL;
//             }

#if ROCKIT_RENDERER_OPENGL == 1
            windowFlags |= SDL_WINDOW_OPENGL;
#endif

            windowPtr = SDL_CreateWindow(
                            title,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            windowFlags);

#if ROCKIT_RENDERER_OPENGL == 1
            glContext = SDL_GL_CreateContext( windowPtr );
#endif

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