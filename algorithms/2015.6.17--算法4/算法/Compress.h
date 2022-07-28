#ifndef _COMPRESS_H_
#define _COMPRESS_H_

//如果p2为0，则本函数会通过len2返回压缩之后的内存总字节数
//如果p2不为，则本函数会将压缩之后的数据放入到p2指向的内存中
void RLE_Compress(const void* p1, //输入的内存
				  int len1, //输入的内存总字节数
				  void* p2, //输出的内存
				  int* len2); //输出的内存总字节数

#endif