#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "MyPlane.h"
#include "Boss.h"

class CWingPlane :
	public CGameObject
{
public:
	CWingPlane(int);
	~CWingPlane(void);

	BOOL Draw(CPoint  ,CDC* , BOOL );
	BOOL Draw(int , CDC* , BOOL );
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
	int blood = 10; 
public:
	// boss������
	static int sumNum;
	static bool shooting(CMyPlane*, CObList*, int, int);
	static bool beShootDown(CObList*, int, int, int);
	bool beInjured(int);
	int tag;
};

