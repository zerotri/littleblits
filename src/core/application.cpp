#include <rockit/core/application.h>
#include <rockit/platform/platform.h>
#include <iostream>

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
            std::cout << "Setting applicationInstance to this" << std::endl;
            Application::applicationInstance = this;
        }

        if(!Platform::Init())
        {
            // Todo(Wynter): we need to handle the error case here
        }



        windowPtr = Platform::CreateWindow(description);
        rendererPtr = Platform::CreateRenderer(description, windowPtr);
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

        if(onLoad)
        {
            onLoad();
        }

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

        if(onUnload)
        {
            onUnload();
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