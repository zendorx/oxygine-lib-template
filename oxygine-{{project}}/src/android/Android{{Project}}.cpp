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
    /*JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newMeRequestResult(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newMeRequestResult(data , (bool) error) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newToken(JNIEnv* env, jobject obj, jstring json_data)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newToken(data) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_loginResult(JNIEnv* env, jobject obj, jboolean value)
    {
        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::loginResult((bool) value) ;
        });
    }

    JNIEXPORT void JNICALL Java_org_oxygine_facebook_FacebookAdapter_newMyFriendsRequestResult(JNIEnv* env, jobject obj, jstring json_data, jboolean error)
    {
        string data = jniGetString(env, json_data);

        core::getMainThreadMessages().postCallback([ = ]()
        {
            facebook::internal::newMyFriendsRequestResult(data, (bool) error);
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

        _jFacebookObject = env->NewGlobalRef(jniFindExtension(env, _j{{Project}}Class));
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

/*bool jniFacebookIsLoggedIn()
{
    if (!isFacebookEnabled())
        return false;

    bool result = false;
    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jisLoggedIn = env->GetMethodID(_jFacebookClass, "isLoggedIn", "()Z");
        JNI_NOT_NULL(jisLoggedIn);

        jboolean jb = env->CallBooleanMethod(_jFacebookObject, jisLoggedIn);
        result = (bool) jb;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookIsLoggedIn failed, class/member not found");
    }

    return result;
}

void jniFacebookNewMeRequest()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jnewMeRequest = env->GetMethodID(_jFacebookClass, "newMeRequest", "()V");
        JNI_NOT_NULL(jnewMeRequest);
        env->CallVoidMethod(_jFacebookObject, jnewMeRequest);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookNewMeRequest failed, class/member not found");
    }
}

string jniFacebookGetAccessToken()
{
    if (!isFacebookEnabled())
        return "";

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetToken = env->GetMethodID(_jFacebookClass, "getAccessToken", "()Ljava/lang/String;");
        JNI_NOT_NULL(jgetToken);

        jobject obj = env->CallObjectMethod(_jFacebookObject, jgetToken);
        string data = jniGetString(env, (jstring) obj);
        return data;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetAccessToken failed, class/member not found");
    }

    return "";
}

string jniFacebookGetUserID()
{
    if (!isFacebookEnabled())
        return "";

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetUserID = env->GetMethodID(_jFacebookClass, "getUserID", "()Ljava/lang/String;");
        JNI_NOT_NULL(jgetUserID);

        jobject obj = env->CallObjectMethod(_jFacebookObject, jgetUserID);
        string data = jniGetString(env, (jstring) obj);
        return data;

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetUserID failed, class/member not found");
    }

    return "";
}

bool jniFacebookAppInviteDialog(const string& appLinkUrl, const string& previewImageUrl)
{
    if (!isFacebookEnabled())
        return false;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jappInviteDialog = env->GetMethodID(_jFacebookClass, "appInviteDialog", "([Ljava/lang/String;[Ljava/lang/String;)Z");
        JNI_NOT_NULL(jappInviteDialog);

        jstring jappLinkUrl = env->NewStringUTF(appLinkUrl.c_str());
        jstring jpreviewImageUrl = env->NewStringUTF(previewImageUrl.c_str());

        env->CallVoidMethod(_jFacebookObject, jappInviteDialog, jappLinkUrl, jpreviewImageUrl);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetFriends failed, class/member not found");
    }
}

void jniFacebookGetFriends()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jgetFriends = env->GetMethodID(_jFacebookClass, "newMyFriendsRequest", "()V");
        JNI_NOT_NULL(jgetFriends);
        env->CallVoidMethod(_jFacebookObject, jgetFriends);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookGetFriends failed, class/member not found");
    }

}
void jniFacebookLogin()
{
    if (!isFacebookEnabled())
        return;

    try
    {
        JNIEnv* env = jniGetEnv();
        LOCAL_REF_HOLDER(env);

        jmethodID jlogin = env->GetMethodID(_jFacebookClass, "login", "()V");
        JNI_NOT_NULL(jlogin);
        env->CallVoidMethod(_jFacebookObject, jlogin);

    }
    catch (const notFound&)
    {
        log::error("jniFacebookLogin failed, class/member not found");
    }
}*/