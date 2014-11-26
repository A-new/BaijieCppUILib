#ifndef ADIRECTORYLISTOR_H
#define ADIRECTORYLISTOR_H

/*
 * Ŀ¼������
 *	���ݸ�����Ŀ¼�����г�������ļ���Ŀ¼
 *		ע�⣺��������Ŀ¼����Ƕ�׵ݹ�
 */

class ASYS_API ADirectoryEnumerator
{
public:
	ADirectoryEnumerator(const AString& sDirectory);
	~ADirectoryEnumerator();

	//�оٲ���
	void ListDirectory(bool v);
	void ListFile(bool v);
	void ListReadOnly(bool v);
	void ListHidden(bool v);
	void ListExtend(const AString& sExt);

	bool Next();
	AString Cur();
	AString CurWithPath();
	int Index();
	void End();
	bool IsDirectory();
	bool IsFile();
	bool IsHidden();
	bool IsReadOnly();
	ADateTime GetModifyTime();
	ADateTime GetCreateTime();
	INT64 GetSize();
	AString GetSizeString();
private:
	//=== �о�ʱ�Ĳ���
	AString		m_sDir;
	bool		m_bDirectory;//�Ƿ��о�Ŀ¼		��ȱʡ���ǣ�
	bool		m_bFile;//�Ƿ��о��ļ�			��ȱʡ���ǣ�
	bool		m_bReadOnly;//�Ƿ��о�ֻ���ļ�		��ȱʡ���ǣ�
	bool		m_bHidden;//�Ƿ��о������ļ����ļ���	��ȱʡ����
	AString		m_sExt;

	//=== �оٹ����еĽ��
	AString			m_sFile;
	bool			m_bDir;
	bool			m_bFileHidden;
	bool			m_bFileReadOnly;
	INT64			m_nSize;
	ADateTime		m_tModify;
	ADateTime		m_tCreate;
	int			m_iIndex;
	bool			m_bFirst;

	bool			m_bEnd;

	HANDLE			m_hFind;
	WIN32_FIND_DATA		m_FindData;

	int _next();
};

#endif//ADIRECTORYLISTOR_H