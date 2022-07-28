#include <iostream>

#define _FLAG_1 0x01 //0000 0001
#define _FLAG_2 0x02 //0000 0010
#define _FLAG_3 0x03 //0000 0011
#define _FLAG_4 0x04 //0000 0100

#define _FLAG_1234  (_FLAG_1 | _FLAG_2|_FLAG_3|_FLAG_4)
//
void main()
{
	int a1 = _FLAG_1 | _FLAG_3;

	//00000111
	//&--------
	//11111101

	//00000101
	//&------
	//11111011

	//00000001
	int a2 = _FLAG_1234 & ~_FLAG_2 & ~_FLAG_4;
}