#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"
#include "Ball.h"
#include "Bomb.h"
#include "Explosion.h"

CImageList CEnemy::m_Images;

CEnemy::CEnemy(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT)+1;

	//���ȷ��ͼ������
	// m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT;

	// ȡ���ӻ�������ɳ��л�
	//if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//���ȷ���ٶ�
	m_V = rand()%6+2;

	m_nWait=0;
}

CEnemy::~CEnemy(void)
{
}

BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY,RGB(0,0,0),36,35,1);
}

BOOL CEnemy::Draw(int position, CDC* pDC,BOOL bPause)
{
	m_nWait++;

	// ����ս��Ѫ��
	CPoint point0 = GetPoint();
	CPen p0(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&p0);
	CBrush b0(RGB(255, 0, 0));
	pDC->SelectObject(&b0);
	pDC->Rectangle(point0.x + 3, point0.y - 2, point0.x + (blood * 15) + 20, point0.y - 4);
	if(m_nWait>90)
		m_nWait=0;

	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if(m_ptPos.y > GAME_HEIGHT+ENEMY_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0 ,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}

BOOL CEnemy::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}

// �����м�Ѫ
int CEnemy::beInjured(int i)
{
	blood -= i;
	// TODO: �ڴ˴����ʵ�ִ���.
	return blood;
}


// ���
bool CEnemy::shooting(CMyPlane* m_pMe, CObList* m_ObjList, int enEnemy, int enBall)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = TRUE;

		////�л���ս��ǰ��
		//if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
		//	by = TRUE;
		//�л���ս������
		/*if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
			   by=  TRUE;*/

		if (by)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion(), 0));
		}
	}
	return false;
}


bool CEnemy::beShootDown(CObList* m_ObjList, int enBomb, int enEnemy, int enExplosion)
{
	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				if (pEnemy->beInjured(pBomb->damage)) {
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;

					//ɾ���л�
					m_ObjList[enEnemy].RemoveAt(ePos2);
					delete pEnemy;
					pEnemy = NULL;
					break;
				}
			}
		}
	}
	return TRUE;
}
