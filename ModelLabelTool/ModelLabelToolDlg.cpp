/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 535
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "ModelLabelTool.h"
#include "ModelLabelToolDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ModelLabel.h"

void InitFaceAligiment();
void FeaturePoint(cv::Mat img, std::vector<cv::Point> &point_list);
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CModelLabelToolDlg dialog
CModelLabelToolDlg::CModelLabelToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelLabelToolDlg::IDD, pParent)
	, m_eyeX(0)
	, m_eyeY(0)
	, m_cenX(0)
	, m_cenY(0)
	, m_cenZ(0)
	, m_eyeZ(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModelLabelToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_editbrowse);
	DDX_Control(pDX, IDC_LIST2, m_filelist);
	DDX_Control(pDX, IDC_MFCVSLISTBOX2, m_listbox);
	DDX_Text(pDX, IDC_EDIT_EYEX, m_eyeX);
	DDX_Text(pDX, IDC_EDIT_EYEY, m_eyeY);
	DDX_Text(pDX, IDC_EDIT_EYEZ, m_eyeZ);
	DDX_Text(pDX, IDC_EDIT_CENX, m_cenX);
	DDX_Text(pDX, IDC_EDIT_CENY, m_cenY);
	DDX_Text(pDX, IDC_EDIT_CENZ, m_cenZ);
	DDX_Control(pDX, IDC_IMAGE, m_pic);
	DDX_Control(pDX, IDC_COORD, m_coord);
	DDX_Control(pDX, IDC_3DCOORD, m_3dcoor);
	DDX_Control(pDX, IDC_3DCOORD_LAST, m_3dcoorl);
	DDX_Control(pDX, IDC_RICHEDIT_MSG, m_msgedit);
}

BEGIN_MESSAGE_MAP(CModelLabelToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CModelLabelToolDlg::OnClickFileList)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CModelLabelToolDlg::OnEditBrowseChange)
	ON_BN_CLICKED(IDC_BT_APPLY, &CModelLabelToolDlg::OnBnSetEyes)
	ON_COMMAND(ID_T_CLOSE, &CModelLabelToolDlg::OnBnClose)
	ON_COMMAND(ID_T_SNAP, &CModelLabelToolDlg::OnBnSnap)
	ON_COMMAND(ID_T_OPEN, &CModelLabelToolDlg::OnBnOpenwrl)
	ON_COMMAND(ID_T_PLAY, &CModelLabelToolDlg::OnUnLock)
	ON_COMMAND(ID_T_PAUSE, &CModelLabelToolDlg::OnLock)
	ON_COMMAND(ID_T_DEBUG, &CModelLabelToolDlg::OnDebug)
	ON_COMMAND(ID_T_CHOOSE, &CModelLabelToolDlg::OnChoose)
	ON_COMMAND(ID_T_ADD, &CModelLabelToolDlg::OnAdd)
	ON_COMMAND(ID_T_DELETE, &CModelLabelToolDlg::OnDelete)
	ON_COMMAND(ID_T_FLAG, &CModelLabelToolDlg::OnFlag)
	ON_COMMAND(ID_T_SAVETXT, &CModelLabelToolDlg::OnSaveText)
	ON_COMMAND(ID_T_SAVEIMG, &CModelLabelToolDlg::OnSaveImage)
	ON_COMMAND(ID_T_WRITEPROTECT, &CModelLabelToolDlg::OnWriteProtect)
	ON_COMMAND(ID_T_INFO, &CModelLabelToolDlg::OnAboutDialog)
	ON_COMMAND(ID_T_DETECT, &CModelLabelToolDlg::OnDetect)
	ON_COMMAND(ID_T_BATCH, &CModelLabelToolDlg::OnBatch)
END_MESSAGE_MAP()


