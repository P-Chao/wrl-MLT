/*	This File is part of ModelLabelTool Project.
*	More Reference at http://www.p-chao.com
*	4-15-2016, total line: 468
*	Copyright © 2016 Peng Chao
*	All rights reserved.
*/

#include "stdafx.h"
#include "icp.h"

bool static	fullscreen = TRUE;									//窗口是否全屏
bool static	active = TRUE;										//窗口是否最小化
bool static	keys[256];
static icp* pIcp = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

icp::icp()
{
	pIcp = this;
	Init();
}

icp::icp(std::string WindowTitle){
	size_t size = WindowTitle.length();
	title = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, WindowTitle.c_str(), size, title, size * sizeof(wchar_t));
	title[size] = 0;  // 确保以 '\0' 结尾 
	Init();
}

icp::~icp()
{
}

static GLfloat x = 45.4901, y = -58.6223, z = -946.649;
int icp::paint(){
	MSG		msg;
	BOOL	done = FALSE;
	fullscreen = FALSE;						// FALSE为窗口模式
	if (!CreateGLWindow(title, 640, 480, 16, fullscreen)){
		return 0;							// 失败退出
	}
	while (!done){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT){
				done = TRUE;
			} else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else{
			if (active){
				if (keys[VK_ESCAPE]){
					done = TRUE;
				} else{
					DrawGLScene();
					SwapBuffers(hDC);
					if (keys['A']){
						yrot -= 0.3;
					}
					if (keys['D']){
						yrot += 0.3;
					}
					if (keys['S']){
						xrot -= 0.3;
					}
					if (keys['W']){
						xrot += 0.3;
					}
					if (keys['Q']){
						zrot -= 0.3;
					}
					if (keys['E']){
						zrot += 0.3;
					}
					if (keys['R']){
						xspeed -= 0.001f;
					}
					if (keys['X']){
						xspeed += 0.001f;
					}
					if (keys['C']){
						yspeed -= 0.001f;
					}
					if (keys['V']){
						yspeed += 0.001f;
					}
					if (keys['B']){
						zspeed -= 0.001f;
					}
					if (keys['N']){
						zspeed += 0.001f;
					}
					if (keys['P']){
						xspeed = 0;
						yspeed = 0;
						zspeed = 0;
					}
					if (keys['M']){
						xrot = 0;
						yrot = 0;
						zrot = 0;
						xspeed = 0;
						yspeed = 0;
						zspeed = 0;
						x = 80;
						y = 195;
						z = 1550;
					}
					if (keys['L']){
						
					}
					//ResizeGLScene(640, 480);
				}
			}
			if (keys[VK_F1]){
				keys[VK_F1] = FALSE;
				KillGLWindow();
				fullscreen = !fullscreen;
				if (!CreateGLWindow(title, 640, 480, 16, fullscreen)){
					return 0;				// 如果窗口未能创建，程序退出
				}
			}
		}
	}
	KillGLWindow();
	
	return (msg.wParam);
}


GLvoid icp::ResizeGLScene(GLsizei width, GLsizei height){	// 充值opengl窗口大小
	if (0 == height){
		height = 1;
	}
	
	glViewport(0, 0, width, height);						// 重置当前窗口
	glMatrixMode(GL_PROJECTION);							// 选择投影矩阵
	glLoadIdentity();										// 充值投影矩阵
	gluPerspective(25.0f, (GLfloat)width / (GLfloat)height, 1.0f, 3000.0f); // 设置视口大小
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	setViewpoint();
	gluLookAt(x, y, z,
		0, 0, z,
		0, 1, 0);
	glLoadIdentity();
}

int icp::setViewpoint(){
	eyex = 45.4901;
	eyey = -58.6223;
	eyez = -946.649;
	upz = 1;
	return 0;
}

void icp::Init(){
	for (int i = 0; i < 4; i++){
		LightAmbient[i] = 1.0f;
		LightDiffuse[i] = 1.0f;
	}
	LightPosition[0] = 0;
	LightPosition[1] = 1;
	LightPosition[2] = 2;
	LightPosition[3] = 1;
}

int icp::InitGL(GLvoid){									// 开始进行opengl设置
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
	setViewpoint();
	gluLookAt(eyex, eyey, eyez,
		centerx, centery, centerz,
		upx, upy, upz);
	return TRUE;
}

int icp::DrawGLScene(GLvoid){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (!shape.size()){
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, -6.0f);
		glBegin(GL_TRIANGLES); {
			glVertex3f(0.0f, 1.0f, 0.0f);					// 上顶点
			glVertex3f(-1.0f, -1.0f, 0.0f);					// 左下
			glVertex3f(1.0f, -1.0f, 0.0f);
		}
		glEnd();
		return TRUE;
	}
	glTranslatef(0, 0, 0);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
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
	xrot += xspeed;
	yrot += yspeed;
	zrot += zspeed;
	return TRUE;
}

int icp::LoadTextures(){
	return 0;
}

