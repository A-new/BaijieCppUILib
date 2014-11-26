#include "stdafx.h"

/*  ɫ��ο���360��/0��졢60��ơ�120���̡�180���ࡢ240������300�����
 *  
* a) RGB��HSL���㷨������
����1����RGBֵת�ɡ�0��1������ֵ��
����2���ҳ�R,G��B�е����ֵ��
����3���������ȣ�L=(maxcolor + mincolor)/2
����4�����������С����ɫֵ��ͬ������ʾ��ɫ����ôS����Ϊ0����Hδ���岢�ڳ�����ͨ��д��0��
����5�����򣬸�������L���㱥�Ͷ�S��
If L<0.5, S=(maxcolor-mincolor)/(maxcolor + mincolor)
If L>=0.5, S=(maxcolor-mincolor)/(2.0-maxcolor-mincolor)
����6:����ɫ��H��
If R=maxcolor, H=(G-B)/(maxcolor-mincolor)
If G=maxcolor, H=2.0+(B-R)/(maxcolor-mincolor)
If B=maxcolor, H=4.0+(R-G)/(maxcolor-mincolor)
H=H*60.0,���HΪ��ֵ�����360��
˵����1���ɲ���3��ʽ�ӿ��Կ������Ƚ���ͼ��������ɫ�ɷֺ����ٵ���ɫ�ɷֵ������йء�����ԽС��ͼ��Խ���ں�ɫ������Խ��ͼ��Խ���������İ�ɫ��
����2���ɲ���5��ʽ�ӿ��Կ������Ͷ���ͼ��������ɫ�ɷֺ����ٵ���ɫ�ɷֵĲ����йء����Ͷ�ԽС��ͼ��Խ���ڻҶ�ͼ�񡣱��Ͷ�Խ��ͼ��Խ���ޣ����˵ĸо��ǲ�ɫ�ģ������Ǻڰ׻ҵ�ͼ��
  ����3��ɫ���������˶�ͼ��Ĳ�ͬ����ɫ���ܡ�
    ����4���ӵ�6���ļ��㿴��H�ֳ�0��6����RGB��,ɫ�ռ���һ���������HSL��ɫ�ռ�������������׶�壬���е�L��RGB����������Խ��ߡ���ˣ�RGB������Ķ��㣺�졢�ơ��̡��ࡢ����Ʒ��ͳ�ΪHSL�����εĶ��㣬����ֵ0��6�͸�������H���ĸ����֡�
 *
 */
#define min3v(v1, v2, v3)   ((v1)>(v2)? ((v2)>(v3)?(v3):(v2)):((v1)>(v3)?(v3):(v2)))
#define max3v(v1, v2, v3)   ((v1)<(v2)? ((v2)<(v3)?(v3):(v2)):((v1)<(v3)?(v3):(v1)))
void AColorHSL::FromRGB(const AColor& cr)
{
	float h=0, s=0, l=0;
	// normalizes red-green-blue values
	float r = cr.red/255.f;
	float g = cr.green/255.f;
	float b = cr.blue/255.f;
	float maxVal = max3v(r, g, b);
	float minVal = min3v(r, g, b);

	// hue
	if(maxVal == minVal)
	{
		h = 0; // undefined
	}
	else if(maxVal==r && g>=b)
	{
		h = 60.0f*(g-b)/(maxVal-minVal);
	}
	else if(maxVal==r && g<b)
	{
		h = 60.0f*(g-b)/(maxVal-minVal) + 360.0f;
	}
	else if(maxVal==g)
	{
		h = 60.0f*(b-r)/(maxVal-minVal) + 120.0f;
	}
	else if(maxVal==b)
	{
		h = 60.0f*(r-g)/(maxVal-minVal) + 240.0f;
	}
	// luminance
	l = (maxVal+minVal)/2.0f;
	// saturation
	if(l == 0 || maxVal == minVal)
	{
		s = 0;
	}
	else if(0<l && l<=0.5f)
	{
		s = (maxVal-minVal)/(maxVal+minVal);
	}
	else if(l>0.5f)
	{
		s = (maxVal-minVal)/(2 - (maxVal+minVal)); //(maxVal-minVal > 0)?
	}
	this->h = (h>360)? 360 : ((h<0)?0:h);
	this->s = ((s>1)? 1 : ((s<0)?0:s))*100;
	this->l = ((l>1)? 1 : ((l<0)?0:l))*100;
}

/*
* b) HSL��RGB���㷨������
����1��If S=0,��ʾ��ɫ������R,G��B��ΪL.
����2�����򣬲���L:
If L<0.5,temp2=L*(1.0+S)
If L>=0.5,temp2=L+S-L*S
����3��temp1=2.0*L-temp2
����4����Hת����0��1��
����5������R,G,B�������������ʱֵtemp3���������£�
for R, temp3=H+1.0/3.0
for G, temp3=H
for B, temp3=H-1.0/3.0
if temp3<0, temp3=temp3+1.0
if temp3>1, temp3=temp3-1.0
����6������R,G,B�����²��ԣ�
If 6.0*temp3<1,color=temp1+(temp2-temp1)*6.0*temp3
Else if 2.0*temp3<1,color=temp2
Else if 3.0*temp3<2,
color=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0
Else color=temp1
 *
 *
 */
