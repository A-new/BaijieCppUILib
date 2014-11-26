#ifndef PAINTMSGEXTEND_H
#define PAINTMSGEXTEND_H
#include "AMsgExtend.h"

class AWindow;
class AUI_API APaintMsgExtend : public AMsgExtend
{
public:
	APaintMsgExtend();
	virtual ~APaintMsgExtend();
	APaintMsgExtend(AWindow* pWin);

	//��Ϣ����ǰ׺���������false���򲻽��к�������
	virtual bool BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ�����׺
	virtual void AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ���˴���
	virtual bool DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);

private:
	AWindow*	m_pWindow;
};
#endif // PAINTMSGEXTEND_H
