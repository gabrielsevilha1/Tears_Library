#ifndef TEARS_LIBRARY_H
#define TEARS_LIBRARY_H

#include<windows.h>
#include<gdiplus.h>

//====================================================================================
//Display class

Gdiplus::Graphics* tl_graphics;
Gdiplus::SolidBrush* tl_solidbrush;
Gdiplus::Pen* tl_pen;

LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam){
	switch(msg){
		case WM_CLOSE:
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,msg,wparam,lparam);
}

class Display{
	
public:

	Display(const char* title,int width,int height);
	~Display();
	
	void show();
	void shutdown();
	void setSize(int w, int h);
	void setFullscreen(bool fullscreen);
	
	int width,height;
	
	HWND hwnd;

private:

	int WINDOW_RESOLUTION_X = GetSystemMetrics(SM_CXSCREEN);
	int WINDOW_RESOLUTION_Y = GetSystemMetrics(SM_CYSCREEN);

	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	
	PAINTSTRUCT tl_paintstruct;
	HDC tl_hdc;
	HDC tl_hdcbuffer;
	HBITMAP tl_hbitmap;

};
Display::Display(const char* title,int width,int height){
	
	this->width = width;
	this->height = height;
	
	WNDCLASS wc = {};
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = "_TEARS_LIBRARY";
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	RegisterClass(&wc);
	
	hwnd = CreateWindowEx(0,"_TEARS_LIBRARY",title,WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
	GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,
	0,0,GetModuleHandle(0),0);
	ShowWindow(hwnd,SW_SHOW);
	
	Gdiplus::GdiplusStartup(&gdiplustoken,&gdiplusstartupinput,NULL);

	tl_hdc = BeginPaint(hwnd,&tl_paintstruct);
	tl_hdcbuffer = CreateCompatibleDC(tl_hdc);
	tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
	SelectObject(tl_hdcbuffer,tl_hbitmap);
	
	tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
	tl_solidbrush = new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));
	tl_pen = new Gdiplus::Pen(Gdiplus::Color(255,255,255),2);
	
	tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	
}
Display::~Display(){
	shutdown();
}
void Display::setSize(int w, int h){
	this->width = w;
	this->height = h;
	SetWindowPos(hwnd,HWND_TOPMOST,GetSystemMetrics(SM_CXSCREEN)/2-w/2,GetSystemMetrics(SM_CYSCREEN)/2-h/2,w,h,SWP_SHOWWINDOW);
}
void Display::setFullscreen(bool fullscreen){
	if(fullscreen){
		DEVMODE	dv_settings;
		EnumDisplaySettings(NULL, 0, &dv_settings);
		dv_settings.dmPelsWidth = width;
		dv_settings.dmPelsHeight = height;
		dv_settings.dmBitsPerPel = 32;
		dv_settings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
		ChangeDisplaySettings(&dv_settings, CDS_FULLSCREEN);
		SetWindowLong(hwnd,GWL_STYLE,WS_POPUP|WS_VISIBLE);
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_MAXIMIZE);
	}else{
		DEVMODE	dv_settings;
		EnumDisplaySettings(NULL, 0, &dv_settings);
		dv_settings.dmPelsWidth = WINDOW_RESOLUTION_X;
		dv_settings.dmPelsHeight = WINDOW_RESOLUTION_Y;
		dv_settings.dmBitsPerPel = 32;
		dv_settings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
		ChangeDisplaySettings(&dv_settings,0);
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX);
		SetWindowPos(hwnd,HWND_TOPMOST,GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}
void Display::shutdown(){
	EndPaint(hwnd,&tl_paintstruct);
	DeleteObject(tl_hbitmap);
	DeleteDC(tl_hdcbuffer);
	DeleteDC(tl_hdc);
	Gdiplus::GdiplusShutdown(gdiplustoken);
}
void Display::show(){
	MSG msg;
	while(PeekMessage(&msg,0,0,0,PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(msg.message == WM_QUIT){
		exit(0);
	}
	BitBlt(tl_hdc,0,0,width,height,tl_hdcbuffer,0,0,SRCCOPY);
}

//====================================================================================
//Image Class

class Image{
	
public:

	Image(const char* file);
	~Image();
	
	bool cached = false;
	
	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setCropPosition(int crop_x, int crop_y);
	void setCropSize(int crop_w, int crop_h);
	void setAlpha(int a);
	void draw();
	
	float x = 0, y = 0, w = 0, h = 0;
	float crop_x = 0, crop_y = 0, crop_w = 0, crop_h = 0;
	
private:

	Gdiplus::Bitmap* img;
	Gdiplus::CachedBitmap* cached_bitmap;
	Gdiplus::Rect rectangle;
	Gdiplus::ImageAttributes image_attribute;
	Gdiplus::ColorMatrix color_matrix = {
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	
};
Image::Image(const char* file){
	const size_t char_size = strlen(file)+1;
	wchar_t wchar_file[char_size];
	mbstowcs(wchar_file,file,char_size);
	img = new Gdiplus::Bitmap(wchar_file);
	cached_bitmap = new Gdiplus::CachedBitmap(img,tl_graphics);
	image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
	this->w = img->GetWidth();
	this->h = img->GetHeight();
	this->crop_w = w;
	this->crop_h = h;
}
Image::~Image(){
	delete img;
}
void Image::draw(){
	
	if(!cached){
		rectangle = Gdiplus::Rect(x,y,w,h);
		tl_graphics->DrawImage(img,rectangle,crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
	}else{
		tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
	}
	
}
void Image::setPosition(int x, int y){
	this->x = x;
	this->y = y;
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
void Image::setAlpha(int a){
	color_matrix.m[3][3] = ((float)a/255.0f);
	image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
}

//====================================================================================
//Global Functions

void setColor(int r, int g, int b){
	tl_solidbrush->SetColor(Gdiplus::Color(r,g,b));
	tl_pen->SetColor(Gdiplus::Color(r,g,b));
}
void setPenSize(int size){
	tl_pen->SetWidth(size);
}
void fillRect(int x, int y, int w, int h){
	tl_graphics->FillRectangle(tl_solidbrush,x,y,w,h);
}
void fillEllipse(int x, int y, int r){
	tl_graphics->FillEllipse(tl_solidbrush,x,y,r,r);
}
void drawPixel(int x, int y){
	tl_graphics->FillRectangle(tl_solidbrush,x,y,1,1);
}
void drawRect(int x, int y, int w, int h){
	tl_graphics->DrawRectangle(tl_pen,x,y,w,h);
}
void drawEllipse(int x, int y, int r){
	tl_graphics->DrawEllipse(tl_pen,x,y,r,r);
}
void drawLine(int x, int y, int final_x, int final_y){
	tl_graphics->DrawLine(tl_pen,x,y,final_x,final_y);
}

#endif