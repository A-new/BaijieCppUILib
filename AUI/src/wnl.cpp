#include "StdAfx.h"
#include "wnl.h"


wnl::wnl(void)
{
}


wnl::~wnl(void)
{
}


/*
*���գ�Zeller����ʽ����w=y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1 

��ʽ�еķ��ź������£�
w�����ڣ�
c������-1��
y���꣨��λ������
m���£�m���ڵ���3��С�ڵ���14�����ڲ��չ�ʽ�У�ĳ���1��2��Ҫ������һ���13��14�������㣬����2003��1��1��Ҫ����2002���13��1�������㣩��
d���գ�
[ ]����ȡ������ֻҪ�������֡�(C����������һ��y����ݺ���λ��M���·ݣ�d��������1�º�2��Ҫ����һ���13�º� 14�����㣬��ʱC��y������һ��ȡֵ��) 

�������W����7�������Ǽ��������ڼ������������0����Ϊ�����ա� 
 */

int wnl::GetWeek(ADateTime& dt)
{
	int y,m,d,c;
	y = dt.GetYear();
	m = dt.GetMonth();
	d = dt.GetDay();

	c = y /100;
	y = y % 100;
	if( m < 3 ) m += 12;
	int w = y+y/4+c/4-2*c+26*(m+1)/10+d-1;
	return w % 7;//BUG:2013.3.1�����һ����������
}

DWORD wnl::lunarInfo[]={
	0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
	0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
	0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
	0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
	0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
	0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
	0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
	0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
	0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
	0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
	0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
	0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
	0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
	0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
	0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};
//��������
static struct 
{
	char* szDate;//���� MMDD��ʽ
	char* jieri;//����
} g_YLJieri[]=
{
	{"0101","Ԫ��"},{"0202","����ʪ����"},{"0210","���������"},{"0214","���˽�"},
	{"0303","ȫ��������"},{"0308","��Ů��"},{"0312","ֲ����"},{"0314","���ʾ�����"},
	{"0315","����������"},{"0321","����ɭ����"},{"0322","����ˮ��"},{"0323","����������"},
	{"0324","������ν�˲���"},{"0401","���˽�"},{"0407","����������"},
	{"0422","���������"},{"0501","�����Ͷ���"},{"0504","�й������"},{"0505","ȫ����ȱ������"},
	{"0508","�����ʮ����"},{"0512","���ʻ�ʿ��"},{"0515","���ʼ�ͥ��"},{"0517","���������"},
	{"0518","���ʲ������"},{"0519","ȫ��������"},{"0520","ȫ��ѧ��Ӫ����"},{"0522","���������������"},
	{"0523","����ţ����"},{"0531","����������"},{"0601","���ʶ�ͯ��"},{"0605","���绷����"},
	{"0606","ȫ��������"},{"0617","���λ�Į���͸ɺ���"},{"0623","���ʰ���ƥ����"},{"0625","ȫ��������"},
	{"0626","���ʷ���Ʒ��"},{"0701","��ۻع��� ������"},{"0707","�й�������ս��������"},{"0711","�����˿���"},
	{"0801","��һ������"},{"0908","����ɨä��"},{"0910","��ʦ��"},{"0916","���ʳ����㱣����"},
	{"0917","���ʺ�ƽ��"},{"0920","���ʰ�����"},{"0922","�������˽�"},{"0927","����������"},
	{"1001","����� �������ֽ�"},{"1002","���ʼ�����Ȼ�ֺ���"},{"1004","���綯����"},{"1006","���˽�"},{"1007","����ס����"},
	{"1008","ȫ����Ѫѹ�� �����Ӿ���"},{"1009","����������"},{"1010","���羫��������"},{"1015","����ä�˽�"},
	{"1016","������ʳ��"},{"1017","��������ƶ����"},{"1022","���紫ͳҽҩ��"},{"1024","���Ϲ���"},
	{"1031","��ʥ��"},{"1108","�й�������"},{"1109","����������"},{"1112","����ɽ����"},
	{"1114","����������"},
	{"1117","���ʴ�ѧ����"},{"1128","�ж���"},{"1201","���簬�̲���"},{"1203","����м�����"},
	{"1209","����������"},{"1225","ʥ����"},{"1226","ë��ϯ����"}

};

//��ʮ�Ľ�����
char* g_szJieqi[]={
	"С��","��","����","��ˮ","����","����",
	"����","����","����","С��","â��","����",
	"С��","����","����","����","��¶","���",
	"��¶","˪��","����","Сѩ","��ѩ","����"
};
/*
*�ѵ����1900��1��0�գ������գ��Ĳ��Ϊ���գ���ô��y�꣨1900�����0�꣩��x �������Ļ�����  
F = 365.242 * y + 6.2 + 15.22 * x - 1.9 * sin(0.262 * x)  �����ʽ�������0.05�����ҡ� 
 */


UINT wnl::solarMonth[]={31,28,31,30,31,30,31,31,30,31,30,31};
UINT wnl::lYearDays(UINT y)
{
	UINT i, sum = 348; 
	for(i=0x8000; i>0x8; i>>=1)
	{
		sum += (lunarInfo[y-1900] & i)? 1: 0;
	}
	return(sum+leapDays(y));
}

