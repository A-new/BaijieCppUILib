#ifndef APOPUPDATEBOX_H
#define APOPUPDATEBOX_H

class AUI_API APopupDateBox: public APopupContainer
{
	CLASS_INFO(PopupDateBox,PopupContainer);
public:
	APopupDateBox(AComponent* pOwner);
	virtual ~APopupDateBox();

	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);

	virtual ADateTime GetSelected();

	void OnWeekPaint(AObject* pSender,AEvent* pEvent);
	void OnZhouPaint(AObject* pSender,AEvent* pEvent);
	void OnDayPaint(AObject* pSender,AEvent* pEvent);
	void OnCellContainerPaint(AObject* pSender,AEvent* pEvent);
	void OnCellPaint(AObject* pSender,AEvent* pEvent);
	void OnTitlePaint(AObject* pSender,AEvent* pEvent);
	void OnLeftButtonPaint(AObject* pSender,AEvent* pEvent);
	void OnRightButtonPaint(AObject* pSender,AEvent* pEvent);
	void OnLRButtonClick(AObject* pSender,AEvent* pEvent);
	void OnEditKey(AObject* pSender,AEvent* pEvent);
	void OnTodayClick(AObject* pSender,AEvent* pEvent);
	void OnCellMouseMove(AObject* pSender,AEvent* pEvent);
	void OnDayCellClick(AObject* pSender,AEvent* pEvent);
		
	void FillCell(int year,int month);

	virtual int GetCurYear(){ return m_nYear; }
	virtual int GetCurMonth(){ return m_nMonth; }
	virtual int GetCurDay(){ return m_nDay; }

	//��ES��֧��
	virtual void ESGet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESSet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESCall(const AString& sPath,AUI_ES_VALUE_GROUP_INTF* args,AUI_ES_VALUE_INTF* pRetValue);

	AEventHandler		OnSelected;
protected:
	

private:
	int			m_nYear;//��ǰ��
	int			m_nMonth;//��ǰ��
	int			m_nDays;//��ǰ�µ�������
	int			m_nDay;//��ǰѡ�е��죬ȱʡ��ÿ��1��
	AContainer*		m_pTitle;//̧ͷ
	AContainer*		m_pWeekContainer;//���ڼ�����
	AContainer*		m_pWeekLeftSpace;//���ڼ����������
	ATableContainer*	m_pWeek;//���ڼ�
	ATableContainer*	m_pZhou;//�ڼ���
	AContainer*		m_pWeekDay[7];
	AContainer*		m_pZhouCell[6];
	ATableContainer*	m_pDayContainer;//���ڵ�Ԫ������
	AContainer*		m_aDayHead[42];//6 * 7�ı��
	ALabel*			m_pLongLiNian;//ũ����
	AButton*		m_pYearLeft;//����ߵĵ��ڰ�ť
	AButton*		m_pYearRight;
	AButton*		m_pMonthLeft;//����ߵĵ��ڰ�ť
	AButton*		m_pMonthRight;
	ALabel*			m_pYearLabel;
	ALabel*			m_pMonthLael;
	AEdit*			m_pEditYear;
	AEdit*			m_pEditMonth;
	AButton*		m_pBackTodayButton;//�ؽ���
};
#endif//APOPUPDATEBOX_H
