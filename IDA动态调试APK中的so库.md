由于对于java的反编译比较简单，现在市场是也出了很多相应的工具。比如主流的javax,Jeb pro,apktools等工具，而IEDA可以实现对jar包或者是arr包的反编译，这就对java的逆向提供了很大的帮助，因此为了提高APK中的安全性，开发者往往会将固件的核心代码写入到so库中，这样就大大提高了APK逆向的难度。而IDA是一个逆向分析so库的工具，并提供了动态调试代码的功能。
# 1.动态调试so库中动态注册的函数
首先自己使用Android Studio创建一个C++项目来编译包含动态注册函数的一个Demo,源码链接如下
[动态注册函数Demo](https://github.com/yuhanghuang/Android_reverse/tree/main/JNI_Dynamic2)
运行后的截图
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661168920030-77f1b186-71d0-40b1-b767-9c77e8231218.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=825&id=u516a2114&margin=%5Bobject%20Object%5D&name=image.png&originHeight=825&originWidth=420&originalType=binary&ratio=1&rotation=0&showTitle=false&size=75545&status=done&style=none&taskId=u1bddecec-dd99-4580-a66e-84f97918b34&title=&width=420)
```cpp
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
```
## 1.1 搭建调试环境
可以看到native_hello函数是一个动态注册的函数，具体步骤如下

1. 在手机装完该apk后关闭Android Studio,然后在手机上打开该apk文件。
1. 搭建IDA调试环境，将IDA安装目录下的android_server装到手机上，如果你手机是64位的就把android_server64复制到你的手机上，如果你的手机是32位的就把android_server复制到你的手机上，查看命令为：
```bash
adb shell getprop ro.product.cpu.abi
```
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661169469285-c4480ad8-d6fe-44b9-8126-5a1e44330cf2.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=121&id=u0be74a82&margin=%5Bobject%20Object%5D&name=image.png&originHeight=121&originWidth=768&originalType=binary&ratio=1&rotation=0&showTitle=false&size=9655&status=done&style=none&taskId=u37bf6109-5ad6-4ab8-b6c4-3a90e7a7f44&title=&width=768)
可以看到我的手机架构是ARM下的64位机器，因此需要把android_server64复制到手机上，一般辅助的位置是/data/local/tmp下，建议使用root后的手机。

3. 给该文件添加可执行的权限，在su身份下运行命令
```bash
chmod 777 android_server64
```
接着运行./android_server64就可以运行该文件了。
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661169704976-cc126615-3fa6-41d9-ab80-80a1d4e6362c.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=301&id=uad00f17b&margin=%5Bobject%20Object%5D&name=image.png&originHeight=301&originWidth=942&originalType=binary&ratio=1&rotation=0&showTitle=false&size=41556&status=done&style=none&taskId=u4ce84a1a-7a03-4ba2-9d76-8301bf86877&title=&width=942)
可以看到运行成功了，监听的端口是23946
如果这个端口被占用也可以使用其他端口甚至可以更改该可执行文件名。
```bash
cp android_server64 ida_so
./ida_so -p23333
```

4. 接着就是使用IDA连接该手机，首先打开IDA(不需要加载任何可执行文件),

