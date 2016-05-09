/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 35
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#ifndef CUSTUM_EDIT_LIST_BOX_
#define CUSTUM_EDIT_LIST_BOX_

#include "afxvslistbox.h"

class CCustomEditListBox :public CVSListBox{
protected:
	enum Button{
		NEW = 0,
		INS = 1,
		MUP = 2,
		MDN = 3
	};
	bool IsDelete = false;
	bool IsExist(CString strText);
	void SetItemText(int iIndex, const CString& strText);
	BOOL OnBeforeRemoveItem(int nItem);

	virtual void OnAfterAddItem(int /*iItem*/);
	virtual void OnAfterRenameItem(int /*iItem*/);
	virtual void OnAfterMoveItemUp(int /*iItem*/);
	virtual void OnAfterMoveItemDown(int /*iItem*/);
	virtual void OnBrowse();
	void OnSelectionChanged();
};

#endif