#ifndef AENUMERATOR_H
#define AENUMERATOR_H

/* ö������
 * ���಻��ʵ�����������ڶ���һ�ֹ淶
 * ö���������и�������һ����������
 */
class AFC_API AEnumerator 
{
protected:
	AEnumerator(){}
public:
	virtual ~AEnumerator(){}
	virtual bool Next(){ return false; }//����ö��
	virtual void* Cur(){ return NULL; }//�õ���ǰö��ֵ
	virtual int Index(){ return 0; }//�õ���ǰö������Ӧ���±� (����Map��˵����Key��
};


#endif//AENUMERATOR_H