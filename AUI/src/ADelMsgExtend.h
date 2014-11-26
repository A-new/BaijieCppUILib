#ifndef DELMSGEXTEND_H
#define DELMSGEXTEND_H
#include "AMsgExtend.h"

class AWindow;
class AUI_API ADelMsgExtend : public AMsgExtend
{
public:
	ADelMsgExtend();
	virtual ~ADelMsgExtend();
	ADelMsgExtend(AWindow* pWin);

	//��Ϣ����ǰ׺���������false���򲻽��к�������
	virtual bool BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ�����׺
	virtual void AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);
	//��Ϣ���˴���
	virtual bool DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret);

private:
	AWindow*	m_pWindow;
};
#endif // DELMSGEXTEND_H