// CModelLabelToolDlg message handlers
CModelLabelToolDlg *pMainWin = NULL;
BOOL CModelLabelToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	pMainWin = this;
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL){
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitData();
	InitDialog();
	InitGLWindow();
	InitFaceAligiment();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CModelLabelToolDlg::InitData(){
	wrlFilePath = "E:\\CASIA-3D-FaceV1\\3D-Face-WRL\\001";
	wlbFileRoot = "F:\\database\\label";
	imgFileRoot = "F:\\database\\image";
	wrlFileName = "001-001.wrl";
	return TRUE;
}

BOOL CModelLabelToolDlg::InitDialog(){
	InitFileList();
	InitToorbar();
	InitMessage();
	return TRUE;
}

BOOL CModelLabelToolDlg::InitMessage(){
	m_pMsgCtrl = &m_msgedit;
	LPCTSTR strText = L"  Copyright (c) 2016 Peng Chao, All rights reserved.\n";
	//fprintf(m_infoFile, "%s", (CStringA)addTimeStr);	// save to txt file

	HWND hWnd = m_pMsgCtrl->GetSafeHwnd();

	ULONG_PTR dwResult = 0;
	ULONG_PTR p = dwResult;
	if (SendMessageTimeoutW(hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_NORMAL, 1000L, &dwResult) != 0)
	{
		int nLen = (int)dwResult;
		if (SendMessageTimeout(hWnd, EM_SETSEL, nLen, nLen, SMTO_NORMAL, 1000L, &dwResult) != 0)
		{
			if (SendMessageTimeout(hWnd, EM_REPLACESEL, FALSE, (LPARAM)(LPCTSTR)strText,
				SMTO_NORMAL, 1000L, &dwResult) != 0)
			{
			}
		}
	}
	m_pMsgCtrl->LineScroll(1);
	return TRUE;
}

BOOL CModelLabelToolDlg::InitFileList(){
	m_filelist.InsertColumn(0, L"File", LVCFMT_LEFT, 150, -1);
	m_editbrowse.SetWindowTextW(wrlFilePath);
	UpdateData(false);
	FrashWrlFileList(true);
	return TRUE;
}

BOOL CModelLabelToolDlg::InitToorbar(){
	// 添加工具栏，    是工具栏，不是菜单栏      pc
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_SIZE_DYNAMIC |
		CBRS_TOOLTIPS | WS_CHILD | CBRS_TOP | TBSTYLE_LIST | CBRS_TOOLTIPS)
		|| !m_ToolBar.LoadToolBar(IDR_TOOLBAR1)){
		MessageBox(L"创建工具条失败 ");
	}
	m_ToolBar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	return TRUE;
}

BOOL CModelLabelToolDlg::InitGLWindow(){
	CRect rect;
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect); // Get size and position of the picture control
	ScreenToClient(rect); // Convert screen coordinates to client coordinates
	m_oglWindow.OGLCreate(rect, this); // Create OpenGL Control window
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0); // Setup the OpenGL Window's timer to render
	return TRUE;
}

void CModelLabelToolDlg::FrashWrlFileList(bool isInit){
	CFileFind ff;
	CString path;
	m_editbrowse.GetWindowTextW(path);
	if (path != wrlFilePath || isInit){
		wrlFilePath = path;
		m_filelist.DeleteAllItems();
		BOOL res = ff.FindFile(wrlFilePath + "\\*.wrl");
		while (res){
			res = ff.FindNextFileW();
			if (!ff.IsDirectory() && !ff.IsDots()){
				m_filelist.InsertItem(0, ff.GetFileName());
			}
		} ff.Close();
	}
}

void CModelLabelToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CModelLabelToolDlg::AppendMessage(std::string msg){
	//std::string msg = tmp + path + name + "\n";
	size_t size = msg.length();
	wchar_t *w_msg = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, msg.c_str(), size, w_msg, size * sizeof(wchar_t));
	w_msg[size] = 0;
	AppendMessage((LPCTSTR)w_msg);
}

