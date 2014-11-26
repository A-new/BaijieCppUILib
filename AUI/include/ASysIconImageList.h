#ifndef ASYSICONIMAGELIST_H
#define ASYSICONIMAGELIST_H

/*
 * ���õ�ͼ��Key
 * �ղؼ� Favorites
 * ����� Computer
 * ��  Profile
 * ���� Network
 * Ŀ¼ Folder
 */
class AUI_API ASysIconImageList : public AImageList
{
	CLASS_INFO(SysIconImageList,ImageList);
public:
	ASysIconImageList(AComponent* pOwner);
	virtual ~ASysIconImageList();

	virtual int GetIndex(const AString& sKey);//�������������õ�Key��Ҳ�������ļ���չ��
};

#endif//ASYSICONIMAGELIST_H