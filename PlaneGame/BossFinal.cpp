#include "StdAfx.h"
#include "Ball.h"
#include "BossFinal.h"
#include "Bomb.h"
#include "Explosion.h"
#include "resource.h"

CImageList BossFinal::m_Images;
int BossFinal::sumNum = 0;

BossFinal::BossFinal(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS1_HEIGHT) + 1;

	//���ȷ��ͼ������
	// m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -BOSS1_HEIGHT;

	// ȡ���ӻ�������ɳ��л�
	//if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;
	++sumNum;
	m_nWait = 0;
}

BossFinal::~BossFinal(void)
{
	--sumNum;
}

BOOL BossFinal::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP11, RGB(0, 0, 0), 174, 298, 1);
}

BOOL BossFinal::Draw(int position, CDC* pDC, BOOL bPause)
{
	m_nWait++;

	// ����ս��Ѫ��
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	pDC->Rectangle(point0.x + 20, point0.y - 2, point0.x + (blood / 2) + 10, point0.y - 4);
	if (m_nWait > 1000)
		m_nWait = 0;

	if (point0.x + 230 >= GAME_WIDTH && position > 0) {
		position = 0;
	}
	else if (point0.x <= 0 && position < 0) {
		position = 0;
	}

	if (!bPause)
	{
		if (m_V <= 3) {
			m_V = 4;
		}
		if (m_ptPos.y < 60) {
			m_ptPos.y = m_ptPos.y + m_nMotion;
		}
		m_ptPos.x = m_ptPos.x + m_nMotion * m_V * position;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSS1_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS1_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}


int BossFinal::Fired()
{
	if (m_nWait < 400 && m_nWait > 0) {
		if (m_nWait % 100 > 0 && m_nWait % 100 < 30 && m_nWait % 3 == 0)
			return 1;
		else return 0;
	}
	else if (m_nWait > 400 && m_nWait < 800) {
		if (m_nWait % 100 > 0 && m_nWait % 100 < 60 && m_nWait % 10 == 0)
			return 2;
		else return 0;
	}
	else if (m_nWait > 800 && m_nWait < 1000) {
		if (m_nWait % 100 > 0 && m_nWait % 100 < 30 )
			return 3;
		else return 0;
	}

}


bool BossFinal::ifOutSide()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return m_ptPos.y + BOSS1_HEIGHT > GAME_HEIGHT;

}

bool BossFinal::shooting(CMyPlane* m_pMe, CObList* m_ObjList, int enBall)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	if (Fired() == 0) {
		return FALSE;
	}
	else {
		CPoint  ePt = GetPoint();
		//�л���ս��ǰ��
		/*if (pEnemy->GetMontion() < 5)
			by = TRUE;*/
			//�л���ս������
			/*if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
					by=  TRUE;*/
		if (Fired() == 1) {
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 27, ePt.y + 100, GetMontion(), 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 87, ePt.y + 280, GetMontion(), 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 147, ePt.y + 100, GetMontion(), 0));
		}
		else if (Fired() == 2) {
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 35, ePt.y + 100, GetMontion(), 3));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 45, ePt.y + 155, GetMontion(), 2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 87, ePt.y + 280, GetMontion(), 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 125, ePt.y + 155, GetMontion(), -2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 139, ePt.y + 100, GetMontion(), -3));
		}
		else if (Fired() == 3) {
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 35, ePt.y + 100, GetMontion(), 3));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 139, ePt.y + 100, GetMontion(), -3));
		}
	}
	return TRUE;
}


bool BossFinal::beShootDown(CObList* m_ObjList, int enBall, int enExplosion)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	//�л��ӵ�ը��ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			if (blood > 0) {
				--blood;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(bRect.left, bRect.top)
				);

				//ɾ���ӵ�
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;
				return FALSE;
			}
			else
			{
				// ������
				return TRUE;
			}
		}
	}
}


bool BossFinal::beInjured(int i)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	--blood;
	return TRUE;
}
