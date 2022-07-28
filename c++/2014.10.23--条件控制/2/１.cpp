#include<iostream>

//流程控制语句
//01)分支语句：switch-case-break-default,if-else
//02）循环语句：do-while ,while ,for
//03）跳转语句：break,continue,return,goto

void main()
{
	int a;
	std::cin>>a;

	switch(a)
	{
	case 1:
		{
			std::cout<<"1"<<std::endl;
		}
		break;
	case 2:
		{
			std::cout<<"2"<<std::endl;
		}
		break;
	default:
		{
			std::cout<<"其他"<<std::endl;
		}
		break;
	}

	//switch ：开关，选择
	//case:情况，案件
	//break:破坏，跳出
	//default：默认。缺省

	//switch(A)
	//{
	//case 常量1：B;break;
	//case 常量2：C;break;
	//case 常量3：D;break;
	//case 常量4：E;break;
	//defaule:F;break;
	//}
	//G;
	//执行A，将A的结果依次与其后每个case后面的常量
	//表达式的结果（不允许有重复，结果类型必须是整数（
	//含字符，布尔））进行相等判断
	//01）与某个case后面的常量表达式的结果相等
	//则执行该case后面写的所有的语句，之后的case就
	//不在进行相等判断，也就是说再往回所有的case语句都
	//无条件执行，直到遇到break，跳出整个switch语句块，
	//02）与所有的case后面的常量表达式的结果都不相等
	// 有default语句就执行default语句块中的代码。没有则
	//什么都不执行。

	//case后的常量表达式的结果必须是整数，不能重复
	//每个case结束后必须写break
	system("pause");
}