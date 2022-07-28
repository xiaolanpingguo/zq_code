#!/usr/bin/env python3
# -*- coding: utf-8 -*-



#文件读写


#读
f = open("1.txt", "rb")	#"r"是以str形式读取的
print(f.read())
f.close()

#但是上述的代码可能会读取一个不存在的文件
#导致抛出一个错误，正确写法应该是这样的：
try:
    f = open('1.txt', 'r')
    print(f.read())
finally:
    if f:
        f.close()
#但是每次都这么写太麻烦了，可以这么写：
with open('1.txt', 'r') as f:
    print(f.read())
	
#相应的函数：read(size)方法，每次最多读取size个字节的内容
#另外，调用readline()可以每次读取一行内容，调用readlines()一次读取所有内容并按行返回list

#前面讲的默认都是读取文本文件，并且是UTF-8编码的文本文件
#要读取二进制文件，比如图片、视频等等，用'rb'模式打开文件即可：
#f = open('1.jpg', 'rb')
#f.read()	b'\xff\xd8\xff\xe1\x00\x18Exif\x00\x00...' # 十六进制表示的字节

#如果要读取非UTF-8编码的文本文件，需要给open()函数传入encoding参数，例如，读取GBK编码的文件：
#f = open('1.txt', 'r', encoding='gbk')
#f.read()

#遇到有些编码不规范的文件，你可能会遇到UnicodeDecodeError，因为在文本文件中可能夹杂了一些非法编码的字符
#遇到这种情况，open()函数还接收一个errors参数，表示如果遇到编码错误后如何处理。最简单的方式是直接忽略：
#f = open('1.txt', 'r', encoding='gbk', errors='ignore')


#写

#写文件和读文件是一样的，唯一区别是调用open()函数时，传入标识符'w'或者'wb'表示写文本文件或写二进制文件：
f = open('1.txt', 'w')
f.write('Hello, world!')
f.close()
#你可以反复调用write()来写入文件，但是务必要调用f.close()来关闭文件
#当我们写文件时，操作系统往往不会立刻把数据写入磁盘，而是放到内存缓存起来，空闲的时候再慢慢写入
#只有调用close()方法时，操作系统才保证把没有写入的数据全部写入磁盘
#忘记调用close()的后果是数据可能只写了一部分到磁盘，剩下的丢失了。所以，还是用with语句来得保险：
with open('1.txt', 'w', encoding='utf-8') as f:
    f.write('Hello, world!')
#要写入特定编码的文本文件，请给open()函数传入encoding参数，将字符串自动转换成指定编码
#使用with语句操作文件IO是个好习惯。



#StringIO和BytesIO

#写StringIO
#很多时候，数据读写不一定是文件，也可以在内存中读写
#StringIO顾名思义就是在内存中读写str
#要把str写入StringIO，我们需要先创建一个StringIO，然后，像文件一样写入即可：
from io import StringIO
f = StringIO()
f.write('hello')	#5
f.write(' ')	#1
f.write('world!')	#6
print(f.getvalue())	

#读StringIO
#要读取StringIO，可以用一个str初始化StringIO，然后，像读文件一样读取：
f = StringIO('Hello!\nHi!\nGoodbye!')
while True:
    s = f.readline()
    if s == '':
        break
    print(s.strip())


#BytesIO
#StringIO操作的只能是str，如果要操作二进制数据，就需要使用BytesIO。
#BytesIO实现了在内存中读写bytes，我们创建一个BytesIO，然后写入一些bytes：
from io import BytesIO
f = BytesIO()
f.write('中文'.encode('utf-8'))	#6
print(f.getvalue())	#b'\xe4\xb8\xad\xe6\x96\x87'

#请注意，写入的不是str，而是经过UTF-8编码的bytes。
#和StringIO类似，可以用一个bytes初始化BytesIO，然后，像读文件一样读取：
f = BytesIO(b'\xe4\xb8\xad\xe6\x96\x87')
f.read()	#b'\xe4\xb8\xad\xe6\x96\x87'

