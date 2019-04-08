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
	// ����char* strncpy(char *dest, const char *src, size_t n) 
	// strncpy��src��ָ����'\0'��β���ַ�����ǰn���ַ����Ƶ�dest��ָ�������У�����ָ��dest��ָ�롣
	// ��n>=sizeof(src)ʱ��������ȷ������dest�ַ����������'\0';
	// ��n<sizeof(src)ʱ��ֻ����srcǰn-1���ַ�����dest������Ϊdest�ַ����������'\0';
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



// ����WriteData��GetBookFromFile��DeleteData��������д�ļ��ĺ������൱�ڲ������ݿ�Ľӿڡ�

// ��Ա����WriteData��Ҫʵ�ֽ�ͼ�����д�뵽�ļ��С�
void CBook::WriteData()
{
	ofstream ofile;
	// ����һ������ļ�������������ļ�����δ�������κ��ļ�
	ofile.open("book.dat", ios::binary | ios::app);
	// ��������붨����һ�������ofile���������open������������Ϊ��book.dat�����ļ���
	// �����ļ���ofile�󶨡��ڶ�������Ϊios::app�����ļ�ĩβ��ʼд��|ios::binary��������ģʽ����
	// ��ʾ���Զ�����ģʽ���ļ������û���ļ�����ô���ɿ��ļ���������ļ�����ô���ļ�β׷�ӡ� 
	// ע�⣬��ios::app��ʽ���ļ�����ʹ�޸��ļ�ָ�룬Ҳֻ��������ļ�β��
	// ʵ������ios::app�򿪵��ļ���д�룬���ļ�ָ���޹ء�
	// ios::ate��ios::app�Ĺؼ�����ios::appֻ����β��׷�ӣ�ios::ate�������ָ���޸��ļ��еĲ������ݡ�

	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_clsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
		// �Զ������ļ��Ķ�д��Ҫ��istream��ĳ�Ա����read��write��ʵ�֡�
		// ��������Ա������ԭ��Ϊ��
		// istream& read(char* buffer, int len);
		// ostream& write(const char* buffer, int len);
		// �ַ�ָ��bufferָ���ڴ���һ�δ洢�ռ䡣len�Ƕ�д���ֽ��������õķ�ʽΪ��
		// a.write(p1, 50);
		// b.read(p2, 30);
		// �����һ���е�a������ļ�������write�������ַ�ָ��p1�������ĵ�ַ��ʼ��50���ֽڵ����ݲ���ת����д�������ļ��С�
		// �ڵڶ����У�b�������ļ�������read������b�������Ĵ����ļ��У�����30���ֽ�(����EOF��������������ַ�ָ��p2��ָ��һ�οռ��ڡ�

	}
	catch (...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();
}


// ��Ա����GetBookFromFile�ܹ�ʵ�ִ��ļ��ж�ȡ��������������
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




// ��Ա����DeleteData����ͼ����Ϣ���ļ���ɾ����
void CBook::DeleteData(int iCount)
{
	long respos;                 // ����respos������¼��ǰ�ļ����ı��ĳ���
	int iDataCount = 0;          // ����iDataCount������¼��ǰ�ļ��д����ͼ����Ŀ

	fstream file;
	fstream tmpfile;
	ofstream ofile;
	// ������������������ļ�����һ������ļ���

	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	// ����һ�����飬��ռ��С�պ�����һ��ͼ�����Ϣ

	file.open("book.dat", ios::binary | ios::in | ios::out);
	// open�����ĵڶ��������������ļ��Ĵ�ģʽ����д�������ļ�ʱ��
	//  �򿪷�ʽ�б���ָ��ios::binary�������д��������⻹����������ģʽ��
	//	ios::in ��
	//	ios::out д

	tmpfile.open("temp.dat", ios::binary | ios::in | ios::out | ios::trunc);
	//  ios::trunc	��һ���ļ���Ȼ���������

	file.seekg(0, ios::end);
	respos = file.tellg();
	// ͨ�����ļ�ָ���������ļ�ĩβ�������ļ�ĩβ�����׵�ƫ���ֽ�����
	// ���ǵõ��ļ��Ĵ�С�����ֽ���

	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);
	// һ��ͼ�����Ϣ���ļ���ռ��NUM1 + NUM1 + NUM2 + NUM2���ֽ�
	// �� �ļ������ֽ���/ÿ��ͼ����ռ���ֽ��� ������ļ��е�ͼ����Ŀ

	if (iCount < 0 || iCount > iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		// file.seekg((iCount-1)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		// ���ļ�ָ�붨λ��Ҫ���ҵ�ͼ����׵�ַ��

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
				// ��NUM1 + NUM1 + NUM2 + NUM2���ֽڵ�0���������cTempBuf

				file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
				// ��file���󶨵��ļ����ļ�ָ�봦����ȡNUM1 + NUM1 + NUM2 + NUM2���ֽڵ�����
				// �����ݱ���������cTempBuf�С�

				tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
				// ������cTempBuf�е���Ӧ�ֽ���������д�뵽tmpfile���󶨵Ĵ����ļ���
			}
		}
		file.close();

		tmpfile.seekg(0, ios::beg);
		// ��tmpfile���󶨵��ļ����ļ�ָ�붨λ���ļ��׶�

		ofile.open("book.dat");
		// ����Ϊ"book.dat"���ļ��������ļ���ofile�󶨣������������ļ�д������
		// ofile.seekp((iCount - 1)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);

		ofile.seekp(0, ios::beg);
		// seekp����������ļ������ļ���ָ��λ��

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
