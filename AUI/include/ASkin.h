#ifndef ASKIN_H
#define ASKIN_H

class AControl;
class AUI_API ASkin:public AComponent
{
	CLASS_INFO(Skin,Component);
public:
	ASkin(AComponent* pOwner);
	virtual ~ASkin();

	//�������
	//=== ��ɫ
	AColor		m_BackColor;//ȱʡ�ı�����ɫ
	AColor		m_DeckBackColor;//���α�����ɫ
	AColor		m_ForeColor;//ȱʡ��ǰ��ɫ���磺С���ǣ���󻯰�ť�ȵ���ɫ��
	AColor		m_OverColor;//��꾭��ʱ����ɫ
	AColor		m_DownColor;//��갴��ʱ����ɫ
	AColor		m_BorderColor;//ȱʡ�ı߿���ɫ
	AColor		m_CaptionColor;//���ⱳ��ɫ
	AColor		m_EmphasizeColor;//����ɫ������ɫ��
	AColor		m_ButtonColor;//��ť��ɫ
	AColor		m_SpliterColor;//�ָ�����ɫ
	AColor		m_DisableColor;//����ʱ����ɫ
	AColor		m_SelectedColor;//ѡ�к����ɫ
	//=== ��С
	int		m_ScrollBarWidth;//�������Ŀ�ȣ����򣩻�߶ȣ�����
	//=== ����
	AFont		m_DefaultFont;

	virtual void Init();//��ʼ��ȱʡ����

	//��ͼ���
	virtual void DrawLabel(ACanvas* cs,AControl* pControl);
	virtual void DrawEdit(ACanvas* cs,AControl* pControl);
	virtual void DrawScrollBar(ACanvas* cs,AControl* pControl);
	virtual void DrawButton(ACanvas* cs,AControl* pControl);
	virtual void DrawScrollBarOverlap(ACanvas* cs,AControl* pControl,ARect r);//�Ժ��������������������ص�����
	virtual void DrawImage(ACanvas* cs,AControl* pControl);
	virtual void DrawCheckBoxImage(ACanvas* cs,AControl* pControl);
	virtual void DrawRadioButtonImage(ACanvas* cs,AControl* pControl);
	virtual void DrawForm(ACanvas* cs,AControl* pControl);
	virtual void DrawPopup(ACanvas* cs,AControl* pControl);
	virtual void DrawListBox(ACanvas* cs,AControl* pControl);
	virtual void DrawMenu(ACanvas* cs,AControl* pControl);
	virtual void DrawListBoxItem(ACanvas* cs,AControl* pControl);
	virtual void DrawComboBox(ACanvas* cs,AControl* pControl);
	virtual void DrawComboButton(ACanvas* cs,AControl* pControl);
	virtual void DrawComboEdit(ACanvas* cs,AControl* pControl);
	virtual void DrawDateControl(ACanvas* cs,AControl* pControl);
	virtual void DrawListHeaderItem(ACanvas* cs,AControl* pControl);
	virtual void DrawListHeader(ACanvas* cs,AControl* pControl);
	virtual void DrawListViewItem(ACanvas* cs,AControl* pControl);
	virtual void DrawListView(ACanvas* cs,AControl* pControl);
	virtual void DrawTreeViewItem(ACanvas* cs,AControl* pControl);
	virtual void DrawTreeView(ACanvas* cs,AControl* pControl);
	virtual void DrawTreeViewItemArrow(ACanvas* cs,AControl* pControl);
	virtual void DrawPageControl(ACanvas* cs,AControl* pControl);
	virtual void DrawPanel(ACanvas* cs,AControl* pControl);
	virtual void DrawSidePanelTitle(ACanvas* cs,AControl* pControl);
	virtual void DrawSidePanelArrow(ACanvas* cs,AControl* pControl);
	virtual void DrawColorDialog(ACanvas* cs,AControl* pControl);
	virtual void DrawFileOpenDialog(ACanvas* cs,AControl* pControl);
	virtual void DrawFileSaveDialog(ACanvas* cs,AControl* pControl);
	virtual void DrawFontDialog(ACanvas* cs,AControl* pControl);
	virtual void DrawImageList(ACanvas* cs,AControl* pControl);
	virtual void DrawPropEdit(ACanvas* cs,AControl* pControl);
	virtual void DrawMenuItem(ACanvas* cs,AControl* pControl);
	virtual void DrawTitleBar(ACanvas* cs,AControl* pControl);
	virtual void DrawCloseButton(ACanvas* cs,AControl* pControl);
	virtual void DrawMinimizeButton(ACanvas* cs,AControl* pControl);
	virtual void DrawMaximizeButton(ACanvas* cs,AControl* pControl);
	virtual void DrawMenuBar(ACanvas* cs,AControl* pControl);
	virtual void DrawMenuBarLabel(ACanvas* cs,AControl* pControl);
	virtual void DrawHint(ACanvas* cs,const AString& sText,ARect r);
	virtual void DrawSpliter(ACanvas* cs,AControl* pControl);
	virtual void DrawSlide(ACanvas* cs,AControl* pControl);
	virtual void DrawMemo(ACanvas* cs,AControl* pControl);
	virtual void DrawSpinControl(ACanvas* cs,AControl* pControl);
	virtual void DrawSpinUpButton(ACanvas* cs,AControl* pControl);
	virtual void DrawSpinDownButton(ACanvas* cs,AControl* pControl);
};

#define BORDER_COLOR AColor(255,130,135,144)
#define LIGHT_COLOR AColor(255,252,252,252)
#define DARK_COLOR AColor(255,210,210,210)
#define HOVER_COLOR AColor(255,222,242,252)
#define DOWN_COLOR AColor(255,140,202,235)
#define GRAY_COLOR AColor(255,240,240,240)
#define SB_BACK_COLOR AColor(255,239,239,239)
#define SB_BUTTON_NORMAL AColor(255,233,233,235)
#define SB_ARROW_DARK AColor(255,92,92,92)
#define SB_BORDER_COLOR AColor(255,231,231,231)
#define WHITE_COLOR AColor(255,255,255,255)
#define BLACK_COLOR AColor(255,0,0,0)
#define SELECTED_COLOR AColor(255,96,164,183)


#endif//ASKIN_H