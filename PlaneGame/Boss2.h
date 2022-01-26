#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MyPlane.h"
#include "Boss.h"

class Boss2 :
	 public Boss
{
public:
	Boss2(void);
	~Boss2(void);

	BOOL Draw(int position, CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS1_HEIGHT, m_ptPos.y + BOSS1_HEIGHT));
	}


	int GetMontion() const
	{
		return m_nMotion;
	}

	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static const int BOSS1_HEIGHT = 159;
	static const int BOSS1_WIDTH = 87;
	static CImageList m_Images;
	int m_nMotion;//���� 1->���� 0->ֹͣ 
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int m_nWait;//������ʱ
	int blood = 100; // boss2Ѫ��
public:
	bool ifOutSide();
	// boss������
	static int sumNum;
	static bool shooting(CMyPlane*, CObList*, int, int);
	static bool beShootDown(CObList*, int, int, int);
	bool beInjured(int);
};

