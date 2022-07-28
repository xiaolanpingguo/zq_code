#include <windows.h>
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

//1）XML文件的根节点是文档本身，即把文件作为一棵树的根结点
//2）文本是一种特殊的节点，一般来说一个节点要设置它的文本，
//   那么这个节点就只应该有这个文件节点不应该有其它子节点
//3）每个节点里面可以带有任意个属性，属性就是键值对

void main()
{
	//新建文档
	TiXmlDocument* doc = new TiXmlDocument();

	//元素
	TiXmlElement* e0 = new TiXmlElement("MMM");
	doc->LinkEndChild(e0);

	TiXmlElement* e1 = new TiXmlElement("abc");
	doc->LinkEndChild(e1);

	TiXmlElement* e2 = new TiXmlElement("def");
	e1->LinkEndChild(e2);

	TiXmlElement* e3 = new TiXmlElement("xyz");
	e1->LinkEndChild(e3);

	//文本
	TiXmlText* t1 = new TiXmlText("ABCDEF");
	e2->LinkEndChild(t1);

	TiXmlText* t2 = new TiXmlText("123456");
	e3->LinkEndChild(t2);

	TiXmlText* t3 = new TiXmlText("你好");
	e0->LinkEndChild(t3);

	//属性
	e2->SetAttribute("年龄", "21");
	e3->SetAttribute("学号", "123");
	e3->SetAttribute("姓名", "jack");

	//保存文档
	doc->SaveFile("hello.xml");

	//删除文档
	delete doc;

	system("pause");
}