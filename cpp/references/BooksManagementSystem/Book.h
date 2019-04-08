#pragma once
# define NUM1 128
# define NUM2 50

/*
ͼ�����ϵͳ��Ҫ����CBook�࣬ͨ��CBook��ʵ��ͼ���¼��д���ɾ����
������ͨ��CBook��鿴ÿ��ͼ�����Ϣ��
CBook���а���m_cName��m_clsbn��m_cPrice��m_cAuthor4����Ա������
�ֱ����ͼ������ơ�lSBN��š��۸�����ߡ�
�������ʱ�����Խ����ݳ�Ա�����������ԣ��������л���Ҫ���������Ժͻ�ȡ���Եĳ�Ա������
�������Եĺ�����Set��ͷ����ȡ���Եĺ�����Get��ͷ��
*/


class CBook
{
public:
	CBook() {}
	CBook(char* cName, char* clsbn, char* cPrice, char* cAuthor);
	~CBook() {}
public:
	char*  GetName();                // ��ȡͼ������
	void SetName(char* cName);       // ����ͼ������
	char*  Getlsbn();                // ��ȡͼ��ISBN���
	void Setlsbn(char* clsbn);       // ����ͼ��ISBN���
	char*  GetPrice();               // ��ȡͼ��۸�
	void SetPrice(char* cPrice);     // ����ͼ��۸�
	char*  GetAuthor();              // ��ȡͼ������
	void SetAuthor(char* cPrice);    // ����ͼ������
	void  WriteData();               // д��ͼ��
	void  DeleteData(int iCount);    // ɾ��ͼ��
	void GetBookFromFile(int iCount);   // �鿴ͼ�����Ϣ
protected:
	char m_cName[NUM1];
	char m_clsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};
