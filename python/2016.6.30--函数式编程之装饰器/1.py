#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

#装饰器

#我们知道函数也是一个对象，其中函数对象在python中
#有一个内置的属性，可以获得函数名
#比如：
def now():
	print('2015-3-25')
print(now.__name__)
f = now
print(f.__name__)

#现在，假设我们要增强now()函数的功能，比如，在函数调用前后自动打印日志，
#但又不希望修改now()函数的定义，这种在代码运行期间动态增加功能的方式，称之为“装饰器”（Decorator）。
#本质上，decorator就是一个返回函数的高阶函数。所以，我们要定义一个能打印日志的decorator，可以定义如下：
def log(func):
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)
    return wrapper
	
#函数倒是定义好了，那我们怎么使用呢
#由于log()是一个decorator，返回一个函数，所以，原来的now()函数仍然存在，只是现在同名的now变量指向了新的函数
#于是调用now()将执行新函数，即在log()函数中返回的wrapper()函数。
#wrapper()函数的参数定义是(*args, **kw)，因此，wrapper()函数可以接受任意参数的调用
#在wrapper()函数内，首先打印日志，再紧接着调用原始函数
@log	#把@log放到now()函数的定义处，相当于执行了语句：now = log(now)
def now():
    print('2015-3-25')
now()

#如果decorator本身需要传入参数，比如，要自定义log的文本
#那就需要编写一个返回decorator的高阶函数，写出来会更复杂
#和两层嵌套的decorator相比，3层嵌套的效果是这样的：
#now = log('execute')(now)
def log1(text):
	def decorator(func):
		def wrapper(*args, **kw):
			print('%s %s():' % (text, func.__name__))
			return func(*args, **kw)
		return wrapper
	return decorator
#那就需要这么调用
@log1('execute')
def now1():
    print('2015-3-25')
now1()


#那下面我们来看看now函数内置__name__属性变没有
print(now1.__name__)	#打印出来是"wrapper"
#出现上面的原因是之前返回的那个wrapper()函数名字就是'wrapper'
#所以，需要把原始函数的__name__等属性复制到wrapper()函数中，否则，有些依赖函数签名的代码执行就会出错
#我们不用编写wrapper.__name__ = func.__name__这样的代码
#Python内置的functools.wraps就是干这个事的，所以，一个完整的decorator的写法如下：

#不带参数的decorator
def log2(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)
    return wrapper

#带参数的decorator
def log3(text):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)
        return wrapper
    return decorator

@log3('execute')
def now2():
    print('2015-3-25')
now2()


#既支持带参和无参，那就用到变参函数了
def log4(*text):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)
        return wrapper
    return decorator
	
@log4()
def now3():
    print('2015-3-25')
now2()





	