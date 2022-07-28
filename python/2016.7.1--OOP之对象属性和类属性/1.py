#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#实例属性和类属性


class Student(object):
    def __init__(self, name):
        self.name = name

#这个是给一个实例绑定属性
s = Student('Bob')
s.score = 90
		
#但是现在我们需要给整个类绑定一个属性呢，可以这么做：
class Student(object):
    name = 'Student'
	
s = Student() # 创建实例s
print(s.name) # 打印name属性，因为实例并没有name属性，所以会继续查找class的name属性，打印Student
print(Student.name) # 打印类的name属性，打印Student
s.name = 'Michael' # 给实例绑定name属性
print(s.name) # 由于实例属性优先级比类属性高，因此，它会屏蔽掉类的name属性，打印Michael
print(Student.name) # 但是类属性并未消失，用Student.name仍然可以访问，打印Student
del s.name # 如果删除实例的name属性
print(s.name) # 再次调用s.name，由于实例的name属性没有找到，类的name属性就显示出来了，打印Student

#也可以删除类的name属性，不过删除后，再次访问就会提示没有这个属性了
#del Student.name
#print(Student.name)

#这里可以再次赋值
Student.name = "zhang"
print(s.name)	#打印"zhang



#获取对象信息
#当我们拿到一个对象的引用时，如何知道这个对象是什么类型、有哪些方法呢

#1.使用type(),比如：
print(type(123))	#int
print(type("123"))	#str
print(type(abs))	#builtin_function_or_method
#如果一个变量指向函数或者类，也可以用type()判断
print(type(s))		#__main__.Student

#2.使用isinstance()
print(isinstance(123,int))		#True
print(isinstance(s,Student))	#True
#也可以判断一个变量是否是某些类型中的一种，比如下面就判断是否是list或者tuple：
print(isinstance([1, 2, 3], (list, tuple)))	#True

#3.使用dir()
#如果要获得一个对象的所有属性和方法，可以使用dir()函数
#它返回一个包含字符串的list，比如，获得一个str对象的所有属性和方法：
print(dir('ABC'))
['__add__', '__class__', '__contains__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', 
'__getitem__', '__getnewargs__', '__gt__', '__hash__', '__init__', '__iter__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', 
'__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', 
'__subclasshook__', 'capitalize', 'casefold', 'center', 'count', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'format_map',
 'index', 'isalnum', 'isalpha', 'isdecimal', 'isdigit', 'isidentifier', 'islower', 'isnumeric', 'isprintable', 'isspace', 'istitle', 
 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'maketrans', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 
 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
 
#类似__xxx__的属性和方法在Python中都是有特殊用途的，比如__len__方法返回长度。在Python中
#如果你调用len()函数试图获取一个对象的长度，实际上，在len()函数内部
#它自动去调用该对象的__len__()方法，所以，下面的代码是等价的：
print(len('ABC'))	#3
print('ABC'.__len__())	#3


#我们自己写的类，如果也想用len(myObj)的话，就自己写一个__len__()方法：
class MyDog(object):
	def __len__(self):
		return 100
dog = MyDog()
len(dog)	#100

#仅仅把属性和方法列出来是不够的，配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态：
class MyObject(object):
	def __init__(self):
		self.x = 9
	def power(self):
		return self.x * self.x
obj = MyObject()

#紧接着，我们来测试该对象的属性：
print(hasattr(obj, 'x')) # 有属性'x'吗？True
print(hasattr(obj, 'y')) # 有属性'y'吗？False
print(setattr(obj, 'y', 19)) # 设置一个属性'y'
print(hasattr(obj, 'y')) # 有属性'y'吗？True
print(getattr(obj, 'y')) # 获取属性'y'，19
print(obj.y)# 获取属性'y'，19

#如果试图获取不存在的属性，会抛出AttributeError的错误：
#getattr(obj, 'z') # 获取属性'z',Traceback (most recent call last):AttributeError: 'MyObject' object has no attribute 'z'

#但是我们可以传入一个default参数，如果属性不存在，就返回默认值：
print(getattr(obj, 'z', 404)) # 获取属性'z'，如果不存在，返回默认值404


#也可以获得对象的方法：
print(hasattr(obj, 'power')) # 有属性'power'吗？True
print(getattr(obj, 'power')) # 获取属性'power',<bound method MyObject.power of <__main__.MyObject object at 0x10077a6a0>>
fn = getattr(obj, 'power') # 获取属性'power'并赋值到变量fn
print(fn()) # 调用fn()与调用obj.power()是一样的,81


#要注意的是，只有在不知道对象信息的时候，我们才会去获取对象信息。如果可以直接写：
sum = obj.x + obj.y
#就不要写：
sum = getattr(obj, 'x') + getattr(obj, 'y')

#下面说一个正确的用法的例子如下：
#假设我们希望从文件流fp中读取图像，我们首先要判断该fp对象是否存在read方法
#如果存在，则该对象是一个流，如果不存在，则无法读取。hasattr()就派上了用场
#请注意，在Python这类动态语言中，根据鸭子类型，有read()方法，不代表该fp对象就是一个文件流
#它也可能是网络流，也可能是内存中的一个字节流，但只要read()方法返回的是有效的图像数据，就不影响读取图像的功能
def readImage(fp):
    if hasattr(fp, 'read'):
        return readData(fp)
    return None
	