AColor AColorHSL::ToRGB()
{
	float h = this->h;                  // h must be [0, 360]
	float s = this->s/100.f; // s must be [0, 1]
	float l = this->l/100.f;      // l must be [0, 1]
	float R, G, B;
	if(this->s == 0)
	{
		// achromatic color (gray scale)
		R = G = B = l*255.f;
	}
	else
	{
		float q = (l<0.5f)?(l * (1.0f+s)):(l+s - (l*s));
		float p = (2.0f * l) - q;
		float Hk = h/360.0f;
		float T[3];
		T[0] = Hk + 0.3333333f; // Tr   0.3333333f=1.0/3.0
		T[1] = Hk;              // Tb
		T[2] = Hk - 0.3333333f; // Tg
		for(int i=0; i<3; i++)
		{
			if(T[i] < 0) T[i] += 1.0f;
			if(T[i] > 1) T[i] -= 1.0f;
			if((T[i]*6) < 1)
			{
				T[i] = p + ((q-p)*6.0f*T[i]);
			}
			else if((T[i]*2.0f) < 1) //(1.0/6.0)<=T[i] && T[i]<0.5
			{
				T[i] = q;
			}
			else if((T[i]*3.0f) < 2) // 0.5<=T[i] && T[i]<(2.0/3.0)
			{
				T[i] = p + (q-p) * ((2.0f/3.0f) - T[i]) * 6.0f;
			}
			else T[i] = p;
		}
		R = T[0]*255.0f;
		G = T[1]*255.0f;
		B = T[2]*255.0f;
	}
	AColor cr;
	cr.alpha = 255;
	cr.red = (BYTE)((R>255)? 255 : ((R<0)?0 : R));
	cr.green = (BYTE)((G>255)? 255 : ((G<0)?0 : G));
	cr.blue = (BYTE)((B>255)? 255 : ((B<0)?0 : B));
	return cr;
}

int AUTIL::Point2Pixel(int pt,bool x)
{
	HDC hDC = AApplication::Get()->GetMainForm()->GetWindow()->GetDC();// ::GetDC(0);
	int iRet= pt * 100 * ::GetDeviceCaps(hDC,x ? LOGPIXELSX : LOGPIXELSY) / 7200;
	//::ReleaseDC(0,hDC);
	return iRet;
}

void AUTIL::TextAlignToStringAlignmeng(TTextAlign ta,StringAlignment& ha,StringAlignmentV &va)
{
	switch( ta )
	{
	case taLeftTop:
		ha = StringAlignmentNear;
		va = StringAlignmentTop;
		break;
	case taCenterTop:
		ha = StringAlignmentCenter;
		va = StringAlignmentTop;
		break;
	case taRightTop:
		ha = StringAlignmentFar;
		va = StringAlignmentTop;
		break;
	default:
	case taLeftMiddle:
		ha = StringAlignmentNear;
		va = StringAlignmentMiddle;
		break;
	case taCenterMiddle:
		ha = StringAlignmentCenter;
		va = StringAlignmentMiddle;
		break;
	case taRightMiddle:
		ha = StringAlignmentFar;
		va = StringAlignmentMiddle;
		break;
	case taLeftBottom:
		ha = StringAlignmentNear;
		va = StringAlignmentBottom;
		break;
	case taCenterBottom:
		ha = StringAlignmentCenter;
		va = StringAlignmentBottom;
		break;
	case taRightBottom:
		ha = StringAlignmentFar;
		va = StringAlignmentBottom;
		break;
	}
}

AString AUTIL::FloatTypeToString(TFloatType ft)
{
	AString s;
	if( ft == ftFloat ) s = _T("xy");
	else if( ft == ftFloatX ) s = _T("x");
	else if( ft == ftFloatY ) s = _T("y");
	return s;
}

TFloatType AUTIL::StringToFloatType(const AString& s)
{
	if( s == _T("xy") ) return ftFloat;
	if( s == _T("x"))  return ftFloatX;
	if( s == _T("y")) return ftFloatY;
	return ftFloatNone;
}

AString AUTIL::AnchorsToString(const AAnchors& a)
{
	AString s;
	if( a.m_bLeft ) s += L"l";
	else if( a.m_bRight ) s += L"r";
	else if( a.m_bTop ) s += L"t";
	else if( a.m_bBottom ) s += L"b";
	return s;
}
void AUTIL::StringToAnchors(const AString& s,AAnchors& a)
{
	a.m_bLeft = s.Find(L"l") > -1 ? true : false;
	a.m_bTop = s.Find(L"t") > -1 ? true : false;
	a.m_bRight = s.Find(L"r") > -1 ? true : false;
	a.m_bBottom = s.Find(L"b") > -1 ? true : false;
}

AString AUTIL::AlignToString(eAlign e)
{
	if( e == alLeft ) return _T("l");
	if( e == alTop ) return _T("t");
	if( e == alRight ) return _T("r");
	if( e == alBottom ) return _T("b");
	if( e == alClient ) return _T("c");
	return _T("");
}
eAlign AUTIL::StringToAlign(const AString& s)
{
	if( s == _T("l")) return alLeft;
	if( s == _T("t")) return alTop;
	if( s == _T("r")) return alRight;
	if( s == _T("b")) return alBottom;
	if( s == _T("c")) return alClient;
	return alNone;
}

AString AUTIL::ListViewStyleToString(TListViewStyle e)
{
	if( e == lvsReport ) return _T("r");
	else if( e == lvsList ) return _T("l");
	else if( e == lvsIcon) return _T("i");
	else return _T("r");
}

TListViewStyle AUTIL::StringToListViewStyle(const AString& s)
{
	if( s == _T("i") ) return lvsIcon;
	else if( s == _T("l")) return lvsList;
	else return lvsReport;
}

bool AUTIL::IsSeperatorChar(ACHAR ch)
{
	if( ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t' ||
		ch == ',' || ch == '-' || ch == '+' || ch == '|' ||
		ch == '(' || ch == ')' || ch == ':' || ch == ';' ||
		ch == '<' || ch == '>' || ch == '?' || ch == '=' ||
		ch == '.' || ch == '\"' || ch == '\'')
		return true;
	else return false;
}