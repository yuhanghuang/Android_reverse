package com.example.native_test2;

public class Myjni {
    public native int native_add(int a,int b);
    static {
        System.loadLibrary("JNITest");
    }

//    public native  String native_hello();


}
