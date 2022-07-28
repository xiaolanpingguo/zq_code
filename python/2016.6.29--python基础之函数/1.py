#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#可变参数
#在参数前面加了一个*号即可。但是在函数内部，参数numbers接收到的是一个tuple，
#因此，函数代码完全不变。但是，调用该函数时，可以传入任意个参数，包括0个参数
def sum(*number):
	sum = 0
	for i in number:
		sum += i
	return sum
	
print(sum(1,2,3))

#但是如果参数本身就是一个tuple或者是一个list呢
#print(sum([1,2,3])) #这句代码报错，说类型错误，传入的是list，list不能相加

#所以要解决上面的问题，就要在一个tuple或者list前面加上一个*号，
#这样就把list或tuple的元素变成可变参数传进去
print(sum(*(1,2,3)))


#关键字参数
#关键字参数允许你传入0个或任意个含参数名的参数，这些关键字参数在函数内部自动组装为一个dict，例子如下：
def person(name, age, **kw):
    print('name:', name, 'age:', age, 'other:', kw)

#调用时，可以只填必选参数
person("zhang", 12)
#也可以填上可选参数，此时python在内部将可选参数组装为一个dict
person('Bob', 35, city='Beijing')

#当然，既然最后是组装成一个dict，我们在传入的时候就可以传入一个dict
extra = {'city': 'Beijing', 'job': 'Engineer'}
person('Jack', 24, city=extra['city'], job=extra['job'])

#但我们不能这样调用，必须以关键字参数传入，就像上面一样，但这样就很麻烦，代码很多
#所以我们可以这样，来省掉代码量
#**extra表示把extra这个dict的所有key-value用关键字参数传入到函数的**kw参数，
#kw将获得一个dict，注意kw获得的dict是extra的一份拷贝，对kw的改动不会影响到函数外的extra
person('Jack', 24, **extra)



#命名关键字参数
#但是对于上面的关键字参数，函数的调用者可以传入任意不受限制的关键字参数
#至于到底传入了哪些，就需要在函数内部通过kw检查
#接下来我们改下上面的person函数
def person1(name, age, **kw):
    if 'city' in kw:
        # 有city参数
        pass
    if 'job' in kw:
        # 有job参数
        pass
    print('name:', name, 'age:', age, 'other:', kw)
person1('Jack', 24, city='Beijing', addr='Chaoyang', zipcode=123456)

#但如果我们只接收某些关键字呢，例如，只接收city和job作为关键字参数，可以这样定义：
#和关键字参数**kw不同，命名关键字参数需要一个特殊分隔符*，*后面的参数被视为命名关键字参数。
def person2(name, age, *, city, job):
    print(name, age, city, job)
#但是调用的时候，关键字参数不能多不能少也不能写错，否则报错
person2('Jack', 24, city='Beijing', job='Engineer')
#person2('Jack', 24, city='Beijing') 错误，缺少job关键字
#person2('Jack', 24, city='Beijing', job1='Engineer') 错误，没有job1关键字


#接下来，我们来混合使用，我们把分隔符*换成可变参数
def person3(name, age, *args, city, job):
    print(name, age, args, city, job)
#调用的时候，关键字参数不能多不能少也不能写错，否则报错
#可变参数还是跟上述一样，python内部会把它转换成tuple
person3('Jack', 24, city='Beijing', job='Engineer')
person3('Jack', 24, *[1,2,3], city='Beijing', job='Engineer')
#person3('Jack', 24, city='Beijing') #错误，缺少job关键字
#person2('Jack', 24, city='Beijing', job1='Engineer') #错误，没有job1关键字



#参数组合
#在Python中定义函数，可以用必选参数、默认参数、可变参数、关键字参数和命名关键字参数，
#这5种参数都可以组合使用。但是请注意，参数定义的顺序必须是：必选参数、默认参数、可变参数、命名关键字参数和关键字参数。
#比如定义一个函数，包含上述若干种参数：

#必选参数，默认参数，可变参数，关键字参数
def f1(a, b, c=0, *args, **kw):
    print('a =', a, 'b =', b, 'c =', c, 'args =', args, 'kw =', kw)
	
#必选参数，默认参数，可变参数，命名关键字参数
def f2(a, b, c=0, *, d, **kw):
    print('a =', a, 'b =', b, 'c =', c, 'd =', d, 'kw =', kw)

#在函数调用的时候，Python解释器自动按照参数位置和参数名把对应的参数传进去。
f1(1, 2) 						#a = 1 b = 2 c = 0 args = () kw = {}
f1(1, 2, c=3)					#a = 1 b = 2 c = 3 args = () kw = {}
f1(1, 2, 3, 'a', 'b')			#a = 1 b = 2 c = 3 args = ('a', 'b') kw = {}
f1(1, 2, 3, 'a', 'b', x=99)		#a = 1 b = 2 c = 3 args = ('a', 'b') kw = {'x': 99}
f2(1, 2, d=99, ext=None)		#a = 1 b = 2 c = 0 d = 99 kw = {'ext': None}

















	