/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 183
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "wrl.h"

std::string& replace_all(std::string& str, const std::string& old_value, const std::string& new_value)
{
	while (true) {
		std::string::size_type pos(0);
		if ((pos = str.find(old_value)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else break;
	}
	return str;
}

wrl::wrl(std::string filename){
	fin.open(filename);
	if (!fin){
		MessageBox(NULL, L"No such file!", L"Error", NULL);
		return;
	};
	getline(fin, name);
	if (name != "#VRML V2.0 utf8"){
		MessageBox(NULL, L"Check head failed!", L"Error", NULL);
		fin.close();
	};
}

wrl::~wrl(){
	if (fin){
		fin.close();
	}
}

int wrl::read(const char* node_name, std::vector<cv::Scalar> & surface){
	if (!fin) return -1;
	bool record[3] = { false, false, false };
	int point_index = 0;
	while (getline(fin, name)){
		if (name.find_first_of("#") <= name.length()){
			name.erase(name.find_first_of("#"), name.length());
		}
		replace_all(name, ",", " ");
		name.erase(0, name.find_first_not_of(" \t,"));
		name.erase(name.find_last_not_of(" \t,{}") + 1);
		//LOG(INFO) << name;
		ss.clear();
		ss << name;
		if (record[2] == true) break;
		while (ss >> str){
			//LOG(INFO) << str;
			if ((str == node_name) || record[0]){
				record[0] = true;
				if (str.find_first_of("[") < str.length()){
					if ((str == "[")){
						record[1] = true;
						continue;
					}
					record[1] = true;
					str.erase(str.find_first_of("["), str.find_first_of("["));
				}
				if (record[1]){
					if ((str == "]")){
						record[2] = true;
						break;
					}
					sst.clear();
					sst << str;
					sst >> num;
					point.val[point_index % 3] = num;
					point_index++;
					if (point_index == 3){
						surface.push_back(point);
						//LOG(INFO) << surface.size();
						point_index = 0;
					}
				}
			}
		}
	}
	//LOG(INFO) << "detected " << node_name << " point count: " << surface.size();
	return (int)surface.size();
}

int wrl::read(const char* node_name, std::vector<std::vector<unsigned int>> & surface){
	if (!fin) return -1;
	bool record[4] = { false, false, false, false };
	int point_index = 0, no;
	std::vector<unsigned int> tri;
	while (getline(fin, name)){
		if (name.find_first_of("#") <= name.length()){
			name.erase(name.find_first_of("#"), name.length());
		}
		name.erase(0, name.find_first_not_of(" \t,"));
		name.erase(name.find_last_not_of(" \t,{}") + 1);
	//	LOG(INFO) << name;
		ss.clear();
		ss << name;
		if (record[2]) break;
		while (ss >> str){
	//		LOG(INFO) << str;
			str.erase(str.find_last_not_of(",{}") + 1);
			if ((str == node_name) || record[0]){
				record[0] = true;
				if (str.find_first_of("[") < str.length()){
					if ((str == "[")){
						record[1] = true;
						continue;
					}
					record[1] = true;
					str.erase(str.find_first_of("["), str.find_first_of("[")+1);
				}
	//			LOG(INFO) << str;
				if (record[1]){
					if ((str == "]")){
						record[2] = true;
						break;
					}
					sst.clear();
					sst << str;
					sst >> no;
					if (no >= 0){
						if (no > maxIndex){
							maxIndex = no;
						}
						tri.push_back(no);
					} else if(no == -1){
						surface.push_back(tri);
						//LOG(INFO) << tri[0] << "," << tri[1] << "," << tri[2];
						tri.clear();
					} else{
						continue;
					}
				}
			}
		}
	}
	//LOG(INFO) << "detected " << node_name << " point count: " << surface.size();
	return maxIndex;
}

int wrl::read(const char* node_name, cv::Scalar & point){
	bool record[3] = { false, false, false };
	int index = 0;
	double data;
	while (getline(fin, name)){
		if (name.find_first_of("#") <= name.length()){
			name.erase(name.find_first_of("#"), name.length());
		}
		replace_all(name, ",", " ");
		name.erase(0, name.find_first_not_of(" \t,"));
		name.erase(name.find_last_not_of(" \t,{}") + 1);
		//LOG(INFO) << name;
		ss.clear();
		ss << name;
		if (record[2] == true) break;
		while (ss >> str){
			//LOG(INFO) << str;
			if ((str == node_name) || record[0]){
				if (str == node_name){
					record[0] = true;
					continue;
				}
				sst.clear();
				sst << str;
				sst >> data;
				point.val[index] = data;
				index++;
				if (index == 3){
					record[2] = true;
					break;
				}
			}
		}
	}
	//LOG(INFO) << "detected " << node_name << " point count: " << surface.size();
	return 0;
}