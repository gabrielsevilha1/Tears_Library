//Created by Gabriel Sevilha ♥

//First release: 06/24/2020

//C++ library

//For compile in windows:
//		if use GDI+   :	link librarys: -lgdi32 -lgdiplus
//		if use OPENGL : link librarys: -lopengl32
//For compile in linux:
//		link librarys: -lX11 -lXrandr -lGL

//Dependences:
//
//		If you use a GDI+	: nothing
//		If you use a OPENGL : stb_image.h
//
//      (For almost all cases, stb_image is already included in tears library)
//

//Define configure:
//
//		USE_OPENGL				 (Tears OpenGL render)
//		USE_OPENGL_CONTEXT (Raw OpenGL Context)
//		USE_GDIPLUS			 	 (Tears GDI+ render(only windows))(Not recommended)
//
//		FIX_BORDER				 (Show client area ignoring a border size)
//

//
//Attention:
//
//    This library is open source, and has its dependencies, these dependencies have been added internally for easy use, without the user having to download each of the dependencies manually.
//    Your unique dependence for now is stb_image.h, that has included in this code to facilitate use of library
//

//(Read documentation for more information)

//====================================================================================================
//Dependences (begin)
//====================================================================================================

//====================================================================================================
//Dependences (end)
//====================================================================================================

//tears_library.h

//======================================================= Window Section =======================================================

#elif defined WIN32 || defined _WIN32 || defined __WIN32__ || defined __NT__ || defined __WIN64__

#ifdef USE_GDIPLUS
#define TL_USE_GDIPLUS
#elif defined USE_OPENGL_CONTEXT
#define TL_USE_OPENGL_CONTEXT
#else
#define TL_USE_OPENGL
#endif

#define TL_ERROR_LOG printf("Erro: Tears Library: ");printf

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#if defined TL_USE_GDIPLUS
#include<windows.h>
#include<gdiplus.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>

//if, for some reason, you get tears_library without stb_image integrated, you need add this:
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
//Of course, only if you have a stb_image.h in include folder
//You know how to made this!

#endif

//tears_window_proc.h (file init)
#include"tears_window_proc.h"
//tears_window_proc.h (file end)

#if defined TL_USE_GDIPLUS
Gdiplus::Graphics* tl_graphics;
Gdiplus::SolidBrush* tl_solidbrush;
Gdiplus::Pen* tl_pen;
Gdiplus::Font* tl_font;
Gdiplus::FontFamily* tl_font_type;
#elif defined TL_USE_OPENGL
unsigned int tl_bitmap_texture;
unsigned char* tl_bitmap_data;
int tl_font_bitmap_width,tl_font_bitmap_height;
float tl_font_size_width = 24.0f;
float tl_font_size_height = 24.0f;
float tl_font_horizontal_space = 0.0f;
float tl_font_vertical_space = 0.0f;
float tl_font_glyph_width = 0.0f;
float tl_font_glyph_height = 0.0f;
#endif

#if defined TL_USE_OPENGL
int tl_ellipse_sides = 24;
void setEllipseSides(int num_sides){
	tl_ellipse_sides = num_sides;
}
#endif

//Configure border size, if you want show a accuracy client area (varying plataform to plataform)
#define WINDOW_BORDER_X 6
#define WINDOW_BORDER_Y 28

bool tl_is_display_active = false;
void check_display_exist(){
	if(tl_is_display_active){
		TL_ERROR_LOG("You do not can use two or more Displays/Windows\n");
		exit(0);
	}else{
		tl_is_display_active = true;
	}
}

double tl_current_time = time(0);
double tl_last_time = tl_current_time;
int tl_fps_conter = 0;
static int fps = 0;

class TWindow{
	
public:

	TWindow();
	TWindow(const char* title);
	TWindow(const char* title,int width,int height);
	TWindow(const char* title,int width,int height,bool fullscreen);
	TWindow(const char* title,int width,int height,bool fullscreen,bool vsync);
	~TWindow();
	
	void show();
	void shutdown();
	void setSize(int w, int h);
	void setViewSize(int w, int h);
	void setFullscreen(bool fullscreen);
	void setVsync(bool enable);
	void setTitle(const char* title);
	void setIcon(const char* file);
	void setSmallIconSize(int w, int h);
	void setBigIconSize(int w, int h);
	void setResizable(bool enable);
	void setCursor(const char* file);
	void showCursor(bool enable);
	void setFixedViewScale(bool enable);
	void setBorderless(bool enable);
	
	int width,height;
	int view_width,view_height;
	
	HWND hwnd;

private:

	int DESKTOP_RESOLUTION_X = GetSystemMetrics(SM_CXSCREEN);
	int DESKTOP_RESOLUTION_Y = GetSystemMetrics(SM_CYSCREEN);
	
	HDC tl_hdc;
	#if defined TL_USE_GDIPLUS
		Gdiplus::GdiplusStartupInput gdiplusstartupinput;
		ULONG_PTR gdiplustoken;
		HDC tl_hdcbuffer;
		PAINTSTRUCT tl_paintstruct;
		HBITMAP tl_hbitmap;
	#else
		HGLRC tl_hglrc;
	#endif

	double current_time = time(0);
	double last_time = current_time;
	int fps_conter = 0;
	
