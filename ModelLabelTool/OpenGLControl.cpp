/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 457
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "OpenGLControl.h"
#include "ModelLabelToolDlg.h"

extern CModelLabelToolDlg *pMainWin;

COpenGLControl::COpenGLControl(){
}

COpenGLControl::~COpenGLControl(){
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// 外部初始化调用
void COpenGLControl::OGLCreate(CRect rect, CWnd *parent){
	CString className = AfxRegisterWndClass(CS_HREDRAW |
		CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);
	CreateEx(0, className, L"OpenGL", WS_CHILD | WS_VISIBLE |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);
	// Set initial variables' values
	m_oldWindow = rect;
	m_originalRect = rect;
	hWnd = parent;
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here
	oglInitialize();
	createData();
	createScence();
	return 0;
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup:
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,    // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,    // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};
	hdc = GetDC()->m_hDC; // Get device context only once.	
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd); // Pixel format.
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);
	hrc = wglCreateContext(hdc); // Create the OpenGL Rendering Context.
	wglMakeCurrent(hdc, hrc);
}

void COpenGLControl::createData(){
	switch (scence)
	{
	case COpenGLControl::AUTO:

		break;
	case COpenGLControl::FACE:
		for (int i = 0; i < 4; i++){
			LightAmbient[i] = 1.0f;
			LightDiffuse[i] = 1.0f;
		}
		LightPosition[0] = 0;
		LightPosition[1] = 1;
		LightPosition[2] = 2;
		LightPosition[3] = 1;

		m_fPosX = 0;    // X position of model in camera view
		m_fPosY = 0;    // Y position of model in camera view
		m_fZoom = 0;   // Zoom on model in camera view
		m_fRotX = 0;    // Rotation on model in camera view
		m_fRotY = 0;    // Rotation on model in camera view
		break;
	default:
		break;
	}
}

void COpenGLControl::createScence(){
	switch (scence)
	{
	case COpenGLControl::AUTO:
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);// Set color to use when clearing the background.
		glClearDepth(1.0f);
		glFrontFace(GL_CCW); // Turn on backface culling
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST); // Turn on depth testing
		glDepthFunc(GL_LEQUAL);
		OnDraw(NULL); // Send draw request
		break;
	case COpenGLControl::FACE:
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);										// 设置深度缓存
		glEnable(GL_DEPTH_TEST);								// 启用深度测试
		glDepthFunc(GL_LEQUAL);									// 所作深度测试的类型
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// 告诉系统进行透视修正
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
		glEnable(GL_LIGHT1);
		break;
	default:
		break;
	}
}

void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent){
	case 1:{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		oglDrawScene();
		SwapBuffers(hdc);
		break;
	}
	case 2:{
		break;
	}
	default:
		break;
	}
	CWnd::OnTimer(nIDEvent);
}

void COpenGLControl::OnPaint(){
	ValidateRect(NULL);
	CPaintDC dc(this);
	OnDraw(&dc);
}

