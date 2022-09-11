//#include "com_xxx_jni_JNI.h"
#include <stdio.h>
#include <android/log.h>
#include <jni.h>
#define TAG "JNI"
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
void native_helloNative(JNIEnv * env, jobject jobject){

    LOGE(TAG,"This RegisterNatives fun\n");
}
/*需要注册的函数列表，放在JNINativeMethod 类型的数组中，
 以后如果需要增加函数，只需在这里添加就行了
 参数：
 1.java中用native关键字声明的函数名
 2.签名（传进来参数类型和返回值类型的说明）
 3.C/C++中对应函数的函数名（地址）
 */
static JNINativeMethod methods[] =
        {

                {
                        "helloNative", "()V",(void*) native_helloNative },
        };
//此函数通过调用RegisterNatives方法来注册我们的函数
static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* getMethods, int methodsNum) {

    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(className);
    if (clazz == NULL) {

        return JNI_FALSE;
    }
    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
    if (env->RegisterNatives(clazz, getMethods, methodsNum) < 0) {

        return JNI_FALSE;
    }
    return JNI_TRUE;
}
static int registerNatives(JNIEnv* env) {

    //指定类的路径，通过FindClass 方法来找到对应的类
    const char* className = "com/xxx/jni/JNI";
    return registerNativeMethods(env, className, methods,
                                 sizeof(methods) / sizeof(methods[0]));
}
//动态注册
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env = NULL;
    //获取JNIEnv
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {

        return -1;
    }
    //注册函数 registerNatives ->registerNativeMethods ->env->RegisterNatives
    if (!registerNatives(env)) {

        return -1;
    }
    //返回jni 的版本
    return JNI_VERSION_1_6;
}