![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661170110695-e0187c41-1efb-48d0-a904-b4059a5489b6.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=219&id=u9f284944&margin=%5Bobject%20Object%5D&name=image.png&originHeight=219&originWidth=966&originalType=binary&ratio=1&rotation=0&showTitle=false&size=16449&status=done&style=none&taskId=u8720e1c2-7a9c-46d6-b950-c265477ab9b&title=&width=966)
接着选择Remote ARMLinux /Android Debugger，
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661170484916-f5a9eb1e-17fe-4b8c-badc-3e22021ab935.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=323&id=uf46adee1&margin=%5Bobject%20Object%5D&name=image.png&originHeight=323&originWidth=553&originalType=binary&ratio=1&rotation=0&showTitle=false&size=7949&status=done&style=none&taskId=u91cdfbad-24dd-4d67-bb70-a90110b2a90&title=&width=553)
Hostname选择你手机上的IP,Port选择你手机打开android_server64时候的端口号，对于Parameters选项如果你进行有参数的话就填，如果没有还是报错的话就随便填一下或者把警告的弹窗x一下忽略即可。为了方便起见可以将手机与pc端进行端口映射，命令如下
```bash
adb forward tcp:23333 tcp:23946
```
表示将安卓的23946端口映射到PC上的23333端口，因此在调试的时候可以选择如下
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661172410403-6c299b7b-9f8e-4408-b85b-9f53ab793969.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=323&id=uf128ad53&margin=%5Bobject%20Object%5D&name=image.png&originHeight=323&originWidth=556&originalType=binary&ratio=1&rotation=0&showTitle=false&size=7932&status=done&style=none&taskId=u71e80410-00a3-4f31-a62b-5d786e746a8&title=&width=556)
接下来就选择attach到相应的进程，
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661172686349-02d7001a-76c4-4544-ae35-677f1aa41984.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=240&id=u3a4a5a54&margin=%5Bobject%20Object%5D&name=image.png&originHeight=240&originWidth=891&originalType=binary&ratio=1&rotation=0&showTitle=false&size=40498&status=done&style=none&taskId=uc1be666e-3fc6-4c03-9e07-916c643aeef&title=&width=891)
可以看到在apk中打开的进程名字就是“com.example.jin_dynamic2”.
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661172745034-09758ac7-a960-4647-9e9a-55f8278ce8bb.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=651&id=u5423bace&margin=%5Bobject%20Object%5D&name=image.png&originHeight=651&originWidth=538&originalType=binary&ratio=1&rotation=0&showTitle=false&size=11479&status=done&style=none&taskId=ufd06a1bb-c6fd-4b7a-a8cc-bf36781871d&title=&width=538)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661172808259-aa105065-6651-4744-83b8-2ae5b7dae3bb.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=298&id=ue66f9010&margin=%5Bobject%20Object%5D&name=image.png&originHeight=298&originWidth=839&originalType=binary&ratio=1&rotation=0&showTitle=false&size=20877&status=done&style=none&taskId=uc8b4f189-c00e-40fb-a8c3-e74b801a262&title=&width=839)
可以看到确实已经加载出了该so文件。
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661172860922-6a2cd937-3856-476e-b7dd-c48e98182a37.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=566&id=u76ed6002&margin=%5Bobject%20Object%5D&name=image.png&originHeight=566&originWidth=1002&originalType=binary&ratio=1&rotation=0&showTitle=false&size=70775&status=done&style=none&taskId=uf8baac7c-3fe6-4231-936d-2631d82537d&title=&width=1002)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661173005690-c9d9051c-513a-41ea-b0ed-0d9f0d049ab0.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=232&id=ua0f8d0d8&margin=%5Bobject%20Object%5D&name=image.png&originHeight=232&originWidth=845&originalType=binary&ratio=1&rotation=0&showTitle=false&size=15863&status=done&style=none&taskId=ub459e0b5-2402-458b-b00c-85689a89cb6&title=&width=845)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661173063775-4f6648b3-74bf-48c5-86e4-acc497418f60.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=343&id=u39fd1341&margin=%5Bobject%20Object%5D&name=image.png&originHeight=343&originWidth=1775&originalType=binary&ratio=1&rotation=0&showTitle=false&size=49920&status=done&style=none&taskId=ub72d15b3-5dee-40b1-930b-61f79a310ec&title=&width=1775)
然后在该函数的位置下一个断点。F9继续运行程序就可以运行在在我们下的断点处。
# 2.动态调试so库中静态注册的函数
[静态注册函数demo](https://github.com/yuhanghuang/Android_reverse/tree/main/JNI_static2)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661174615354-2fa8f132-f4e1-44eb-a798-651341aba858.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=696&id=uc0cb3388&margin=%5Bobject%20Object%5D&name=image.png&originHeight=696&originWidth=519&originalType=binary&ratio=1&rotation=0&showTitle=false&size=14135&status=done&style=none&taskId=u15cc47a0-42e6-4c08-b2ab-d8d9bca888c&title=&width=519)
![image.png](https://cdn.nlark.com/yuque/0/2022/png/21766399/1661174653283-9374a9e3-9750-445c-b637-a5d0270f90b5.png#clientId=ua1d4de63-00c4-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=213&id=ubf712797&margin=%5Bobject%20Object%5D&name=image.png&originHeight=213&originWidth=829&originalType=binary&ratio=1&rotation=0&showTitle=false&size=9320&status=done&style=none&taskId=u781a7832-8600-45e7-8173-f885c63ad12&title=&width=829)
同样下一个断点也可以进行动态调试。