void COpenGLControl::OnDraw(CDC *pDC)
{
	// TODO: Camera controls.
	glLoadIdentity();
	if (scence == AUTO){
		glTranslatef(0.0f, 0.0f, -m_fZoom);
		glTranslatef(m_fPosX, m_fPosY, 0.0f);
	}
	glRotatef(-m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(-m_fRotY, 0.0f, 1.0f, 0.0f);
	if (scence != AUTO){
		m_centerX = m_eyeX - m_oriX;
		m_centerY = m_eyeY - m_oriY;
		m_centerZ = m_eyeZ - m_oriZ;
		gluLookAt(m_eyeX, m_eyeY, m_eyeZ,
			m_centerX, m_centerY, m_centerZ,
			m_upX, m_upY, m_upZ);
	}
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	switch (scence){
	case COpenGLControl::AUTO:
		glViewport(0, 0, cx, cy); // Map the OpenGL coordinates.
		glMatrixMode(GL_PROJECTION); // Projection view
		glLoadIdentity();
		gluPerspective(35.0f, (float)cx / (float)cy, 1.0f, 2000.0f); // Set our current view perspective
		glMatrixMode(GL_MODELVIEW); // Model view
		break;
	case COpenGLControl::FACE:
/*		glViewport(0, 0, cx, cy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(35.0f, (float)cx / (float)cy, 1.0f, 2000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(m_eyeX, m_eyeY, m_eyeZ,
			m_centerX, m_centerY, m_centerZ,
			m_upX, m_upY, m_upZ);*/
		break;
	default:
		break;
	}

	switch (nType){ // If window resize token is "maximize"
	case SIZE_MAXIMIZED:{
		GetWindowRect(m_rect); // Get the current window rect
		MoveWindow(6, 6, cx - 14, cy - 14); // Move the window accordingly
		GetWindowRect(m_rect); // Get the new window rect
		m_oldWindow = m_rect; // Store our old window as the new rect
		break;
	}
	case SIZE_RESTORED:{ // If window resize token is "restore"
		if (m_bIsMaximized) {// If the window is currently maximized
			GetWindowRect(m_rect); // Get the current window rect
			MoveWindow(m_oldWindow.left, // Move the window accordingly (to our stored old window)
				m_oldWindow.top - 18,
				m_originalRect.Width() - 4,
				m_originalRect.Height() - 4);
			GetWindowRect(m_rect); // Get the new window rect
			m_oldWindow = m_rect; // Store our old window as the new rect
		}
		break;
	}
	}
}

// 定时调用
void COpenGLControl::oglDrawScene(void)
{
	switch (scence)
	{
	case COpenGLControl::AUTO:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe Mode
		glBegin(GL_QUADS); {
			// Top Side
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			// Bottom Side
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			// Front Side
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			// Back Side
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			// Left Side
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			// Right Side
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
		} glEnd();
		break;
	case COpenGLControl::FACE:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES); {
			for (int i = 0; i < index.size(); i++){
				for (int j = 0; j < 3; j++){
					unsigned int idx = index[i][j];
					glColor3dv(shape[idx].color);
					glNormal3dv(shape[idx].vecte);
					glVertex3dv(shape[idx].point);
				}
			}
		}
		glEnd();
		break;
	default:
		break;
	}
	glFinish();
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mouse = point;
	screen2GLPoint();
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;
	if (!m_bLock){
		if (nFlags & MK_LBUTTON){ // Left mouse button
			m_fRotX += (float)0.5f * diffY;
			if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f)){
				m_fRotX = 0.0f;
			}
			m_fRotY += (float)0.5f * diffX;
			if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f)){
				m_fRotY = 0.0f;
			}
		}
		else if (nFlags & MK_RBUTTON){ // Right mouse button
			m_fZoom -= (float)0.1f * diffY;
			m_eyeZ -= (float)0.1f * diffY;
		}
		else if (nFlags & MK_MBUTTON){ // Middle mouse button
			m_fPosX += (float)0.05f * diffX;
			m_fPosY -= (float)0.05f * diffY;
			m_eyeX -= (float)0.05f * diffX;
			m_eyeY -= (float)0.05f * diffY;
		}
	}
	OnDraw(NULL);
	UpDateInfo();
	CWnd::OnMouseMove(nFlags, point);
}

void COpenGLControl::screen2GLPoint(){
	pointTo3Dpoint(m_mouse.x, m_mouse.y, m_posx, m_posy, m_posz);
	//cout << posx << ' ' << posy << ' ' << posz << endl;
}

void COpenGLControl::pointTo3Dpoint(int x, int y, double & pos_x, double & pos_y, double & pos_z){
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLfloat winx, winy, winz;

	glPushMatrix();

	//glScalef(0.1, 0.1, 0.1);   
	glGetIntegerv(GL_VIEWPORT, viewport);           /* 获取三个矩阵 */
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	glPopMatrix();

	winx = x;
	winy = viewport[3] - y;

	glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);          /* 获取深度 */
	gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &pos_x, &pos_y, &pos_z);    /* 获取三维坐标 */
}

