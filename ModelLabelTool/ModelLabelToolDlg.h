/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 125
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#ifndef MODEL_LABEL_TOOL_DLG_
#define MODEL_LABEL_TOOL_DLG_

#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include "afxvslistbox.h"
#include "CustomEditListBox.h"
#include "OpenGLControl.h"
#include "resource.h"
#include <iostream>
#include <vector>
#include "wrl.h"
#include "afxwin.h"
#include <opencv2\opencv.hpp>
#include "ILabelControl.h"
#include "ModelLabel.h"
#include "mlt.pb.h"
#ifdef _DEBUG
//#pragma comment(lib, "debug/libglog_static.lib")
#pragma comment(lib, "debug/libprotobuf.lib")
#pragma comment(lib, "debug/libprotoc.lib")
#else
//#pragma comment(lib, "release/libglog_static.lib")
#pragma comment(lib, "release/libprotobuf.lib")
#pragma comment(lib, "release/libprotoc.lib")
#endif

// CModelLabelToolDlg dialog
class CModelLabelToolDlg : public CDialogEx
{
// Construction
public:
	CModelLabelToolDlg(CWnd* pParent = NULL);	// standard constructor
	enum { IDD = IDD_MODELLABELTOOL_DIALOG };
	CString wrlFilePath;
	CString wrlFileName;
	CString wlbFileRoot;
	CString wlbFilePath;	//=wrlFileName + L"\\";
	CString wlbFileName;
	CString imgFileRoot;
	CString imgFilePath;
	CString imgFileName;
	bool	showMessage = true;
// Dialog Data
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	BOOL	InitDialog();
	BOOL	InitData();
	BOOL	InitGLWindow();
	BOOL	InitFileList();
	BOOL	InitToorbar();
	BOOL	InitMessage();
	void	FrashWrlFileList(bool isInit = false);
	void	FrashWlbFileList();
	void	CheckWlbFilePath(int);
	void	CheckImgFilePath(int);
	void	ShowImage(cv::Mat);
	void	OnLock();
	void	OnUnLock();
	void	Lock3DView(bool);
	

// Implementation
protected:
	HICON m_hIcon;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	ModelLabel			labelfile;
	CMFCEditBrowseCtrl	m_editbrowse;		// 选择目录控件
	CListCtrl			m_filelist;			// wrl文件列表
	CCustomEditListBox	m_listbox;			// 文本列表
	COpenGLControl		m_oglWindow;
	CToolBar			m_ToolBar;
	CReBar				m_ReBar;
	CImageList			m_ImageList;
	CString				m_ToolBarTipStr[20];
	CImage				CI;
	//cv::Mat				m_img;
	cv::Scalar			viewpoint, orientation;
	std::vector<std::vector<unsigned int>> surface_index;
	std::vector<cv::Scalar> surface_point, surface_color, surface_vector;
	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;
	float m_cenX;
	float m_cenY;
	float m_cenZ;

	void	AppendMessage(LPCTSTR);
	void	AppendMessage(std::string);
	afx_msg void OnClickFileList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnSnap();
	afx_msg void OnBnOpenwrl();
	afx_msg void OnBnPrevious();
	afx_msg void OnBnSave();
	afx_msg void OnBnDelete();
	afx_msg void OnBnClear();
	afx_msg void OnBnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditBrowseChange();
	afx_msg void OnBnSetEyes();
	afx_msg void OnDebug();
	afx_msg void OnChoose();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnFlag();
	afx_msg void OnSaveText();
	afx_msg void OnSaveImage();
	afx_msg void OnWriteProtect();
	afx_msg void OnAboutDialog();
	afx_msg void OnDetect();
	afx_msg void OnBatch();
	
	CILabelControl m_pic;
	CStatic m_coord;
	CStatic m_3dcoor;
	CStatic m_3dcoorl;
	CRichEditCtrl m_msgedit;
	CRichEditCtrl* m_pMsgCtrl;
};

#endif
