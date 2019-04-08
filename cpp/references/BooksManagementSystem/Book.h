#pragma once
# define NUM1 128
# define NUM2 50

/*
图书管理系统需要创建CBook类，通过CBook类实现图书记录的写入和删除，
还可以通过CBook类查看每条图书的信息。
CBook类中包含m_cName、m_clsbn、m_cPrice和m_cAuthor4个成员变量，
分别代表图书的名称、lSBN编号、价格和作者。
在类设计时，可以将数据成员变量看作属性，这样类中还需要有设置属性和获取属性的成员函数，
设置属性的函数以Set开头，获取属性的函数以Get开头。
*/


class CBook
{
public:
	CBook() {}
	CBook(char* cName, char* clsbn, char* cPrice, char* cAuthor);
	~CBook() {}
public:
	char*  GetName();                // 获取图书名称
	void SetName(char* cName);       // 设置图书名称
	char*  Getlsbn();                // 获取图书ISBN编号
	void Setlsbn(char* clsbn);       // 设置图书ISBN编号
	char*  GetPrice();               // 获取图书价格
	void SetPrice(char* cPrice);     // 设置图书价格
	char*  GetAuthor();              // 获取图书作者
	void SetAuthor(char* cPrice);    // 设置图书作者
	void  WriteData();               // 写入图书
	void  DeleteData(int iCount);    // 删除图书
	void GetBookFromFile(int iCount);   // 查看图书的信息
protected:
	char m_cName[NUM1];
	char m_clsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};
