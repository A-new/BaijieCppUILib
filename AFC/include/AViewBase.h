#ifndef AVIEWBASE_H
#define AVIEWBASE_H


class AFC_API AViewBase : public AObject
{
	CLASS_INFO(ViewBase,Object);
public:
	AViewBase(void);
	virtual ~AViewBase(void);

	//-- ����ͬ��
	virtual void SyncFromModel()=0;//��ģ������ͬ������ͼ
	virtual void SyncToModel()=0;//����ͼ�����ݻ�仯ͬ����ģ��
};

#endif
