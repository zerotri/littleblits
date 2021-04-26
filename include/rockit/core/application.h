#pragma once

#include <cstdint>
#include <functional>

namespace Rockit
{
    namespace Application
    {
        using OnLoadMethod = std::function<void()>;
        using OnUnloadMethod = std::function<void()>;
        using OnStartMethod = std::function<void()>;
        using OnStopMethod = std::function<void()>;
        using OnPauseMethod = std::function<void()>;
        using OnResumeMethod = std::function<void()>;
        using OnUpdateMethod = std::function<void(float deltaTime)>;
        using OnFixedUpdateMethod = std::function<void(float deltaTime)>;
        using OnDisplaySwapMethod = std::function<void(float deltaTime)>;
        using OnSoundProcessMethod = std::function<void()>;
        
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
        
        bool Create(Description description);
        bool Destroy();
        bool Run();
    };
}