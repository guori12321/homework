#include <afxwin.h>

BITMAP bm;
int x = 0;
int y = 0;
bool flag[4];
bool clicked[4];
bool refresh[4];
int po[4];
int WIDTH = 400;
int HEIGHT = 300;
int picWIDTH = 200;
int picHEIGHT = 300;

//memset(clicked, true, sizeof(clicked));

class CGameWnd : public CFrameWnd
{
public:
	CGameWnd()
	{
		memset(clicked, false, sizeof(clicked));
		memset(refresh, true, sizeof(clicked));
		Create(0,"GR_Poker");

		CClientDC dc(this);
		int width = dc.GetDeviceCaps(HORZRES);
		int height = dc.GetDeviceCaps(VERTRES);
		width = (width-WIDTH)/2;
		height = (height-HEIGHT)/2;
		MoveWindow(width,height,WIDTH,HEIGHT,true);

		for (int i = 0; i < 4; i++)
			flag[i] = false;

		m_pmdc=new CDC;

		for (int i = 0; i < 5; i++)
		{
			bmap[i] = new CBitmap;
		}
		m_pmdc->CreateCompatibleDC(&dc);
		
		bmap[0]->m_hObject=(HBITMAP)::LoadImage(NULL,"a.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		bmap[1]->m_hObject=(HBITMAP)::LoadImage(NULL,"b.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		bmap[2]->m_hObject=(HBITMAP)::LoadImage(NULL,"c.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		bmap[3]->m_hObject=(HBITMAP)::LoadImage(NULL,"d.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		bmap[0]->GetBitmap(&bm);
		bmap[1]->GetBitmap(&bm);
		bmap[2]->GetBitmap(&bm);
		bmap[3]->GetBitmap(&bm);

		background = new CBitmap;
		background->m_hObject=(HBITMAP)::LoadImage(NULL,"background.bmp",IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		background->GetBitmap(&bm);
		
		m_pmdc->SelectObject(background);
	}
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

	public:
		CDC* m_pmdc;
		CBitmap* bmap[5], *background;
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

class CGameApp : public CWinApp
{
	BOOL InitInstance();
};

BOOL CGameApp::InitInstance()
{
	CGameWnd *pf = new CGameWnd;
	pf->ShowWindow(m_nCmdShow);
	pf->UpdateWindow();
	pf->MoveWindow(300,20,700,700);
	this->m_pMainWnd = pf;
	return TRUE;
}
CGameApp g_myapp;
BEGIN_MESSAGE_MAP(CGameWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CGameWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(flag[0])
	{
		m_pmdc->SelectObject(bmap[0]);
		dc.BitBlt(100,10,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	else
	{
		m_pmdc->SelectObject(background);
		dc.BitBlt(100,10,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	
	if(flag[1])
	{
		m_pmdc->SelectObject(bmap[1]);
		dc.BitBlt(100,340,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	else
	{
		m_pmdc->SelectObject(background);
		dc.BitBlt(100,340,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}

	if(flag[2])
	{
		m_pmdc->SelectObject(bmap[2]);
		dc.BitBlt(400,10,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	else
	{
		m_pmdc->SelectObject(background);
		dc.BitBlt(400, 10,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	
	if(flag[3])
	{
		m_pmdc->SelectObject(bmap[3]);
		dc.BitBlt(400,340,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}
	else
	{
		m_pmdc->SelectObject(background);
		dc.BitBlt(400,340,bm.bmWidth ,bm.bmHeight, m_pmdc, 0, 0, SRCCOPY);
	}

	// TODO: Add your message handler code here
	// Do not call CFrameWnd::OnPaint() for painting messages
}


void CGameWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnLButtonDown(nFlags, point);
	if((point.x>=100&&point.x<=300) && (point.y>=10&&point.y<=310))
		flag[0] = !flag[0];

	if((point.x>=100&&point.x<=300) && (point.y>=340&&point.y<=640))
		flag[1] = !flag[1];

	if((point.x>=400&&point.x<=600) && (point.y>=10&&point.y<=310))
		flag[2] = !flag[2];

	if((point.x>=400&&point.x<=600) && (point.y>=340&&point.y<=640))
		flag[3] = !flag[3];

	this->Invalidate();
}
