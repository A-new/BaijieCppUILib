#ifndef AFORM_H
#define AFORM_H

//�����Ĵ����࣬������MFC��CWindow��BCB��TForm
class AUI_API AForm : public AWinControlBase
{
	CLASS_INFO(Form,WinControlBase);
public:
	AForm(AComponent* pOwner);
	virtual ~AForm();

	virtual void SetIcon(HICON hIcon);

	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);
	virtual void CenterToScreen();

	
	virtual void SetPropFromNode(AMLBody* pNode);

	virtual void FromXML(AMLBody* pBody);
public:


protected:
	virtual AWindow* CreateWnd();
	
};


#endif//AFORM_H
