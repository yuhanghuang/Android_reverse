#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO, "========= fenfei Info =========   ", __VA_ARGS__)

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "========= fenfei Error =========   ", __VA_ARGS__)

#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "========= fenfei Debug =========   ", __VA_ARGS__)

#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "========= fenfei Warn =========   ", __VA_ARGS__)

/*
 * <pre>
 * Created by fenfei
 * http://91fans.com.cn/
 * public accounts: fenfei330
 * wx:fenfei331  mail:fenfei331@126.com
 * data ：2020/11/26
 * <pre>
 * ********************************我佛慈悲*********************************
 * **                              _oo0oo_                               **
 * **                             o8888888o                              **
 * **                             88" . "88                              **
 * **                             (| -_- |)                              **
 * **                             0\  =  /0                              **
 * **                           ___/'---'\___                            **
 * **                        .' \\\|     |// '.                          **
 * **                       / \\\|||  :  |||// \\                        **
 * **                      / _ ||||| -:- |||||- \\                       **
 * **                      | |  \\\\  -  /// |   |                       **
 * **                      | \_|  ''\---/''  |_/ |                       **
 * **                      \  .-\__  '-'  __/-.  /                       **
 * **                    ___'. .'  /--.--\  '. .'___                     **
 * **                 ."" '<  '.___\_<|>_/___.' >'  "".                  **
 * **                | | : '-  \'.;'\ _ /';.'/ - ' : | |                 **
 * **                \  \ '_.   \_ __\ /__ _/   .-' /  /                 **
 * **            ====='-.____'.___ \_____/___.-'____.-'=====             **
 * **                              '=---='                               **
 * ************************************************************************
 * **                佛祖保佑      镇类之宝       永无bug                   **
 * ************************************************************************
 */

struct Method {
    int    clazz;  // 代表这个方法所属的类
    int  accessFlags;     // 访问标识符， 定义是public？ native？synchronized？
    int  methodIndex;   // index，在ClassObject中一个保存Method对象的数组的位置。
    int  registersSize;  // 仅对native方法有用，保存方法的参数的个数。
    int  outsSize;   // unknown， 不重要
    int  insSize;    // unknown， 不重要
    const char*   name;   // 方法名
    int  prototype;   // 我们可以理解这是一个代表该方法签名的字符串（包含返回值以及参数类型）
    const char*  shorty; // 跟上面的意义，方法的签名，like：（ILjava/lang/String）V
    int  insns;  // 方法的指令代码
    int  jniArgInfo;  // jni参数信息，好像没啥用
    int nativeFunc;   // native函数指针，可能是真正的native函数，也可能是JNI桥接函数
    bool fastJni;   // unknown， 不重要
    bool noRef;     // unknown， 不重要
    bool shouldTrace;   // unknown， 不重要
    int registerMap;   // unknown， 不重要
    bool   inProfile;   // unknown， 不重要
};

//静态注册
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jni_1dynamic2_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
//native_hello
// ---- 动态注册 ----

// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/example/jni_dynamic2/MainActivity"


// 返回字符串"hello load jni"
JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz)
{
    return env->NewStringUTF("fenfei hello load jni.");
}

// Java和JNI函数的绑定表
static JNINativeMethod method_table[] = {
        { "native_hello", "()Ljava/lang/String;", (void*)native_hello },//绑定

};

// 注册native方法到java中
static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ( env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int register_ndk_load(JNIEnv *env)
{
    // 调用注册方法
    return registerNativeMethods(env, JNIREG_CLASS,
                                 method_table, NELEM(method_table));
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ( vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    register_ndk_load(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}

