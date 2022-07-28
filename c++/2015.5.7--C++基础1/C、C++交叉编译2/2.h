#ifndef _2_H_
#define _2_H_

#ifdef __cplusplus
extern "C" //告知下面代码这个void f()函数是C编译出来的
#endif
void f();

#ifdef __cplusplus
extern "C" {
#endif
void f1();
void f2();
void f3();
#ifdef __cplusplus
}
#endif

#endif