#include <windows.h>
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

void main()
{
	//打开文档
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile("hello.xml");

	//得到doc的左孩子
	TiXmlElement* p = doc->FirstChildElement();
	for (; p; p = p->NextSiblingElement())
	{
		std::cout<<p->Value();

		//得到文本
		if (p->GetText())
			std::cout<<":"<<p->GetText()<<std::endl;
		else
			std::cout<<std::endl;

		TiXmlElement* q = p->FirstChildElement();
		for (; q; q = q->NextSiblingElement())
		{
			std::cout<<q->Value();

			//得到文本
			if (q->GetText())
				std::cout<<":"<<q->GetText()<<std::endl;
			else
				std::cout<<std::endl;

			//得到属性
			for (TiXmlAttribute* a = q->FirstAttribute(); a; a = a->Next())
			{
				std::cout<<a->Name()<<" = "<<a->Value()<<std::endl;
			}
		}
	}

	//删除文档
	delete doc;

	system("pause");
}

//atoi
//atof