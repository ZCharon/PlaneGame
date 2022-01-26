#pragma once
#include "stdafx.h"
#include "gameobject.h"
#include "MyPlane.h"

class CEnemy2 :public CGameObject
{
public:
	CEnemy2(void);
	~CEnemy2(void);

	BOOL Draw(int, CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ENEMY_HEIGHT, m_ptPos.y + ENEMY_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int m_nMotion;//���� 1->���� 0->ֹͣ 
	//ͼ������
	// int m_nImgIndex;
	//�ٶ�
	int m_V;
	int m_nWait;//������ʱ
	int blood = 5;
	// �����м�Ѫ
	bool beInjured(int);
public:
	// ���
	static bool shooting(CMyPlane*, CObList*, int, int);
	static bool beShootDown(CObList*, int, int, int);
};