	double current_tick = GetTickCount();
	double last_tick = current_tick;
	double frame_time = current_tick - last_tick;
	
	char icon_file[128] = {};
	double big_icon_w = 64, big_icon_h = 64;
	double small_icon_w = 32, small_icon_h = 32;
	
	bool resizable = false;
	bool borderless = false;
	bool fullscreen = false;
	bool vsync = false;
	bool fixed_view_scale = false;
	
};
TWindow::TWindow(){

	check_display_exist();
	
	this->width = 800;
	this->height = 600;
	this->view_width = 800;
	this->view_height = 600;
	
	WNDCLASS wc = {};
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	#if defined FIX_BORDER
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#else
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#endif
	
	#if defined TL_USE_GDIPLUS
	
		Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

		tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
		tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
		tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
		tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
		
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		
		tl_font_type = new Gdiplus::FontFamily(L"Arial");
		tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
	#elif defined TL_USE_OPENGL
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
		
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
	
	#endif
	
}
TWindow::TWindow(const char* title){

	check_display_exist();
	
	this->width = 800;
	this->height = 600;
	this->view_width = 800;
	this->view_height = 600;
	
	WNDCLASS wc = {};
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	#if defined FIX_BORDER
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#else
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#endif
	
	#if defined TL_USE_GDIPLUS
	
		Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

		tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
		tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
		tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
		tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
		
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		
		tl_font_type = new Gdiplus::FontFamily(L"Arial");
		tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
	#elif defined TL_USE_OPENGL
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
		
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
	
	#endif
		
	}
TWindow::TWindow(const char* title,int width,int height){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	
	WNDCLASS wc = {};
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	#if defined FIX_BORDER
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#else
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#endif
	
	#if defined TL_USE_GDIPLUS
	
		Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

		tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
		tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
		tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
		tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
		
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		
		tl_font_type = new Gdiplus::FontFamily(L"Arial");
		tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
	#elif defined TL_USE_OPENGL
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
		
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
	
	#endif
	
}
TWindow::TWindow(const char* title,int width,int height,bool fullscreen){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	this->fullscreen = fullscreen;
	
	WNDCLASS wc = {};
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	#if defined FIX_BORDER
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#else
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#endif
	
	this->fullscreen = fullscreen;
	DEVMODE	dv_settings;
	EnumDisplaySettings(NULL, 0, &dv_settings);
	dv_settings.dmBitsPerPel = 32;
	dv_settings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
	if(fullscreen){
		dv_settings.dmPelsWidth = width;
		dv_settings.dmPelsHeight = height;
		ChangeDisplaySettings(&dv_settings,CDS_FULLSCREEN);
		SetWindowLong(hwnd,GWL_STYLE,WS_POPUP|WS_VISIBLE);
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
	
	ShowWindow(hwnd,SW_SHOW);
	
	#if defined TL_USE_GDIPLUS
	
		Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

		tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
		tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
		tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
		tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
		
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		
		tl_font_type = new Gdiplus::FontFamily(L"Arial");
		tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
	#elif defined TL_USE_OPENGL
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
		
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
	
	#endif
}
TWindow::TWindow(const char* title,int width,int height,bool fullscreen,bool vsync){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	this->fullscreen = fullscreen;
	this->vsync = vsync;
	
	WNDCLASS wc = {};
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	#if defined FIX_BORDER
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#else
		hwnd = CreateWindowEx(0,"_TEARS_LIBRARY","",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
		0,0,GetModuleHandle(0),0);
		ShowWindow(hwnd,SW_SHOW);
	#endif
	
	this->fullscreen = fullscreen;
	DEVMODE	dv_settings;
	EnumDisplaySettings(NULL, 0, &dv_settings);
	dv_settings.dmBitsPerPel = 32;
	dv_settings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
	if(fullscreen){
		dv_settings.dmPelsWidth = width;
		dv_settings.dmPelsHeight = height;
		ChangeDisplaySettings(&dv_settings,CDS_FULLSCREEN);
		SetWindowLong(hwnd,GWL_STYLE,WS_POPUP|WS_VISIBLE);
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
	
	ShowWindow(hwnd,SW_SHOW);
	
	#if defined TL_USE_GDIPLUS
	
		Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

		tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
		tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
		tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
		tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
		
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		
		tl_font_type = new Gdiplus::FontFamily(L"Arial");
		tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		
	#elif defined TL_USE_OPENGL
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
		
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		tl_hdc = GetDC(hwnd);
		static PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,32,0,0,0,0,0,0,0,0,0,0,0,0,0,24,8,0,PFD_MAIN_PLANE,0,0,0,0};
		int pixel_format = ChoosePixelFormat(tl_hdc,&pfd);
		SetPixelFormat(tl_hdc,pixel_format,&pfd);
		tl_hglrc = wglCreateContext(tl_hdc);
		wglMakeCurrent(tl_hdc,tl_hglrc);
	
	#endif
}
TWindow::~TWindow(){
	shutdown();
}
void TWindow::setSize(int w, int h){
	this->width = w;
	this->height = h;
	SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-w/2,GetSystemMetrics(SM_CYSCREEN)/2-h/2,w+WINDOW_BORDER_X,h+WINDOW_BORDER_Y,SWP_SHOWWINDOW);
	#if defined TL_USE_GDIPLUS
		tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
		SelectObject(tl_hdcbuffer,tl_hbitmap);
		tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
	#elif defined TL_USE_OPENGL
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0.0,0.0,width,height);
	#elif defined TL_USE_OPENGL_CONTEXT
		
	#endif
}
void TWindow::setViewSize(int w, int h){
	this->view_width = w;
	this->view_height = h;
}
void TWindow::setFullscreen(bool fullscreen){
	this->fullscreen = fullscreen;
	DEVMODE	dv_settings;
	EnumDisplaySettings(NULL, 0, &dv_settings);
	dv_settings.dmBitsPerPel = 32;
	dv_settings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
	if(fullscreen){
		dv_settings.dmPelsWidth = width;
		dv_settings.dmPelsHeight = height;
		ChangeDisplaySettings(&dv_settings,CDS_FULLSCREEN);
		SetWindowLong(hwnd,GWL_STYLE,WS_POPUP|WS_VISIBLE);
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_MAXIMIZE);
	}else{
		dv_settings.dmPelsWidth = DESKTOP_RESOLUTION_X;
		dv_settings.dmPelsHeight = DESKTOP_RESOLUTION_Y;
		ChangeDisplaySettings(&dv_settings,0);
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
		SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,SWP_FRAMECHANGED);
		ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}
