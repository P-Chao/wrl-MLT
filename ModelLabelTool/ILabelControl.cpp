/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 315
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "ILabelControl.h"
#include "ModelLabelToolDlg.h"
extern CModelLabelToolDlg* pMainWin;
CILabelControl::CILabelControl()
{
	m_labelstate = ShowNone;
	m_cursor = OnNormal;
	m_iIsDrag = -1;
}

CILabelControl::~CILabelControl()
{
}

void CILabelControl::DoCreate(CRect rect, CWnd *parent){

}

BEGIN_MESSAGE_MAP(CILabelControl, CStatic)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	
END_MESSAGE_MAP()

void CILabelControl::ShowMat(cv::Mat & img){
	//m_img = cv::imread("temp.png");
	//cv::swap(m_img, img);
	img.copyTo(m_img);
	int w = img.cols;
	int h = img.rows;  
	int chinnels = img.channels();
	CI.Destroy(); 
	CI.Create(w, h, 8 * chinnels);
	RGBQUAD* ColorTable;
	int MaxColors = 256;  
	ColorTable = new RGBQUAD[MaxColors];
	CI.GetColorTable(0, MaxColors, ColorTable);  
	for (int i = 0; i<MaxColors; i++){
		ColorTable[i].rgbBlue = (BYTE)i;
		ColorTable[i].rgbGreen = (BYTE)i;
		ColorTable[i].rgbRed = (BYTE)i;
	}
	CI.SetColorTable(0, MaxColors, ColorTable);
	delete[]ColorTable;
	if (chinnels == 1){  
		uchar *pS;
		uchar *pImg = (uchar *)CI.GetBits();
		int step = CI.GetPitch();
		for (int i = 0; i<h; i++){
			pS = img.ptr<uchar>(i);
			for (int j = 0; j<w; j++){
				*(pImg + i*step + j) = pS[j];
			}
		}
	}
	if (chinnels == 3){
		uchar *pS;
		uchar *pImg = (uchar *)CI.GetBits(); 
		int step = CI.GetPitch();   
		for (int i = 0; i<h; i++){
			pS = img.ptr<uchar>(i);
			for (int j = 0; j<w; j++){
				for (int k = 0; k<3; k++)
					*(pImg + i*step + j * 3 + k) = pS[j * 3 + k];   
			}
		}
	}  
	CWnd * pCWnd = CWnd::FromHandle(GetSafeHwnd());//通过变量得到dc比较复杂，但很好用   
	CPaintDC dc(pCWnd);
	Invalidate(false);
	CRect rect;
	this->GetWindowRect(&rect);  // m_pic.GetWind...
	this->ScreenToClient(&rect);   
	CI.StretchBlt(dc.m_hDC, rect, SRCCOPY);   
	CDC *pDC = GetDC();
	Invalidate(false);
	CI.StretchBlt(pDC->m_hDC, rect, SRCCOPY);//	或者 CPaintDC dc(this);CI.Draw(dc.m_hDC, 0, 0);//这个以某个dc(可以是窗口)的(0,0)为起点
}

void CILabelControl::OnSaveImg(std::string filename){
	if (!m_img.empty()){
		cv::imwrite(filename, m_img);
		std::string msg = "Saved Image: " + filename + "\n";
		pMainWin->AppendMessage(msg);
	}
}

int CILabelControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// CPaintDC dc(this);
// OnDraw(&dc);
void CILabelControl::OnDraw(CDC* ppDC){
	CDC* pDC = GetDC();
	CPen *pen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *spen = new CPen(PS_SOLID, 2, RGB(0, 0, 255));
	CRect rc;
	GetClientRect(&rc);
	CDC dcMem;
	CBitmap bmp;
	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	CBitmap *pOldBit = dcMem.SelectObject(&bmp);
	if (!CI.IsNull()){
		CI.StretchBlt(dcMem.m_hDC, rc, SRCCOPY);
	} else{
		dcMem.FillSolidRect(rc, RGB(244, 244, 244));
	}

	for (int i = 0; i < pMainWin->labelfile.m_list.size(); ++i){
		if (i == pMainWin->labelfile._idSelect){
			dcMem.SelectObject(&spen);
		} else{
			dcMem.SelectObject(&pen);
		}
		dcMem.SetROP2(R2_XORPEN);
		CPoint point = pMainWin->labelfile.m_list[i];
		CRect rect;
		rect.top = point.y - 2;
		rect.bottom = point.y + 2;
		rect.left = point.x - 2;
		rect.right = point.x + 2;
		dcMem.Rectangle(rect);
		CString str;
		str.Format(L"%d", i);
		switch (m_labelstate)
		{
		case CILabelControl::ShowAll:
			dcMem.TextOutW(point.x + 4, point.y + 2, str);
			break;
		case CILabelControl::ShowOne:
			if (i == pMainWin->labelfile._idSelect){
				dcMem.TextOutW(point.x + 4, point.y + 2, str);
			}
			break;
		case CILabelControl::ShowNone:
			break;
		default:
			break;
		}
	}
	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.DeleteDC();
	bmp.DeleteObject();
}

