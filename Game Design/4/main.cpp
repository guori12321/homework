#include <afxwin.h>
#include <ctime>

int WIDTH = 800, HEIGHT = 600;
int now[2], aim[2]; //分别为当前坐标和目的地坐标
int mg[2]; //蘑菇的坐标
bool cai; //是否已经采到蘑菇，在回家的路上

bool mogu; //记录是否点下鼠标
int picWIDTH = 132, picHEIGHT = 91;
int mgWIDTH = 60, mgHEIGHT = 74; 
int num; //应该放第几张图
int x, y; //记录鼠标位置
int step; //一步走多少像素
int dir; //方向 0-3为上下左右

class GRWnd : public CFrameWnd
{
public :
	CDC * m_pmdc, * ma, * mb, *mc, *md, *mtemp, *p0, *pm0, *p1, *pm1, *p2, *pm2, *p3, *pm3;
	CBitmap *m_pbitmap;
	CBitmap *itemp;

	GRWnd()
	{
		step = 10;
		num = 0;
		now[0] = 100; 
		now[1] = 100;
		mogu = false;
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
		m_a->m_hObject=(HBITMAP)::LoadImage(NULL,"mogua.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		ma->SelectObject(m_a);

		mb =new CDC;
		CBitmap *m_b=new CBitmap;
		mb->CreateCompatibleDC(&dc);
		m_b->m_hObject=(HBITMAP)::LoadImage(NULL,"mogub.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		mb->SelectObject(m_b);

		p0 =new CDC;
		CBitmap *m_c=new CBitmap;
		p0->CreateCompatibleDC(&dc);
		m_c->m_hObject=(HBITMAP)::LoadImage(NULL,"p0.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		p0->SelectObject(m_c);

		pm0 =new CDC;
		CBitmap *m_pm0=new CBitmap;
		pm0->CreateCompatibleDC(&dc);
		m_pm0->m_hObject=(HBITMAP)::LoadImage(NULL,"pm0.bmp",
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

public:
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

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

GRApp myApp;
BEGIN_MESSAGE_MAP(GRWnd, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void GRWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		CClientDC dc(this); // device context for painting

		//dc.BitBlt(0,0,WIDTH ,HEIGHT , m_pmdc, 0, 0, SRCCOPY);
		mtemp->BitBlt(0,0,WIDTH ,HEIGHT , m_pmdc, 0, 0, SRCCOPY);
		
		switch(dir)
		{
		case 0:
			{
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, pm0, 55*num, 0, SRCAND);
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, p0, 55*num, 0, SRCPAINT);
				break;
			}
		case 1:
			{
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, pm1, 55*num, 0, SRCAND);
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, p1, 55*num, 0, SRCPAINT);
				break;
			}
		case 2:
			{
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, pm2, 55*num, 0, SRCAND);
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, p2, 55*num, 0, SRCPAINT);
				break;
			}
		case 3:
			{
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, pm3, 55*num, 0, SRCAND);
				mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, p3, 55*num, 0, SRCPAINT);
				break;
			}
			;
		}
		/*mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, pm0, 55*num, 0, SRCAND);
		mtemp->BitBlt(now[0], now[1], mgWIDTH, mgHEIGHT, p0, 55*num, 0, SRCPAINT);
		*/
		//把蘑菇放到原处
		if (now[0] > 80 && now[0] < 120 && now[1] > 80 && now[1] < 120)
		{
			mogu = false;
			aim[0] = 600;
			aim[1] = 100;
			dir = 3;
		}
		//采到蘑菇
		if (now[0] > mg[0] - 20 && now[0] < mg[0] + 20 && now[1] > mg[1] - 20 && now[1] < mg[1]+20)
		{
			cai = true;
			aim[0] = 100;
			aim[1] = 100;
		}

		//没有蘑菇时的路线
		if (!mogu && (now[0] > 580 && now[0] < 620 && now[1] > 80 && now[1] < 120))
		{
			aim[0] = 600; 
			aim[1] = 400;
		}
		if (!mogu && (now[0] > 580 && now[0] < 620 && now[1] > 380 && now[1] < 420))
		{
			aim[0] = 100; 
			aim[1] = 400;
		}
		if (!mogu && (now[0] > 80 && now[0] < 120 && now[1] > 380 && now[1] < 420))
		{
			aim[0] = 100; 
			aim[1] = 100;
		}

		if (aim[0] > now[0] + 10)
		{
			now[0] += 10;
			dir = 3;
		}
		if (aim[0] < now[0] - 10)
		{
			now[0] -= 10;
			dir = 2;
		}
		if (aim[1] > now[1] + 10)
		{
			now[1] += 10;
			dir = 1;
		}
		if (aim[1] < now[1] - 10)
		{
			now[1] -= 10;
			dir = 0;
		}

		if (mogu && !(cai)) //如果图中有蘑菇而没有被采
		{
			mtemp->BitBlt(x, y, mgWIDTH, mgHEIGHT, mb, 0, 0, SRCAND);
			mtemp->BitBlt(x, y, mgWIDTH, mgHEIGHT, ma, 0, 0, SRCPAINT);
		}

		num = (num+1) % 8;
		dc.BitBlt(0,0,WIDTH ,HEIGHT , mtemp, 0, 0, SRCCOPY);
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void GRWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnLButtonDown(nFlags, point);

	if (!mogu)
	{
		mogu = true;
		cai = false;
		x = point.x;
		y = point.y;
		mg[0] = x;
		mg[1] = y;
		aim[0] = x;
		aim[1] = y;
	}
}