void CModelLabelToolDlg::AppendMessage(LPCTSTR strText){
	if (NULL == m_pMsgCtrl){
		return;
	}
	strText = strText;
	CString addTimeStr;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	addTimeStr.Format(_T("%4d/%02d/%02d %02d:%02d:%02d: %s"), sysTime.wYear, sysTime.wMonth,
		sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, strText);
	//fprintf(m_infoFile, "%s", (CStringA)addTimeStr);	// save to txt file

	HWND hWnd = m_pMsgCtrl->GetSafeHwnd();
	
	ULONG_PTR dwResult = 0;
	ULONG_PTR p = dwResult;
	if (SendMessageTimeoutW(hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_NORMAL, 1000L, &dwResult) != 0)
	{
		int nLen = (int)dwResult;
		if (SendMessageTimeout(hWnd, EM_SETSEL, nLen, nLen, SMTO_NORMAL, 1000L, &dwResult) != 0)
		{
			if (SendMessageTimeout(hWnd, EM_REPLACESEL, FALSE, (LPARAM)(LPCTSTR)addTimeStr,
				SMTO_NORMAL, 1000L, &dwResult) != 0)
			{
			}
		}
	}
	m_pMsgCtrl->LineScroll(1);

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CModelLabelToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CModelLabelToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	switch (nType){
	case SIZE_RESTORED:{
		if (m_oglWindow.m_bIsMaximized){
			m_oglWindow.OnSize(nType, cx, cy);
			m_oglWindow.m_bIsMaximized = false;
		}break;
	}
	case SIZE_MAXIMIZED:{
		m_oglWindow.OnSize(nType, cx, cy);
		m_oglWindow.m_bIsMaximized = true;
		break;
	}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CModelLabelToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 点击wrl文件列表事件
void CModelLabelToolDlg::OnClickFileList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//FrashWrlFileList();
	int nItem = -1;
	if (lpNMItemActivate != NULL){
		nItem = lpNMItemActivate->iItem;
	}
	CheckWlbFilePath(nItem);
	CheckImgFilePath(nItem);
	FrashWlbFileList();
	OnBnOpenwrl();
	OnBnSnap();
	m_pic.OnDraw(NULL);
	*pResult = 0;
}

void CModelLabelToolDlg::CheckWlbFilePath(int nItem){
	wrlFileName = m_filelist.GetItemText(nItem, -1);
	wlbFilePath = L"\\" + wrlFileName + L"\\";
	CString labelfilepath = wlbFileRoot + wlbFilePath;
	if (!PathFileExists(labelfilepath)){
		CreateDirectory(labelfilepath, NULL);
	}
}

void CModelLabelToolDlg::CheckImgFilePath(int nItem){
	wrlFileName = m_filelist.GetItemText(nItem, -1);
	imgFilePath = L"\\" + wrlFileName + L"\\";
	CString imagefilepath = imgFileRoot + imgFilePath;
	if (!PathFileExists(imagefilepath)){
		CreateDirectory(imagefilepath, NULL);
	}
}

void CModelLabelToolDlg::FrashWlbFileList(){
	CFileFind ff;
	CString str;
	int count = m_listbox.GetCount();
	for (int i = count-1; i >= 0; i--){
		m_listbox.RemoveItem(i);
	}
	BOOL res = ff.FindFile(wlbFileRoot + wlbFilePath + "\\*.wlb");
	while (res){
		res = ff.FindNextFileW();
		if (!ff.IsDirectory() && !ff.IsDots()){
			str = ff.GetFileName();
			PathRemoveExtensionW(str.GetBuffer());
			m_listbox.AddItem(str);
		}
	} ff.Close();
}

void CModelLabelToolDlg::OnBnSnap(){
	// TODO: Add your control notification handler code here
	m_oglWindow.OnTimer(1);
	m_oglWindow.OnTimer(1);
	
	m_oglWindow.SnapShot(m_pic.m_img);
	ShowImage(m_pic.m_img);
	m_pic.OnDraw(NULL);

}

void CModelLabelToolDlg::ShowImage(cv::Mat img_in){
	//m_img = cv::imread("temp.png");
	m_pic.ShowMat(img_in);
	//cv::swap(m_img, img_in);
}

void CModelLabelToolDlg::OnBnOpenwrl()
{
	// TODO: Add your control notification handler code here
	std::string path((LPCSTR)CStringA(wrlFilePath+L"\\"));
	std::string name((LPCSTR)CStringA(wrlFileName));
	surface_index.clear();
	surface_point.clear();
	surface_color.clear();
	surface_vector.clear();
	wrl wrlFile(path+name);
	wrlFile.read("position", viewpoint);
	wrlFile.read("orientation", orientation);
	wrlFile.read("point", surface_point);
	wrlFile.read("color", surface_color);
	wrlFile.read("vector", surface_vector);
	wrlFile.read("coordIndex", surface_index);
	assert(surface_point.size() > wrlFile.maxIndex);
	assert(surface_point.size() == surface_color.size());
	assert(surface_point.size() == surface_vector.size());
	m_oglWindow.SetVertex(surface_point, surface_color, surface_vector);
	m_oglWindow.SetIndex(surface_index);
	m_oglWindow.SetViewpoint(viewpoint, orientation);
	m_cenX = orientation.val[0];
	m_cenY = orientation.val[1];
	m_cenZ = orientation.val[2];
	UpdateData(false);
	m_oglWindow.SetScence(COpenGLControl::FACE);

	std::string tmp = "Opened Wrl File: ";
	std::string msg = tmp + path + name + "\n";
	size_t size = msg.length();
	wchar_t *w_msg = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, msg.c_str(), size, w_msg, size * sizeof(wchar_t));
	w_msg[size] = 0;
	AppendMessage((LPCTSTR)w_msg);
	return;
}

