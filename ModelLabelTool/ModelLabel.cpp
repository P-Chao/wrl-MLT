/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 216
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "ModelLabel.h"
#include "io.hpp"
#include "ModelLabelToolDlg.h"

#define	WLB_VERSION "v0.3"

extern CModelLabelToolDlg* pMainWin;

ModelLabel::ModelLabel(){
}

ModelLabel::ModelLabel(std::string filename){
	Open(filename);
}

ModelLabel::~ModelLabel(){
}

void ModelLabel::Open(std::string filename, bool isMessage){
	InitializeClass(isMessage);
	wlbFileName = filename;
	if (!CheckFormat()){ // 格式或版本不正确则重写文件
		FILE *fp = fopen(wlbFileName.data(), "w+");
		fclose(fp);
	}
	CopyFromFileToList();
	isOpen = true;
}

bool ModelLabel::InitializeClass(bool isMessage){
	wlbFileName = "001.wlb";
	m_data.Clear();
	m_list.clear();
	m_point.x = 0;
	m_point.y = 0;
	isOpen = false;
	isProtect = true;
	isMessageBox = isMessage;
	pMainWin->OnWriteProtect();
	pMainWin->OnWriteProtect();
	return true;
}

void ModelLabel::Save(bool binary){
	if (wlbFileName.length() == 0){
		if (isMessageBox){
			MessageBox(0, L"File not open, now open default.wlb", L"Tip", 0);
		}
		wlbFileName = "default.wlb";
	}
	SaveAs(wlbFileName);
}

void ModelLabel::SaveAs(std::string filename, bool binary){
	if (isProtect){
		return;
	}
	if (binary){
		CString wrlfile = pMainWin->wrlFilePath + "\\" + pMainWin->wrlFileName;
		CString imgfile = pMainWin->imgFileRoot + pMainWin->imgFilePath + pMainWin->imgFileName;
		std::string wrlfilename((LPCSTR)CStringA(wrlfile));
		std::string imgfilename((LPCSTR)CStringA(imgfile));
		m_data.set_version(WLB_VERSION);
		m_data.set_wrlfilename(wrlfilename);
		m_data.set_imgfilename(imgfilename);

		mlt::Info* info = m_data.mutable_info();
		//mlt::Info &info = (mlt::Info &)m_data.info();

		info->set_viewpoint_x(pMainWin->m_oglWindow.m_eyeX);
		info->set_viewpoint_y(pMainWin->m_oglWindow.m_eyeY);
		info->set_viewpoint_z(pMainWin->m_oglWindow.m_eyeZ);
		info->set_lookori_x(pMainWin->m_oglWindow.m_oriX);
		info->set_lookori_y(pMainWin->m_oglWindow.m_oriY);
		info->set_lookori_z(pMainWin->m_oglWindow.m_oriZ);
		info->set_rot_x(pMainWin->m_oglWindow.m_fRotX);
		info->set_rot_y(pMainWin->m_oglWindow.m_fPosY);
		info->set_rot_z(0);
		CopyFromListToFile();
		CompleteData();
		mlt::WriteProtoToBinaryFile(m_data, filename.data());
		if (!pMainWin->imgFileName.IsEmpty()){
			//pMainWin->m_oglWindow.SnapShot2File(imgfilename);
			pMainWin->m_pic.OnSaveImg(imgfilename);
		}
	}
	else{
		CString wrlfile = pMainWin->wrlFilePath + "\\" + pMainWin->wrlFileName;
		CString imgfile = pMainWin->imgFileRoot + pMainWin->imgFilePath + pMainWin->imgFileName;
		std::string wrlfilename((LPCSTR)CStringA(wrlfile));
		std::string imgfilename((LPCSTR)CStringA(imgfile));
		m_data.set_version(WLB_VERSION);
		m_data.set_wrlfilename(wrlfilename);
		m_data.set_imgfilename(imgfilename);

		mlt::Info* info=m_data.mutable_info();
		//mlt::Info &info = (mlt::Info &)m_data.info();
		
		info->set_viewpoint_x(pMainWin->m_oglWindow.m_eyeX);
		info->set_viewpoint_y(pMainWin->m_oglWindow.m_eyeY);
		info->set_viewpoint_z(pMainWin->m_oglWindow.m_eyeZ);
		info->set_lookori_x(pMainWin->m_oglWindow.m_oriX);
		info->set_lookori_y(pMainWin->m_oglWindow.m_oriY);
		info->set_lookori_z(pMainWin->m_oglWindow.m_oriZ);
		info->set_rot_x(pMainWin->m_oglWindow.m_fRotX);
		info->set_rot_y(pMainWin->m_oglWindow.m_fPosY);
		info->set_rot_z(0);
		CopyFromListToFile();
		CompleteData();
		mlt::WriteProtoToTextFile(m_data, filename.data());
		if (!pMainWin->imgFileName.IsEmpty()){
			pMainWin->m_oglWindow.SnapShot2File(imgfilename);
		}
	}
}