UINT wnl::leapDays(UINT y)
{
	if(leapMonth(y))
	{
		return (lunarInfo[y-1900] & 0x10000)? 30: 29;
	}
	else
	{
		return 0;
	}
}

UINT wnl::leapMonth(UINT y)
{
	return lunarInfo[y-1900] & 0xf;
}

UINT wnl::monthDays(UINT y,UINT m)
{
	return (lunarInfo[y-1900] & (0x10000>>m))? 30: 29;
}
LONG wnl::lDaysFrom1900(myDATE date)
{
	LONG days;

	days=365*date.year+(date.year-1)/4-(date.year-1)/100+(date.year-1)/400-
		(365*1900+(1900-1)/4-(1900-1)/100+(1900-1)/400);

	for(int i=0;i<date.month-1;i++)
	{
		days+=solarMonth[i];
	}
	days+=date.day;
	if((date.year%4==0&&date.year%100!=0)||date.year%400==0)
	{
		if(date.month>2)
		{
			days++;
		}
	}
	return days;
}

wnl::myDATE wnl::Lunar(myDATE date)
{
	LONG offset;
	int i, leap=0, temp=0;
	myDATE retdate;

	offset=lDaysFrom1900(date)-30;

	for(i=1900; i<2050 && offset>0; i++)
	{
		temp = lYearDays(i);
		offset -= temp;
	}

	if(offset<0)
	{
		offset += temp;
		i--;
	}

	retdate.year = i;

	leap = leapMonth(i);
	bool isLeap = false;

	for(i=1; i<13 && offset>0; i++)
	{
		if(leap>0 && i==(leap+1) && isLeap==false)
		{
			--i;
			isLeap = true;
			temp = leapDays(retdate.year);
		}
		else
		{
			temp = monthDays(retdate.year, i);
		}
		if(isLeap==true && i==(leap+1)) 
		{
			isLeap = false;
		}
		offset -= temp;
	}
	if(offset==0 && leap>0 && i==leap+1)
	{
		if(isLeap)
		{ 
			isLeap = false;
		}
		else
		{
			isLeap = true;
			--i;
		}
	}
	if(offset<=0)
	{
		offset += temp;
		--i;
	}
	retdate.month = i;
	retdate.day = offset ;
	retdate.isRunYue=isLeap;
	return retdate;
}

static const char *g_cDayName[]  = { "*","��һ","����","����","����","����", /*ũ��������*/
	"����","����","����","����","��ʮ",
	"ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",
	"ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
	"إһ","إ��","إ��","إ��","إ��",       
	"إ��","إ��","إ��","إ��","��ʮ"};
static const char *g_cMonName[]  = {"*","��","��","��","��","��","��", "��","��","��","ʮ","ʮһ","��"};

AString wnl::GetYinliDayString(myDATE de)
{
	AString s;
	if( de.day == 1 )
	{
		if( de.isRunYue ) s += L"��";
		s += AString( g_cMonName[de.month] );
		s += L"��";
	}
	else
	{
		s = g_cDayName[de.day];
	}
	
	return s;
}
int wnl::dayOfWeek(myDATE date)
{
	//char *cWeekName[]  = {"������","����һ","���ڶ�","������","������","������","������"};

	if(date.month==1||date.month==2)
	{
		date.month+=12;
		date.year--;
	}
	return (date.day+1+2*date.month+3*(date.month+1)/5+date.year+date.year/4-date.year/100+date.year/400)%7;
}

UINT wnl::solarDays(UINT y,UINT m)
{
	if(m==1)//2��
	{
		return(((y%4 == 0) && (y%100 != 0) || (y%400 == 0))? 29: 28);
	}
	else
	{
		return(solarMonth[m]);
	}
}

char* wnl::GetJieri(int m,int d)
{
	char szBuf[48];
	sprintf(szBuf,"%02d%02d",m,d);
	int iCount = sizeof(g_YLJieri)/sizeof(g_YLJieri[0]);
	for(int i=0;i<iCount;i++)
	{
		if( strcmp(szBuf,g_YLJieri[i].szDate) == 0 )
			return g_YLJieri[i].jieri;
	}
	return NULL;
}

const char *g_cShuXiang[] = {"��","ţ","��","��","��","��","��","��","��","��","��","��"}; /*��������*/

const char* wnl::GetShuXiang(int y)
{
	int nShuXiang = ((y - 4) % 60) % 12;
	return g_cShuXiang[nShuXiang];
}

static const char *g_cTianGan[]  = {"��","��","��","��","��","��","��","��","��","��"}; /*�������*/
static const char *g_cDiZhi[]    = {"��","��","��","î","��","��","��", "δ","��","��","��","��"}; /*��֧����*/

AString wnl::GetYearString(myDATE de)
{
	AString s(L"ũ��");
	/*--����ũ����ɡ���֧������ ==> wNongli--*/
	int nShuXiang = ((de.year - 4) % 60) % 12;
	
	int nTianGan = ((de.year - 4) % 60) % 10;
	int nDiZhi = ((de.year - 4) % 60) % 12;
	s += AString(g_cTianGan[nTianGan]) + AString(g_cDiZhi[nDiZhi]);
	s += AString(L"(")+AString(g_cShuXiang[nShuXiang])+L")��";

	return s;
}