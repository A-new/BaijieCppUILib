#ifndef CAPTUREMSGEXTEND_H
#define CAPTUREMSGEXTEND_H
#include "AMsgExtend.h"

class AWindow;
class AUI_API ACaptureMsgExtend : public AMsgExtend
{
public:
	ACaptureMsgExtend();
	virtual ~ACaptureMsgExtend();
	ACaptureMsgExtend(AWindow* pWin);

	//��Ϣ����ǰ׺���������false���򲻽��к�������
	virtual bool BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ�����׺
	virtual void AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ���˴���
	virtual bool DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);

private:
	AWindow*	m_pWindow;
};
#endif // CAPTUREMSGEXTEND_H
