#ifndef NCMSGEXTEND_H
#define NCMSGEXTEND_H
#include "AMsgExtend.h"

class AWindow;
class AUI_API ANcMsgExtend : public AMsgExtend
{
public:
	ANcMsgExtend();
	virtual ~ANcMsgExtend();
	ANcMsgExtend(AWindow* pWin);
	
	//��Ϣ����ǰ׺���������false���򲻽��к�������
	virtual bool BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ�����׺
	virtual void AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ���˴���
	virtual bool DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	
private:
	AWindow*	m_pWindow;
	APoint		m_ptDown;
	DWORD		m_dwLastDown;
};
#endif // NCMSGEXTEND_H
