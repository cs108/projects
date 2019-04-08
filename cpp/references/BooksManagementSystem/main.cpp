#include<iostream>
#include<iomanip>
#include<stdlib.h>
//include<conio.h>
#include<string.h>
#include<fstream>
#include "Book.h"

#define CMD_COLS 80  
#define CMD_LINES 25 

using namespace std;

/*
除主函数外，系统自定义了许多函数，主要函数及功能如下:
void SetScreenGrid：设置屏幕显示行数和列数。
void ClearScreen：清除屏幕信息。
void SetSysCaption(const char *pText)：设置窗体标题栏。
void Show Welcome：显示欢迎信息。
void ShowRootMenu：显示开始菜单。
void WaitView(int iCurPage):浏览数据时等待用户操作。
void WaitUser：等待用户操作。
void Guidelnput：使用向导添加图书信息。
int GetSelect：获得用户菜单选择。
long GetFileLength(ifstream & ifs)：获取文件长度。
void ViewData(int iSelPage):浏览所有图书记录。
voidDeleteBookFromFile:在文件中产生图书信息。
void mainloop：主循环。
*/
void SetScreenGrid();
void ClearScreen();
void SetSysCaption();
void SetSysCaption(const char *pText);
void ShowWelcome();
void ShowRootMenu();
void WaitView(int  iCurPage);
void WaitUser();
void GuideInput();
int GetSelect();
long GetFileLength(ifstream & ifs);
void ViewData(int iSelPage);
void DeleteBookFromFile();
void mainloop();



void SetScreenGrid()
/*
在控制台中输入mode命令可以设置控制显示信息的行数、列数和背景颜色等信息。
SetScreenGrid函数主要通过system函数来执行mode命令，
CMD_COLS和CMD_LINES是宏定义中的值。
*/
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}


void SetSysCaption()
/*
SetSysCaption函数主要完成在控制台的标题栏上显示Sample信息。
控制台的标题栏信息可以使用title命令来设置，
函数中使用system函数来执行title命令。
*/
{
	system("title Sample");
}



void ClearScreen()
/*
函数ClearScreen主要通过system函数来执行cls命令，
完成控制台屏幕信息的清除。
*/
{
	system("cls");
	// system("cls")包含头文件 #include <stdlib.h>中，
	// 其作用是清楚屏幕先前的显示内容
}



void SetSysCaption(const char *pText)
/*
SetSysCaption函数共有两个版本，这是SetSysCaption函数的另一个版本，
主要实现在控制 台的标题栏上显示指定字符
*/
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}


void ShowWelcome()
/*
ShowWelcome函数在屏幕上显示“图书管理系统”字样的欢迎信息，
“图书管理系统”字样应尽量显示在屏幕的中央位置。
*/
{
	for (int i = 0; i<7; i++)
	{
		cout << endl;
	}
	cout << setw(50);
	cout << "*********************" << endl;
	cout << setw(50);
	cout << "* 图 书 管 理 系 统 *" << endl;
	cout << setw(50);
	cout << "*********************" << endl;
	// std::setw(n)是标准库中的格式化流操作符,位于头文件iomanip中(#include <iomanip>)
	// setw（int n）只对其后面紧跟的输出（<<）产生作用，
	// 是在输出时分配了n个字符的输出宽度，默认填充的内容为空格，
	// 可以setfill()配合使用设置其他字符填充，且默认的是在n个字符宽度中右对齐输出。
	// 若想让它左对齐的话，只需要插入std::left，如下：
	// cout << std::left << "*图书管理系统*" <<  endl;
	// 同理，右对齐只要插入std::right，不过右对齐是默认状态，不必显式声明。
}



void ShowRootMenu()
/*
ShowRootMenu函数主要显示系统的主菜单，
系统中有3个菜单选项，分别是“添加新书”、 “浏览全部”、“删除图书”。
3个菜单选项是进入系统3个模块的入口。
*/
{
	cout << setw(45) << "请选择功能" << endl;
	cout << endl;
	cout << setw(45) << "1 添加新书" << endl;
	cout << endl;
	cout << setw(45) << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(45) << "3 删除图书" << endl;
}


int GetSelect()
/*函数GetSelect主要负责获取用户菜单的选择。*/
{
	char buf[256];
	gets_s(buf);
	// gets() 接受一个字符串，可以接收空格并输出，
	// 注意，不能写成 buf = gets_s();
	// 它与cin的区别在于cin不接受空格，TAB等键的输入，遇到这些键，字符串会终止，
	// 而gets()则接受连续的输入，包括空格，TAB，可以无限读取，不会判断上限，以回车结束读取，
	// 并将读取的结果存放在buffer指针所指向的字符数组中，
	// 换行符不作为读取串的内容，读取的换行符被转换为‘\0’空字符，并由此来结束字符串。
	return atoi(buf);
	// atoi()函数包含在头文件：#include <stdlib.h>中，
	// atoi()函数用来将字符串转换成整数(int)，其原型为int atoi(const char* str);
	// atoi()函数会扫描参数str字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过isspace()函数来检测），
	// 直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，
	// 并返回转换后的整型数；如果str不能转换成int或者str为空字符串，那么将返回0。
}



