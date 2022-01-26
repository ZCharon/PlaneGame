#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x,int y,int nMontion, int t);
	~CBall(void);

	BOOL Draw(int, CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT=8;
	static CImageList m_Images;
	int   m_nMotion;
	int   tag;  // �ӵ��ķ��з���
	int pos = 1;   // �ӵ���������
public:
	// ������
	int damage = 1;
};
