static int a;
//此处定义了一个static的变量a，那么1.cpp和2.cpp中
//都同时会出现一个static int a的定义,但这种情况
//不会出现链接错误，因为1.obj发现不了2.obj中的a。
//同理，2.obj发现不了1.obj中的a