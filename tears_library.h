//Created by Gabriel Sevilha ♥

// -lgdi32 -lgdiplus

#ifndef TEARS_LIBRARY_H
#define TEARS_LIBRARY_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<windows.h>
#include<gdiplus.h>

bool tl_window_sized = false;

bool key_w = 0,key_d = 0,key_a = 0,key_s = 0,key_shift = 0,key_ctrl = 0,key_e = 0,key_q = 0,key_space = 0,key_escape = 0,key_up = 0,key_down = 0,key_right = 0,key_left = 0,key_1 = 0,key_2 = 0,key_3 = 0,key_4 = 0,key_5 = 0,key_6 = 0,key_7 = 0,key_8 = 0,key_9 = 0,key_0 = 0,key_r = 0,key_f = 0,key_z = 0,key_x = 0,key_c = 0,key_v = 0,key_b = 0,key_n = 0,key_m = 0,key_t = 0,key_g = 0,key_y = 0,key_h = 0,key_u = 0,key_j = 0,key_i = 0,key_k = 0,key_o = 0,key_l = 0,key_p = 0,key_tab = 0,key_enter = 0;
bool left_click = 0, right_click = 0, middle_click = 0;

POINT mouse_position;
POINT mouse_position_view;

//Begin of tears_window_proc.h

LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam){
	
	switch(msg){
		case WM_CLOSE:
			PostQuitMessage(0);
		break;
		case WM_SIZE:
			tl_window_sized = true;
		break;
		case WM_KEYDOWN:
			if(wparam == 'Q')
				key_q = true;
			if(wparam == 'W')
				key_w = true;
			if(wparam == 'E')
				key_e = true;
			if(wparam == 'R')
				key_r = true;
			if(wparam == 'T')
				key_t = true;
			if(wparam == 'Y')
				key_y = true;
			if(wparam == 'U')
				key_u = true;
			if(wparam == 'I')
				key_i = true;
			if(wparam == 'O')
				key_o = true;
			if(wparam == 'P')
				key_p = true;
			if(wparam == 'A')
				key_a = true;
			if(wparam == 'S')
				key_s = true;
			if(wparam == 'D')
				key_d = true;
			if(wparam == 'F')
				key_f = true;
			if(wparam == 'G')
				key_g = true;
			if(wparam == 'H')
				key_h = true;
			if(wparam == 'J')
				key_j = true;
			if(wparam == 'K')
				key_k = true;
			if(wparam == 'L')
				key_l = true;
			if(wparam == 'Z')
				key_z = true;
			if(wparam == 'X')
				key_x = true;
			if(wparam == 'C')
				key_c = true;
			if(wparam == 'V')
				key_v = true;
			if(wparam == 'B')
				key_b = true;
			if(wparam == 'N')
				key_n = true;
			if(wparam == 'M')
				key_m = true;
			if(wparam == VK_ESCAPE)
				key_escape = true;
			if(wparam == VK_TAB)
				key_tab == true;
			if(wparam == VK_SHIFT)
				key_shift = true;
			if(wparam == VK_CONTROL)
				key_ctrl = true;
			if(wparam == 0x30)
				key_0 = true;
			if(wparam == 0x31)
				key_1 = true;
			if(wparam == 0x32)
				key_2 = true;
			if(wparam == 0x33)
				key_3 = true;
			if(wparam == 0x34)
				key_4 = true;
			if(wparam == 0x35)
				key_5 = true;
			if(wparam == 0x36)
				key_6 = true;
			if(wparam == 0x37)
				key_7 = true;
			if(wparam == 0x38)
				key_8 = true;
			if(wparam == 0x39)
				key_9 = true;
			if(wparam == VK_UP)
				key_up = true;
			if(wparam == VK_DOWN)
				key_down = true;
			if(wparam == VK_LEFT)
				key_left = true;
			if(wparam == VK_RIGHT)
				key_right = true;
			if(wparam == VK_RETURN)
				key_enter = true;
			if(wparam == VK_SPACE)
				key_space = true;
		break;
			
		case WM_KEYUP:
			if(wparam == 'Q')
				key_q = false;
			if(wparam == 'W')
				key_w = false;
			if(wparam == 'E')
				key_e = false;
			if(wparam == 'R')
				key_r = false;
			if(wparam == 'T')
				key_t = false;
			if(wparam == 'Y')
				key_y = false;
			if(wparam == 'U')
				key_u = false;
			if(wparam == 'I')
				key_i = false;
			if(wparam == 'O')
				key_o = false;
			if(wparam == 'P')
				key_p = false;
			if(wparam == 'A')
				key_a = false;
			if(wparam == 'S')
				key_s = false;
			if(wparam == 'D')
				key_d = false;
			if(wparam == 'F')
				key_f = false;
			if(wparam == 'G')
				key_g = false;
			if(wparam == 'H')
				key_h = false;
			if(wparam == 'J')
				key_j = false;
			if(wparam == 'K')
				key_k = false;
			if(wparam == 'L')
				key_l = false;
			if(wparam == 'Z')
				key_z = false;
			if(wparam == 'X')
				key_x = false;
			if(wparam == 'C')
				key_c = false;
			if(wparam == 'V')
				key_v = false;
			if(wparam == 'B')
				key_b = false;
			if(wparam == 'N')
				key_n = false;
			if(wparam == 'M')
				key_m = false;
			if(wparam == VK_ESCAPE)
				key_escape = false;
			if(wparam == VK_TAB)
				key_tab == false;
			if(wparam == VK_SHIFT)
				key_shift = false;
			if(wparam == VK_CONTROL)
				key_ctrl = false;
			if(wparam == 0x30)
				key_0 = false;
			if(wparam == 0x31)
				key_1 = false;
			if(wparam == 0x32)
				key_2 = false;
			if(wparam == 0x33)
				key_3 = false;
			if(wparam == 0x34)
				key_4 = false;
			if(wparam == 0x35)
				key_5 = false;
			if(wparam == 0x36)
				key_6 = false;
			if(wparam == 0x37)
				key_7 = false;
			if(wparam == 0x38)
				key_8 = false;
			if(wparam == 0x39)
				key_9 = false;
			if(wparam == VK_UP)
				key_up = false;
			if(wparam == VK_DOWN)
				key_down = false;
			if(wparam == VK_LEFT)
				key_left = false;
			if(wparam == VK_RIGHT)
				key_right = false;
			if(wparam == VK_RETURN)
				key_enter = false;
			if(wparam == VK_SPACE)
				key_space = false;
		break;
		
		case WM_RBUTTONDOWN:
			right_click = true;
		break;
		
		case WM_RBUTTONUP:
			right_click = false;
		break;
		
		case WM_LBUTTONDOWN:
			left_click = true;
		break;
		
		case WM_LBUTTONUP:
			left_click = false;
		break;
		
		case WM_MBUTTONDOWN:
			middle_click = true;
		break;
		
		case WM_MBUTTONUP:
			middle_click = false;
		break;
		
	}
	
	GetCursorPos(&mouse_position);
	ScreenToClient(hwnd,&mouse_position);
	
	return DefWindowProc(hwnd,msg,wparam,lparam);
}

