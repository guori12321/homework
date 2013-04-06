#include <afxwin.h>
#include <ctime>

int WIDTH = 550, HEIGHT = 367;
bool click; //记录是否点下鼠标
int picWIDTH = 132, picHEIGHT = 91;
int num;
int x, y; //记录鼠标位置
int tot, hittot; //分别为出现的老鼠总数和已经击中的老鼠总数
int pos[6][2]; //六只老鼠的位置
int dishu; //第几只老鼠出现
class GRWnd : public CFrameWnd
{
public :
	CDC * m_pmdc, * ma, * mb, *mc, *md ;
	int moving;
	GRWnd()
	{
		ShowCursor(false);
		click = false;
		srand((unsigned)time(0));
		dishu = rand() % 6;

		moving = 0;
		tot = 0;
		hittot = 0;

		Create(0, (LPCTSTR)"GuoRui");
		CPaintDC dc(this);
		m_pmdc=new CDC;
		CBitmap *m_pbitmap=new CBitmap;
		m_pmdc->CreateCompatibleDC(&dc);
		m_pbitmap->m_hObject=(HBITMAP)::LoadImage(NULL,"background.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		m_pmdc->SelectObject(m_pbitmap);

		ma =new CDC;
		CBitmap *m_a=new CBitmap;
		ma->CreateCompatibleDC(&dc);
		m_a->m_hObject=(HBITMAP)::LoadImage(NULL,"b.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		ma->SelectObject(m_a);

		mb =new CDC;
		CBitmap *m_b=new CBitmap;
		mb->CreateCompatibleDC(&dc);
		m_b->m_hObject=(HBITMAP)::LoadImage(NULL,"ham1.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		mb->SelectObject(m_b);

		mc =new CDC;
		CBitmap *m_c=new CBitmap;
		mc->CreateCompatibleDC(&dc);
		m_c->m_hObject=(HBITMAP)::LoadImage(NULL,"ham2.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		mc->SelectObject(m_c);


		for (int i = 0; i < 6; i++)
		{
			pos[i][0] = WIDTH/4 * (i % 3 +1) - picWIDTH / 2;
			pos[i][1] = HEIGHT/3 * (i % 2 +1)- picHEIGHT / 2 ;
		}
		this->SetTimer(1, 2000, NULL);
	}

	void aMove();
//	void OnPaint();

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
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void GRWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.BitBlt(0,0,WIDTH ,HEIGHT , m_pmdc, moving, 0, SRCCOPY);
	/*for (int i = 0; i < 6; i++)
	{*/
	dc.BitBlt(pos[dishu][0], pos[dishu][1],picWIDTH/2, picHEIGHT , ma, picWIDTH/2, 0, SRCAND);
	dc.BitBlt(pos[dishu][0], pos[dishu][1],picWIDTH/2, picHEIGHT, ma, 0, 0, SRCPAINT);
	//}

	if (click)
	{
		dc.BitBlt(x, y, 68, 68, mb, 0, 68, SRCAND);
		dc.BitBlt(x, y, 68, 68, mc, 0, 68, SRCPAINT);
	}
	else
	{
		dc.BitBlt(x, y, 68, 68, mb, 0, 0, SRCAND);
		dc.BitBlt(x, y, 68, 68, mc, 0, 0, SRCPAINT);
	}
}


void GRWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		tot++;
		hittot = 0;//到时间了还没打中，则连续击中数目为0

		int old = dishu;
		while (dishu == old)
		{
			dishu = rand() % 6;
		}
		this->Invalidate();
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void GRWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnLButtonDown(nFlags, point);
	x = point.x;
	y = point.y;
	click = true;

	if ( (x >= pos[dishu][0] - 68 ) && (x <= pos[dishu][0] + picWIDTH/2 + 68 )
			&& (y >= pos[dishu][1] - 68 ) && (y <= pos[dishu][1] + picHEIGHT + 68 ))
	{
		tot++;
		hittot++;
		
		int old = dishu;
		while (dishu == old)
		{
			dishu = rand() % 6;
		}
	}

	if (hittot == 3)
	{
		MessageBox("You Win!");
		hittot = 0;
		tot = 0;
	}

	if (tot == 10)
	{
		MessageBox("You Lost!");
		hittot = 0;
		tot = 0;
	}
	/*if(x>=pt[lastPo].x && x<=(pt[lastPo].x+124) && y>=pt[lastPo].y && y<=(pt[lastPo].y+85))
	{
		hit = true;
	}*/

	Invalidate();
}


void GRWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	x = point.x;
	y = point.y;
	/*if(x>=0 && x<=433 && y>=0 && y<=348)
	{
		ShowCursor(false);
	}
	else
		ShowCursor(true);
	*/
	Invalidate();
	CFrameWnd::OnMouseMove(nFlags, point);
}


void GRWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	click = false;
	Invalidate();
	CFrameWnd::OnLButtonUp(nFlags, point);
}
