#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

#偏函数

#我们先来看第一个问题，如果要把str转换成数字需要怎么做：
#很明显这么做
print(int("123"))

#那好，转换成功，但是我不想转成十进制，我想转成2进制怎么办
#也可以
print(int("10",base = 2))

#但如果程序需要大量用到这个转换，那就可以定义成函数：
def int2(x, base=2):
    return int(x, base)
print(int2('1000000'))

#但是python有一个东西可以不用创建上面那个函数，
#直接用下面这个代码就可以创建跟上面功能等同的函数
int2 = functools.partial(int, base=2)
print(int2('1000000'))

#所以，functools.partial的作用就是，把一个函数的某些参数给固定住（也就是设置默认值）
#返回一个新的函数，调用这个新函数会更简单。
#注意到上面的新的int2函数，仅仅是把base参数重新设定默认值为2，但也可以在函数调用时传入其他值：
print(int2('1000000', base=10))

#最后，创建偏函数时，实际上可以接收函数对象、*args和**kw这3个参数，当传入：
#int2 = functools.partial(int, base=2)
#实际上固定了int()函数的关键字参数base，也就是：int2('10010')
#相当于：
kw = { 'base': 10 }
print(int('10010', **kw))


#最后一个例子
a = (5, 6, 7)
#现在我要求a中的最大值，但是我调用的时候又想加一个数
#那就可以这样：
max2 = functools.partial(max, 100)	#实际上会把10作为*args的一部分自动加到左边，也就是
print(max2(*a))


	