void GuideInput()
/*
添加图书需要调用函数GuideInput来完成，
需要用户分别输入书名、ISBN编号、价格和作者，
然后利用CBook类构建一个CBook对象，
通过CBook对象的成员函数WriteData将图书信息写入文件。
*/
{
	char inName[NUM1];
	char inlsdn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "请输入书名：" << endl;
	cin >> inName;
	cout << "请输入ISBN：" << endl;
	cin >> inlsdn;
	cout << "请输入价格：" << endl;
	cin >> inPrice;
	cout << "请输入作者：" << endl;
	cin >> inAuthor;
	// 注意:cin不接受空格，TAB等键的输入，遇到这些键，字符串会终止

	CBook book(inName, inlsdn, inPrice, inAuthor);     // 构造一个CBook类对象，并利用构造函数对数据成员初始化
	book.WriteData();
	cout << "Write Finish！" << endl;

	// 等待用户进行下一步处理
	cout << endl;
	cout << "******************************" << endl;
	cout << "请选择接下来的操作（任意键:继续添加新书，q键:退出）：" << endl;
	char buf;
	cin >> buf;
	if (buf == 'q')
		system("exit");
	else
		GuideInput();
}


void WaitUser()
/*
WaitUser函数主要负责当程序完成某一模块的执行后，等待用户进行处理。
用户可以选择返回主菜单，也可以直接退出系统。
*/
{
	int iInputPage = 0;
	cout << "enter返回主菜单，q退出" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
}


void ViewData(int iSelPage)
/*
显示图书信息主要通过函数ViewData来完成。函数ViewData按页数显示图书记录，
每页可以显示20条记录。在函数ViewData中直接使用文件流类打开存储图书信息的文件book.dat,
然后根据页序号读取文件内容，因为每条图书记录的长度相同，
这样就很容易计算出每条记录在文件中的位置，然后将文件指针移动到每页第一条图书记录处，
顺序地从文件中读取20条记录，并将信息显示在屏幕上。
*/
{
	int iPage = 0;              // iPage根据图书数目来确定需要安排几页来显示
	int iCurPage = 0;           // iCurPage表示当前页面数
	int iDataCount = 0;         // iDataCount表示文件中记录的图书数目

	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;

	ifstream ifile;
	// 创建一个未绑定的文件输入流，ifstream是头文件#include<fstream>中定义的一个类型
	ifile.open("book.dat", ios::binary);
	// 打开名为"book.dat"的文件，并将文件与ifstream绑定。
	// 此处文件名（第一个参数）由C风格的字符串常量类型的参数指定，在新的C++标准中，
	// 文件名既可以是库类型string对象，也可以是C风格字符数组。
	// open函数的第二个参数定义了文件的打开模式，读写二进制文件时，
	//  打开方式中必须指定ios::binary，否则读写会出错，总共有如下模式：
	//	ios::in 读
	//	ios::out 写
	//  ios::app  从文件末尾开始写
	//  ios::binary 二进制模式
	//  ios::nocreate	打开一个文件时，如果文件不存在，不创建文件。
	//  ios::noreplace	打开一个文件时，如果文件不存在，创建该文件
	//  ios::trunc	打开一个文件，然后清空内容
	//  ios::ate	打开一个文件时，将位置移动到文件尾
	//  注意：默认模式是文本；默认如果文件不存在，那么创建一个新的文件；
	//  多种模式可以混合，用 | (按位或)； 文件的byte索引从0开始，（就像数组一样）。

	iFileLength = GetFileLength(ifile);         // 获取目标二进制文件的文本长度，即字节数
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);  //根据文件长度，计算文件中总的记录数
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;

	ClearScreen();                 	//清除屏幕信息
	cout << setw(15) << "共有记录:" << iDataCount << " ";
	cout << setw(15) << "共有页数:" << iPage << " ";
	cout << setw(15) << "当前页数:" << iCurPage << " ";
	cout << setw(25) << "n 显示下一页 m 返回" << endl;
	cout << std::left << setw(15) << "lndex";
	cout << std::left << setw(15) << "Name" << std::left << setw(15) << "Isbn";
	cout << std::left << setw(15) << "Price" << std::left << setw(15) << "Author";
	cout << endl;

	// 
	try
	{
		// 根据图书页面编号查找该页面第一本图书在文件中的位置
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);

		// 根据IO类所定义的一些函数和标志，可以帮助我们访问和操纵流的条件状态
		// 部分常用的IO库条件状态为：
		// ifile.eof()：若流ifile的eofbit置位，则返回true；
		// ifile.fail()：若流ifile的failbit或badbit置位，则返回true；
		// ifile.bad()：若流ifile的badbit置位，则返回true；
		// ifile.good()：若流ifile处于有效状态，则返回true；
		// 操作good在所有错误位均未置位的情况下返回true，而bad、fail和eof则在
		// 对应错误位被置位时返回true。此外，在badbit被置位时，fail也会返回true。
		// 这意味着，使用good或fail是确定流的总体状态的正确方法，
		// 常用的确定流对象的状态的方法是：将!ifile.fail()作为条件来使用。
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)   // 循环20次，读取出20条图书信息
			{

				//将变量清零，也就是说将目标数组的给个字节全别赋0
				// memset函数是内存赋值函数，用来给某一块内存空间进行赋值的。 
				// 其原型是：void* memset(void *_Dst, int  _Val, size_t _Size)
				// _Dst是目标起始地址，_Val是要赋的值，_Size是要赋值的字节数。
				// 例如，char inName[128], 我们用memset给数组inName初始化为“0000...0000（128个0）”，
				// 用法如下：memset(inName, 0, sizeof(char) *128);
				// 注意，memset是逐字节拷贝的。
				memset(inName, 0, sizeof(char) * NUM1);
				memset(inlsbn, 0, sizeof(char) * NUM1);
				memset(inPrice, 0, sizeof(char) * NUM2);
				memset(inAuthor, 0, sizeof(char) * NUM2);

				if (ifile.eof())          // 当读到二进制文件的末尾时，将bIndex置为false
				{
					bIndex = false;
				}
				else
					bIndex = true;

				if (bIndex)
					cout << std::right << setw(3) << ((iCurPage - 1) * 20 + i);

				// 我们用read函数和write函数来对二进制文件进行读写
				// read函数常用格式为：文件流对象.read(char *buf,int len);
				// write函数常用格式为：文件流对象.write(const char *buf, int len);
				// 两者格式上差不多，第一个参数是一个字符指针，
				// 用于指向读入读出数据所放的内存空间的其实地址。
				// 第二个参数是一个整数，表示要读入读出的数据的字节数。
				ifile.read(inName, NUM1);	   //读取图书名称
				cout << setw(18) << inName;
				ifile.read(inlsbn, NUM1);	   //读取图书 ISBN 编号
				cout << setw(18) << inlsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(10) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(15) << inAuthor;
				cout << endl;
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}


	if (iCurPage < iPage)
	{
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);      // 等待用户处理
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}



