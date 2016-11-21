#include <jni.h>
#include <android/log.h>
#include <assert.h>
#include "core/oxygine.h"
#include "core/Object.h"
#include "core/ThreadMessages.h"
#include "core/oxygine.h"
#include "core/android/jniHelper.h"
#include "core/android/jniUtils.h"
#include "json/json.h"
#include "src/{{project}}.h"


using namespace oxygine;

jclass _j{{Project}}Class = 0;
jobject _j{{Project}}Object = 0;

bool is{{Project}}Enabled()
{
    return _j{{Project}}Class && _j{{Project}}Object;
}


extern "C"
{
    /*JNIEXPORT void JNICALL Java_org_oxygine_{{project}}_{{Project}}Adapter_YOUR_FUNC_NAME(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadDispatcher().postCallback([ = ]()
        {
            //call internal function there from src/{{project}}/{{project}}.h
            {{project}}::internal::callItFromNativeCallback();
        });
    }*/


}


void jni{{Project}}Init()
{
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        JNI_NOT_NULL(env);

        _j{{Project}}Class = env->FindClass("org/oxygine/{{project}}/{{Project}}Adapter");
        JNI_NOT_NULL(_j{{Project}}Class);

        _j{{Project}}Class = (jclass) env->NewGlobalRef(_j{{Project}}Class);
        JNI_NOT_NULL(_j{{Project}}Class);

        _j{{Project}}Object = env->NewGlobalRef(jniFindExtension(env, _j{{Project}}Class));
        JNI_NOT_NULL(_j{{Project}}Object);
    }
    catch (const notFound&)
    {
        log::error("jni{{Project}}Init failed, class/member not found");
    }
}

void jni{{Project}}Free()
{
    if (!is{{Project}}Enabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        env->DeleteGlobalRef(_j{{Project}}Class);
        _j{{Project}}Class = 0;

        env->DeleteGlobalRef(_j{{Project}}Object);
        _j{{Project}}Object = 0;
    }
    catch (const notFound&)
    {

    }
}

/*
bool jni{{Project}}SomeBoolFunc()
    {
    if (!is{{Project}}Enabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);
        //jstring jappLinkUrl = env->NewStringUTF(appLinkUrl.c_str()); //to jstring example
        jmethodID jisMethod = env->GetMethodID(_j{{Project}}Class, "FUNC_NAME_JAVA", "()Z");
        JNI_NOT_NULL(jisMethod);
        //string data = jniGetString(env, (jstring) obj); //string example
        jboolean jb = env->CallBooleanMethod(_j{{Project}}Object, jisMethod);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jni{{Project}}SomeBoolFunc failed, class/member not found");
    }

    return result;
}
*/
