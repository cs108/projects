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
���������⣬ϵͳ�Զ�������ຯ������Ҫ��������������:
void SetScreenGrid��������Ļ��ʾ������������
void ClearScreen�������Ļ��Ϣ��
void SetSysCaption(const char *pText)�����ô����������
void Show Welcome����ʾ��ӭ��Ϣ��
void ShowRootMenu����ʾ��ʼ�˵���
void WaitView(int iCurPage):�������ʱ�ȴ��û�������
void WaitUser���ȴ��û�������
void Guidelnput��ʹ�������ͼ����Ϣ��
int GetSelect������û��˵�ѡ��
long GetFileLength(ifstream & ifs)����ȡ�ļ����ȡ�
void ViewData(int iSelPage):�������ͼ���¼��
voidDeleteBookFromFile:���ļ��в���ͼ����Ϣ��
void mainloop����ѭ����
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
�ڿ���̨������mode����������ÿ�����ʾ��Ϣ�������������ͱ�����ɫ����Ϣ��
SetScreenGrid������Ҫͨ��system������ִ��mode���
CMD_COLS��CMD_LINES�Ǻ궨���е�ֵ��
*/
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}


void SetSysCaption()
/*
SetSysCaption������Ҫ����ڿ���̨�ı���������ʾSample��Ϣ��
����̨�ı�������Ϣ����ʹ��title���������ã�
������ʹ��system������ִ��title���
*/
{
	system("title Sample");
}



void ClearScreen()
/*
����ClearScreen��Ҫͨ��system������ִ��cls���
��ɿ���̨��Ļ��Ϣ�������
*/
{
	system("cls");
	// system("cls")����ͷ�ļ� #include <stdlib.h>�У�
	// �������������Ļ��ǰ����ʾ����
}



void SetSysCaption(const char *pText)
/*
SetSysCaption�������������汾������SetSysCaption��������һ���汾��
��Ҫʵ���ڿ��� ̨�ı���������ʾָ���ַ�
*/
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}


void ShowWelcome()
/*
ShowWelcome��������Ļ����ʾ��ͼ�����ϵͳ�������Ļ�ӭ��Ϣ��
��ͼ�����ϵͳ������Ӧ������ʾ����Ļ������λ�á�
*/
{
	for (int i = 0; i<7; i++)
	{
		cout << endl;
	}
	cout << setw(50);
	cout << "*********************" << endl;
	cout << setw(50);
	cout << "* ͼ �� �� �� ϵ ͳ *" << endl;
	cout << setw(50);
	cout << "*********************" << endl;
	// std::setw(n)�Ǳ�׼���еĸ�ʽ����������,λ��ͷ�ļ�iomanip��(#include <iomanip>)
	// setw��int n��ֻ�����������������<<���������ã�
	// �������ʱ������n���ַ��������ȣ�Ĭ����������Ϊ�ո�
	// ����setfill()���ʹ�����������ַ���䣬��Ĭ�ϵ�����n���ַ�������Ҷ��������
	// �������������Ļ���ֻ��Ҫ����std::left�����£�
	// cout << std::left << "*ͼ�����ϵͳ*" <<  endl;
	// ͬ���Ҷ���ֻҪ����std::right�������Ҷ�����Ĭ��״̬��������ʽ������
}



void ShowRootMenu()
/*
ShowRootMenu������Ҫ��ʾϵͳ�����˵���
ϵͳ����3���˵�ѡ��ֱ��ǡ�������顱�� �����ȫ��������ɾ��ͼ�顱��
3���˵�ѡ���ǽ���ϵͳ3��ģ�����ڡ�
*/
{
	cout << setw(45) << "��ѡ����" << endl;
	cout << endl;
	cout << setw(45) << "1 �������" << endl;
	cout << endl;
	cout << setw(45) << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(45) << "3 ɾ��ͼ��" << endl;
}


