/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 64
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#pragma once
#include "afxwin.h"
#include <opencv2\opencv.hpp>
class CILabelControl :
	public CStatic
{
public:
	//int		_idSelect;
	CILabelControl();
	~CILabelControl();
	void	DoCreate(CRect rect, CWnd *parent);
	void	ShowMat(cv::Mat &);
	void	OnDraw(CDC*);
	void	OnCursorChoose();
	void	OnCursorAdd();
	void	OnCursorDelete();
	void	OnShowLabel();
	void	OnSaveImg(std::string);
	cv::Mat	m_img;

protected:
	CWnd*	hWnd;
	HDC		hdc;
	HGLRC	hrc;
	
	CImage	CI;
	CRect	m_oldWindow;
	CRect	m_originalRect;
	int		m_iIsDrag;
	enum CursorState{
		OnNormal = 0, // 0-2都是左键事件
		OnAdd = 1,
		OnDelete = 2,
	} m_cursor;
	enum LabelState{
		ShowAll = 0,
		ShowOne = 1,
		ShowNone = 2
	} m_labelstate;

private:
	BOOL m_bCaptured;
	CSize m_sizeOffset;
	CPoint m_pointTopLeft;
	const CSize m_sizeEllipse;
	
public:
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};