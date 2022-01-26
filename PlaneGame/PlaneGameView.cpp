// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//
#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Bomb.h"
#include "Ball.h"
#include "bigBall.h"
#include "Explosion.h"
#include <atlimage.h>
#include "Boss1.h"
#include "Boss2.h"
#include "life.h"
#include "WingPlane.h"
#include "Boss3.h"
#include "BossFinal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL), m_pMemDC(NULL), m_pMemBitmap(NULL), m_pDC(NULL)
{
	// TODO: �ڴ˴���ӹ������
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}

void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}


// ��Ϸ��ʼ��
	
BOOL CPlaneGameView::InitGame()
{
	// ��ÿͻ�����
	CRect rc;  
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	// ����ͼƬ
	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CEnemy2::LoadImage();
	CBomb::LoadImage();
	bigBall::LoadImage();
	CBall::LoadImage();
	Boss1::LoadImage();
	Boss2::LoadImage();
	CExplosion::LoadImage();
	life::LoadImage();
	CWingPlane::LoadImage();
	Boss3::LoadImage();
	BossFinal::LoadImage();

	m_pMe = new CMyPlane;

	SetTimer(1, 30, NULL);
	return TRUE;
}


void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������->��䱳��
	// pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	//�������
	CRect rctClient;
	GetClientRect(rctClient);
	if (level == 2) {
		static int imagelocation = 0;
		CDC memDC;
		memDC.CreateCompatibleDC(pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP1);//����λͼ
		CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);
		pMemDC->BitBlt(0, imagelocation, 600, 1301 - imagelocation, &memDC, 0, 0, SRCCOPY);//���ö�̬����
		pMemDC->BitBlt(0, 0, 600, imagelocation, &memDC, 0, 1301 - imagelocation, SRCCOPY);
		imagelocation++;
		if (imagelocation == 1301)
			imagelocation = 0;
	}

	if (level == 1) {
		static int imagelocation = 0;
		CDC memDC;
		memDC.CreateCompatibleDC(pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP12);//����λͼ
		CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);
		pMemDC->BitBlt(0, imagelocation, 600, 1054 - imagelocation, &memDC, 0, 0, SRCCOPY);//���ö�̬����
		pMemDC->BitBlt(0, 0, 600, imagelocation, &memDC, 0, 1054 - imagelocation, SRCCOPY);
		imagelocation++;
		if (imagelocation == 1054)
			imagelocation = 0;
	}

	if (level == 4) {
		static int imagelocation = 0;
		CDC memDC;
		memDC.CreateCompatibleDC(pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP13);//����λͼ
		CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);
		pMemDC->BitBlt(0, imagelocation, 600, 1184 - imagelocation, &memDC, 0, 0, SRCCOPY);//���ö�̬����
		pMemDC->BitBlt(0, 0, 600, imagelocation, &memDC, 0, 1184 - imagelocation, SRCCOPY);
		imagelocation++;
		if (imagelocation == 1184)
			imagelocation = 0;
	}

	if (level == 3) {
		static int imagelocation = 0;
		CDC memDC;
		memDC.CreateCompatibleDC(pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(IDB_BITMAP2);//����λͼ
		CBitmap* pbmpold = memDC.SelectObject(&bmpDraw);
		pMemDC->BitBlt(0, imagelocation, 600, 1300 - imagelocation, &memDC, 0, 0, SRCCOPY);//���ö�̬����
		pMemDC->BitBlt(0, 0, 600, imagelocation, &memDC, 0, 1300 - imagelocation, SRCCOPY);
		imagelocation++;
		if (imagelocation == 1300)
			imagelocation = 0;
	}

	//������Ϸ������
	if(m_pMe!=NULL){
		m_pMe->Draw(0, m_pMemDC, FALSE, level);

		// ��Ϸ����
		if (model == 1) {
			CString st1 = _T("�޵�ģʽ ��O->��ͨ");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(90, 90, 90));
			pMemDC->TextOut(75, 0, st1);
		}
		else if (model == 0) {
			CString st2 = _T("��ͨģʽ : Z->�޵�");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(90, 90, 90));
			pMemDC->TextOut(75, 0, st2);
		}

		/*CString strs = _T("My plane");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(90, 90, 90));
		pMemDC->TextOut(30, 0, strs);*/

		// ս��Ѫ��

		CString str;
		CString str1 = _T("Blood��");
		str.Format(_T("%d"), m_pMe->blood);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(90, 90, 90));
		pMemDC->TextOut(35, 20, str1);//
		pMemDC->TextOut(65, 21, str);

		// ��ǰ�÷�

		CString str2;
		CString str12 = _T("Score��");
		str2.Format(_T("%d"), score); ++score;
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(90, 90, 90));
		pMemDC->TextOut(35, 35, str12);//
		pMemDC->TextOut(90, 36, str2);//

		// ��ǰ�ȼ�

		CString str3;
		CString str13 = _T("Level��");
		str3.Format(_T("%d"), level);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(90, 90, 90));
		pMemDC->TextOut(35, 50, str13);
		pMemDC->TextOut(65, 51, str3);

		// ս�����浯����

		CString str4;
		CString str14 = _T("Num of bomb:");
		str4.Format(_T("%d"), m_pMe->bigBomb);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(90, 90, 90));
		pMemDC->TextOut(53, 65, str14);
		pMemDC->TextOut(130, 66, str4);
	    m_pMe->Draw(0, m_pMemDC,FALSE);

	   CString str5 = _T("���ܣ�");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(90, 90, 90));
	   pMemDC->TextOut(525, 0, str5);

	   CString str6;
	   CString str16 = _T("�ո񣺻��浯");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(90, 90, 90));
	   pMemDC->TextOut(520, 20, str16);

	   if (level > 2) {
		   CString str7 = _T("Ctrl�����ٻ��Ż�");
		   pMemDC->SetBkMode(TRANSPARENT);
		   pMemDC->SetTextAlign(TA_CENTER);
		   pMemDC->SetTextColor(RGB(90, 90, 90));
		   pMemDC->TextOut(505, 40, str7);
	   }

	   str12 = _T("ʣ���ٻ�������");
	   str2.Format(_T("%d"), wingPlaneTimes);
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(90, 90, 90));
	   pMemDC->TextOut(510, 60, str12);
	   pMemDC->TextOut(570, 60, str2);

	   CString str8 = _T("P������ͣ");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(90, 90, 90));
	   pMemDC->TextOut(530, 80, str8);

	   CString str9 = _T("C��������");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(90, 90, 90));
	   pMemDC->TextOut(530, 100, str9);

	   if (GetKey('Z') == 1)
	   {
		   model = 1;
		   CString str = _T("�޵�״̬�ѿ���!");
		   pMemDC->SetBkMode(TRANSPARENT);
		   pMemDC->SetTextAlign(TA_CENTER);
		   pMemDC->SetTextColor(RGB(255, 0, 0));
		   pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	   }

	   if (GetKey('O') == 1)
	   {
		   model = 0;
		   CString str = _T("�޵�״̬�ѹر�!");
		   pMemDC->SetBkMode(TRANSPARENT);
		   pMemDC->SetTextAlign(TA_CENTER);
		   pMemDC->SetTextColor(RGB(255, 0, 0));
		   pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
	   }
	}
	else
	{   //Game Over
		CString str=_T("Game Over!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);

		++wait;
		if (wait > 50) {
			KillTimer(1);
			if (level < 4) {
				if (AfxMessageBox(L"���ź���սʧ�ܣ��Ƿ����¿�ʼ", MB_YESNO) != 6)
				{
					delete m_pMe;
					m_pMe = NULL;
					exit(1);
				}
				else
				{
					for (int i = 0; i < 11; i++)
						m_ObjList[i].RemoveAll();
					delete m_pMe;
					delete bossFinal;
					bossFinal = NULL;
					m_pMe = new CMyPlane;
					update = 1;
					reStart++;
					checkpoint1 = 0;
					checkpoint2 = 0;
					checkpoint3 = 0;
					checkpoint4 = 0;
					Boss1::sumNum = 0;
					Boss2::sumNum = 0;
					Boss3::sumNum = 0;
					level = 1;
					score = 0;
					tag = 0;
					wait = 0;
				}
			}
			else if (level == 4)
			{	
				if (AfxMessageBox(L"���ź���սʧ�ܣ��Ƿ�������սBOSS������", MB_YESNO) != 6)
				{
					delete m_pMe;
					m_pMe = NULL;
					exit(1);
				}
				else
				{
					for (int i = 0; i < 11; i++)
						m_ObjList[i].RemoveAll();
					delete m_pMe;
					delete bossFinal;
					bossFinal = NULL;
					m_pMe = new CMyPlane;
					m_pMe->blood = 20;
					update = 1;
					reStart++;
					checkpoint1 = 0;
					checkpoint2 = 0;
					checkpoint3 = 0;
					checkpoint4 = 0;
					Boss1::sumNum = 0;
					Boss2::sumNum = 0;
					Boss3::sumNum = 0;
					level = 4;
					score = 0;
					tag = 0;
					wait = 0;
				}
			}
			SetTimer(1, 30, NULL);
		}
	}
	
	//���� ��������ը���л����ӵ�
	for(int i=0;i<4;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(0, pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	
	// ����boss1
	POSITION pos1, pos2;
	for (pos1 = m_ObjList[enBoss1].GetHeadPosition(); (pos2 = pos1) != NULL; )
	{
		if (level == 2 && tag <= 70) {
			CString str = _T("BOSS COMING ! ! ! ! ! !");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
			++tag;
		}

		CGameObject* pObj = (CGameObject*)m_ObjList[enBoss1].GetNext(pos1);

		if (score % 50 == 0) {
			position = rand() % 3 - 1;
		}

		if (((Boss1*)pObj)->ifOutSide()) {
			delete m_pMe;
			m_pMe = NULL;
		}
		if (!pObj->Draw(position, pMemDC, FALSE))
		{
			m_ObjList[enBoss1].RemoveAt(pos2);
			delete pObj;
		}
	}

	// ����boss2

	for (pos1 = m_ObjList[enBoss2].GetHeadPosition(); (pos2 = pos1) != NULL; )
	{
		if (level == 2 && tag <= 70) {
			CString str = _T("BOSS COMING ! ! ! ! ! !");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
			++tag;
		}

		CGameObject* pObj = (CGameObject*)m_ObjList[enBoss2].GetNext(pos1);

		if (score % 50 == 0) {
			position = rand() % 3 - 1;
		}

		if (((Boss2*)pObj)->ifOutSide()) {
			delete m_pMe;
			m_pMe = NULL;
		}
		if (!pObj->Draw(position, pMemDC, FALSE))
		{
			m_ObjList[enBoss2].RemoveAt(pos2);
			delete pObj;
		}
	}

	// ����Enemy2
	
	for (pos1 = m_ObjList[enEnemy2].GetHeadPosition(); (pos2 = pos1) != NULL; )
	{
		CGameObject* pObj = (CGameObject*)m_ObjList[enEnemy2].GetNext(pos1);

		int positionEnemy2 = 0;
		if (score % 50 == 0) {
			positionEnemy2 = rand() % 3 - 1;
		}
		if (!pObj->Draw(positionEnemy2, pMemDC, FALSE))
		{
			m_ObjList[enEnemy2].RemoveAt(pos2);
			delete pObj;
		}
	}
	

	// �����Ż�
	if (level > 2 && m_pMe != NULL) {
		for (pos1 = m_ObjList[enWingPlane].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CWingPlane* pObj = (CWingPlane*)m_ObjList[enWingPlane].GetNext(pos1);

			if (!pObj->Draw(m_pMe->GetPoint(), pMemDC, FALSE))
			{
				m_ObjList[enWingPlane].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	// ����Boss3
	
	for (pos1 = m_ObjList[enBoss3].GetHeadPosition(); (pos2 = pos1) != NULL; )
	{
		if (level == 3 && tag <= 70) {
			CString str = _T("BOSS COMING ! ! ! ! ! !");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextAlign(TA_CENTER);
			pMemDC->SetTextColor(RGB(255, 0, 0));
			pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
			++tag;
		}

		CGameObject* pObj = (CGameObject*)m_ObjList[enWingPlane].GetNext(pos1);

		if (score % 50 == 0) {
			position = rand() % 3 - 1;
		}

		if (((Boss3*)pObj)->ifOutSide()) {
			delete m_pMe;
			m_pMe = NULL;
		}
		if (!pObj->Draw(position, pMemDC, FALSE))
		{
			m_ObjList[enWingPlane].RemoveAt(pos2);
			delete pObj;
		}
	}
	

	// ����BossFinal
	if (level > 3) {
		if(bossFinal != NULL)
		{
			if (level == 4 && tag <= 70) {
				CString str = _T("BOSS COMING ! ! ! ! ! !");
				pMemDC->SetBkMode(TRANSPARENT);
				pMemDC->SetTextAlign(TA_CENTER);
				pMemDC->SetTextColor(RGB(255, 0, 0));
				pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
				++tag;
			}

			if (score % 50 == 0) {
				position = rand() % 3 - 1;
			}

			if (bossFinal->ifOutSide()) {
				delete m_pMe;
				m_pMe = NULL;
			}
			if (!bossFinal->Draw(position, pMemDC, FALSE))
			{
				delete bossFinal;
				bossFinal = NULL;
			}
		}
	}

	if (level > 1) {
		// ����ؿ�����һ�����Ʋ�Ѫ��
		for (pos1 = m_ObjList[enlife].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[enlife].GetNext(pos1);

			if (!pObj->Draw(0, pMemDC, FALSE))
			{
				m_ObjList[enlife].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}



void CPlaneGameView::AI()
{
	// ������Ϸ
	if (score <= 1 && reStart <= 0 && level <= 1) {
		KillTimer(1);
		if (AfxMessageBox(L"Ҫ��ʼ��Ϸ��", MB_YESNO) == 6)
		{
			AfxMessageBox
			(L"��Ϸ����\n 1. ��Ϸ��Ϊ�ĸ��ؿ���ÿ��һ��Boss������Boss����ͨ�ء���;�����ܻ�Boss�����±߽���սʧ��\n 2. ս������������浯���������������ﵽ����һ��ʱ���ɷ�����浯");
			SetTimer(1, 30, NULL);
		}
		else
		{
			exit(1);
		}
	}

	static int nCreator = rand() %5+10;
	static int nCreator2 = rand() % 5 + 10;

	if (level > 1) {
		// ������
		
		if (nCreator2 <= 0)
		{
			nCreator2 = rand() % 1000 + 10;
			m_ObjList[enlife].AddTail(new life);
		}
		nCreator2--;
		
	}

	//��������л�
	if(nCreator<=0)
	{
		if (level == 1) {
			nCreator = rand() % 5 + 30;
			// enEnemy��ö������
			m_ObjList[enEnemy].AddTail(new CEnemy);
			if (score > 1000 && Boss1::sumNum < 1 && checkpoint1 <= 0) {
				m_ObjList[enBoss1].AddTail(new Boss1);
			}
		}
		else if (level == 2) {
			nCreator = rand() % 5 + 10;
			// enEnemy��ö������
			m_ObjList[enEnemy].AddTail(new CEnemy);
			if (score > 1000 && Boss2::sumNum < 1 && checkpoint2 <= 0) {
				m_ObjList[enBoss2].AddTail(new Boss2);
			}
		}
		else if (level == 3) {
			if (score > 1500) {
				nCreator = rand() % 5 + 60;
			}
			else {
				nCreator = rand() % 5 + 20;
			}
			
			if (nCreator % 2 == 0) {
				// enEnemy��ö������
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}
			else {
				m_ObjList[enEnemy2].AddTail(new CEnemy2);
			}
			if (score > 1000 && Boss3::sumNum < 1 && checkpoint3 <= 0) {
				m_ObjList[enBoss3].AddTail(new Boss3);
			}
		}
		else if (level == 4) {
			if (score < 500) {
				nCreator = rand() % 5 + 30;
				m_ObjList[enEnemy2].AddTail(new CEnemy2);
			}
			else {
				if (bossFinal == NULL) {
					if (Boss3::sumNum < 1 && checkpoint4 <= 0) {
						bossFinal = new BossFinal;
					}
				}
			}
		}
	}
	nCreator--;

	// ���ս���Ѿ����
	if(m_pMe==NULL)
		return;

	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	
	// �����Ż�
	if (level >= 3 && wingPlaneTimes > 0 && m_ObjList[enWingPlane].GetHeadPosition() == NULL) {
		if (GetKey(VK_CONTROL) == 1 && wingPlaneTimes > 0) {
			m_ObjList[enWingPlane].AddTail(new CWingPlane(-1));
			m_ObjList[enWingPlane].AddTail(new CWingPlane(1));
			--wingPlaneTimes;
		}
	}

	//����ս������
	if(GetKey(VK_SPACE)==1)//�����˿ո��
	{
		if(m_pMe!=NULL && m_pMe->Fired() && m_pMe ->bigBomb > 500)
		{
			CPoint pt = m_pMe->GetPoint();
			if (model == 0)
			{
				m_pMe->bigBomb -= 10;
			}
			// �����������浯������
			m_ObjList[enBomb].AddTail(new bigBall(pt.x+20,pt.y + 10, -1));
			m_ObjList[enBomb].AddTail(new bigBall(pt.x + 40, pt.y, 0));
			m_ObjList[enBomb].AddTail(new bigBall(pt.x+60,pt.y + 10, 1));
		}
	}
	else {
		if (m_pMe->bigBomb <= 1000) {
			++m_pMe->bigBomb;
		}
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			// ������������
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 34, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 50, pt.y + 10));
		}
	}

	//�л�1�����ӵ�
	CEnemy::shooting(m_pMe, m_ObjList, enEnemy, enBall);
	// boss1�����ӵ�
	Boss1::shooting(m_pMe, m_ObjList, enBoss1, enBall);
	// boss2�����ӵ�
	Boss2::shooting(m_pMe, m_ObjList, enBoss2, enBall);
	// �л�2�����ӵ�
	CEnemy2::shooting(m_pMe, m_ObjList, enEnemy2, enBall);
	// �Ż������ӵ�
	CWingPlane::shooting(m_pMe, m_ObjList, enWingPlane, enBomb);
	// boss3�����ӵ�
	Boss3::shooting(m_pMe, m_ObjList, enBoss3, enBall);
	if (bossFinal != NULL) {
		bossFinal->shooting(m_pMe, m_ObjList, enBall);
	}

	// ��Ѫ
	m_pMe->addBlood(m_ObjList, enlife);
	// ���ս���������
	if (m_pMe->beShootDown(m_ObjList, enBall, enExplosion, model)){
		delete m_pMe;
		m_pMe = NULL;
	}

	// ����Ż��������
	CWingPlane::beShootDown(m_ObjList, enBall, enWingPlane, enExplosion);
	//ս������ը���л�1
	CEnemy::beShootDown(m_ObjList, enBomb, enEnemy, enExplosion);
	//ս�����浯ը�ٵл�1
	CEnemy::beShootDown(m_ObjList, enBigBall, enEnemy, enExplosion);
	//ս������ը���л�2
	CEnemy2::beShootDown(m_ObjList, enBomb, enEnemy2, enExplosion);
	//ս�����浯ը�ٵл�2
	CEnemy2::beShootDown(m_ObjList, enBigBall, enEnemy2, enExplosion);


	// ���boos1���ݻ٣��ҵ�ǰΪ��һ�أ�����ڶ���
	if ((Boss1::beShootDown(m_ObjList, enBomb, enBoss1, enExplosion) ||
		Boss1::beShootDown(m_ObjList, enBigBall, enBoss1, enExplosion)) && level == 1)
	{
		checkpoint1 = 1;
	}
	if (checkpoint1 > 0 && level == 1) {
		++checkpoint1;
		if (checkpoint1 >= 30) {
			KillTimer(1);
			if (AfxMessageBox(L"��ϲͨ����һ�أ��Ƿ����ڶ���", MB_YESNO) != 6)
			{
				delete m_pMe;
				m_pMe = NULL;

			}
			else
			{
				for (int i = 0; i < 11; i++)
					m_ObjList[i].RemoveAll();
				delete m_pMe;
				m_pMe = new CMyPlane;
				m_pMe->blood += 5;
				level = 2;
				score = 0;
				tag = 0;

				AfxMessageBox(L"ս��Ѫ�����޼��壬���ֺ��Ĳ�Ѫ��ÿ�β�����Ѫ��");
			}
			SetTimer(1, 30, NULL);
		}
	}

	// ���boos2���ݻ٣��ҵ�ǰΪ�ڶ��أ����������
	if ((Boss2::beShootDown(m_ObjList, enBomb, enBoss2, enExplosion) ||
		Boss2::beShootDown(m_ObjList, enBigBall, enBoss2, enExplosion)) && level == 2)
	{
		checkpoint2 = 1;
	}
	if (checkpoint2 > 0) {
		++checkpoint2;
		if (checkpoint2 >= 30 && level == 2) {
			KillTimer(1);
			if (AfxMessageBox(L"��ϲͨ���ڶ��أ��Ƿ���������", MB_YESNO) != 6)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			else
			{
				for (int i = 0; i < 11; i++)
					m_ObjList[i].RemoveAll();
				delete m_pMe;
				m_pMe = new CMyPlane;
				level = 3;
				score = 0;
				m_pMe->blood += 10;
				tag = 0;
				AfxMessageBox(L"ս��Ѫ�����޼��壬��ctrl�ٻ��Ż���ÿ�ؿ��ٻ�����");
			}
			SetTimer(1, 30, NULL);
		}
	}


	// ���boos3���ݻ٣��ҵ�ǰΪ�����أ�������Ĺ�
	if ((Boss3::beShootDown(m_ObjList, enBomb, enBoss3, enExplosion) ||
		Boss3::beShootDown(m_ObjList, enBigBall, enBoss3, enExplosion)) && level == 3 )
	{
		checkpoint3 = 1;
	}
	if (checkpoint3 > 0 && level == 3) {
		++checkpoint3;
		if (checkpoint3 >= 30) {
			KillTimer(1);
			if (AfxMessageBox(L"��ϲͨ�������أ��Ƿ������Ĺ�", MB_YESNO) != 6)
			{
				delete m_pMe;
				m_pMe = NULL;
			}
			else
			{
				for (int i = 0; i < 11; i++)
					m_ObjList[i].RemoveAll();
				delete m_pMe;
				m_pMe = new CMyPlane;
				level = 4;
				tag = 0;
				score = 0;
				m_pMe->blood += 15;
				AfxMessageBox(L"ս��Ѫ�����޼��壬����BOSS�أ���������");
			}
			SetTimer(1, 30, NULL);
		}
	}

	// bossFinal���ݻ�
	if (level == 4 && bossFinal != NULL) {
		if ((bossFinal->beShootDown(m_ObjList, enBomb, enExplosion) ||
			bossFinal->beShootDown(m_ObjList, enBigBall, enExplosion)))
		{
			checkpoint4 = 1;
			delete bossFinal;
			bossFinal = NULL;
		}
	}
	if (checkpoint4 > 0 && level == 4) {
		++checkpoint4;
		if (checkpoint4 >= 20) {
			KillTimer(1);
			if (AfxMessageBox(L"��ϲͨ�أ��Ƿ����¿�ʼ", MB_YESNO) != 6)
			{
				delete m_pMe;
				m_pMe = NULL;
				exit(1);
			}
			else

			{
				for (int i = 0; i < 11; i++)
					m_ObjList[i].RemoveAll();
				delete m_pMe;
				delete bossFinal;
				bossFinal = NULL;
				m_pMe = new CMyPlane;
				reStart++;
				checkpoint1 = 0;
				checkpoint2 = 0;
				checkpoint3 = 0;
				checkpoint4 = 0;
				level = 1;
				score = 0;
				tag = 0;
				m_pMe->blood = 5;
				// AfxMessageBox(L"ս��Ѫ�����޼��壬����BOSS�أ���������");
			}
			SetTimer(1, 30, NULL);
		}
	}
}
	

// WM_TIMER��Ϣ��Ӧ����

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{

	if (GetKey('P') == 1)
	{
		update = 0;
	}
	if (GetKey('C') == 1)
	{
		update = 1;
	}

	if (update != 0)
	{
		//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
		UpdateFrame(m_pMemDC);
		AI();
	}
	
	CView::OnTimer(nIDEvent);
}


void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������
}