int GetSelect()
/*����GetSelect��Ҫ�����ȡ�û��˵���ѡ��*/
{
	char buf[256];
	gets_s(buf);
	// gets() ����һ���ַ��������Խ��տո������
	// ע�⣬����д�� buf = gets_s();
	// ����cin����������cin�����ܿո�TAB�ȼ������룬������Щ�����ַ�������ֹ��
	// ��gets()��������������룬�����ո�TAB���������޶�ȡ�������ж����ޣ��Իس�������ȡ��
	// ������ȡ�Ľ�������bufferָ����ָ����ַ������У�
	// ���з�����Ϊ��ȡ�������ݣ���ȡ�Ļ��з���ת��Ϊ��\0�����ַ������ɴ��������ַ�����
	return atoi(buf);
	// atoi()����������ͷ�ļ���#include <stdlib.h>�У�
	// atoi()�����������ַ���ת��������(int)����ԭ��Ϊint atoi(const char* str);
	// atoi()������ɨ�����str�ַ���������ǰ��Ŀհ��ַ�������ո�tab�����ȣ�����ͨ��isspace()��������⣩��
	// ֱ���������ֻ��������Ųſ�ʼ��ת�����������������ֻ��ַ�������ʱ('\0')�Ž���ת����
	// ������ת����������������str����ת����int����strΪ���ַ�������ô������0��
}



void GuideInput()
/*
���ͼ����Ҫ���ú���GuideInput����ɣ�
��Ҫ�û��ֱ�����������ISBN��š��۸�����ߣ�
Ȼ������CBook�๹��һ��CBook����
ͨ��CBook����ĳ�Ա����WriteData��ͼ����Ϣд���ļ���
*/
{
	char inName[NUM1];
	char inlsdn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "������������" << endl;
	cin >> inName;
	cout << "������ISBN��" << endl;
	cin >> inlsdn;
	cout << "������۸�" << endl;
	cin >> inPrice;
	cout << "���������ߣ�" << endl;
	cin >> inAuthor;
	// ע��:cin�����ܿո�TAB�ȼ������룬������Щ�����ַ�������ֹ

	CBook book(inName, inlsdn, inPrice, inAuthor);     // ����һ��CBook����󣬲����ù��캯�������ݳ�Ա��ʼ��
	book.WriteData();
	cout << "Write Finish��" << endl;

	// �ȴ��û�������һ������
	cout << endl;
	cout << "******************************" << endl;
	cout << "��ѡ��������Ĳ����������:����������飬q��:�˳�����" << endl;
	char buf;
	cin >> buf;
	if (buf == 'q')
		system("exit");
	else
		GuideInput();
}


void WaitUser()
/*
WaitUser������Ҫ���𵱳������ĳһģ���ִ�к󣬵ȴ��û����д���
�û�����ѡ�񷵻����˵���Ҳ����ֱ���˳�ϵͳ��
*/
{
	int iInputPage = 0;
	cout << "enter�������˵���q�˳�" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
}