GLvoid icp::KillGLWindow(GLvoid){
	if (fullscreen){
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if (hRC){
		if (!wglMakeCurrent(NULL, NULL)){
			MessageBox(NULL, L"释放DC或RC失败",
				L"关闭错误", MB_OK | MB_ICONEXCLAMATION);
		}
		if (!wglDeleteContext(hRC)){
			MessageBox(NULL, L"释放RC失败。", 
				L"关闭错误", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}
	if (hDC && !ReleaseDC(hWnd, hDC)){
		MessageBox(NULL, L"释放DC失败。", L"关闭错误",
										MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	if (hWnd && !DestroyWindow(hWnd)){
		MessageBox(NULL, L"释放窗口句柄失败。", L"关闭错误", 
										MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}
	if (!UnregisterClass((LPCWSTR)classname, hInstance)){
		MessageBox(NULL, L"不能注销窗口类。", L"关闭错误", 
										MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

BOOL icp::CreateGLWindow(wchar_t* title, int width, int height, int bits, bool fullscreenflag){
	GLuint		PixelFormat;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top	= (long)0;
	WindowRect.bottom = (long)height;
	fullscreen = fullscreenflag;
	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = classname;
	if (!RegisterClass(&wc)){
		MessageBox(NULL, L"注册窗口失败", L"错误", 
										MB_OK | MB_ICONEXCLAMATION);
	}
	if (fullscreen){
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) 
											!= DISP_CHANGE_SUCCESSFUL){
			if (MessageBox(NULL, L"全屏模式在当前显卡上设置失败！\n使用窗口模式？",
				L"NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
				fullscreen = FALSE;
			} else{
				MessageBox(NULL, L"程序将被关闭", L"错误", 
													MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	if (fullscreen){
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	} else{
		dwExStyle = WS_EX_ACCEPTFILES | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	if (!(hWnd = CreateWindowEx(dwExStyle,				// 扩展窗体风格
		classname,								// 类名字
		(LPCWSTR)title,									// 窗口标题
		WS_CLIPSIBLINGS |								// 必须的窗体风格属性
		WS_CLIPCHILDREN |								// 必须的窗体风格属性
		dwStyle,										// 选择的窗体属性
		0, 0,											// 窗口位置
		WindowRect.right - WindowRect.left,				// 计算调整好的窗口宽度
		WindowRect.bottom - WindowRect.top,				// 计算调整好的窗口高度
		NULL,											// 无父窗口
		NULL,											// 无菜单
		hInstance,										// 实例
		NULL))){
		KillGLWindow();
		MessageBox(NULL, L"不能创建一个窗口设备描述表", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	static	PIXELFORMATDESCRIPTOR pfd =	{		// /pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
		sizeof(PIXELFORMATDESCRIPTOR),			// 上述格式描述符的大小
		1,										// 版本号
		PFD_DRAW_TO_WINDOW |					// 格式支持窗口
		PFD_SUPPORT_OPENGL |					// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER,						// 必须支持双缓冲
		PFD_TYPE_RGBA,							// 申请 RGBA 格式
		bits,									// 选定色彩深度
		0, 0, 0, 0, 0, 0,						// 忽略的色彩位
		0,										// 无Alpha缓存
		0,										// 忽略Shift Bit
		0,										// 无累加缓存
		0, 0, 0, 0,								// 忽略聚集位
		16,										// 16位 Z-缓存 (深度缓存)
		0,										// 无蒙板缓存
		0,										// 无辅助缓存
		PFD_MAIN_PLANE,							// 主绘图层
		0,										// Reserved
		0, 0, 0									// 忽略层遮罩
	};
	if (!(hDC = GetDC(hWnd))) {					// 取得设备描述表了么?
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"不能创建一种相匹配的像素格式", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))){	// Windows 找到相应的象素格式了吗?
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"不能设置像素格式", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {		// 能够设置象素格式么?
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"不能设置像素格式", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if (!(hRC = wglCreateContext(hDC)))	{				// 能否取得着色描述表?
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"不能创建OpenGL渲染描述表", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if (!wglMakeCurrent(hDC, hRC))						// 尝试激活着色描述表
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"不能激活当前的OpenGL渲然描述表", L"错误", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ResizeGLScene(width, height);
	if (!InitGL())	{							// 初始化新建的GL窗口
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, L"Initialization Failed.", L"ERROR", 
													MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg){
	case WM_ACTIVATE:{
		if (!HIWORD(wParam)){
			active = TRUE;
		} else{
			active = FALSE;
		}
		return 0;
	}
	case WM_SYSCOMMAND:{						// 系统中断命令
		switch (wParam){						// 检查系统调用
		case SC_SCREENSAVE:						// 屏保要运行?
		case SC_MONITORPOWER:					// 显示器要进入节电模式?
			return 0;							// 阻止发生
		}
		break;							// 退出
	}
	case WM_CLOSE:{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:{
		keys[wParam] = TRUE;
		return 0;
	}
	case WM_KEYUP:{
		keys[wParam] = FALSE;
		return 0;
	}
	case WM_SIZE:{
		if (!pIcp){
			pIcp->ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int	icp::setVertex(std::vector<cv::Scalar> &point, 
	std::vector<cv::Scalar> &color, std::vector<cv::Scalar> &vecte){
	//CHECK_EQ(point.size(), color.size()) << "point count is not same";
	//CHECK_EQ(point.size(), vecte.size()) << "point count is not same";
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
	return shape.size();
}

int	icp::setIndex(std::vector<std::vector<unsigned int>> & surface){
	index = surface;
	//LOG(INFO) << "openGL received index count: " << index.size();
	return 0;
}