void CILabelControl::OnMouseMove(UINT nFlags, CPoint point)
{	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format(L"(%d,%d)", point.x, point.y);
	pMainWin->m_coord.SetWindowText(str);
	pMainWin->UpdateData(false);

	switch (m_cursor)
	{
	case CILabelControl::OnNormal:
		if (-1 != m_iIsDrag){
			pMainWin->labelfile.MoveTo(point, m_iIsDrag);
		}
		break;
	case CILabelControl::OnAdd:
		break;
	case CILabelControl::OnDelete:
		break;
	default:
		break;
	}
	OnDraw(NULL);
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT); //监控鼠标离开   
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = this->m_hWnd;
	::_TrackMouseEvent(&tme);
	CStatic::OnMouseMove(nFlags, point);
}

void CILabelControl::OnMouseLeave(){
	switch (m_cursor)
	{
	case CILabelControl::OnNormal:
		m_iIsDrag = -1;
		break;
	case CILabelControl::OnAdd:
		break;
	case CILabelControl::OnDelete:
		break;
	default:
		break;
	}
	CStatic::OnMouseLeave();
}

void CILabelControl::OnLButtonDblClk(UINT nFlags, CPoint point){
	switch (m_cursor)
	{
	case CILabelControl::OnNormal:
		break;
	case CILabelControl::OnAdd:
		break;
	case CILabelControl::OnDelete:
		m_iIsDrag = pMainWin->labelfile.SearchForID(point, 7);
		if (-1 != m_iIsDrag){
			pMainWin->labelfile.DeletePoint(m_iIsDrag);
		}
		m_iIsDrag = -1;
		break;
	default:
		break;
	}
	OnDraw(NULL);
}

void CILabelControl::OnLButtonDown(UINT nFlags, CPoint point){
	switch (m_cursor)
	{
	case CILabelControl::OnNormal:
		m_iIsDrag = pMainWin->labelfile.SearchForID(point, 7);
		if (-1 == m_iIsDrag){
			pMainWin->labelfile.InsertPoint(point);
			m_iIsDrag = pMainWin->labelfile.m_list.size() - 1;
		}
		break;
	case CILabelControl::OnAdd:
		break;
	case CILabelControl::OnDelete:
		break;
	default:
		break;
	}
	OnDraw(NULL);
	CStatic::OnLButtonDown(nFlags, point);
}


void CILabelControl::OnLButtonUp(UINT nFlags, CPoint point){
	switch (m_cursor)
	{
	case CILabelControl::OnNormal:
		if (-1 != m_iIsDrag){
			pMainWin->labelfile.MoveTo(point, m_iIsDrag);
			m_iIsDrag = -1;
		}
		break;
	case CILabelControl::OnAdd:
		break;
	case CILabelControl::OnDelete:
		break;
	default:
		break;
	}
	OnDraw(NULL);
	CStatic::OnLButtonUp(nFlags, point);
}


void CILabelControl::OnRButtonDblClk(UINT nFlags, CPoint point){

	CStatic::OnRButtonDblClk(nFlags, point);
}


void CILabelControl::OnRButtonDown(UINT nFlags, CPoint point){

	CStatic::OnRButtonDown(nFlags, point);
}


void CILabelControl::OnRButtonUp(UINT nFlags, CPoint point){

	CStatic::OnRButtonUp(nFlags, point);
}


void CILabelControl::OnCursorChoose(){
	m_cursor = OnNormal;
}

void CILabelControl::OnCursorAdd(){
	m_cursor = OnAdd;
}

void CILabelControl::OnCursorDelete(){
	m_cursor = OnDelete;
}

void CILabelControl::OnShowLabel(){
	switch (m_labelstate)
	{
	case CILabelControl::ShowAll:
		m_labelstate = ShowOne;
		break;
	case CILabelControl::ShowOne:
		m_labelstate = ShowNone;
		break;
	case CILabelControl::ShowNone:
		m_labelstate = ShowAll;
		break;
	default:
		m_labelstate = ShowOne;
		break;
	}
	OnDraw(NULL);
}
