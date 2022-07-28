#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#类


#现在我们来创建一个类，就叫Student吧，我们先什么都不做
class Student(object):
	pass
	
#然后我们创建类的对象
obj1 = Student()
print(obj1)
#给该对象绑定一个name属性
obj1.name = "zhang"
print(obj1.name)

#然后我们再创建第二个类的对象
#但我们看下第二个对象有没name属性
obj2 = Student()
#很遗憾，该对象没绑定name属性的话，是没有的
#也就是说一个对象的属性需要自己定义出来后绑定
#print(obj2.name)

#要解决上面的问题，我们可以这样定义一个类
#注意到__init__方法，它会在类对象创建的时候自动调用，它的第一个参数永远是self，表示创建的实例本身
#因此，在__init__方法内部，就可以把各种属性绑定到self，因为self就指向创建的实例本身。
#有了__init__方法，在创建实例的时候，就不能传入空的参数了
#必须传入与__init__方法匹配的参数，但self不需要传，Python解释器自己会把实例变量传进去：
class Student(object):
    def __init__(self, name, score):
        self.name = name
        self.score = score
		
#这样每个对象创建的时候就有了对应属性
obj1 = Student("zhang", 100)
obj2 = Student("qi", 100)
print(obj1.name, obj2.name)


#访问权限
#现在我们又变了，我们不想让name属性变为公有的，变为私有的怎么办
#可以把属性的名称前加上两个下划线__，在Python中，实例的变量名如果以__开头
#就变成了一个私有变量（private），只有内部可以访问，外部不能访问，所以，我们把Student类改一改：
class Student(object):

    def __init__(self, name, score):
        self.__name = name
        self.__score = score
		
#现在我们发现，这个变量已经访问不了了，提示这个类没有这个name属性
obj1 = Student("zhang", 100)
#print(obj1.name)
#但实际上，不能直接访问__name是因为Python解释器对外把__name变量改成了_Student__name
#所以，仍然可以通过_Student__name来访问__name变量：
print(obj1._Student__name)	
#但是强烈建议不要这么干，因为不同版本的Python解释器可能会把__name改成不同的变量名
#总的来说就是，Python本身没有任何机制阻止你干坏事，一切全靠自觉

		
		
		
		
		
		
		
		
		
		
		