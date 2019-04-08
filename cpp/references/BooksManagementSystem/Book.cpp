#include "Book.h"
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>

using namespace std;


CBook::CBook(char* cName, char* clsbn, char* cPrice, char* cAuthor)
{
	strncpy(m_cName, cName, NUM1);
	strncpy(m_clsbn, clsbn, NUM1);
	strncpy(m_cPrice, cPrice, NUM2);
	strncpy(m_cAuthor, cAuthor, NUM2);
	// 函数char* strncpy(char *dest, const char *src, size_t n) 
	// strncpy把src所指向以'\0'结尾的字符串的前n个字符复制到dest所指的数组中，返回指向dest的指针。
	// 当n>=sizeof(src)时，拷贝正确，并在dest字符串后面加入'\0';
	// 当n<sizeof(src)时，只拷贝src前n-1个字符串到dest，不会为dest字符串后面加入'\0';
}

char* CBook::GetName()
{
	return m_cName;
}

void CBook::SetName(char* cName)
{
	strncpy(m_cName, cName, NUM1);
}

char* CBook::Getlsbn()
{
	return m_clsbn;
}

void CBook::Setlsbn(char* clsbn)
{
	strncpy(m_clsbn, clsbn, NUM1);
}

char* CBook::GetPrice()
{
	return m_cPrice;
}

void CBook::SetPrice(char* cPrice)
{
	strncpy(m_cPrice, cPrice, NUM2);
}

char* CBook::GetAuthor()
{
	return m_cAuthor;
}

void CBook::SetAuthor(char* cAuthor)
{
	strncpy(m_cAuthor, cAuthor, NUM2);
}



// 函数WriteData、GetBookFromFile、DeleteData是类对象读写文件的函数，相当于操作数据库的接口。

// 成员函数WriteData主要实现将图书对象写入到文件中。
void CBook::WriteData()
{
	ofstream ofile;
	// 创建一个输出文件流，但是这个文件流并未关联到任何文件
	ofile.open("book.dat", ios::binary | ios::app);
	// 这两句代码定义了一个输出流ofile，流对象的open函数用来打开名为“book.dat”的文件，
	// 并将文件与ofile绑定。第二个参数为ios::app（从文件末尾开始写）|ios::binary（二进制模式），
	// 表示，以二进制模式打开文件，如果没有文件，那么生成空文件；如果有文件，那么在文件尾追加。 
	// 注意，以ios::app方式打开文件，即使修改文件指针，也只能输出到文件尾。
	// 实际上以ios::app打开的文件的写入，和文件指针无关。
	// ios::ate和ios::app的关键区别，ios::app只能在尾部追加，ios::ate可以配合指针修改文件中的部分内容。

	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_clsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
		// 对二进制文件的读写主要用istream类的成员函数read和write来实现。
		// 这两个成员函数的原型为：
		// istream& read(char* buffer, int len);
		// ostream& write(const char* buffer, int len);
		// 字符指针buffer指向内存中一段存储空间。len是读写的字节数。调用的方式为：
		// a.write(p1, 50);
		// b.read(p2, 30);
		// 上面第一行中的a是输出文件流对象，write函数将字符指针p1所给出的地址开始的50个字节的内容不加转换地写到磁盘文件中。
		// 在第二行中，b是输入文件流对象，read函数从b所关联的磁盘文件中，读入30个字节(或遇EOF结束），存放在字符指针p2所指的一段空间内。

	}
	catch (...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();
}


// 成员函数GetBookFromFile能够实现从文件中读取数据来构建对象。
void CBook::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char clsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];

	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	try
	{
		ifile.seekg(iCount*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		ifile.read(cName, NUM1);
		if (ifile.tellg() > 0)
			strncpy(m_cName, cName, NUM1);
		ifile.read(clsbn, NUM1);
		if (ifile.tellg() > 0)
			strncpy(m_clsbn, clsbn, NUM1);
		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0)
			strncpy(m_cPrice, cPrice, NUM2);
		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0)
			strncpy(m_cAuthor, cAuthor, NUM2);
	}
	catch (...)
	{
		throw "file error occurred";
		ifile.close();
	}
	ifile.close();
}




// 成员函数DeleteData负责将图书信息从文件中删除。
void CBook::DeleteData(int iCount)
{
	long respos;                 // 变量respos用来记录当前文件中文本的长度
	int iDataCount = 0;          // 变量iDataCount用来记录当前文件中储存的图书数目

	fstream file;
	fstream tmpfile;
	ofstream ofile;
	// 创建了两个输入输出文件流，一个输出文件流

	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	// 创建一个数组，其空间大小刚好容纳一本图书的信息

	file.open("book.dat", ios::binary | ios::in | ios::out);
	// open函数的第二个参数定义了文件的打开模式，读写二进制文件时，
	//  打开方式中必须指定ios::binary，否则读写会出错，此外还有另外两个模式：
	//	ios::in 读
	//	ios::out 写

	tmpfile.open("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
	//  ios::trunc	打开一个文件，然后清空内容

	file.seekg(0, ios::end);
	respos = file.tellg();
	// 通过将文件指针设置在文件末尾，返回文件末尾到文首的偏移字节数，
	// 于是得到文件的大小，即字节数

	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);
	// 一本图书的信息在文件中占据NUM1 + NUM1 + NUM2 + NUM2个字节
	// 用 文件的总字节数/每本图书所占的字节数 来获得文件中的图书数目

	if (iCount < 0 || iCount > iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		// file.seekg((iCount-1)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		// 将文件指针定位来要查找的图书的首地址处

		file.seekg(0, ios::beg);

		for (int j = 1; j <= iDataCount; j++)
		{
			if (j == iCount)
			{
				file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
			}
			if (!file.eof())
			{
				memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
				// 用NUM1 + NUM1 + NUM2 + NUM2个字节的0来填充数组cTempBuf

				file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
				// 从file所绑定的文件的文件指针处向后读取NUM1 + NUM1 + NUM2 + NUM2个字节的内容
				// 将内容保存在数组cTempBuf中。

				tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
				// 将数组cTempBuf中的相应字节数的内容写入到tmpfile所绑定的磁盘文件中
			}
		}
		file.close();

		tmpfile.seekg(0, ios::beg);
		// 将tmpfile所绑定的文件的文件指针定位到文件首端

		ofile.open("book.dat");
		// 打开名为"book.dat"的文件，并将文件与ofile绑定，它被用来向文件写入数据
		// ofile.seekp((iCount - 1)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);

		ofile.seekp(0, ios::beg);
		// seekp：设置输出文件流的文件流指针位置

		for (int i = 1; i <= iDataCount; i++)
		{
			if (!ofile.eof())
			{
				memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
				tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
				ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			}
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}
