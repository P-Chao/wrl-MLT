/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 37
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2\opencv.hpp>
#ifdef __OPEN_CV
#include <opencv2\opencv.hpp>
#else
//#include "Scalar.h"
#endif
//#include "glog\logging.h"

class wrl{
public:
	wrl(std::string);
	~wrl();
	int read(const char*, cv::Scalar &);
	int read(const char*, std::vector<cv::Scalar> &);
	int read(const char*, std::vector<std::vector<unsigned int>> &);
	unsigned int maxIndex=0;
private:
	cv::Scalar point;
	std::ifstream fin;
	double num;
	std::string str;
	std::stringstream ss, sst;
	std::string name;
};