void TWindow::setVsync(bool enable){
	vsync = enable;
}
void TWindow::setTitle(const char* title){
	SetWindowTextA(hwnd,title);
}
void TWindow::setIcon(const char* file){
	strcpy(icon_file,file);
	HICON hicon_big = (HICON)LoadImage(NULL,file,IMAGE_ICON,big_icon_w,big_icon_h,LR_LOADFROMFILE);
	HICON hicon_small = (HICON)LoadImage(NULL,file,IMAGE_ICON,small_icon_w,small_icon_h,LR_LOADFROMFILE);
	SendMessage(hwnd, WM_SETICON, ICON_BIG,(LPARAM)hicon_big);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL,(LPARAM)hicon_small);
}
void TWindow::setBigIconSize(int w, int h){
	if(icon_file[0] != '\0'){
		this->big_icon_w = w;
		this->big_icon_h = h;
		HICON hicon_big = (HICON)LoadImage(NULL,icon_file,IMAGE_ICON,big_icon_w,big_icon_h,LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_BIG,(LPARAM)hicon_big);
	}else{
		TL_ERROR_LOG("Use setIcon(const char* file) method before call setBigIconSize(int w, int h)\n");
	}
}
void TWindow::setSmallIconSize(int w, int h){
	if(icon_file[0] != '\0'){
		this->small_icon_w = w;
		this->small_icon_h = h;
		HICON hicon_small = (HICON)LoadImage(NULL,icon_file,IMAGE_ICON,small_icon_w,small_icon_h,LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL,(LPARAM)hicon_small);
	}else{
		TL_ERROR_LOG("Use setIcon(const char* file) method before call setSmallIconSize(int w, int h)\n");
	}
}
void TWindow::setResizable(bool enable){
	this->resizable = enable;
	if(!fullscreen){
		if(enable){
			SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_MAXIMIZEBOX|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX);
			ShowWindow(hwnd,SW_SHOW);
		}else{
			SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX);
			ShowWindow(hwnd,SW_SHOW);
		}
		resizable = enable;
	}else{
		TL_ERROR_LOG("You only can use setResizable(bool enable) method if you window is windowed\n");
	}
}
void TWindow::setBorderless(bool enable){
	this->borderless = enable;
	if(enable){
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED);
		SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,SWP_SHOWWINDOW);
		ShowWindow(hwnd,SW_SHOW);
	}else{
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_MINIMIZEBOX|WS_CAPTION|WS_SYSMENU);
		SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,SWP_SHOWWINDOW);
		ShowWindow(hwnd,SW_SHOW);
	}
}
void TWindow::setFixedViewScale(bool enable){
	fixed_view_scale = enable;
}
void TWindow::showCursor(bool enable){
	ShowCursor(enable);
}
void TWindow::setCursor(const char* file){
	int len = strlen(file);
	if(file[len-1] == 'o' && file[len-2] == 'c' && file[len-3] == 'i'){
		HCURSOR hcursor = (HCURSOR)LoadImage(NULL,file,IMAGE_ICON,32,32,LR_LOADFROMFILE);
		SetClassLong(hwnd,GCL_HCURSOR,(LONG)hcursor);
	}else{
		TL_ERROR_LOG("You can not use this image file for cursor (try .ico)\n");
	}
}
void TWindow::shutdown(){
	tl_is_display_active = false;
	if(this->fullscreen)setFullscreen(false);
	#if defined TL_USE_GDIPLUS
		EndPaint(hwnd,&tl_paintstruct);
		DeleteObject(tl_hbitmap);
		DeleteDC(tl_hdcbuffer);
		DeleteDC(tl_hdc);
		Gdiplus::GdiplusShutdown(gdiplustoken);
	#else
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(tl_hglrc);
		ReleaseDC(hwnd,tl_hdc);
		DeleteDC(tl_hdc);
	#endif
}
void TWindow::show(){
	MSG msg;
	while(PeekMessage(&msg,0,0,0,PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		mouse_position_view.x = (((float)(mouse_position.x)/width)*view_width);
		mouse_position_view.y = (((float)(mouse_position.y)/height)*view_height);
		if(tl_window_sized){
			//(MAIN BUG)Fix: GDI+ resize not work (not work in linux)
			RECT rect;
			GetClientRect(hwnd,&rect);
			this->width = rect.right;
			this->height = rect.bottom;
			if(!fixed_view_scale){
				this->view_width = rect.right;
				this->view_height = rect.bottom;
				#if defined TL_USE_GDIPLUS
					tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
				#elif defined TL_USE_OPENGL
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					glOrtho(0.0,width,height,0.0,0.0,1.0);
					glMatrixMode(GL_MODELVIEW);
					glViewport(0.0,0.0,width,height);
				#endif
			}else if(fixed_view_scale){
				#if defined TL_USE_GDIPLUS
					tl_hbitmap = CreateCompatibleBitmap(tl_hdc,view_width,view_height);
				#elif defined TL_USE_OPENGL
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					glOrtho(0.0,view_width,view_height,0.0,0.0,1.0);
					glMatrixMode(GL_MODELVIEW);
					glViewport(0.0,0.0,width,height);
				#endif
			}
			#if defined TL_USE_GDIPLUS
				SelectObject(tl_hdcbuffer,tl_hbitmap);
				tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
			#elif defined TL_USE_OPENGL
				
			#endif
			tl_window_sized = false;
		}
	}
	if(msg.message == WM_QUIT){
		exit(0);
	}
	#if defined TL_USE_GDIPLUS
		tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
		StretchBlt(tl_hdc,0,0,width,height,tl_hdcbuffer,0,0,view_width,view_height,SRCCOPY);
	#elif defined TL_USE_OPENGL
		SwapBuffers(tl_hdc);
		glClear(GL_COLOR_BUFFER_BIT);
	#elif defined TL_USE_OPENGL_CONTEXT
		SwapBuffers(tl_hdc);
	#endif
	fps_conter++;
	current_time = time(0);
	if(current_time - last_time > 0){
		fps = fps_conter;
		//This is bad i know ;-;
		//--Mark for devs-- Remove this after:
		if(vsync && fps > 60 && fps < 70)
			fps = 60;
		last_time = current_time;
		fps_conter = 0;
	}
	//--Mark for devs-- Fix Vsync:
	if(vsync){
		frame_time = GetTickCount() - current_tick;
		current_tick = GetTickCount();
		if(16 > frame_time){
			Sleep(16 - frame_time);
			last_tick = current_tick;
		}
	}
	
}

double getTime(){
	return GetTickCount();
}

#ifndef TL_USE_OPENGL_CONTEXT
//If you want raw opengl context, you also do not need the followed code

class Image{
	
public:

	Image(const char* file);
	Image(const char* file,int x, int y);
	Image(const char* file,int x, int y, int w, int h);
	~Image();
	
	bool cached = false;
	
	void setPosition(int x, int y);
	void setScale(int x, int y);
	void setSize(int w, int h);
	void setCropPosition(int crop_x, int crop_y);
	void setCropSize(int crop_w, int crop_h);
	void setOrigin(int x, int y);
	void setAlpha(int a);
	void setColor(int r, int g, int b);
	void draw();
	void draw(float a);
	void draw(int x, int y);
	void draw(int x, int y, int w, int h);
	void draw(int x, int y, int w, int h, float a);
	
	float x = 0, y = 0, w = 0, h = 0, scale_x = 1, scale_y = 1, a = 0;
	float crop_x = 0, crop_y = 0, crop_w = 0, crop_h = 0;
	int origin_x = 0, origin_y = 0;
	int image_width = 0, image_height = 0;
  bool flipped_x = 0, flipped_y = 0;
  int color_r = 255, color_g = 255, color_b = 255;
  int alpha = 255;
	
private:

	#if defined TL_USE_GDIPLUS

		HBITMAP * bitmap;
		Gdiplus::Image* img;
		Gdiplus::CachedBitmap* cached_bitmap;
		Gdiplus::ImageAttributes image_attribute;
		Gdiplus::ColorMatrix color_matrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		
	#else
	
		unsigned int texture;
	
	#endif
		
};
Image::Image(const char* file){

	#if defined TL_USE_GDIPLUS
	
		const size_t char_size = strlen(file)+1;
		wchar_t wchar_file[char_size];
		mbstowcs(wchar_file,file,char_size);
		img = new Gdiplus::Image(wchar_file,PixelFormat24bppRGB);
		if(img->GetLastStatus() != Gdiplus::Ok){
			TL_ERROR_LOG("Can not load image: %s\n",file);
			exit(0);}
		Gdiplus::Bitmap img_bitmap(wchar_file);
		cached_bitmap = new Gdiplus::CachedBitmap(&img_bitmap,tl_graphics);
		image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
		this->image_width = img->GetWidth();
		this->image_height = img->GetHeight();
		this->crop_w = img->GetWidth();
		this->crop_h = img->GetHeight();
		this->w = img->GetWidth();
		this->h = img->GetHeight();
		
	#else
	
		unsigned char* data = stbi_load(file,&this->image_width,&this->image_height,0,STBI_rgb_alpha);
		this->crop_w = (float)this->image_width;
		this->crop_h = (float)this->image_height;
		this->w = (float)this->image_width;
		this->h = (float)this->image_height;
		
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,crop_w,crop_h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
		glBindTexture(GL_TEXTURE_2D,0);
		
		stbi_image_free(data);
	
	#endif
}
Image::Image(const char* file, int x, int y){

	#if defined TL_USE_GDIPLUS
	
		const size_t char_size = strlen(file)+1;
		wchar_t wchar_file[char_size];
		mbstowcs(wchar_file,file,char_size);
		img = new Gdiplus::Image(wchar_file,PixelFormat24bppRGB);
		if(img->GetLastStatus() != Gdiplus::Ok){
			TL_ERROR_LOG("Can not load image: %s\n",file);
			exit(0);}
		Gdiplus::Bitmap img_bitmap(wchar_file);
		cached_bitmap = new Gdiplus::CachedBitmap(&img_bitmap,tl_graphics);
		image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
		this->image_width = img->GetWidth();
		this->image_height = img->GetHeight();
		this->crop_w = img->GetWidth();
		this->crop_h = img->GetHeight();
		this->w = img->GetWidth();
		this->h = img->GetHeight();
		this->x = x; this->y = y;
		
	#else
	
		unsigned char* data = stbi_load(file,&this->image_width,&this->image_height,0,STBI_rgb_alpha);
		this->crop_w = (float)this->image_width;
		this->crop_h = (float)this->image_height;
		this->w = (float)this->image_width;
		this->h = (float)this->image_height;
		this->x = x; this->y = y;
		
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,crop_w,crop_h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
		glBindTexture(GL_TEXTURE_2D,0);
		
		stbi_image_free(data);
	
	#endif
}
Image::Image(const char* file, int x, int y, int w, int h){

	#if defined TL_USE_GDIPLUS
	
		const size_t char_size = strlen(file)+1;
		wchar_t wchar_file[char_size];
		mbstowcs(wchar_file,file,char_size);
		img = new Gdiplus::Image(wchar_file,PixelFormat24bppRGB);
		if(img->GetLastStatus() != Gdiplus::Ok){
			TL_ERROR_LOG("Can not load image: %s\n",file);
			exit(0);}
		Gdiplus::Bitmap img_bitmap(wchar_file);
		cached_bitmap = new Gdiplus::CachedBitmap(&img_bitmap,tl_graphics);
		image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
		this->image_width = img->GetWidth();
		this->image_height = img->GetHeight();
		this->crop_w = img->GetWidth();
		this->crop_h = img->GetHeight();
		this->w = w; this->h = h;
		this->x = x; this->y = y;
		
	#else
	
		unsigned char* data = stbi_load(file,&this->image_width,&this->image_height,0,STBI_rgb_alpha);
		this->crop_w = (float)this->image_width;
		this->crop_h = (float)this->image_height;
		this->w = w; this->h = h;
		this->x = x; this->y = y;
		
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,crop_w,crop_h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
		glBindTexture(GL_TEXTURE_2D,0);
		
		stbi_image_free(data);
	
	#endif
}
Image::~Image(){
	#if defined TL_USE_GDIPLUS
		delete img;
		delete bitmap;
		delete cached_bitmap;
	#endif
}
void Image::draw(){

	#if defined TL_USE_GDIPLUS
	
		if(!cached){
			tl_graphics->ResetTransform();
			tl_graphics->TranslateTransform(x,y);
      if(flipped_x)
        tl_graphics->ScaleTransform(-1.0,1.0);
      if(flipped_y)
        tl_graphics->ScaleTransform(1.0,-1.0);
			tl_graphics->ScaleTransform(scale_x,scale_y);
			tl_graphics->RotateTransform(a);
			tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
			tl_graphics->ResetTransform();
		}else{
			tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
		}
	
	#else
	
		glLoadIdentity();
		glTranslatef(x,y,0.0);
    if(flipped_x)
      glScalef(-1.0,1.0,1.0);
    if(flipped_y)
      glScalef(1.0,-1.0,1.0);
		glScalef(scale_x,scale_y,0.0);
		glRotatef(a,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glColor4f(color_r,color_g,color_b,alpha);
		glBegin(GL_POLYGON);
			glTexCoord2f(crop_x/image_width,crop_y/image_height);
			glVertex2f(0-origin_x,0-origin_y);
			glTexCoord2f(crop_x/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x+w,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,crop_y/image_height);
			glVertex2f(0-origin_x+w,0-origin_y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glLoadIdentity();
	
	#endif
	
}
void Image::draw(float a){

	#if defined TL_USE_GDIPLUS
	
		if(!cached){
			tl_graphics->ResetTransform();
			tl_graphics->TranslateTransform(x,y);
      if(flipped_x)
        tl_graphics->ScaleTransform(-1.0,1.0);
      if(flipped_y)
        tl_graphics->ScaleTransform(1.0,-1.0);
			tl_graphics->ScaleTransform(scale_x,scale_y);
			tl_graphics->RotateTransform(a);
			tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
			tl_graphics->ResetTransform();
		}else{
			tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
		}
	
	#else
	
		glLoadIdentity();
		glTranslatef(x,y,0.0);
    if(flipped_x)
      glScalef(-1.0,1.0,1.0);
    if(flipped_y)
      glScalef(1.0,-1.0,1.0);
		glScalef(scale_x,scale_y,0.0);
		glRotatef(a,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glColor4f(color_r,color_g,color_b,alpha);
		glBegin(GL_POLYGON);
			glTexCoord2f(crop_x/image_width,crop_y/image_height);
			glVertex2f(0-origin_x,0-origin_y);
			glTexCoord2f(crop_x/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x+w,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,crop_y/image_height);
			glVertex2f(0-origin_x+w,0-origin_y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glLoadIdentity();
	
	#endif
	
}
void Image::draw(int x, int y){

	#if defined TL_USE_GDIPLUS
	
		if(!cached){
			tl_graphics->ResetTransform();
			tl_graphics->TranslateTransform(x,y);
      if(flipped_x)
        tl_graphics->ScaleTransform(-1.0,1.0);
      if(flipped_y)
        tl_graphics->ScaleTransform(1.0,-1.0);
			tl_graphics->ScaleTransform(scale_x,scale_y);
			tl_graphics->RotateTransform(a);
			tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
			tl_graphics->ResetTransform();
		}else{
			tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
		}
	
	#else
	
		glLoadIdentity();
		glTranslatef(x,y,0.0);
    if(flipped_x)
      glScalef(-1.0,1.0,1.0);
    if(flipped_y)
      glScalef(1.0,-1.0,1.0);
		glScalef(scale_x,scale_y,0.0);
		glRotatef(a,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glColor4f(color_r,color_g,color_b,alpha);
		glBegin(GL_POLYGON);
			glTexCoord2f(crop_x/image_width,crop_y/image_height);
			glVertex2f(0-origin_x,0-origin_y);
			glTexCoord2f(crop_x/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x+w,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,crop_y/image_height);
			glVertex2f(0-origin_x+w,0-origin_y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glLoadIdentity();
	
	#endif
	
}
void Image::draw(int x, int y, int w, int h){

	#if defined TL_USE_GDIPLUS
	
		if(!cached){
			tl_graphics->ResetTransform();
			tl_graphics->TranslateTransform(x,y);
      if(flipped_x)
        tl_graphics->ScaleTransform(-1.0,1.0);
      if(flipped_y)
        tl_graphics->ScaleTransform(1.0,-1.0);
			tl_graphics->ScaleTransform(scale_x,scale_y);
			tl_graphics->RotateTransform(a);
			tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
			tl_graphics->ResetTransform();
		}else{
			tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
		}
	
	#else
	
		glLoadIdentity();
		glTranslatef(x,y,0.0);
    if(flipped_x)
      glScalef(-1.0,1.0,1.0);
    if(flipped_y)
      glScalef(1.0,-1.0,1.0);
		glScalef(scale_x,scale_y,0.0);
		glRotatef(a,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glColor4f(color_r,color_g,color_b,alpha);
		glBegin(GL_POLYGON);
			glTexCoord2f(crop_x/image_width,crop_y/image_height);
			glVertex2f(0-origin_x,0-origin_y);
			glTexCoord2f(crop_x/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x+w,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,crop_y/image_height);
			glVertex2f(0-origin_x+w,0-origin_y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glLoadIdentity();
	
	#endif
	
}
void Image::draw(int x, int y, int w, int h, float a){

	#if defined TL_USE_GDIPLUS
	
		if(!cached){
			tl_graphics->ResetTransform();
			tl_graphics->TranslateTransform(x,y);
      if(flipped_x)
        tl_graphics->ScaleTransform(-1.0,1.0);
      if(flipped_y)
        tl_graphics->ScaleTransform(1.0,-1.0);
			tl_graphics->ScaleTransform(scale_x,scale_y);
			tl_graphics->RotateTransform(a);
			tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
			tl_graphics->ResetTransform();
		}else{
			tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
		}
	
	#else
	
		glLoadIdentity();
		glTranslatef(x,y,0.0);
    if(flipped_x)
      glScalef(-1.0,1.0,1.0);
    if(flipped_y)
      glScalef(1.0,-1.0,1.0);
		glScalef(scale_x,scale_y,0.0);
		glRotatef(a,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_2D,texture);
		glColor4f(color_r,color_g,color_b,alpha);
		glBegin(GL_POLYGON);
			glTexCoord2f(crop_x/image_width,crop_y/image_height);
			glVertex2f(0-origin_x,0-origin_y);
			glTexCoord2f(crop_x/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,(crop_y+crop_h)/image_height);
			glVertex2f(0-origin_x+w,0-origin_y+h);
			glTexCoord2f((crop_x+crop_w)/image_width,crop_y/image_height);
			glVertex2f(0-origin_x+w,0-origin_y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glLoadIdentity();
	
	#endif
	
}
void Image::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}
void Image::setScale(int x, int y){
	this->scale_x = x;
	this->scale_y = y;
}
void Image::setSize(int w, int h){
	this->w = w;
	this->h = h;
}
void Image::setCropPosition(int crop_x, int crop_y){
	this->crop_x = crop_x;
	this->crop_y = crop_y;
}
void Image::setCropSize(int crop_w, int crop_h){
	this->crop_w = crop_w;
	this->crop_h = crop_h;
}
void Image::setOrigin(int x, int y){
	this->origin_x = x;
	this->origin_y = y;
}
void Image::setAlpha(int a){
	#if defined TL_USE_GDIPLUS
		color_matrix.m[3][3] = ((float)a/255.0f);
		image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
	#elif defined TL_USE_OPENGL
		this->alpha = a;
	#endif
}
void Image::setColor(int r, int g, int b){
	#if defined TL_USE_GDIPLUS
		color_matrix.m[0][0] = ((float)r/255.0f);
		color_matrix.m[1][1] = ((float)g/255.0f);
		color_matrix.m[2][2] = ((float)b/255.0f);
		image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
	#elif defined TL_USE_OPENGL
		this->color_r = r;
		this->color_g = g;
		this->color_b = b;
	#endif
}
void Image::flip_x(bool flip){
  flipped_x = flip;
}
void Image::flip_y(bool flip){
  flipped_y = flip;
}

/*
	The Tears library intention has always been to be a library without external dependencies,
  or dependences that destroy a idea of a unique header,because of that, the use of OpenGL
  will use bitmap images (".png", ".bpm", ".jpg",...) to write texts on the screen.
  For now there is no use of a library for reading ".ttf" files, and even if Tears later
  gain the use of freetype, this dependency will be completely optional.
*/

#if defined TL_USE_GDIPLUS

#define REGULAR 0
#define BOLD 1
#define ITALIC 2

void loadFont(const char* font, int size, int format){
		const size_t char_size = strlen(font)+1;
		wchar_t wchar_font[char_size];
		mbstowcs(wchar_font,font,char_size);
		tl_font_type = new Gdiplus::FontFamily(wchar_font);
		switch(format){
			case REGULAR:
				tl_font = new Gdiplus::Font(tl_font_type,size,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
			break;
			case BOLD:
				tl_font = new Gdiplus::Font(tl_font_type,size,Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
			break;
			case ITALIC:
				tl_font = new Gdiplus::Font(tl_font_type,size,Gdiplus::FontStyleItalic, Gdiplus::UnitPixel);
			break;
			default:
				tl_font = new Gdiplus::Font(tl_font_type,size,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
			break;
		}
}
void drawText(const char* text){
		const size_t char_size = strlen(text)+1;
		wchar_t wchar_text[char_size];
		mbstowcs(wchar_text,text,char_size);
		tl_graphics->DrawString(wchar_text,-1,tl_font,Gdiplus::PointF(0,16),tl_solidbrush);
}
void drawText(const char* text,int x, int y){
		const size_t char_size = strlen(text)+1;
		wchar_t wchar_text[char_size];
		mbstowcs(wchar_text,text,char_size);
		tl_graphics->DrawString(wchar_text,-1,tl_font,Gdiplus::PointF(x,y),tl_solidbrush);
}

#elif defined TL_USE_OPENGL

void loadFont(const char* bitmap,int letter_width, int letter_height){
	tl_font_glyph_width = letter_width;
	tl_font_glyph_height = letter_height;
	tl_bitmap_data = stbi_load(bitmap,&tl_font_bitmap_width,&tl_font_bitmap_height,0,STBI_rgb_alpha);
	glGenTextures(1,&tl_bitmap_texture);
	glBindTexture(GL_TEXTURE_2D,tl_bitmap_texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,tl_font_bitmap_width,tl_font_bitmap_height,0,GL_RGBA,GL_UNSIGNED_BYTE,tl_bitmap_data);
	glBindTexture(GL_TEXTURE_2D,0);
	stbi_image_free(tl_bitmap_data);
}
void drawText(const char* text,int x,int y){
	glBindTexture(GL_TEXTURE_2D,tl_bitmap_texture);
	int line = 0;
	int letter_pos = 0;
	for(int i = 0; i < strlen(text); i++){
		if(text[i] == '\n'){
			line++;
			letter_pos = 0;
			i++;
		}
		char letter = text[i];
		float font_pos_x = x+(letter_pos*tl_font_size_width)+tl_font_horizontal_space;
		float font_pos_y = y+(line*tl_font_size_height)+tl_font_vertical_space;
		float font_image_pos_x = (letter*tl_font_glyph_width);
		float font_image_pos_y = ((int)(letter*tl_font_glyph_width)/tl_font_bitmap_width)*tl_font_glyph_height;
		glBegin(GL_POLYGON);
			glTexCoord2f(font_image_pos_x/tl_font_bitmap_width,font_image_pos_y/tl_font_bitmap_height);
			glVertex2f(font_pos_x,font_pos_y);
			glTexCoord2f(font_image_pos_x/tl_font_bitmap_width,(font_image_pos_y+tl_font_glyph_height)/tl_font_bitmap_height);
			glVertex2f(font_pos_x,font_pos_y+tl_font_size_height);
			glTexCoord2f((font_image_pos_x+tl_font_glyph_width)/tl_font_bitmap_width,(font_image_pos_y+tl_font_glyph_height)/tl_font_bitmap_height);
			glVertex2f(font_pos_x+tl_font_size_width,font_pos_y+tl_font_size_height);
			glTexCoord2f((font_image_pos_x+tl_font_glyph_width)/tl_font_bitmap_width,font_image_pos_y/tl_font_bitmap_height);
			glVertex2f(font_pos_x+tl_font_size_width,font_pos_y);
		glEnd();
		letter_pos++;
	}
	glBindTexture(GL_TEXTURE_2D,0);
}

#endif

void resetMatrix(){
	#if defined TL_USE_GDIPLUS
		tl_graphics->ResetTransform();
	#elif defined TL_USE_OPENGL
		glLoadIdentity();
	#endif
}
void translate(float x, float y){
	#if defined TL_USE_GDIPLUS
		tl_graphics->TranslateTransform(x,y);
	#elif defined TL_USE_OPENGL
		glTranslatef(x,y,0.0);
	#endif
}
void rotate(float a){
	#if defined TL_USE_GDIPLUS
		tl_graphics->RotateTransform(a);
	#elif defined TL_USE_OPENGL
		glRotatef(a,0.0,0.0,1.0);
	#endif
}
void scale(float x, float y){
	#if defined TL_USE_GDIPLUS
		tl_graphics->ScaleTransform(x,y);
	#elif defined TL_USE_OPENGL
		glScalef(x,y,0.0);
	#endif
}
void setColor(int r, int g, int b){
	#if defined TL_USE_GDIPLUS
		tl_solidbrush->SetColor(Gdiplus::Color(r,g,b));
		tl_pen->SetColor(Gdiplus::Color(r,g,b));
	#elif defined TL_USE_OPENGL
		glColor3f((float)r/255.0f,(float)g/255.0f,(float)b/255.0f);
	#endif
}
void setLineSize(int size){
	#if defined TL_USE_GDIPLUS
		tl_pen->SetWidth(size);
	#elif defined TL_USE_OPENGL
		glLineWidth(size);
	#endif
}
void fillRect(int x, int y, int w, int h){
	#if defined TL_USE_GDIPLUS
		tl_graphics->FillRectangle(tl_solidbrush,x,y,w,h);
	#elif defined TL_USE_OPENGL
		glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x,y+h);
			glVertex2f(x+w,y+h);
			glVertex2f(x+w,y);
		glEnd();
	#endif
}
void fillEllipse(int x, int y, int r){
	#if defined TL_USE_GDIPLUS
		tl_graphics->FillEllipse(tl_solidbrush,x-r,y-r,r*2,r*2);
	#elif defined TL_USE_OPENGL
		glBegin(GL_POLYGON);
			for(int i = 0; i < 360; i+=360/tl_ellipse_sides){
				glVertex2f(x+cos(i*3.14159265/180)*r,y+sin(i*3.14159265/180)*r);
			}
		glEnd();
	#endif
}
void fillPolygon(int point[], int points_count){
	#if defined TL_USE_GDIPLUS
		Gdiplus::Point points[points_count];
		for(int i = 0; i < points_count; i++)
			points[i] = Gdiplus::Point(point[i*2],point[(i*2)+1]);
		tl_graphics->FillPolygon(tl_solidbrush,points,points_count);
	#elif defined TL_USE_OPENGL
		glBegin(GL_POLYGON);
			for(int i = 0; i < points_count; i++){
				glVertex2f(point[i*2],point[(i*2)+1]);
			}
		glEnd();
	#endif
}
void drawPixel(int x, int y){
	#if defined TL_USE_GDIPLUS
		tl_graphics->FillRectangle(tl_solidbrush,x,y,1,1);
	#elif defined TL_USE_OPENGL
		glBegin(GL_POINTS);
			glVertex2f(x,y);
		glEnd();
	#endif
}
void drawRect(int x, int y, int w, int h){
	#if defined TL_USE_GDIPLUS
		tl_graphics->DrawRectangle(tl_pen,x,y,w,h);
	#elif defined TL_USE_OPENGL
		glBegin(GL_LINE_LOOP);
			glVertex2f(x,y);
			glVertex2f(x,y+h);
			glVertex2f(x+w,y+h);
			glVertex2f(x+w,y);
		glEnd();
	#endif
}
void drawEllipse(int x, int y, int r){
	#if defined TL_USE_GDIPLUS
		tl_graphics->DrawEllipse(tl_pen,x,y,r,r);
	#elif defined TL_USE_OPENGL
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i < 360; i+=360/tl_ellipse_sides){
				glVertex2f(x+cos(i*3.14159265/180)*r,y+sin(i*3.14159265/180)*r);
			}
		glEnd();
	#endif
}
void drawLine(int x, int y, int final_x, int final_y){
	#if defined TL_USE_GDIPLUS
		tl_graphics->DrawLine(tl_pen,x,y,final_x,final_y);
	#elif defined TL_USE_OPENGL
		glBegin(GL_LINES);
			glVertex2f(x,y);
			glVertex2f(final_x,final_y);
		glEnd();
	#endif
}
void drawPolygon(int point[], int points_count){
	#if defined TL_USE_GDIPLUS
		Gdiplus::Point points[points_count];
		for(int i = 0; i < points_count; i++)
			points[i] = Gdiplus::Point(point[i*2],point[(i*2)+1]);
		tl_graphics->DrawPolygon(tl_pen,points,points_count);
	#elif defined TL_USE_OPENGL
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i < points_count; i++){
				glVertex2f(point[i*2],point[(i*2)+1]);
			}
		glEnd();
	#endif
}

#endif

#endif

#endif