void COpenGLControl::UpDateInfo(){
	pMainWin->m_eyeX = (float)m_eyeX;
	pMainWin->m_eyeY = (float)m_eyeY;
	pMainWin->m_eyeZ = (float)m_eyeZ;
	//pMainWin->m_cenX = (float)(m_centerX - m_eyeX);
	//pMainWin->m_cenY = (float)(m_centerY - m_eyeY);
	//pMainWin->m_cenZ = (float)(m_centerZ - m_eyeZ);
	CString str;
	str.Format(L"(%d,%d)", m_mouse.x, m_mouse.y);
	pMainWin->m_coord.SetWindowText(str);
	str.Format(L"(%.2f, %.2f, %.2f)", m_posx, m_posy, m_posz);
	pMainWin->m_3dcoor.SetWindowText(str);
	str.Format(L"(%.2f, %.2f, %.2f)", m_poslx, m_posly, m_poslz);
	pMainWin->m_3dcoorl.SetWindowText(str);
	pMainWin->UpdateData(false);
}

int	COpenGLControl::SetVertex(std::vector<cv::Scalar> &point,
	std::vector<cv::Scalar> &color, std::vector<cv::Scalar> &vecte){
	//CHECK_EQ(point.size(), color.size()) << "point count is not same";
	//CHECK_EQ(point.size(), vecte.size()) << "point count is not same";
	shape.clear();
	cv::Scalar cs;
	vertext vec;
	for (int i = 0; i < point.size(); i++){
		cs = point[i];
		vec.point[0] = cs.val[0];
		vec.point[1] = cs.val[1];
		vec.point[2] = cs.val[2];
		cs = color[i];
		vec.color[0] = cs.val[0];
		vec.color[1] = cs.val[1];
		vec.color[2] = cs.val[2];
		cs = vecte[i];
		vec.vecte[0] = cs.val[0];
		vec.vecte[1] = cs.val[1];
		vec.vecte[2] = cs.val[2];
		shape.push_back(vec);
	}
	//CHECK_EQ(point.size(), shape.size()) << "point count is not same";
	//LOG(INFO) << "openGL received point count: " << shape.size();
	return (int)shape.size();
}

int	COpenGLControl::SetIndex(std::vector<std::vector<unsigned int>> & surface){
	index.clear();
	index = surface;
	//LOG(INFO) << "openGL received index count: " << index.size();
	return 0;
}

void COpenGLControl::SetScence(Scence scen){
	scence = scen;
	createData();
	createScence();
	OnDraw(NULL);
	UpDateInfo();
}

void COpenGLControl::SetEyes(float eyeX, float eyeY, float eyeZ,
				float centerX, float centerY, float centerZ){
	m_eyeX = eyeX;
	m_eyeY = eyeY;
	m_eyeZ = eyeZ;
	m_oriX = centerX;
	m_oriY = centerY;
	m_oriZ = centerZ;
	m_centerX = eyeX - m_oriX;
	m_centerY = eyeY - m_oriY;
	m_centerZ = eyeZ - m_oriZ;
	OnDraw(NULL);
}

int COpenGLControl::SetViewpoint(cv::Scalar & viewpoint, cv::Scalar & orientation){
	m_eyeX = viewpoint.val[0];
	m_eyeY = viewpoint.val[1];
	m_eyeZ = viewpoint.val[2];
	m_oriX = orientation.val[0];
	m_oriY = orientation.val[1];
	m_oriZ = orientation.val[2];
	m_centerX = m_eyeX - m_oriX;
	m_centerY = m_eyeY - m_oriY;
	m_centerZ = m_eyeZ - m_oriZ;
	return 0;
}

void COpenGLControl::SnapShot(cv::Mat & m_img){
	std::string name = "a.png";
	m_snap.glGrab();
	
		m_snap.save2mat(m_img);
	
	
}

void COpenGLControl::SnapShot2File(std::string filename){
	m_snap.glGrab();
	m_snap.saveColorImg(filename);
}

void COpenGLControl::OnLButtonDown(UINT nFlags, CPoint point)
{	// TODO: Add your message handler code here and/or call default
	m_mouse = point;
	screen2GLPoint();
	m_poslx = m_posx;
	m_posly = m_posy;
	m_poslz = m_posz;
	UpDateInfo();
	CWnd::OnLButtonDown(nFlags, point);
}

void COpenGLControl::SetLock(bool lock){
	m_bLock = lock;
}