void CModelLabelToolDlg::OnBnPrevious(){
	// TODO: Add your control notification handler code here
}

void CModelLabelToolDlg::OnBnSave(){
	// TODO: Add your control notification handler code here
}

void CModelLabelToolDlg::OnBnDelete(){
	// TODO: Add your control notification handler code here
}

void CModelLabelToolDlg::OnBnClear(){
	// TODO: Add your control notification handler code here
}

void CModelLabelToolDlg::OnBnClose(){
	// TODO: Add your control notification handler code here
	labelfile.Save();
	PostMessage(WM_CLOSE);
}

void CModelLabelToolDlg::OnEditBrowseChange(){
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	FrashWrlFileList();
	FrashWlbFileList();
}

void CModelLabelToolDlg::OnBnSetEyes()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_oglWindow.SetEyes(m_eyeX, m_eyeY, m_eyeZ,
						m_cenX, m_cenY, m_cenZ);
}

void CModelLabelToolDlg::OnLock(){
	m_oglWindow.SetLock(true);
	Lock3DView(true);
}

void CModelLabelToolDlg::OnUnLock(){
	m_oglWindow.SetLock(false);
	Lock3DView(false);
}

void CModelLabelToolDlg::Lock3DView(bool isLock){
	CWnd* pWnd = GetDlgItem(IDC_BT_APPLY);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_EYEX);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_EYEY);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_EYEZ);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_CENX);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_CENY);
	pWnd->EnableWindow(!isLock);
	pWnd = GetDlgItem(IDC_EDIT_CENZ);
	pWnd->EnableWindow(!isLock);
}

void CModelLabelToolDlg::OnChoose(){
	m_pic.OnCursorChoose();
}

void CModelLabelToolDlg::OnAdd(){
	m_pic.OnCursorAdd();
}

void CModelLabelToolDlg::OnDelete(){
	m_pic.OnCursorDelete();
}

void CModelLabelToolDlg::OnFlag(){
	m_pic.OnShowLabel();
}

void CModelLabelToolDlg::OnSaveImage(){
	CString strFilter;
	//strFilter = "BMP位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";
	strFilter = "JPEG File|*.jpg||";
	CFileDialog dlg(FALSE, NULL, NULL, NULL, strFilter);
	if (IDOK != dlg.DoModal()){
		return;
	}
	CString strFileName;
	CString strExtension;
	strExtension = "jpg";
	strFileName = dlg.m_ofn.lpstrFile;
	if (dlg.m_ofn.nFileExtension == 0){
		switch (dlg.m_ofn.nFileExtension)
		{
		case 1:
			strExtension = "bmp";
			break;
		case 2:
			strExtension = "jpg";
			break;
		case 3:
			strExtension = "gif";
			break;
		case 4:
			strExtension = "png";
			break;
		default:
			// strExtension = "jpg";
			break;
		}		
	}
	strFileName = strFileName + L"." + strExtension;
	std::string filename((LPCSTR)CStringA(strFileName));
	m_oglWindow.SnapShot2File(filename);
}

