#include "StdAfx.h"
#include "Boss1.h"
#include "Ball.h"
#include "Bomb.h"
#include "Explosion.h"
#include "resource.h"

CImageList Boss1::m_Images;
int Boss1::sumNum = 0;

Boss1::Boss1(void)
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

Boss1::~Boss1(void)
{
	--sumNum;
}

BOOL Boss1::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP5, RGB(0, 0, 0), 224, 159, 1);
}

BOOL Boss1::Draw(int position, CDC* pDC, BOOL bPause)
{
	m_nWait++;

	// ����ս��Ѫ��
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	pDC->Rectangle(point0.x + 63, point0.y - 2, point0.x + (blood * 1.2) + 63, point0.y - 4);
	if (m_nWait > 90)
		m_nWait = 0;

	if (point0.x  + 230>= GAME_WIDTH && position > 0) {
		position = 0;
	}
	else if (point0.x <= 0 && position < 0) {
		position =0;
	}

	if (!bPause)
	{
		if (m_V <= 3) {
			m_V = 4;
		}
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V * 0.3;
		m_ptPos.x = m_ptPos.x + m_nMotion * m_V * position;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSS1_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS1_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL Boss1::Fired()
{
	if (m_nWait < 40 && m_nWait % 6 == 0)
		return TRUE;
	else
		return FALSE;
}

bool Boss1::ifOutSide()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	return m_ptPos.y + BOSS1_HEIGHT > GAME_HEIGHT;
	
}


bool Boss1::shooting(CMyPlane* m_pMe, CObList* m_ObjList, int enBoss1, int enBall)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enBoss1].GetHeadPosition(); ePos != NULL;)
	{
		Boss1* pEnemy = (Boss1*)m_ObjList[enBoss1].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		else {
			CPoint  ePt = pEnemy->GetPoint();

			//�л���ս��ǰ��
			/*if (pEnemy->GetMontion() < 5)
				by = TRUE;*/
			//�л���ս������
			/*if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
					by=  TRUE;*/

			m_ObjList[enBall].AddTail(new CBall(ePt.x + 100, ePt.y + 160, pEnemy->GetMontion(), 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 124, ePt.y + 160, pEnemy->GetMontion(), 0));
		}
	}
	return TRUE;
}


bool Boss1::beShootDown(CObList* m_ObjList, int enBomb, int enEnemy, int enExplosion)
{
	bool tag = false;
	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		if (pBomb != NULL) {
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				tag = true;
				Boss1* pEnemy = (Boss1*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
					);
					if (pEnemy->beInjured(pBomb->damage)) {
						//ɾ������
						m_ObjList[enBomb].RemoveAt(mPos2);
						delete pBomb;

						if (pEnemy->blood <= 0) {
							//ɾ���л�
							m_ObjList[enEnemy].RemoveAt(ePos2);
							delete pEnemy;
							break;
						}
					}
				}
			}
		}
	}
	if (tag) {
		if (sumNum <= 0) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return tag;
	
}

bool Boss1::beInjured(int i)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	--blood;
	return TRUE;
}