//End of tears_window_proc.h

Gdiplus::Graphics* tl_graphics;
Gdiplus::SolidBrush* tl_solidbrush;
Gdiplus::Pen* tl_pen;
Gdiplus::Font* tl_font;
Gdiplus::FontFamily* tl_font_type;

#define WINDOW_BORDER_X 6
#define WINDOW_BORDER_Y 28

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
	
	char icon_file[128] = {};
	double big_icon_w = 64, big_icon_h = 64;
	double small_icon_w = 32, small_icon_h = 32;
	
	bool resizable = false;
	bool borderless = false;
	bool fullscreen = false;
	bool vsync = false;
	bool fixed_view_scale = false;
	
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
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	RegisterClass(&wc);
	
	hwnd = CreateWindowEx(0,"_TEARS_LIBRARY",title,WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,
	GetSystemMetrics(SM_CXSCREEN)/2-width/2,GetSystemMetrics(SM_CYSCREEN)/2-height/2,width+WINDOW_BORDER_X,height+WINDOW_BORDER_Y,
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
	SetWindowPos(hwnd,HWND_TOP,GetSystemMetrics(SM_CXSCREEN)/2-w/2,GetSystemMetrics(SM_CYSCREEN)/2-h/2,w+WINDOW_BORDER_X,h+WINDOW_BORDER_Y,SWP_SHOWWINDOW);
	tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
	SelectObject(tl_hdcbuffer,tl_hbitmap);
	tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
}
void Display::setViewSize(int w, int h){
	this->view_width = w;
	this->view_height = h;
}
void Display::setFullscreen(bool fullscreen){
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
void Display::setVsync(bool enable){
	vsync = enable;
}
void Display::setTitle(const char* title){
	SetWindowTextA(hwnd,title);
}
void Display::setIcon(const char* file){
	strcpy(icon_file,file);
	HICON hicon_big = (HICON)LoadImage(NULL,file,IMAGE_ICON,big_icon_w,big_icon_h,LR_LOADFROMFILE);
	HICON hicon_small = (HICON)LoadImage(NULL,file,IMAGE_ICON,small_icon_w,small_icon_h,LR_LOADFROMFILE);
	SendMessage(hwnd, WM_SETICON, ICON_BIG,(LPARAM)hicon_big);
	SendMessage(hwnd, WM_SETICON, ICON_SMALL,(LPARAM)hicon_small);
}
void Display::setBigIconSize(int w, int h){
	if(icon_file[0] != '\0'){
		this->big_icon_w = w;
		this->big_icon_h = h;
		HICON hicon_big = (HICON)LoadImage(NULL,icon_file,IMAGE_ICON,big_icon_w,big_icon_h,LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_BIG,(LPARAM)hicon_big);
	}else{
		printf("Tears Library: Use setIcon(const char* file) method before call setBigIconSize(int w, int h)\n");
	}
}
void Display::setSmallIconSize(int w, int h){
	if(icon_file[0] != '\0'){
		this->small_icon_w = w;
		this->small_icon_h = h;
		HICON hicon_small = (HICON)LoadImage(NULL,icon_file,IMAGE_ICON,small_icon_w,small_icon_h,LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL,(LPARAM)hicon_small);
	}else{
		printf("Tears Library: Use setIcon(const char* file) method before call setSmallIconSize(int w, int h)\n");
	}
}
void Display::setResizable(bool enable){
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
		printf("Tears Library: You only can use setResizable(bool enable) method if you window is windowed\n");
	}
}
void Display::setBorderless(bool enable){
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
void Display::setFixedViewScale(bool enable){
	fixed_view_scale = enable;
}
void Display::showCursor(bool enable){
	ShowCursor(enable);
}
void Display::setCursor(const char* file){
	int len = strlen(file);
	if(file[len-1] == 'o' && file[len-2] == 'c' && file[len-3] == 'i'){
		HCURSOR hcursor = (HCURSOR)LoadImage(NULL,file,IMAGE_ICON,32,32,LR_LOADFROMFILE);
		SetClassLong(hwnd,GCL_HCURSOR,(LONG)hcursor);
	}else{
		printf("Tears Library: you can not use this image file for cursor (try .ico)\n");
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
		mouse_position_view.x = (((float)(mouse_position.x)/width)*view_width);
		mouse_position_view.y = (((float)(mouse_position.y)/height)*view_height);
		if(tl_window_sized){
			RECT rect;
			GetClientRect(hwnd,&rect);
			this->width = rect.right;
			this->height = rect.bottom;
			if(!fixed_view_scale && resizable){
				this->view_width = rect.right;
				this->view_height = rect.bottom;
				tl_hbitmap = CreateCompatibleBitmap(tl_hdc,width,height);
			}else{
				tl_hbitmap = CreateCompatibleBitmap(tl_hdc,view_width,view_height);
			}
			SelectObject(tl_hdcbuffer,tl_hbitmap);
			tl_graphics = new Gdiplus::Graphics(tl_hdcbuffer);
			tl_window_sized = false;
		}
	}
	if(msg.message == WM_QUIT){
		exit(0);
	}
	tl_graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	StretchBlt(tl_hdc,0,0,width,height,tl_hdcbuffer,0,0,view_width,view_height,SRCCOPY);
	fps_conter++;
	current_time = time(0);
	if(current_time - last_time > 0){
		fps = fps_conter;
		if(vsync && fps > 60 && fps < 70)
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
	if(img->GetLastStatus() != Gdiplus::Ok){
		printf("Tears Library: Can not load image: %s\n",file);
		exit(0);}
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
	delete bitmap;
	delete cached_bitmap;
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
double getTicks(){
	return GetTickCount();
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
void drawPolygon(int point[], int points_count){
	Gdiplus::Point points[points_count];
	for(int i = 0; i < points_count; i++)
		points[i] = Gdiplus::Point(point[i*2],point[(i*2)+1]);
	tl_graphics->DrawPolygon(tl_pen,points,points_count);
}

#endif