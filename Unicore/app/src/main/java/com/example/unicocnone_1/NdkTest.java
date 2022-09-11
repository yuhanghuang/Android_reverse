package com.example.unicocnone_1;

public class NdkTest {

//    static {
//        System.loadLibrary("JNITest");
//    }

//    public native  String native_hello();

//    public native int native_add(int a,int b);

    public native void helloNative();
    static {

        System.loadLibrary("jni");
    }

}