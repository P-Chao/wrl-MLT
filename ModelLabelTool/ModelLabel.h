/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 53
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2\opencv.hpp>
#include "mlt.pb.h"
class ModelLabel{
public:
	int	 _idSelect = -1;
	bool isOpen = false;
	bool isProtect = true;
	bool isMessageBox = true;
	std::vector<CPoint> m_list;
	mlt::Label	m_data;
	
	ModelLabel();
	ModelLabel(std::string);
	~ModelLabel();
	void Open(std::string filename, bool isMessage = true);
	void Save(bool binary = true);
	void SaveAs(std::string, bool binary = true);
	void InsertPoint(CPoint);
	void InsertPoint(CPoint, int);
	void DeletePoint(int);
	void DeletePointBefore(int);
	void DeletePointAfter(int);
	void DeletePointFromTo(int, int);
	void MoveTo(CPoint, int);
	void SwapPoint(int, int);
	void SelectPoint(int);
	int  GetPointCount();
	int  GetMaxID();
	int	 SearchForID(CPoint, int pad = 3);
	bool InitializeClass(bool isMessage = true);
	void Set(std::vector<cv::Point>);

protected:
	bool CheckFormat(void);
	bool CheckData(void);
	bool CompleteData(void);
	bool Insert(CPoint, int);
	bool CopyFromFileToList();
	bool CopyFromListToFile();

private:
	std::string	wlbFileName;
	CPoint		m_point;
};
