#include <rockit/core/application.h>
#include <rockit/platform/platform.h>

namespace Rockit {

    Application *Application::applicationInstance = nullptr;

    Application::Application(Application::Description description)
    : onLoad(description.onLoad), onUnload(description.onUnload),
      onStart(description.onStart), onStop(description.onStop),
      onPause(description.onPause), onResume(description.onResume),
      onUpdate(description.onUpdate), onFixedUpdate(description.onFixedUpdate),
      onDisplaySwap(description.onDisplaySwap), onSoundProcess(description.onSoundProcess)
    {
        if(!Application::applicationInstance)
        {
            Application::applicationInstance = this;
        }

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
        double currentTime = 0.0;
        double lastTime = Platform::Time();

        while(!shouldQuit)
        {
            Platform::PumpEvents(*this);

            currentTime = Platform::Time();
            double deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            if(onUpdate)
            {
                onUpdate(deltaTime);
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