// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//

#pragma once
#include "BossFinal.h"
class CMyPlane;

class CPlaneGameView : public CView
{
	enum ObjType{enEnemy,enBomb,enBall,enExplosion, enBoss1, enBigBall, enBoss2, enlife, enEnemy2, enWingPlane, enBoss3, enBossFinal
	};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);

	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	BossFinal* bossFinal = NULL;
	
	CObList    m_ObjList[11];
	
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();

	// ��Ϸ�ĵȼ�
	int level = 1;
	// ��ǰ��Ϸ����
	int score = 0;
	// ��ǰ��Ϸģʽ
	int model = 0;
	// �Ƿ����¿�ʼ
	int reStart = 0;
	//  ��1�ص�����
	int checkpoint1 = 0;
	// ��2�ص�����
	int checkpoint2 = 0;
	// ��3�ص�����
	int checkpoint3 = 0;
	// ���Ĺص�����
	int checkpoint4 = 0;
	// �Ż��ٻ�����
	int wingPlaneTimes = 2;
	// �����ȴ�ʱ��
	int wait = 0;
private:
	// �ɻ����з���
	int update = 1;
	int position = rand() % 3 - 1;
	int tag = 0;
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

