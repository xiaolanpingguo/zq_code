#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from functools import reduce


#高阶函数

#map()
#首先我们来看map。map()函数接收两个参数，一个是函数，一个是Iterable或者Iterator
#map将传入的函数依次作用到序列的每个元素，并把结果作为新的Iterator返回。
#举例说明，比如我们有一个函数f(x)=x2，要把这个函数作用在一个list [1, 2, 3, 4, 5, 6, 7, 8, 9]上，就可以用map()实现如下：
def f(x):
	return x * x

#生成的r是一个generator
r = map(f, [1, 2, 3, 4, 5, 6, 7, 8, 9])
#转成list
print(list(r))

#因为map函数把运算抽象化，因此我们也可以把一个list所有数字转为字符串：
print(list(map(str, [x for x in range(10)])))


#reduce()
#reduce()函数接收两个参数，一个是函数，一个是Iterable或者Iterator
#reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数
#reduce把结果继续和序列的下一个元素做累积计算，其效果就是：
#reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)
#举个例子，对一个序列求和：
#函数必须接受2个参数
def add(x, y):
	return x + y
print(reduce(add, [1, 3, 5, 7, 9]))

#当然求和运算可以直接用Python内建函数sum()，没必要动用reduce。
#但是如果要把序列[1, 3, 5, 7, 9]变换成整数13579，reduce就可以派上用场：
def fn(x, y):
	return x * 10 + y
reduce(fn, [1, 3, 5, 7, 9])

#接下来，我们利用上述函数来写出一个str转int的函数
def fn(x, y):
	return x * 10 + y
def char2num(s):
	return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
print(reduce(fn, map(char2num, '13579')))
#整合成一个函数就是
def str2int(s):
    def fn(x, y):
        return x * 10 + y
    def char2num(s):
        return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
    return reduce(fn, map(char2num, s))
print(str2int("123"))
#再用lamda简化一下
def char2num(s):
    return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
def str2int(s):
    return reduce(lambda x, y: x * 10 + y, map(char2num, s))
print(str2int("123"))



#filter()
#内建的filter()函数用于过滤序列，和map()类似，filter()也接收一个函数和一个序列
#和map()不同的是，filter()把传入的函数依次作用于每个元素，然后根据返回值是True还是False决定保留还是丢弃该元素
#例如，在一个list中，删掉偶数，只保留奇数，可以这么写：
def is_odd(n):
    return n % 2 == 1
print(list(filter(is_odd, [1, 2, 4, 5, 6, 9, 10, 15])))

#把一个序列中的空字符串删掉，可以这么写：
def not_empty(s):
    return s and s.strip()
print(list(filter(not_empty, ['A', '', 'B', None, 'C', '  '])))
#接下来，我们用filter来算100以内的质数
def not_zhishu(n):
	if n == 0 or n == 1:
		return False
	for i in range(2,n // 2):
		if n % i == 0:
			return False
	return True
print(list(filter(not_zhishu, (x for x in range(100) ) ) ))



#sorted()
#sorted()函数是一个高阶函数，接收一个key函数来实现自定义的排序，例如按绝对值大小排序：
print(sorted([36, 5, -12, 9, -21], key=abs))
		
#我们再看一个字符串排序的例子：
['Credit', 'Zoo', 'about', 'bob']
#默认情况下，对字符串排序，是按照ASCII的大小比较的，由于'Z' < 'a'，结果，大写字母Z会排在小写字母a的前面
#现在，我们提出排序应该忽略大小写，按照字母序排序。要实现这个算法，不必对现有代码大加改动，
#只要我们能用一个key函数把字符串映射为忽略大小写排序即可
#忽略大小写来比较两个字符串，实际上就是先把字符串都变成大写（或者都变成小写），再比较
#这样，我们给sorted传入key函数，即可实现忽略大小写的排序：
print(sorted(['bob', 'about', 'Zoo', 'Credit'], key=str.lower))













	