void CModelLabelToolDlg::OnSaveText(){
	if (labelfile.isProtect == true){
		labelfile.isProtect = false;
		labelfile.Save();
		labelfile.isProtect = true;
	}else{
		labelfile.Save();
	}
}

void CModelLabelToolDlg::OnWriteProtect(){
	CWnd *pWnd = GetDlgItem(IDC_TXT_WRITE);
	if (labelfile.isProtect){
		labelfile.isProtect = false;
		pWnd->ShowWindow(SW_HIDE);

	} else{
		labelfile.isProtect = true;
		pWnd->ShowWindow(SW_SHOW);
	}
}

void CModelLabelToolDlg::OnAboutDialog(){
	CAboutDlg dlg;
	dlg.DoModal();
}

void CModelLabelToolDlg::OnDetect(){
	std::vector<cv::Point> point_list;
	FeaturePoint(m_pic.m_img, point_list);
	labelfile.Set(point_list);
	m_pic.OnDraw(NULL);
}

void CModelLabelToolDlg::OnBatch(){
	UpdateData(true);
	//int x[2] = { -80, +80 };
	//int y[2] = { -60, +100 };
	float px = m_eyeX;
	float py = m_eyeY;
	float pz = m_eyeZ;
	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j){
			for (int k = 0; k < 5; ++k){
				int x = i * 40 - 80;
				int y = j * 40 - 60;
				int z = k * 80;
				m_oglWindow.SetEyes(px + x, py + y, pz + z,
					m_cenX, m_cenY, m_cenZ);
				OnBnSnap();

				CString str;
				str.Format(L"%d%d%d_2016y4m28d", i, j, k);
				imgFileName = str + L".jpg";
				wlbFileName = str + L".wlb";
				CString wlbfile = wlbFileRoot + wlbFilePath + wlbFileName;
				CFile f;
				f.Open(wlbfile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
				f.Close();

				std::string filename((LPCSTR)CStringA(wlbfile));
				labelfile.Open(filename, false);

				OnDetect();
				OnSaveText();
			}
		}
	}
	m_eyeX = px;
	m_eyeY = py;
	m_eyeZ = pz;
	OnBnSetEyes();
	OnBnSnap();
	FrashWlbFileList();
	UpdateData(false);
}

void CModelLabelToolDlg::OnDebug(){
	/*
	CString wrlPath = L"E:\\CASIA-3D-FaceV1\\3D-Face-WRL\\002";
	m_editbrowse.SetWindowTextW(wrlPath);
	FrashWrlFileList(false);
	showMessage = false;
	int count = m_filelist.GetItemCount();
	for (int i = 0; i < count; ++i){
		int nItem = i;
		CheckWlbFilePath(nItem);
		CheckImgFilePath(nItem);
		FrashWlbFileList();
		AppendMessage(m_filelist.GetItemText(i, 0) + "\n");
		OnBnOpenwrl();
		OnBatch();
	}
	showMessage = true;
	*/

	CString wrlPath;
	//for (int k = 4; k < 10; ++k)
	int k = 4;
	for (int j = 9; j < 10; ++j){
		//if (j == 0 && k == 0) continue;
		wrlPath.Format(L"E:\\CASIA-3D-FaceV1\\3D-Face-WRL\\0%d%d", k, j);
		m_editbrowse.SetWindowTextW(wrlPath);
		FrashWrlFileList(false);
		showMessage = false;
		int count = m_filelist.GetItemCount();
		
		//for (int i = 0; i < count; ++i){
			//int nItem = i;
			int nItem = count - 1;
			CheckWlbFilePath(nItem);
			CheckImgFilePath(nItem);
			FrashWlbFileList();
			AppendMessage(L"Opening:  " + m_filelist.GetItemText(nItem, 0) + L"\n");
			OnBnOpenwrl();
			OnBatch();
		//}
		showMessage = true;
	}
	AppendMessage("Finish Batch Process!\n");
}
