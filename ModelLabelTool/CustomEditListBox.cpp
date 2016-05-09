/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 141
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "CustomEditListBox.h"
#include "ModelLabelToolDlg.h"
#include "ModelLabel.h"
extern CModelLabelToolDlg *pMainWin;

bool CCustomEditListBox::IsExist(CString strText){
	for (int i = 0; i<GetCount(); i++){
		CString strContent = GetItemText(i);
		if (strContent == strText){
			return true;//已经存在
		}
	}
	return false;
}

void CCustomEditListBox::SetItemText(int iIndex, const CString& strText){
	if (IsExist(strText)){
		CString strPrompt = _T("");
		strPrompt.Format(_T("【%s】已经存在"), strText);
		RemoveItem(iIndex);
		AfxMessageBox(strPrompt);
		EditItem(iIndex);
		m_wndEdit.SetWindowText(strText);
		// m_wndEdit.SetSel(0, -1);//全选
		// m_wndEdit.SetSel(-1);//光标处于文字的末端
		return;
	}
	if (GetSafeHwnd() == NULL || m_pWndList == NULL){
		ASSERT(FALSE);
		return;
	}
	ASSERT_VALID(m_pWndList);
	m_pWndList->SetItemText(iIndex, 0, strText);
}

BOOL CCustomEditListBox::OnBeforeRemoveItem(int nItem)	{
	CString strText = GetItemText(nItem);
	CString strPrompt = _T("");
	strPrompt.Format(_T("确定要删除%s.wlb吗？"), strText);
	if (MessageBox(strPrompt, _T("提示"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK){
		int nSel = GetSelItem();
		CString filename = GetItemText(nSel);
		pMainWin->wlbFileName = filename + L".wlb";
		filename = pMainWin->wlbFileRoot + pMainWin->wlbFilePath
			+ pMainWin->wlbFileName;
		DeleteFile(filename);
		
		filename = GetItemText(nSel);
		pMainWin->imgFileName = filename + L".jpg";
		filename = pMainWin->imgFileRoot + pMainWin->imgFilePath
			+ pMainWin->imgFileName;
		DeleteFile(filename);

		IsDelete = true;
		return TRUE;
	}
	return FALSE;
}

void CCustomEditListBox::OnAfterAddItem(int /*iItem*/) {
	int nSel = GetSelItem();
	CString filename = GetItemText(nSel);
	pMainWin->wlbFileName = filename + L".wlb";
	filename = pMainWin->wlbFileRoot + pMainWin->wlbFilePath
		+ pMainWin->wlbFileName;
	CFile f;
	f.Open(filename, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	f.Close();
}

void CCustomEditListBox::OnAfterRenameItem(int /*iItem*/) {
	int nSel = GetSelItem();
	CString newname = GetItemText(nSel) + L".wlb";
	CString oldname = pMainWin->wlbFileRoot + pMainWin->wlbFilePath
		+ pMainWin->wlbFileName;
	newname = pMainWin->wlbFileRoot + pMainWin->wlbFilePath
		+ newname;
	pMainWin->wlbFileName = GetItemText(nSel) + L".wlb";
	MoveFile(oldname, newname);

	newname = GetItemText(nSel) + L".jpg";
	oldname = pMainWin->imgFileRoot + pMainWin->imgFilePath
		+ pMainWin->imgFileName;
	newname = pMainWin->imgFileRoot + pMainWin->imgFilePath
		+ newname;
	pMainWin->imgFileName = GetItemText(nSel) + L".jpg";
	MoveFile(oldname, newname);

	IsDelete = true;
}

void CCustomEditListBox::OnAfterMoveItemUp(int /*iItem*/) {
}

void CCustomEditListBox::OnAfterMoveItemDown(int /*iItem*/) {
}

void CCustomEditListBox::OnBrowse(){
	int nSel = GetSelItem();
	MessageBox(_T("Browse item..."));
	if (nSel == GetCount()) // New item		
	{
		nSel = AddItem(_T("New text"));
		SelectItem(nSel);
	}
	else{
		SetItemText(nSel, _T("Updated text"));
	}
}

void CCustomEditListBox::OnSelectionChanged(){
	int nSel = GetSelItem();
	if (-1 == nSel){
		if (IsDelete){
			IsDelete = false;
			return;
		}
		if (pMainWin->labelfile.isOpen){
			pMainWin->labelfile.Save();
			pMainWin->labelfile.InitializeClass();
			return;
		}
	}
	pMainWin->wlbFileName = GetItemText(nSel) + L".wlb";
	pMainWin->imgFileName = GetItemText(nSel) + L".jpg";
	CString wrlfile = pMainWin->wlbFileRoot + pMainWin->wlbFilePath + pMainWin->wlbFileName;
	if (!PathFileExists(wrlfile)){
		return;
	}
	std::string filename((LPCSTR)CStringA(wrlfile));
	pMainWin->labelfile.Open(filename, pMainWin->showMessage);
	std::string file = pMainWin->labelfile.m_data.imgfilename();
	
	wrlfile.Format(L"%s",CStringW(file.c_str()));
	if (PathFileExists(wrlfile)){
		//MessageBox(L"", L"", 0);
		cv::Mat img = cv::imread(file);
		pMainWin->m_pic.ShowMat(img);
	}
	
	pMainWin->m_pic.OnDraw(NULL);
}
