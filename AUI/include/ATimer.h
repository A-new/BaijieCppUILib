#ifndef ATIMER_H
#define ATIMER_H

typedef void (AObject::*FOnTimerFunc)(AObject* pAsso,int nTimerID);

class AUI_API ATimer : public AInvisibleControl
{
	CLASS_INFO(Timer,InvisibleControl);
public:
	ATimer(AComponent* pOwner);
	virtual ~ATimer();

	//nInterval �� ��ʱ�����ʱ�䣬��λ�Ǻ���
	//pEvtObject��evtFunc�ǵ�ʱ�䵽ʱҪִ�е����Ա����
	//pAsso���붨ʱ�������Ķ���
	static int StartTimer(UINT nInterval,AObject* pEvtObject,FOnTimerFunc evtFunc,AObject* pAsso);
	static void EndTimer(int nTimerID);
};

#endif//ATIMER_H