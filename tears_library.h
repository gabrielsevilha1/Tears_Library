//Created by Gabriel Sevilha ♥

#ifndef TEARS_LIBRARY_H
#define TEARS_LIBRARY_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<windows.h>
#include<gdiplus.h>

#include"window_proc.h"

Gdiplus::Graphics* tl_graphics;
Gdiplus::SolidBrush* tl_solidbrush;
Gdiplus::Pen* tl_pen;
Gdiplus::Font* tl_font;
Gdiplus::FontFamily* tl_font_type;

static int fps = 0;

class Display{
	
public:

	Display(const char* title,int width,int height);
	~Display();
	
	void show();
	void shutdown();
	void setSize(int w, int h);
	void setViewSize(int w, int h);
	void setFullscreen(bool fullscreen);
	void setVsync(bool enable);
	void setIcon(const char* file);
	void setTitle(const char* title);
	void setIcon(const char* icon_file);
	
	int width,height;
	int view_width,view_height;
	
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

	double current_time = time(0);
	double last_time = current_time;
	int fps_conter = 0;
	
	double current_tick = GetTickCount();
	double last_tick = current_tick;
	double frame_time = current_tick - last_tick;
	
	bool vsync = false;
	
};
Display::Display(const char* title,int width,int height){
	
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	hwnd = CreateWindowEx(0,"_TEARS_LIBRARY",title,WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
	GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+6,height+28,
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
	
	tl_font_type = new Gdiplus::FontFamily(L"Arial");
	tl_font = new Gdiplus::Font(tl_font_type,36,Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	
}
Display::~Display(){
	shutdown();
}
void Display::setSize(int w, int h){
	this->width = w;
	this->height = h;
	this->view_width = w;
	this->view_height = h;
	SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-w/2,GetSystemMetrics(SM_CYSCREEN)/2-h/2,w+6,h+28,SWP_SHOWWINDOW);
	tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
	SelectObject(tl_hdcbuffer,tl_hbitmap);
	tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
}
void Display::setViewSize(int w, int h){
	this->view_width = w;
	this->view_height = h;
}
void Display::setFullscreen(bool fullscreen){
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
		dv_settings.dmPelsWidth = WINDOW_RESOLUTION_X;
		dv_settings.dmPelsHeight = WINDOW_RESOLUTION_Y;
		ChangeDisplaySettings(&dv_settings,0);
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX);
		SetWindowPos(hwnd,HWND_TOPMOST,GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width,height,SWP_FRAMECHANGED);
		ShowWindow(hwnd,SW_SHOWNORMAL);
	}
	
}
void Display::setVsync(bool enable){
	vsync = enable;
}
void Display::setIcon(const char* file){
	
}
void Display::setTitle(const char* title){
	SetWindowTextA(hwnd,title);
}
void Display::setIcon(const char* icon_file){
	
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
		mouse_position_view.x = (((float)(mouse_position.x)/width)*view_width);
		mouse_position_view.y = (((float)(mouse_position.y)/height)*view_height);
	}
	if(msg.message == WM_QUIT){
		exit(0);
	}
	StretchBlt(tl_hdc,0,0,width,height,tl_hdcbuffer,0,0,view_width,view_height,SRCCOPY);
	fps_conter++;
	current_time = time(0);
	if(current_time - last_time > 0){
		//This is bad, i know
		fps = fps_conter;
		if(vsync && fps > 60)
			fps = 60;
		last_time = current_time;
		fps_conter = 0;
	}
	if(vsync){
		frame_time = GetTickCount() - current_tick;
		current_tick = GetTickCount();
		if(16 > frame_time){
			Sleep(16 - frame_time);
			last_tick = current_tick;
		}
	}
}

class Image{
	
public:

	Image(const char* file);
	~Image();
	
	bool cached = false;
	
	void setPosition(int x, int y);
	void setScale(int x, int y);
	void setCropPosition(int crop_x, int crop_y);
	void setCropSize(int crop_w, int crop_h);
	void setOrigin(int x, int y);
	void setAlpha(int a);
	void setColor(int r, int g, int b);
	void draw();
	
	float x = 0, y = 0, w = 0, h = 0, scale_x = 1, scale_y = 1, a = 0;
	float crop_x = 0, crop_y = 0, crop_w = 0, crop_h = 0;
	int origin_x = 0, origin_y = 0;
	
private:

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
	
};
Image::Image(const char* file){
	const size_t char_size = strlen(file)+1;
	wchar_t wchar_file[char_size];
	mbstowcs(wchar_file,file,char_size);
	img = new Gdiplus::Image(wchar_file,PixelFormat24bppRGB);
	Gdiplus::Bitmap img_bitmap(wchar_file);
	cached_bitmap = new Gdiplus::CachedBitmap(&img_bitmap,tl_graphics);
	image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
	this->crop_w = img->GetWidth();
	this->crop_h = img->GetHeight();
	this->w = img->GetWidth();
	this->h = img->GetHeight();
}
Image::~Image(){
	delete img;
}
void Image::draw(){
	
	if(!cached){
		tl_graphics->ResetTransform();
		tl_graphics->TranslateTransform(x,y);
		tl_graphics->ScaleTransform(scale_x,scale_y);
		tl_graphics->RotateTransform(a);
		tl_graphics->DrawImage(img,Gdiplus::Rect(0-origin_x,0-origin_y,w,h),crop_x,crop_y,crop_w,crop_h,Gdiplus::UnitPixel,&image_attribute);
		tl_graphics->ResetTransform();
	}else{
		tl_graphics->DrawCachedBitmap(cached_bitmap,x,y);
	}
	
}
void Image::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}
void Image::setScale(int x, int y){
	this->scale_x = x;
	this->scale_y = y;
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
	color_matrix.m[3][3] = ((float)a/255.0f);
	image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
}
void Image::setColor(int r, int g, int b){
	color_matrix.m[0][0] = ((float)r/255.0f);
	color_matrix.m[1][1] = ((float)g/255.0f);
	color_matrix.m[2][2] = ((float)b/255.0f);
	image_attribute.SetColorMatrix(&color_matrix,Gdiplus::ColorMatrixFlagsDefault,Gdiplus::ColorAdjustTypeBitmap);
}

#define REGULAR 0
#define BOLD 1
#define ITALIC 2

void setFont(const char* font, int size, int format){
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

void showCursor(bool enable){
	ShowCursor(enable);
}
void resetMatrix(){
	tl_graphics->ResetTransform();
}
void translate(float x, float y){
	tl_graphics->TranslateTransform(x,y);
}
void rotate(float a){
	tl_graphics->RotateTransform(a);
}
void scale(float x, float y){
	tl_graphics->ScaleTransform(x,y);
}
void drawText(const char* text,int x, int y){
	const size_t char_size = strlen(text)+1;
	wchar_t wchar_text[char_size];
	mbstowcs(wchar_text,text,char_size);
	tl_graphics->DrawString(wchar_text,-1,tl_font,Gdiplus::PointF(x,y),tl_solidbrush);
}
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
void fillPolygon(int point[], int points_count){
	Gdiplus::Point points[points_count];
	for(int i = 0; i < points_count; i++)
		points[i] = Gdiplus::Point(point[i*2],point[(i*2)+1]);
	tl_graphics->FillPolygon(tl_solidbrush,points,points_count);
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
void drawPolygon(int x[], int y[], int points_count){
	Gdiplus::Point points[points_count];
	for(int i = 0; i < points_count; i++)
		points[i] = Gdiplus::Point(x[i],y[i]);
	tl_graphics->DrawPolygon(tl_pen,points,points_count);
}

#endif