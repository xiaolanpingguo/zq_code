#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import Iterable
from collections import Iterator

#迭代
#在pyhton中，一切可以用for作用于一个对象时，就称这个对象
#为可迭代对象，tuple,list,str,或者dict等
#那如何才判断一个对象是不是可迭代对象呢，
#可以通过collections模块的Iterable类型判断
print(isinstance('abc', Iterable)) # str是否可迭代，True
print(isinstance([1,2,3], Iterable)) # list是否可迭代,True
print(isinstance(123, Iterable)) # 整数是否可迭代,False

#迭代dict，注：迭代dict时，元素顺序可能不一样
#按key迭代dict
d = {'a': 1, 'b': 2, 'c': 3}
for key in d:
	print(key)
#按value迭代dict
for value in d.values():
	print(value)
#key和value同事迭代
for k,v in d.items():
	print(k, v)
	
#用下标来迭代list
#Python内置的enumerate函数可以把一个list变成索引-元素对，这样就可以在for循环中同时迭代索引和元素本身
for i, value in enumerate((10,20,30)):
	print(i, value)
	
	
#列表生成式
#举个例子：要生成list [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]可以用list(range(1, 11))：
#但如果要生成[1x1, 2x2, 3x3, ..., 10x10]怎么做
#1：采用循环：
a = []
for x in range(1, 11):
	a.append(x * x)
print(a)
#所以还是那句话，你觉得这样写代码很多，
#那么就可以用列表生成式一句话搞定
print([x * x for x in range(1,5) ])
#还可以进行筛选，把偶数筛选出来
print([x * x for x in range(1,5) if x % 2 == 0])
#还可以使用两层循环生产全排列
print([m + n for n in 'abc' for m in 'xyz'])
#最后，还可以把一个list中所有单词变为小写
print([s.lower() for s in ['Hello', 'WORLD']])
#混合使用
print([v.lower() for v in ['Hello', 'World', 18, 'Apple', None] if type(v) is str])
#所以经过上面例子可以看出，列表生成式无非就是把多行代码变为一行代码，然后用
#列表的[]括起来而已


#生产器与迭代器
#通过列表生成式，我们可以直接创建一个列表。但是，受到内存限制，列表容量肯定是有限的
#所以，如果列表元素可以按照某种算法推算出来，那我们是否可以在循环的过程中不断推算出后续的元素呢？
#在Python中，这种一边循环一边计算的机制，称为生成器：generator。
#要创建一个generator，有很多种方法。第一种方法很简单，只要把一个列表生成式的[]改成()，就创建了一个generator

#创建list和generator的区别仅在于最外层的[]和()
print([x * x for x in range(10)])	#[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
g = (x * x for x in range(10))	#<generator object <genexpr> at 0x1022ef630>

#那我们怎么打印generator的每一个元素呢，可以通过next()获得generator的下一个元素
print(next(g))	#0
print(next(g))	#1

#其中generator本质保存的是算法，每次调用next(g)，就计算出g的下一个元素的值，
#直到计算到最后一个元素，没有更多的元素时，抛出StopIteration的错误
#但是如果采用上面的next()一行一行来获得元素，不免太麻烦，那就可以用for
for n in g:
	print(n)	#再次注意，因为generator本质保存的是算法，所以这里打印是从4开始的
	
	
#从上面可以看出generator也是可迭代对象，还可以被next()函数不断调用并返回下一个值
#可以被next()函数调用并不断返回下一个值的对象称为迭代器：Iterator
#同样的，可以使用isinstance()判断一个对象是否是Iterator对象
print(isinstance((x for x in range(10)), Iterator))	#True
print(isinstance([], Iterator))						#False
print(isinstance({}, Iterator))						#False
print(isinstance('abc', Iterator))					#False

#生成器都是Iterator对象，但list、dict、str虽然是Iterable，却不是Iterator
#把list、dict、str等Iterable变成Iterator可以使用iter()函数：
print(isinstance(iter([]), Iterator))				#True
print(isinstance(iter('abc'), Iterator))			#True



#用生成器实现斐波那契数列
#1, 1, 2, 3, 5, 8, 13, 21, 34, ...
def fib(num):
	a = 0
	b = 1
	for i in range(num):
		print(b)
		a, b = b, a+b
fib(6)
#把上述函数改成generator
#如果一个函数定义中包含yield关键字，那么这个函数就不再是一个普通函数，而是一个generator：
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'
#因为是一个generator，所以得这样调用
for n in fib(6):
	print(n)
#但是用for循环调用generator时，发现拿不到generator的return语句的返回值
#如果想要拿到返回值，必须捕获StopIteration错误，返回值包含在StopIteration的value中：
g = fib(6)
while True:
	try:
		x = next(g)
		print('g:', x)
	except StopIteration as e:
		print('Generator return value:', e.value)
		break








		













	