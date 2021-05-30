#pragma once

#include <rockit/core/function.h>
#include <rockit/core/pointer.h>
#include <rockit/platform/window.h>
#include <rockit/graphics/renderer.h>
#include <rockit/graphics/rendertarget.h>

#include <cstdint>

namespace Rockit
{
    class Application
    {
    public:

        using OnLoadMethod = TFunction<void()>;
        using OnUnloadMethod = TFunction<void()>;
        using OnStartMethod = TFunction<void()>;
        using OnStopMethod = TFunction<void()>;
        using OnPauseMethod = TFunction<void()>;
        using OnResumeMethod = TFunction<void()>;
        using OnUpdateMethod = TFunction<void(double deltaTime)>;
        using OnFixedUpdateMethod = TFunction<void(double deltaTime)>;
        using OnDisplaySwapMethod = TFunction<void(double deltaTime)>;
        using OnSoundProcessMethod = TFunction<void()>;

    protected:
        bool shouldQuit = false;

        SharedPointer<Window> windowPtr;
        SharedPointer<RenderTarget> backBuffer;

        OnLoadMethod onLoad;
        OnUnloadMethod onUnload;
        OnStartMethod onStart;
        OnStopMethod onStop;
        OnPauseMethod onPause;
        OnResumeMethod onResume;
        OnUpdateMethod onUpdate;
        OnFixedUpdateMethod onFixedUpdate;
        OnDisplaySwapMethod onDisplaySwap;
        OnSoundProcessMethod onSoundProcess;

        Renderer::Backend rendererBackend;

        static Application *applicationInstance;

    public:
        struct Description
        {
            const char* name = "";
            int32_t width = 0;
            int32_t height = 0;

            OnLoadMethod onLoad;
            OnUnloadMethod onUnload;
            OnStartMethod onStart;
            OnStopMethod onStop;
            OnPauseMethod onPause;
            OnResumeMethod onResume;
            OnUpdateMethod onUpdate;
            OnFixedUpdateMethod onFixedUpdate;
            OnDisplaySwapMethod onDisplaySwap;
            OnSoundProcessMethod onSoundProcess;
        };

        Application(Description description);
        ~Application();
        bool Run();
        bool Quit();

        static Application *GetApplicationInstance() { return applicationInstance; };
        Renderer::Backend GetRendererBackendType() { return rendererBackend; };
    };
}