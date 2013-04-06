#include <afxwin.h>

class GRWnd : public CFrameWnd
{
public :
	CDC * m_pmdc;
	int moving;
	GRWnd()
	{
		moving = 0;

		Create(0, (LPCTSTR)"GuoRui");
		CPaintDC dc(this);
		m_pmdc=new CDC;
		CBitmap *m_pbitmap=new CBitmap;
		m_pmdc->CreateCompatibleDC(&dc);
		m_pbitmap->m_hObject=(HBITMAP)::LoadImage(NULL,"pic.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
		m_pmdc->SelectObject(m_pbitmap);

		this->SetTimer(1, 40, NULL);
	}

	void aMove();
//	void OnPaint();

public:
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
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
	width=(width-400)/2;
	height=(height-285)/2;
	MoveWindow(width,height,400,285,true);
}

/*void GRWnd :: OnPaint()
{
	CDC* m_pmdc=new CDC;
    CBitmap * m_pbitmap=new CBitmap;
	m_pmdc->CreateCompatibleDC(dc);
    m_pbitmap->m_hObject=(HBITMAP)::LoadImage(NULL,"pic.bmp",
              IMAGE_BITMAP, 0,0,LR_LOADFROMFILE);
	m_pmdc->SelectObject(m_pbitmap);
	dc->BitBlt(0,0,400, 285, m_pmdc, 5, 5, NULL);


	return;

}*/
GRApp myApp;
BEGIN_MESSAGE_MAP(GRWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



void GRWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	dc.BitBlt(0,-40,400, 285, m_pmdc, moving, 0, SRCCOPY);
}


void GRWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		moving += 10;
		if (moving >= 19920)
			moving = 0;
		this->Invalidate();
	}
	CFrameWnd::OnTimer(nIDEvent);
}
