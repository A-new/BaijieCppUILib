#ifndef ACANVAGDI_H
#define ACANVAGDI_H

#include "GBrush.h"
#include "GFont.h"
#include "GPen.h"
#include "GCanvas.h"

class AMatrixGdi;


class ACanvasGdi : public ACanvas
{
	CLASS_INFO(CanvasGdi,Canvas);
public:
	ACanvasGdi();
	virtual ~ACanvasGdi();

public://attributes
	virtual void Create(HDC hDC,int nWidth,int nHeight);
	virtual void Write(ARect rDest,ARect rSrc);//�����Ŀ�ģ���Ļ��ͼƬ�ȣ�
	virtual bool IsValid();
	virtual void Free();
	virtual HDC GetDC(){return m_hDC; }//�õ���ǰ��DC
	virtual int GetWidth(){return m_nWidth; }//�õ��������
	virtual int GetHeight(){ return m_nHeight; }//�õ������߶�

	virtual ACanvas* Use(AFont* pFont);
	virtual ACanvas* Use(APen* pPen);
	virtual ACanvas* Use(ABrush* pBrush);
	virtual ACanvas* Use(AMatrix* pMatrix);

	virtual APath* CreatePath();
	virtual void DestroyPath(APath* p);
	virtual AMatrix* CreateMatrix();
	virtual void DestroyMatrix(AMatrix *p);

	virtual SmoothingMode GetSmoothingMode();
	virtual void SetSmoothingMode(SmoothingMode smoothingMode);

	virtual TextHint GetTextHint(){ return m_TextHint; }
	virtual void SetTextHint(TextHint th){ m_TextHint = th; }

	virtual void Translate(int dx,int dy);

	virtual void DrawPoint(APoint pt,AColor cr);

	virtual void DrawLine(int x1,int y1,int x2,int y2);
	virtual void DrawLine(APoint pt1,APoint pt2);

	virtual void DrawRect(int x1,int y1,int x2,int y2);
	virtual void DrawRect(ARect r);

	virtual void FillRect(int x1,int y1,int x2,int y2);
	virtual void FillRect(ARect r);

	virtual void DrawRoundRect(int x1,int y1,int x2,int y2,int round);
	virtual void DrawRoundRect(ARect r,int round);

	virtual void FillRoundRect(int x1,int y1,int x2,int y2,int round);
	virtual void FillRoundRect(ARect r,int round);

	virtual void DrawEllipse(int x1,int y1,int x2,int y2);
	virtual void DrawEllipse(ARect r);

	virtual void FillEllipse(int x1,int y1,int x2,int y2);
	virtual void FillEllipse(ARect r);

	virtual void DrawPolygon(APoint* pts,int count);

	virtual void FillPolygon(APoint* pts,int count);


	virtual void DrawTrigle(APoint pt1,APoint pt2,APoint pt3);
	virtual void FillTrigle(APoint pt1,APoint pt2,APoint pt3);

	virtual void DrawText(int x1,int y1,const AString& sText);
	virtual void DrawText(int x1,int y1,const AString& sText,int iRowSpace);
	virtual void DrawText(ARect r,const AString& sText,StringAlignment hAlign = StringAlignmentNear,StringAlignmentV vAlign=StringAlignmentMiddle);
	virtual ASize MeasureText(const AString& sText);
	virtual ASize MeasureText(const AString& sText,int iRowSpace);//�����ı��ļ���
	virtual int MeasurePosition(const AString& sText,int iPos);//����λ���ҵ������ַ������±�

	virtual void DrawGraphic(AImage* pGraphic,int x,int y,int w=0,int h=0);

	virtual void DrawPath(APath* pPath);
	virtual void FillPath(APath* pPath);

	virtual void SetClipBox(ARect r);
	virtual ARect GetClipBox();
protected:

	int		m_nWidth;
	int		m_nHeight;
	HDC		m_hDC;
	APen*		m_pPen;
	ABrush*		m_pBrush;
	AFont*		m_pFont;
	HDC		m_dcEmpty;
	ARect		m_rClip;

	HDC m_hPaintDC;
	//::SetWindowOrgEx(hPaintDC,r.left,r.top,NULL);

	//�ü�
	HRGN m_hRgn;
	HRGN m_hOldRgn;

	HBITMAP m_hMemBitmap;
	TextHint	m_TextHint;
	GCanvas*	m_pCanvas;


	APen* GetPen();
	ABrush* GetBrush();
	AFont* GetFont();

	void _clip();
	void Reset();
};

#endif//ACANVAGDI_H