void ViewData(int iSelPage)
/*
��ʾͼ����Ϣ��Ҫͨ������ViewData����ɡ�����ViewData��ҳ����ʾͼ���¼��
ÿҳ������ʾ20����¼���ں���ViewData��ֱ��ʹ���ļ�����򿪴洢ͼ����Ϣ���ļ�book.dat,
Ȼ�����ҳ��Ŷ�ȡ�ļ����ݣ���Ϊÿ��ͼ���¼�ĳ�����ͬ��
�����ͺ����׼����ÿ����¼���ļ��е�λ�ã�Ȼ���ļ�ָ���ƶ���ÿҳ��һ��ͼ���¼����
˳��ش��ļ��ж�ȡ20����¼��������Ϣ��ʾ����Ļ�ϡ�
*/
{
	int iPage = 0;              // iPage����ͼ����Ŀ��ȷ����Ҫ���ż�ҳ����ʾ
	int iCurPage = 0;           // iCurPage��ʾ��ǰҳ����
	int iDataCount = 0;         // iDataCount��ʾ�ļ��м�¼��ͼ����Ŀ

	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;

	ifstream ifile;
	// ����һ��δ�󶨵��ļ���������ifstream��ͷ�ļ�#include<fstream>�ж����һ������
	ifile.open("book.dat", ios::binary);
	// ����Ϊ"book.dat"���ļ��������ļ���ifstream�󶨡�
	// �˴��ļ�������һ����������C�����ַ����������͵Ĳ���ָ�������µ�C++��׼�У�
	// �ļ����ȿ����ǿ�����string����Ҳ������C����ַ����顣
	// open�����ĵڶ��������������ļ��Ĵ�ģʽ����д�������ļ�ʱ��
	//  �򿪷�ʽ�б���ָ��ios::binary�������д������ܹ�������ģʽ��
	//	ios::in ��
	//	ios::out д
	//  ios::app  ���ļ�ĩβ��ʼд
	//  ios::binary ������ģʽ
	//  ios::nocreate	��һ���ļ�ʱ������ļ������ڣ��������ļ���
	//  ios::noreplace	��һ���ļ�ʱ������ļ������ڣ��������ļ�
	//  ios::trunc	��һ���ļ���Ȼ���������
	//  ios::ate	��һ���ļ�ʱ����λ���ƶ����ļ�β
	//  ע�⣺Ĭ��ģʽ���ı���Ĭ������ļ������ڣ���ô����һ���µ��ļ���
	//  ����ģʽ���Ի�ϣ��� | (��λ��)�� �ļ���byte������0��ʼ������������һ������

	iFileLength = GetFileLength(ifile);         // ��ȡĿ��������ļ����ı����ȣ����ֽ���
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);  //�����ļ����ȣ������ļ����ܵļ�¼��
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;

	ClearScreen();                 	//�����Ļ��Ϣ
	cout << setw(15) << "���м�¼:" << iDataCount << " ";
	cout << setw(15) << "����ҳ��:" << iPage << " ";
	cout << setw(15) << "��ǰҳ��:" << iCurPage << " ";
	cout << setw(25) << "n ��ʾ��һҳ m ����" << endl;
	cout << std::left << setw(15) << "lndex";
	cout << std::left << setw(15) << "Name" << std::left << setw(15) << "Isbn";
	cout << std::left << setw(15) << "Price" << std::left << setw(15) << "Author";
	cout << endl;

	// 
	try
	{
		// ����ͼ��ҳ���Ų��Ҹ�ҳ���һ��ͼ�����ļ��е�λ��
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);

		// ����IO���������һЩ�����ͱ�־�����԰������Ƿ��ʺͲ�����������״̬
		// ���ֳ��õ�IO������״̬Ϊ��
		// ifile.eof()������ifile��eofbit��λ���򷵻�true��
		// ifile.fail()������ifile��failbit��badbit��λ���򷵻�true��
		// ifile.bad()������ifile��badbit��λ���򷵻�true��
		// ifile.good()������ifile������Ч״̬���򷵻�true��
		// ����good�����д���λ��δ��λ������·���true����bad��fail��eof����
		// ��Ӧ����λ����λʱ����true�����⣬��badbit����λʱ��failҲ�᷵��true��
		// ����ζ�ţ�ʹ��good��fail��ȷ����������״̬����ȷ������
		// ���õ�ȷ���������״̬�ķ����ǣ���!ifile.fail()��Ϊ������ʹ�á�
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)   // ѭ��20�Σ���ȡ��20��ͼ����Ϣ
			{

				//���������㣬Ҳ����˵��Ŀ������ĸ����ֽ�ȫ��0
				// memset�������ڴ渳ֵ������������ĳһ���ڴ�ռ���и�ֵ�ġ� 
				// ��ԭ���ǣ�void* memset(void *_Dst, int  _Val, size_t _Size)
				// _Dst��Ŀ����ʼ��ַ��_Val��Ҫ����ֵ��_Size��Ҫ��ֵ���ֽ�����
				// ���磬char inName[128], ������memset������inName��ʼ��Ϊ��0000...0000��128��0������
				// �÷����£�memset(inName, 0, sizeof(char) *128);
				// ע�⣬memset�����ֽڿ����ġ�
				memset(inName, 0, sizeof(char) * NUM1);
				memset(inlsbn, 0, sizeof(char) * NUM1);
				memset(inPrice, 0, sizeof(char) * NUM2);
				memset(inAuthor, 0, sizeof(char) * NUM2);

				if (ifile.eof())          // �������������ļ���ĩβʱ����bIndex��Ϊfalse
				{
					bIndex = false;
				}
				else
					bIndex = true;

				if (bIndex)
					cout << std::right << setw(3) << ((iCurPage - 1) * 20 + i);

				// ������read������write�������Զ������ļ����ж�д
				// read�������ø�ʽΪ���ļ�������.read(char *buf,int len);
				// write�������ø�ʽΪ���ļ�������.write(const char *buf, int len);
				// ���߸�ʽ�ϲ�࣬��һ��������һ���ַ�ָ�룬
				// ����ָ���������������ŵ��ڴ�ռ����ʵ��ַ��
				// �ڶ���������һ����������ʾҪ������������ݵ��ֽ�����
				ifile.read(inName, NUM1);	   //��ȡͼ������
				cout << setw(18) << inName;
				ifile.read(inlsbn, NUM1);	   //��ȡͼ�� ISBN ���
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
		WaitView(iCurPage);      // �ȴ��û�����
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
����GetFileLength������ȡ�ļ��ĳ��ȣ�������Ҫָ��һ���ļ�������
�ú�����˼·�ǣ�1.����ifstream��һ���ļ�������ֱ�Ӵ����ļ������󣩣�
2.����seekg��get pointer��Ϊ�ļ�ĩβ��seekg(0, ios_base::end)��
3.����tellg��ȡ���ֽ�����ʵ���ϻ�ȡ����get pointer������ļ�ͷ��ƫ���ֽ�����
4.����get pointer��ʹ��ָ���ļ�ͷ����ԭλ�ã��Ա�ִ������������ָ���ļ�ͷΪseekg(0, ios_base::beg)��
*/
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	// tellg������������Ҫ�������������ص�ǰ��λָ���λ��
	ifs.seekg(0, ios::end);
	// ����ַΪ�ļ���������ƫ�Ƶ�ַΪ0������ָ�붨λ���ļ���������
	// seekg�����Ƕ������ļ���λ������������������һ��������ƫ�������ڶ��������ǻ���ַ��
	// ���ڵ�һ��������������������ֵ�����ı�ʾ���ƫ�ƣ����ı�ʾ��ǰƫ�ơ�
	// ���ڶ������������ǣ�
	// ios����beg����ʾ�������Ŀ�ʼλ�ã��ļ�ͷ��
	// ios����cur����ʾ�������ĵ�ǰλ�ã�
	// ios����end����ʾ�������Ľ���λ�ã��ļ�β��
	// ifstream������istream, ��һ������Ϊget pointer��ָ�룬ָ����һ��������ȡ��Ԫ�ء�
	respos = ifs.tellg();
	// ��Ϊ��λָ�����ļ�������������ifs.tellg()��ֵҲ�����ļ��Ĵ�С��
	// ��Ϊtellg��ȡ���ֽ�����ʵ���ϻ�ȡ����get pointer������ļ�ͷ��ƫ���ֽ���
	ifs.seekg(tmppos, ios::beg);
	// ����ַΪ�ļ�ͷ��ƫ����Ϊtmppos�����Ƕ�λ��ԭ����λ��
	return respos;
}



void DeleteBookFromFile()
/*
ɾ��ͼ����Ҫͨ�����ú���DeleteBookFromFile����ɣ�
���ں���DeleteBookFromFile������Ҫ����CBook���DeleteData��Ա��������ɡ�
DeleteData��Ա������Ҫ����ɾ��ͼ�����ļ��е�˳���ţ�
�����ͼ��ʱ���Կ����˱�š�
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
main�����ǳ������ڣ���Ҫ������SetScreenGrid��SetSysCaption��mainloop3������,
����mainloop������������������ģ��ִ�еĵ��ȡ�
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
			break;           // ���GetSelect()�����ķ���ֵ����1��2��3���е�ֵ��������ִ��whileѭ����
		}
	}
}


// ������
void main()
{
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
	mainloop();
}
