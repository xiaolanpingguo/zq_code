#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#继承和多态


#我们先来创建一个动物类
class Animal(object):
    def run(self):
        print('Animal is running...')

#然后再派生出dog和cat类，这两个类就自动拥有了Animal类的Run方法
class Dog(Animal):
    pass

class Cat(Animal):
    pass		
		
dog = Dog()
dog.run()
cat = Cat()
cat.run()	
		
#那现在我们再来改进	
class Dog(Animal):
    def run(self):
        print('Dog is running...')

class Cat(Animal):
    def run(self):
        print('Cat is running...')
#可以看到，Cat和Dog的Run已经重写了Animal的Run方法
dog = Dog()
dog.run()
cat = Cat()
cat.run()

#此时，我们再来看看生成的dog和cat对象是属于什么类型
#因此我们可以总结出来子类既可以看作是本类类型，也可以看作父类的类型
print(isinstance(dog, Dog))	#True
print(isinstance(dog, Animal))	#True


#要理解多态的用处，下面这个例子可以有一个很清楚的认识:
def run_twice(animal):
    animal.run()
run_twice(dog)
run_twice(cat)

#看上去没啥意思，但是仔细想想，现在，如果我们再定义一个Tortoise类型，也从Animal派生：
class Tortoise(Animal):
    def run(self):
        print('Tortoise is running slowly...')		
#因此我们发现，新增一个Animal的子类，不必对run_twice()做任何修改
#实际上，任何依赖Animal作为参数的函数或者方法都可以不加修改地正常运行，原因就在于多态
run_twice(Tortoise())	
		
		