bool ModelLabel::CheckFormat(){// 版本及格式检查
	if (!mlt::ReadProtoFromTextFile(wlbFileName, &m_data)){
		if (!mlt::ReadProtoFromBinaryFile(wlbFileName, &m_data)){
			if (isMessageBox){
				MessageBox(0, L"File will be recreate!", L"Tip", 0);
			}
			return false;
		}
	}
	if (m_data.version() != WLB_VERSION){
		if (isMessageBox){
			MessageBox(0, L"File version error, file will be recreate!", L"Tip", 0);
		}
		return false;
	}
	return true;
}

bool ModelLabel::CheckData(){
	return false;
}

bool ModelLabel::CompleteData(){
	return false;
}

bool ModelLabel::CopyFromFileToList(){
	int size = GetPointCount();
	m_list.resize(size);
	for (int i = 0; i < size; ++i){
		mlt::Point &mpoint = (mlt::Point &)m_data.point(i);
		m_point.x = mpoint.x();
		m_point.y = mpoint.y();
		m_list[mpoint.id()] = m_point;
	}
	_idSelect = 0;
	return true;
}

bool ModelLabel::CopyFromListToFile(){
	double xd, yd, zd;
	m_data.clear_point();
	for (int i = 0; i < m_list.size(); ++i){
		mlt::Point *point = m_data.add_point();
		point->set_id(i);
		point->set_x(m_list[i].x);
		point->set_y(m_list[i].y);
		pMainWin->m_oglWindow.pointTo3Dpoint(m_list[i].x, m_list[i].y, xd, yd, zd);
		point->set_xl(xd);
		point->set_yl(yd);
		point->set_zl(zd);
	}
	return false;
}

void ModelLabel::Set(std::vector<cv::Point> point_list){
	m_list.clear();
	for (int i = 0; i < point_list.size(); ++i){
		m_point.x = point_list[i].x;
		m_point.y = point_list[i].y;
		m_list.push_back(m_point);
		_idSelect = i;
	}
}

int ModelLabel::SearchForID(CPoint point, int pad){ // 搜索所属结点，用于选择
	_idSelect = -1;
	for (int i = 0; i < m_list.size(); ++i){
		if ((abs(m_list[i].x - point.x) + abs(m_list[i].y - point.y)) < pad){
			_idSelect = i;
			break;
		}
	}
	return _idSelect;
}

void ModelLabel::InsertPoint(CPoint point){ // 在末尾直接插入
	m_list.push_back(point);
	_idSelect = m_list.size() - 1;
}

void ModelLabel::InsertPoint(CPoint point, int id){ // 在指定位置插入
	if (id >= m_list.size()){
		m_list.push_back(point);
		_idSelect = m_list.size() - 1;
	} else if(id >= 0){
		m_list.insert(m_list.begin() + id, point);
		_idSelect = id;
	}
}

void ModelLabel::DeletePoint(int id){
	if (id < m_list.size()){
		m_list.erase(m_list.begin() + id);
		_idSelect = id - 1;
	}
}

void ModelLabel::DeletePointBefore(int id){
	if (id < m_list.size() && id >= 0){
		m_list.erase(m_list.begin(), m_list.begin() + id);
	} else if (id >= m_list.size()){
		m_list.clear();
	}
}

void ModelLabel::DeletePointAfter(int id){
}

void ModelLabel::DeletePointFromTo(int start, int end){
}

void ModelLabel::MoveTo(CPoint point, int id){
	m_list[id] = point;
}

void ModelLabel::SwapPoint(int idf, int idg){
	std::swap(m_list[idf], m_list[idg]);
}

void ModelLabel::SelectPoint(int id){
	_idSelect = id;
}

int ModelLabel::GetPointCount(){
	return m_data.point_size();
}

int ModelLabel::GetMaxID(){
	int maxid = -1;
	int size = GetPointCount();
	for (int i = 0; i < size; ++i){
		mlt::Point point = m_data.point(i);
		if (point.id() > maxid){
			maxid = point.id();
		}
	}
	return maxid;
}
