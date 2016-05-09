/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 72
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <windows.h>
#include <string>
#include <vector>
#ifdef __OPEN_CV
#include <opencv2\opencv.hpp>
#else
#include "Scalar.h"
#endif
//#include <glog\logging.h>

#pragma comment(lib, "glew32s.lib")
#ifdef _DEBUG
#pragma comment(lib, "debug/freeglut_static.lib")
#else
#pragma comment(lib, "release/freeglut_static.lib")
#endif

class icp{
public:
	icp();
	icp(std::string);
	~icp();
	int paint();
	GLvoid ResizeGLScene(GLsizei width, GLsizei height);
	typedef struct{
		GLdouble point[3];
		GLdouble color[3];
		GLdouble vecte[3];
	} vertext;
	int		setVertex(std::vector<cv::Scalar> &, 
					  std::vector<cv::Scalar> &, std::vector<cv::Scalar> &);
	int		setIndex(std::vector<std::vector<unsigned int>> &);
	int		setViewpoint();
protected:
	void Init();
	void initializeGL();
	void paintGL();
	void resizeGL();
	HGLRC	hRC = NULL;												//着色描述表
	HDC		hDC = NULL;												//设备描述表
	HWND	hWnd = NULL;											//窗口指派句柄
	HINSTANCE hInstance;											//为程序创建实例	
	int		InitGL(GLvoid);
	int		DrawGLScene(GLvoid);
	GLvoid	KillGLWindow(GLvoid);
	BOOL	CreateGLWindow(wchar_t * title, int width, int height,
								int bits, bool fullscreenflag);
	int		LoadTextures();
private:
	wchar_t *title = L"OpenGL Program";
	wchar_t *classname = L"thisisglclass";
	GLfloat	xrot=0, yrot=0, zrot=0, xspeed=0, yspeed=0, zspeed=0;
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];
	GLdouble eyex = 0,eyey = 0,eyez = 0;
	GLdouble centerx = 0, centery = 0, centerz = 0;
	GLdouble upx = 0, upy = 0, upz = 1;
	std::vector<vertext> shape;
	std::vector<std::vector<unsigned int>> index;
};

