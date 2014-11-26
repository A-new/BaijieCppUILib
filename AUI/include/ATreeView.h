#ifndef ATREEVIEW_H
#define ATREEVIEW_H

typedef bool (*FWalkTreeItemFunc)(ATreeViewItem* pItem,void* pArg);//����falseʱֹͣ����


class AUI_API ATreeView: public AContainer
{
	CLASS_INFO(TreeView,Container);
	friend class ATreeViewEnumerator;
	friend class ATreeViewItem;
public:
	ATreeView(AComponent* pOwner);
	virtual ~ATreeView();

	virtual void SetIndent(int v);
	virtual int GetIndent();

	virtual ATreeViewItem* GetHoveredItem();
	virtual ATreeViewItem* AddItem(ATreeViewItem* pParentItem=NULL,AString sText=_T(""));

	virtual void DoLayout();
	virtual void WalkItem(FWalkTreeItemFunc f,void* pArg);

	virtual ATreeViewItem* GetSelected();
	virtual void SetSelected(ATreeViewItem* pItem);

	virtual void RemoveItem(ATreeViewItem* pItem);
	virtual void RemoveAllItem();

	virtual void SetImageList(AImageList* pImageList);
	virtual AImageList* GetImageList();

	virtual void SetPropFromNode(AMLBody* pNode);
	virtual void CreateChildren(AMLBody* pNode);

	virtual void MakeVisible(ATreeViewItem* pItem);

	//��ES��֧��
	virtual void ESGet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESSet(const AString& sPath,AUI_ES_VALUE_INTF* pValue);
	virtual void ESCall(const AString& sPath,AUI_ES_VALUE_GROUP_INTF* args,AUI_ES_VALUE_INTF* pRetValue);

	AEventHandler		OnChange;//ѡ����ı�
protected:
	virtual void DoPaint(ACanvas* cs,AEvent* pEvent);

	int _calcItem(ATreeViewItem* pItem,ACanvas* pCanvas);
	bool _walkItem(ATreeViewItem* pItem,FWalkTreeItemFunc f,void* pArg);
	AArray		m_aChild;
	ATreeViewItem*	m_pHoveredItem;
	ATreeViewItem*	m_pSelectedItem;
	int		m_iIndent;
	AImageList*	m_pImageList;

	virtual void ESSetValue(AMLBody* pNode);
	virtual void ESGetValue(AMLBody* pNode);

};

class AUI_API ATreeViewEnumerator : public AObject
{
	CLASS_INFO(TreeViewEnumerator,Object);
public:
	ATreeViewEnumerator(ATreeView* pView);
	virtual ~ATreeViewEnumerator();

	bool Next();
	ATreeViewItem* Cur();
private:
	ATreeView*	m_pView;
	bool		m_bEnd;
	
	ATreeViewItem*	m_pCurItem;//��ǰ�ڵ�
	int		m_iIndex;//��ǰ�ڵ���ͬ�����ӽڵ㼯���С����±�
	AArray		m_aParentIndex;//���ڵ�������ͬ�����ӽڵ㼯�ϡ��е��±�

	bool NextNode(ATreeViewItem* pNode);//���ݵ�ǰ�ڵ㶨λ����һ�������ڵ�
};

#endif//ATREEVIEW_H