void WaitView(int iCurPage)
{
	char buf[256];
	cin >> buf;
	if (buf[0] == 'q')
		system("exit");
	if (buf[0] == 'm')
		mainloop();
	if (buf[0] == 'n')
		ViewData(iCurPage);
}



long GetFileLength(ifstream& ifs)
/*
函数GetFileLength用来获取文件的长度，函数需要指定一个文件流对象。
该函数的思路是：1.调用ifstream打开一个文件（或者直接传入文件流对象）；
2.调用seekg将get pointer置为文件末尾，seekg(0, ios_base::end)；
3.调用tellg获取总字节数，实际上获取的是get pointer相对于文件头的偏移字节数；
4.重置get pointer，使其指向文件头或者原位置，以便执行其他操作，指向文件头为seekg(0, ios_base::beg)。
*/
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	// tellg（）函数不需要带参数，它返回当前定位指针的位置
	ifs.seekg(0, ios::end);
	// 基地址为文件结束处，偏移地址为0，于是指针定位在文件结束处。
	// seekg（）是对输入文件定位，它有两个参数：第一个参数是偏移量，第二个参数是基地址。
	// 对于第一个参数，可以是正负数值，正的表示向后偏移，负的表示向前偏移。
	// 而第二个参数可以是：
	// ios：：beg：表示输入流的开始位置，文件头；
	// ios：：cur：表示输入流的当前位置；
	// ios：：end：表示输入流的结束位置，文件尾。
	// ifstream，类似istream, 有一个被称为get pointer的指针，指向下一个将被读取的元素。
	respos = ifs.tellg();
	// 因为定位指针在文件结束处，所以ifs.tellg()的值也就是文件的大小，
	// 因为tellg获取总字节数，实际上获取的是get pointer相对于文件头的偏移字节数
	ifs.seekg(tmppos, ios::beg);
	// 基地址为文件头，偏移量为tmppos，于是定位在原来的位置
	return respos;
}



void DeleteBookFromFile()
/*
删除图书主要通过调用函数DeleteBookFromFile来完成，
而在函数DeleteBookFromFile中则主要调用CBook类的DeleteData成员函数来完成。
DeleteData成员函数需要设置删除图书在文件中的顺序编号，
在浏览图书时可以看到此编号。
*/
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}






void mainloop()
/*
main函数是程序的入口，主要调用了SetScreenGrid、SetSysCaption和mainloop3个函数,
其中mainloop函数是主函数，负责模块执行的调度。
*/
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData(1);
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		default:
			break;           // 如果GetSelect()函数的返回值不是1、2、3当中的值，便重新执行while循环。
		}
	}
}


// 主函数
void main()
{
	SetScreenGrid();
	SetSysCaption("图书管理系统");
	mainloop();
}
