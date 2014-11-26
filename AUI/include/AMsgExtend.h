#ifndef MSGEXTEND_H
#define MSGEXTEND_H

class AUI_API AMsgExtend
{
public:
	AMsgExtend();
	virtual ~AMsgExtend();

	//��Ϣ����ǰ׺���������false���򲻽��к�������
	virtual bool BeforeMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)=0;
	//��Ϣ�����׺
	virtual void AfterMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)=0;
	//��Ϣ���˴���
	virtual bool DealMsg(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT& ret)=0;
};

#endif // MSGEXTEND_H
