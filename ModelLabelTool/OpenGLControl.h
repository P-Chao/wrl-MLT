/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 120
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#ifndef OPENGL_CONTROL_
#define OPENGL_CONTROL_
#include "afxwin.h"
#include <iostream>
#include <vector>
#define __OPEN_CV
#ifdef __OPEN_CV
#include <opencv2\opencv.hpp>
#pragma comment(lib, "opencv_world310.lib")
#else
#include "Scalar.h"
#endif
#include <GL\glew.h>
#include <GL\freeglut.h>
#pragma comment(lib, "glew32s.lib")
#ifdef _DEBUG
#pragma comment(lib, "debug/freeglut_static.lib")
#else
#pragma comment(lib, "release/freeglut_static.lib")
#endif
#include "glGraber.h"

class COpenGLControl :
	public CWnd
{
public:
	COpenGLControl();
	~COpenGLControl();
	enum Scence{
		AUTO = 0,
		FACE = 1
	} scence = AUTO;
	
	void	OGLCreate(CRect rect, CWnd *parent);
	void	SetScence(Scence);
	void	SetEyes(float, float, float, float, float, float);
	void	UpDateInfo();
	void	SnapShot(cv::Mat &);
	void	SetLock(bool);
	void	pointTo3Dpoint(int, int, double &, double &, double &);
	void	SnapShot2File(std::string);

	typedef struct{
		GLdouble point[3];
		GLdouble color[3];
		GLdouble vecte[3];
	} vertext;
	int		SetViewpoint(cv::Scalar &, cv::Scalar &);
	int		SetVertex(std::vector<cv::Scalar> &,
			std::vector<cv::Scalar> &, std::vector<cv::Scalar> &);
	int		SetIndex(std::vector<std::vector<unsigned int>> &);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];
	std::vector<vertext> shape;
	std::vector<std::vector<unsigned int>> index;
	glGraber m_snap;
	bool	m_bLock = false;

public:
	UINT_PTR m_unpTimer;
	float	 m_fLastX;
	float	 m_fLastY;
	bool	 m_bIsMaximized = false;

	GLfloat  m_fPosX = 0;    // X position of model in camera view
	GLfloat  m_fPosY = 0;    // Y position of model in camera view
	GLfloat  m_fZoom = 10;   // Zoom on model in camera view
	GLfloat  m_fRotX = 0;    // Rotation on model in camera view
	GLfloat  m_fRotY = 0;    // Rotation on model in camera view
	double m_eyeX = 0;
	double m_eyeY = 0;
	double m_eyeZ = 1;
	GLdouble m_centerX = 0;
	GLdouble m_centerY = 0;
	GLdouble m_centerZ = 10;
	GLdouble m_oriX = 0, m_oriY = 0, m_oriZ = 1;
	GLdouble m_upX = 0;
	GLdouble m_upY = 1;
	GLdouble m_upZ = 0;
	GLdouble m_posx = 0, m_posy = 0, m_posz = 0;
	GLdouble m_poslx = 0, m_posly = 0, m_poslz = 0;

protected:
	CWnd*	hWnd;
	HDC		hdc;
	HGLRC	hrc;
	int		m_nPixelFormat;
	CRect	m_rect;
	CRect	m_oldWindow;
	CRect	m_originalRect;
	CPoint	m_mouse;

	void	oglInitialize(void);
	void	createData(void);
	void	createScence();
	void	oglDrawScene(void);
	void	screen2GLPoint(void);
	
public:
	afx_msg void OnPaint();
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
#endif