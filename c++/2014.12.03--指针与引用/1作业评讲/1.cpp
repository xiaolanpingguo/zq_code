#include<iostream>

void main()
{
	////01)
	//char a1,a2;
	//short b1,b2;
	//int c1,c2;
	//double d1,d2;
	//char e[15];//1 + 2 + 4 + 8
	//std::cout<<"请输入a1（char）";
	//std::cin>>a1;
	//std::cout<<"请输入b1（short）";
	//std::cin>>b1;
	//std::cout<<"请输入c1（int）";
	//std::cin>>c1;
	//std::cout<<"请输入d1（double）";
	//std::cin>>d1;
	//*e = a1;//e[0] = a1;
	//*((short*)(e + 1)) = b1;
	////((short*)(e + 1))[0] = b1;
	//*((int*)(e + 3)) = c1;
	//*((double*)(e + 7)) = d1;

	////传递到a2,b2,c2,d2
	//a2 = *e;
	//b2 = *((short*)(e + 1));
	//c2 = *((int*)(e + 3));
	//d2 = *((double*)(e + 7));

	//02)
	//double a;
	///*bool b = false;*/
	//char* p = (char*)&a;
	////char p[8];
	//for(int i = 0; i < 8; ++i)
	//{
	//	std::cin>>p[i];
	//}
	//方法1
	//bool bz = false;
	//for(int i = 0; i < 7; ++i)
	//{
	//	for(int j = i + 1;j < 8; ++j)
	//	{
	//		if(p[i] == p[j])
	//		{
	//			bz = true;
	//			break;
	//		}
	//	}
	//}
	//if(bz)
	//{
	//
	//}
	//else
	//{
	//
	//}

	//方法2
	//bool bz = false;
	//char x[256] = {};
	//for(int i = 0; i < 8;++i)
	//{
	//	//-128->127 + 128 ->0 - >255
	//	if(x[p[i] + 128] == 0)
	//	{
	//		x[p[i] + 128] = 1;
	//	}
	//	else
	//	{
	//		bz = true;
	//		break;
	//	}
	//}

	//03)
	int a;
	std::cin>>a;
	unsigned char* p = (unsigned char*)&a;
	
	//p[0] - p[3]
	int c;
	for(int i = 0; i < 4; ++i)
	{
		int b[2] = {};
		c = 0;
		while(p[i])
		{
			b[c] = p[i] % 16;
			p[i] /= 16;
			c+=1;
		}
		std::cout<<"0123456789ABCDEF"[b[1]]<<"0123456789ABCDEF"[b[0]]<<" ";
	}
	system("pause");
}
