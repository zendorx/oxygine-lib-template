#include "{{project}}.h"

#ifdef __ANDROID__
    #include "android/Android{{Project}}.h"
#elif __APPLE__
    #include <TargetConditionals.h>
    #include "ios/ios{{Project}}.h"
#else
    #include "sim/{{Project}}Simulator.h"
#endif



#define {{PROJECT}}_EXT_ENABLED 1

namespace {{project}}
{

    spEventDispatcher _dispatcher;

    spEventDispatcher dispatcher()
    {
        return _dispatcher;
    }

    void init()
    {
#if !{{PROJECT}}_EXT_ENABLED
        return;
#endif

        log::messageln("{{project}}::init");

        OX_ASSERT(_dispatcher == 0);
        _dispatcher = new EventDispatcher;

#ifdef __ANDROID__
        jni{{Project}}Init();
#elif TARGET_OS_IPHONE

#else
        {{project}}SimulatorInit();
#endif
        log::messageln("{{project}}::init done");
    }

    void free()
    {
#if !{{PROJECT}}_EXT_ENABLED
        return;
#endif

        log::messageln("{{project}}::free");

        OX_ASSERT(_dispatcher);

#ifdef __ANDROID__
        jni{{Project}}Free();
#endif
        _dispatcher->removeAllEventListeners();
        _dispatcher = 0;
        log::messageln("{{project}}::free done");
    }

    /*void doSomething()
    {
#ifdef __ANDROID__
        jniDoSomethingInJava();
#elif TARGET_OS_IPHONE
        jniDoSomethingInObjectiveC();
#else
        simulatorFunction();
#endif
        
    }*/


    namespace internal
    {

        /*void callItFromNativeCallback()
        {
            YourEventExample ev;
            _dispatcher->dispatchEvent(&ev);
        }*/
    }
}

