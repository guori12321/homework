#include <afxwin.h>
#include <ctime>
#include <math.h>

int home; //记录火箭发射时的位置

int WIDTH = 800, HEIGHT = 600; //背景的尺寸
int rocWIDTH = 15, rocHEIGHT = 75; //火箭的尺寸
int roc[3][2]; //记录三个火箭的位置
int air[10][2]; //记录十个飞机的位置
int fire[10][3]; //记录十架飞机是否被击落，有则表示应该火焰的位置和应该放第几张火焰图
int roctot, airtot;

int airWIDTH = 100, airHEIGHT = 34;
int fireWIDTH = 1200 / 8, fireHEIGHT = 120; 


class GRWnd : public CFrameWnd
{
public :
	CDC * m_pmdc, * ma, * mb, *mc, *md, *mtemp, *p0, *pm0, *p1, *pm1, *p2, *pm2, *p3, *pm3;
	CBitmap *m_pbitmap;
	CBitmap *itemp;

	GRWnd()
	{
		for (int i = 0; i < 10; i++)
			fire[i][0] = -100; //负数表示没有火焰
		airtot = 0;
		srand((unsigned)time(0));

		roctot = 0;
		home = 400;
		Create(0, (LPCTSTR)"GuoRui");
		CPaintDC dc(this);
		m_pmdc=new CDC;
		m_pbitmap=new CBitmap; 
		m_pmdc->CreateCompatibleDC(&dc);
		m_pbitmap->m_hObject=(HBITMAP)::LoadImage(NULL,"background.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		m_pmdc->SelectObject(m_pbitmap);

		ma =new CDC;
		CBitmap *m_a=new CBitmap;
		ma->CreateCompatibleDC(&dc);
		m_a->m_hObject=(HBITMAP)::LoadImage(NULL,"rocket.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		ma->SelectObject(m_a);

		mb =new CDC;
		CBitmap *m_b=new CBitmap;
		mb->CreateCompatibleDC(&dc);
		m_b->m_hObject=(HBITMAP)::LoadImage(NULL,"airport.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		mb->SelectObject(m_b);

		mc =new CDC;
		CBitmap *m_c=new CBitmap;
		mc->CreateCompatibleDC(&dc);
		m_c->m_hObject=(HBITMAP)::LoadImage(NULL,"fire.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		mc->SelectObject(m_c);


		pm0 =new CDC;
		CBitmap *m_pm0=new CBitmap;
		pm0->CreateCompatibleDC(&dc);
		m_pm0->m_hObject=(HBITMAP)::LoadImage(NULL,"rocket.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		pm0->SelectObject(m_pm0);

		pm1 =new CDC;
		CBitmap *m_pm1=new CBitmap;
		pm1->CreateCompatibleDC(&dc);
		m_pm1->m_hObject=(HBITMAP)::LoadImage(NULL,"pm1.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		pm1->SelectObject(m_pm1);

		p1 =new CDC;
		CBitmap *m_p1=new CBitmap;
		p1->CreateCompatibleDC(&dc);
		m_p1->m_hObject=(HBITMAP)::LoadImage(NULL,"p1.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		p1->SelectObject(m_p1);

		pm2 =new CDC;
		CBitmap *m_pm2=new CBitmap;
		pm2->CreateCompatibleDC(&dc);
		m_pm2->m_hObject=(HBITMAP)::LoadImage(NULL,"pm2.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		pm2->SelectObject(m_pm2);

		p2 =new CDC;
		CBitmap *m_p2=new CBitmap;
		p2->CreateCompatibleDC(&dc);
		m_p2->m_hObject=(HBITMAP)::LoadImage(NULL,"p2.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		p2->SelectObject(m_p2);

		pm3 =new CDC;
		CBitmap *m_pm3=new CBitmap;
		pm3->CreateCompatibleDC(&dc);
		m_pm3->m_hObject=(HBITMAP)::LoadImage(NULL,"pm3.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		pm3->SelectObject(m_pm3);

		p3 =new CDC;
		CBitmap *m_p3=new CBitmap;
		p3->CreateCompatibleDC(&dc);
		m_p3->m_hObject=(HBITMAP)::LoadImage(NULL,"p3.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		p3->SelectObject(m_p3);

		itemp = new CBitmap;
		itemp->CreateCompatibleBitmap(&dc, WIDTH, HEIGHT);

		mtemp = new CDC;
		mtemp->CreateCompatibleDC(&dc);
		mtemp->SelectObject(itemp);

		this->SetTimer(1, 50, NULL);
	}

	void aMove();
	void paint();

public:
	
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};

class GRApp : public CWinApp
{
public:
	GRWnd *wd;
	BOOL InitInstance();
};

BOOL GRApp :: InitInstance()
{
		wd= new GRWnd;
		wd->ShowWindow(m_nCmdShow);
		wd->UpdateWindow();
		//wd->MoveWindow(100,100,400,300);
		wd->aMove();
		this->m_pMainWnd=wd;
		return TRUE;
}

void GRWnd :: aMove()
{
	
	CClientDC *dc = new CClientDC(this);
	int width=dc->GetDeviceCaps(HORZRES);
	int height=dc->GetDeviceCaps(VERTRES);
	//GetWindowRect(&rect);
	width=(width-WIDTH)/2;
	height=(height-HEIGHT)/2;
	MoveWindow(width,height,WIDTH,HEIGHT,true);
}

void GRWnd::paint()
{
		CClientDC dc(this); // device context for painting
		
		mtemp->BitBlt(0,0,WIDTH ,HEIGHT , m_pmdc, 0, 0, SRCCOPY);
		
		//发射台的火箭
		mtemp->BitBlt(home, 480, rocWIDTH, rocHEIGHT, ma, rocWIDTH, 0, SRCAND);
		mtemp->BitBlt(home, 480, rocWIDTH, rocHEIGHT, ma, 0, 0, SRCPAINT);
		
		//在天上的火箭
		for (int i = 0; i < roctot; i++)
		{
			mtemp->BitBlt(roc[i][0], roc[i][1], rocWIDTH, rocHEIGHT, ma, rocWIDTH, 0, SRCAND);
			mtemp->BitBlt(roc[i][0], roc[i][1], rocWIDTH, rocHEIGHT, ma, 0, 0, SRCPAINT);
		}

		//在天上的飞机
		for (int i = 0; i < airtot; i++)
		{
			mtemp->BitBlt(air[i][0], air[i][1], airWIDTH, airHEIGHT, mb, 0, airHEIGHT, SRCAND);
			mtemp->BitBlt(air[i][0], air[i][1], airWIDTH, airHEIGHT, mb, 0, 0, SRCPAINT);
		}
		
		//在天上的火焰
		for (int i = 0; i < 10; i++)
			if (fire[i][0] >= 0)
			{
				mtemp->BitBlt(fire[i][0], fire[i][1], fireWIDTH, fireHEIGHT, mc, fireWIDTH * fire[i][2], fireHEIGHT, SRCAND);
				mtemp->BitBlt(fire[i][0], fire[i][1], fireWIDTH, fireHEIGHT, mc, fireWIDTH * fire[i][2], 0, SRCPAINT);
			}

		dc.BitBlt(0,0,WIDTH ,HEIGHT , mtemp, 0, 0, SRCCOPY);
}

GRApp myApp;
BEGIN_MESSAGE_MAP(GRWnd, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void GRWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		for (int i = 0; i < roctot; i++)
		{
			roc[i][1] -= 10;
		}

		for (int i = 0; i < airtot; i++)
		{
			air[i][0] -= 10;
		}

		//火箭飞出屏幕的情况
		for (int i = 0; i < roctot; i++)
			if (roc[i][1] < 0 - rocHEIGHT)
			{
				roc[i][0] = roc[roctot-1][0];
				roc[i][1] = roc[roctot-1][1];
				roctot--;
			}

		for (int i = 0; i < airtot; i++)
			if (air[i][0] < 0 - airWIDTH)
			{
				air[i][0] = air[airtot-1][0];
				air[i][1] = air[airtot-1][1];
				airtot--;
			}

		//刷新火焰
		for (int i = 0; i < 10; i++)
			if (fire[i][0] >= 0)
			{
				fire[i][2] += 1;
				if (fire[i][2] >= 8)
					fire[i][0] = -100;
			}
			
		//经测试，每50毫秒有12分之一的概率出现飞机的话，效果最好
		int a = rand() % 12;
		//int a = 1;
		if (a == 1 && airtot < 10)
		{
			air[airtot][0] = 800;
			air[airtot][1] = rand() % 400;
			airtot ++;
		}

		for (int i = 0; i < roctot; i++)
			for (int j = 0; j < airtot; j++)
			{
				if ( abs(roc[i][0] - air[j][0]) < airWIDTH
					&& abs(roc[i][1] - air[j][1]) < airHEIGHT)
				{
					fire[j][0] = air[j][0];
					fire[j][1] = air[j][1];
					fire[j][2] = 0;

					air[j][0] = air[airtot-1][0];
					air[j][1] = air[airtot-1][1];
					airtot--;

					roc[i][0] = roc[roctot-1][0];
					roc[i][1] = roc[roctot-1][1];
					roctot--;
				}
			}
		paint();
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void GRWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar)
	{
	case VK_LEFT:
		home -= 10;
		break;
	case VK_RIGHT:
		home += 10;
		break;
	case VK_SPACE:
		if (roctot < 3)
		{	
			roc[roctot][0] = home;
			roc[roctot][1] = 480;
			roctot++;
		}
		break;
	}

	paint();
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
