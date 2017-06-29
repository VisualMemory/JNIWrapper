# JNIWrapper
A simple JNI wrapper. (java in C++)

JNI introduction:

Detail tech docs:
http://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/jniTOC.html
https://www.ibm.com/developerworks/java/tutorials/j-jni/j-jni.html

Copy from Oracle doc:
Overview
The following code example illustrates how to use functions in the Invocation API. In this example, the C++ code creates a Java VM and invokes a static method, called Main.test. For clarity, we omit error checking.

    #include <jni.h>       /* where everything is defined */
    ...
    JavaVM *jvm;       /* denotes a Java VM */
    JNIEnv *env;       /* pointer to native method interface */
    JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = "-Djava.class.path=/usr/lib/java";
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    /* load and initialize a Java VM, return a JNI interface
     * pointer in env */
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;
    /* invoke the Main.test method using the JNI */
    jclass cls = env->FindClass("Main");
    jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V");
    env->CallStaticVoidMethod(cls, mid, 100);
    /* We are done. */
    jvm->DestroyJavaVM();

This example uses three functions in the API. The Invocation API allows a native application to use the JNI interface pointer to access VM features. The design is similar to Netscape’s JRI Embedding Interface.

Creating the VM

The JNI_CreateJavaVM() function loads and initializes a Java VM and returns a pointer to the JNI interface pointer. The thread that called JNI_CreateJavaVM() is considered to be the main thread.

Attaching to the VM

The JNI interface pointer (JNIEnv) is valid only in the current thread. Should another thread need to access the Java VM, it must first call AttachCurrentThread() to attach itself to the VM and obtain a JNI interface pointer. Once attached to the VM, a native thread works just like an ordinary Java thread running inside a native method. The native thread remains attached to the VM until it calls DetachCurrentThread() to detach itself.

The attached thread should have enough stack space to perform a reasonable amount of work. The allocation of stack space per thread is operating system-specific. For example, using pthreads, the stack size can be specified in the pthread_attr_t argument to pthread_create.

Detaching from the VM

A native thread attached to the VM must call DetachCurrentThread() to detach itself before exiting. A thread cannot detach itself if there are Java methods on the call stack.
