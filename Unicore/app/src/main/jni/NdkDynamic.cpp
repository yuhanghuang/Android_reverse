//
// Created by Administrator on 2022/8/20.
//

#include "NdkDynamic.h"
#include <stddef.h>
#include "jni.h"

#define JNI_CLASS "com/simple/dynamicdemo/NdkTest" //定义native方法的java文件

/**
 * 返回一个字符串
 * **/
JNIEXPORT jstring JNICALL native_hello(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("Hello from C++");
}

/**
 * 求两个int的值
 * **/
JNIEXPORT jint JNICALL native_add(JNIEnv *env, jobject object, jint a, jint b) {
    return a + b;
}

/**
 * 方法数组，JNINativeMethod的第一个参数是Java中的方法名，第二个参数是函数签名，第三个参数是对应的方法指针，
 * java方法的签名一定要与对应的C++方法参数类型一致，否则注册方法可能失败
 * **/
static JNINativeMethod method_table[] = {
        {"native_hello", "()Ljava/lang/String;", (void *) native_hello},
        {"native_add",   "(II)I",                (void *) native_add}
};

/**
 * 默认会调用的方法，这里把方法注册好
 **/
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
//OnLoad方法是没有JNIEnv参数的，需要通过vm获取。
JNIEnv *env = NULL;
if (vm->AttachCurrentThread(&env, NULL) == JNI_OK) {
//获取对应声明native方法的Java类
jclass  clazz = env->FindClass(JNI_CLASS);
if (clazz == NULL) {
return JNI_FALSE;
}
//注册方法，成功返回正确的JNIVERSION。
if (env->RegisterNatives(clazz, method_table, sizeof(method_table)/ sizeof(method_table[0]))==JNI_OK) {
return JNI_VERSION_1_4;
}
}
return JNI_FALSE;
}
