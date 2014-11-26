#pragma once

//�������㷨��
class wnl
{
public:
	struct myDATE{
		int  year;
		int  month;
		int  day;
		bool isRunYue;
	};
	wnl(void);
	~wnl(void);

	//�������ڼ� 0�������� 1:����һ ...
	static int GetWeek(ADateTime& dt);

	LONG lDaysFrom1900(myDATE date);//date��1900����������
	UINT lYearDays(UINT y);//ũ��y���������
	UINT leapDays(UINT y);//����ũ�� y�����µ�����
	UINT leapMonth(UINT y);// ����ũ�� y�����ĸ��� 1-12 , û�򴫻� 0
	UINT monthDays(UINT y,UINT m);//����ũ�� y��m�µ�������
	myDATE Lunar(myDATE date);//�����������ڣ������������� 
	int dayOfWeek(myDATE date);//�����������ڣ��������ڼ� 
	UINT solarDays(UINT y,UINT m);//���ع��� y��ĳm+1�µ�����
	char* GetJieri(int m,int d);//�õ����ջ�����յ�����
	const char* GetShuXiang(int y);
	AString GetYinliDayString(myDATE de);
	AString GetYearString(myDATE de);
private:
	char                    m_slunar[100];//���ڴ洢ũ����Ϣ

	static DWORD   lunarInfo[];//
	static UINT    solarMonth[];
	static char    sSolarTerm[];
	static DWORD   dTermInfo[];
	static char    sFtv[];
};

