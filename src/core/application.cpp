#include <rockit/core/application.h>
#include <rockit/platform/platform.h>

namespace Rockit {

    Application::Application(Application::Description description)
    : onLoad(description.onLoad), onUnload(description.onUnload),
      onStart(description.onStart), onStop(description.onStop),
      onPause(description.onPause), onResume(description.onResume),
      onUpdate(description.onUpdate), onFixedUpdate(description.onFixedUpdate),
      onDisplaySwap(description.onDisplaySwap), onSoundProcess(description.onSoundProcess)
    {
        if(!Platform::Init())
        {
            // Todo(Wynter): we need to handle the error case here
        }

        windowPtr = Platform::CreateWindow(description);
    }

    Application::~Application()
    {
        if(!Platform::Shutdown())
        {
            // Todo(Wynter): we need to handle the error case here
        }

    }

    bool Application::Run()
    {
        while(!shouldQuit)
        {
            Platform::PumpEvents(*this);

            if(onUpdate)
            {
                onUpdate(0.0f);
            }
        }
        return false;
    }

    bool Application::Quit()
    {
        auto previousState = shouldQuit;
        shouldQuit = true;
        return previousState;
    }
}