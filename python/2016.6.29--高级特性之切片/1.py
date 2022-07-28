#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#切片

#一个列表或者tuple，如果要取前2个元素，怎么取
a = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']

#1.最容易想到的
print(a[0], a[1])
#2.循环
for i in range(2):
	print(a[i])
	
#还有没呢？python提供了切片的方法，可以用切片
print(a[:3])
#切片的索引位置默认从0开始到n-1
#b = a[:n]

#也可以用负数索引，-1代表倒数第一个元素，依次为-2，-3..
print(a[-4:])	#这样的话默认从-4到-1

#还可以间隔取元素，比如
#先创建一个10个元素列表
a = list(range(10))
#从第一个元素开始，每隔2个元素取一次
print(a[0:10:2])
#取所有元素，每隔2个元素取一次
print(a[::2])















	