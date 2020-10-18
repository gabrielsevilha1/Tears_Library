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

//======================================================= Linux Section =======================================================

#ifndef TEARS_LIBRARY_H
#define TEARS_LIBRARY_H

#if defined __linux__

#ifdef USE_OPENGL_CONTEXT
#define TL_USE_OPENGL_CONTEXT
#else
#define TL_USE_OPENGL
#endif

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include<X11/Xlib.h>
#include<X11/extensions/Xrandr.h>
//#include<X11/extensions/xf86vmode.h>
#include<X11/Xatom.h>
#include<GL/glx.h>

//if, for some reason, you get tears_library without stb_image integrated, you need add this:
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
//Of course, only if you have a stb_image.h in include folder
//You know how to made this!

//linux input.h (file init)
#include"linux_input.h"
//linux_input.h (file end)

#define TL_ERROR_LOG printf("Erro: Tears Library: ");printf

#if defined TL_USE_OPENGL
int tl_ellipse_sides = 24;
void setEllipseSides(int num_sides){
	tl_ellipse_sides = num_sides;
}
#endif

#if defined TL_USE_OPENGL
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

bool tl_is_display_active = false;
void check_display_exist(){
	if(tl_is_display_active){
		TL_ERROR_LOG("You do not can use two or more Displays/Windows\n");
		exit(0);
	}else{
		tl_is_display_active = true;
	}
}

int fps = 0;
double tl_init_time;

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

private:

	Display* display = XOpenDisplay(NULL);
	Screen* screen = ScreenOfDisplay(display,0);
	Window window;
	
	XVisualInfo* visualinfo;
	XSetWindowAttributes setwindowattributes;
	
	XRRScreenSize *xrrs;
	Rotation original_rotation;
	XRRScreenConfiguration* conf;
	short original_rate, original_size_id;

	int DESKTOP_RESOLUTION_X = screen->width;
	int DESKTOP_RESOLUTION_Y = screen->height;

	struct timespec _ts;
	
	double current_time = time(0);
	double last_time = current_time;
	int fps_counter = 0;

	double current_tick;
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
	
	clock_gettime(CLOCK_REALTIME,&_ts);
	current_tick = (_ts.tv_sec*1000)+(_ts.tv_nsec/1.0e6);
	last_tick = current_tick;
	frame_time = current_tick - last_tick;
  tl_init_time = _ts.tv_sec;
	
	int att[] = {GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,1};
	visualinfo = glXChooseVisual(display,0,att);
	setwindowattributes.colormap = XCreateColormap(display,DefaultRootWindow(display),visualinfo->visual,0);
	setwindowattributes.event_mask = ExposureMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	window = XCreateWindow(display,DefaultRootWindow(display),0,0,800,600,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
	GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
	glXMakeCurrent(display,window,glxcontext);
	XMapWindow(display,window);
	
	XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
	
	XMapRaised(display,window);
  XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
  XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);

	XSizeHints sizehints;
  sizehints.flags = PMinSize|PMaxSize;
  sizehints.min_width = 800;
  sizehints.min_height= 600;
  sizehints.max_width = 800;
  sizehints.max_height= 600;
	XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	
	conf = XRRGetScreenInfo(display, RootWindow(display,0));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,800.0,600.0,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#endif
	
}
TWindow::TWindow(const char* title){

	check_display_exist();
	
	this->width = 800;
	this->height = 600;
	this->view_width = 800;
	this->view_height = 600;
	
	clock_gettime(CLOCK_REALTIME,&_ts);
	current_tick = (_ts.tv_sec*1000)+(_ts.tv_nsec/1.0e6);
	last_tick = current_tick;
	frame_time = current_tick - last_tick;
  tl_init_time = _ts.tv_sec;
	
	int att[] = {GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,1};
	visualinfo = glXChooseVisual(display,0,att);
	setwindowattributes.colormap = XCreateColormap(display,DefaultRootWindow(display),visualinfo->visual,0);
	setwindowattributes.event_mask = ExposureMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	window = XCreateWindow(display,DefaultRootWindow(display),0,0,800,600,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
	XStoreName(display,window,title);
	GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
	glXMakeCurrent(display,window,glxcontext);
	XMapWindow(display,window);
	
	XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
	
	XMapRaised(display,window);
  XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
  XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);

	XSizeHints sizehints;
  sizehints.flags = PMinSize|PMaxSize;
  sizehints.min_width = 800;
  sizehints.min_height= 600;
  sizehints.max_width = 800;
  sizehints.max_height= 600;
	XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	
	conf = XRRGetScreenInfo(display, RootWindow(display,0));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,800.0,600.0,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#endif
	
}
TWindow::TWindow(const char* title, int width, int height){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	
	clock_gettime(CLOCK_REALTIME,&_ts);
	current_tick = (_ts.tv_sec*1000)+(_ts.tv_nsec/1.0e6);
	last_tick = current_tick;
	frame_time = current_tick - last_tick;
  tl_init_time = _ts.tv_sec;
	
	int att[] = {GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,1};
	visualinfo = glXChooseVisual(display,0,att);
	setwindowattributes.colormap = XCreateColormap(display,DefaultRootWindow(display),visualinfo->visual,0);
	setwindowattributes.event_mask = ExposureMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	window = XCreateWindow(display,DefaultRootWindow(display),0,0,800,600,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
	XStoreName(display,window,title);
	GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
	glXMakeCurrent(display,window,glxcontext);
	XMapWindow(display,window);
	
	XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
	
	XMapRaised(display,window);
  XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
  XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);

	XSizeHints sizehints;
  sizehints.flags = PMinSize|PMaxSize;
  sizehints.min_width = width;
  sizehints.min_height= height;
  sizehints.max_width = width;
  sizehints.max_height= height;
	XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	
	conf = XRRGetScreenInfo(display, RootWindow(display,0));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#endif
	
}
TWindow::TWindow(const char* title, int width, int height, bool fullscreen){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	this->fullscreen = fullscreen;
	
	clock_gettime(CLOCK_REALTIME,&_ts);
	current_tick = (_ts.tv_sec*1000)+(_ts.tv_nsec/1.0e6);
	last_tick = current_tick;
	frame_time = current_tick - last_tick;
  tl_init_time = _ts.tv_sec;
	
	int att[] = {GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,1};
	visualinfo = glXChooseVisual(display,0,att);
	setwindowattributes.colormap = XCreateColormap(display,DefaultRootWindow(display),visualinfo->visual,0);
	setwindowattributes.event_mask = ExposureMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	window = XCreateWindow(display,DefaultRootWindow(display),0,0,800,600,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
	XStoreName(display,window,title);
	GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
	glXMakeCurrent(display,window,glxcontext);
	XMapWindow(display,window);
	
	XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
	
	XMapRaised(display,window);
  XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
  XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);

	XSizeHints sizehints;
  sizehints.flags = PMinSize|PMaxSize;
  sizehints.min_width = width;
  sizehints.min_height= height;
  sizehints.max_width = width;
  sizehints.max_height= height;
	XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	
	conf = XRRGetScreenInfo(display, RootWindow(display,0));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#endif
	
	if(fullscreen){
		int use_this_resolution = 0;
		int num_sizes;
		xrrs = XRRSizes(display,0,&num_sizes);
		for(int i = 0; i < num_sizes; i++){
			if(xrrs[i].width == width && xrrs[i].height == height){
				use_this_resolution = i;
			}
		}
		
		XUnmapWindow(display,window);
		XDestroyWindow(display,window);
		setwindowattributes.override_redirect = 1;
		window = XCreateWindow(display,DefaultRootWindow(display),0,0,width,height,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask|CWOverrideRedirect,&setwindowattributes);
		GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
		glXMakeCurrent(display,window,glxcontext);
		XMoveWindow(display,window,0,0);
		XMapWindow(display,window);
		
		XMapRaised(display,window);
		XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
		XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);
		
		XRRSetScreenConfigAndRate(display,conf,RootWindow(display,0),use_this_resolution,RR_Rotate_0,60,CurrentTime);

	}
	
}
TWindow::TWindow(const char* title, int width, int height, bool fullscreen, bool vsync){

	check_display_exist();
	
	this->width = width;
	this->height = height;
	this->view_width = width;
	this->view_height = height;
	this->fullscreen = fullscreen;
	this->vsync = vsync;
	
	clock_gettime(CLOCK_REALTIME,&_ts);
	current_tick = (_ts.tv_sec*1000)+(_ts.tv_nsec/1.0e6);
	last_tick = current_tick;
	frame_time = current_tick - last_tick;
  tl_init_time = _ts.tv_sec;
	
	int att[] = {GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,1};
	visualinfo = glXChooseVisual(display,0,att);
	setwindowattributes.colormap = XCreateColormap(display,DefaultRootWindow(display),visualinfo->visual,0);
	setwindowattributes.event_mask = ExposureMask|StructureNotifyMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	window = XCreateWindow(display,DefaultRootWindow(display),0,0,800,600,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
	XStoreName(display,window,title);
	GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
	glXMakeCurrent(display,window,glxcontext);
	XMapWindow(display,window);
	
	XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
	
	XMapRaised(display,window);
    XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
    XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);
	
	XSizeHints sizehints;
    sizehints.flags = PMinSize|PMaxSize;
    sizehints.min_width = width;
    sizehints.min_height= height;
    sizehints.max_width = width;
    sizehints.max_height= height;
	XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	
	conf = XRRGetScreenInfo(display, RootWindow(display,0));
	original_rate = XRRConfigCurrentRate(conf);
	original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,width,height,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
	#endif
	
	if(fullscreen){
		int use_this_resolution = 0;
		int num_sizes;
		xrrs = XRRSizes(display,0,&num_sizes);
		for(int i = 0; i < num_sizes; i++){
			if(xrrs[i].width == width && xrrs[i].height == height){
				use_this_resolution = i;
			}
		}
		
		XUnmapWindow(display,window);
		XDestroyWindow(display,window);
		setwindowattributes.override_redirect = 1;
		window = XCreateWindow(display,DefaultRootWindow(display),0,0,width,height,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask|CWOverrideRedirect,&setwindowattributes);
		GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
		glXMakeCurrent(display,window,glxcontext);
		XMoveWindow(display,window,0,0);
		XMapWindow(display,window);
		
		XMapRaised(display,window);
		XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
		XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);
		
		XRRSetScreenConfigAndRate(display,conf,RootWindow(display,0),use_this_resolution,RR_Rotate_0,60,CurrentTime);

	}
	
	GLXDrawable drawable = glXGetCurrentDrawable();
	PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
	PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
	PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
	if(vsync){
		glXSwapIntervalEXT(display,drawable,1);
		glXSwapIntervalMESA(1);
		glXSwapIntervalSGI(1);
	}else{
		glXSwapIntervalEXT(display,drawable,0);
		glXSwapIntervalMESA(0);
		glXSwapIntervalSGI(0);
	}
	
}
TWindow::~TWindow(){
	shutdown();
}
void TWindow::setSize(int w, int h){
	this->width = w;
	this->height = h;
	if(!resizable){
		XMoveResizeWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2,w,h);
		XSizeHints sizehints;
		sizehints.flags = PMinSize|PMaxSize;
		sizehints.min_width = w;
		sizehints.min_height= h;
		sizehints.max_width = w;
		sizehints.max_height= h;
		XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	}else{
		XMoveResizeWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2,w,h);
		XSizeHints sizehints;
		sizehints.flags = PMinSize|PMaxSize;
		sizehints.min_width = 100;
		sizehints.min_height= 100;
		sizehints.max_width = DESKTOP_RESOLUTION_X;
		sizehints.max_height= DESKTOP_RESOLUTION_Y;
		XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,width,height,0.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0.0,0.0,width,height);
}
void TWindow::setViewSize(int w, int h){
	this->view_width = w;
	this->view_height = h;
}
void TWindow::setFullscreen(bool fullscreen){
	this->fullscreen = fullscreen;
	if(fullscreen){
		int use_this_resolution = 0;
		int num_sizes;
		xrrs = XRRSizes(display,0,&num_sizes);
		for(int i = 0; i < num_sizes; i++){
			if(xrrs[i].width == width && xrrs[i].height == height){
				use_this_resolution = i;
			}
		}
		
		XUnmapWindow(display,window);
		XDestroyWindow(display,window);
		setwindowattributes.override_redirect = 1;
		window = XCreateWindow(display,DefaultRootWindow(display),0,0,width,height,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask|CWOverrideRedirect,&setwindowattributes);
		GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
		glXMakeCurrent(display,window,glxcontext);
		XMoveWindow(display,window,0,0);
		XMapWindow(display,window);
		
		XMapRaised(display,window);
		XGrabPointer(display,window,True,0,GrabModeAsync,GrabModeAsync,window,0L,CurrentTime);
		XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);
		
		XRRSetScreenConfigAndRate(display,conf,RootWindow(display,0),use_this_resolution,RR_Rotate_0,60,CurrentTime);

	}else{
		
		XUnmapWindow(display,window);
		XDestroyWindow(display,window);
		setwindowattributes.override_redirect = 0;
		window = XCreateWindow(display,DefaultRootWindow(display),0,0,width,height,0,visualinfo->depth,InputOutput,visualinfo->visual,CWColormap|CWEventMask,&setwindowattributes);
		GLXContext glxcontext = glXCreateContext(display,visualinfo,NULL,1);
		glXMakeCurrent(display,window,glxcontext);
		XMoveWindow(display,window,0,0);
		XMapWindow(display,window);
		
		XMapRaised(display,window);
		XGrabPointer(display,window,False,0,GrabModeAsync,GrabModeAsync,0,0,CurrentTime);
		XGrabKeyboard(display,window,False,GrabModeAsync,GrabModeAsync,CurrentTime);
		
		XMoveWindow(display,window,DESKTOP_RESOLUTION_X/2-width/2,DESKTOP_RESOLUTION_Y/2-height/2);
		XRRSetScreenConfigAndRate(display,conf,RootWindow(display,0),original_size_id,original_rotation,original_rate,CurrentTime);
	
		if(!resizable){
			XSizeHints sizehints;
			sizehints.flags = PMinSize|PMaxSize;
			sizehints.min_width = width;
			sizehints.min_height= height;
			sizehints.max_width = width;
			sizehints.max_height= height;
			XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
		}
		
		if(borderless){
			struct MwmHints{
				unsigned long flags;
				unsigned long functions;
				unsigned long decorations;
				long input_mode;
				unsigned long status;
			};
			enum{
				MWM_HINTS_FUNCTIONS = (1L << 0),
				MWM_HINTS_DECORATIONS =  (1L << 1),
				MWM_FUNC_ALL = (1L << 0),
				MWM_FUNC_RESIZE = (1L << 1),
				MWM_FUNC_MOVE = (1L << 2),
				MWM_FUNC_MINIMIZE = (1L << 3),
				MWM_FUNC_MAXIMIZE = (1L << 4),
				MWM_FUNC_CLOSE = (1L << 5)
			};
			Atom mwmHintsProperty = XInternAtom(display, "_MOTIF_WM_HINTS", 0);
			struct MwmHints hints;
			hints.flags = MWM_HINTS_DECORATIONS;
			hints.decorations = 0;
			XChangeProperty(display, window, mwmHintsProperty, mwmHintsProperty, 32,
		    PropModeReplace, (unsigned char *)&hints, 5);
		}else{
			struct MwmHints{
				unsigned long flags;
				unsigned long functions;
				unsigned long decorations;
				long input_mode;
				unsigned long status;
			};
			enum{
				MWM_HINTS_FUNCTIONS = (1L << 0),
				MWM_HINTS_DECORATIONS =  (1L << 1),
				MWM_FUNC_ALL = (1L << 0),
				MWM_FUNC_RESIZE = (1L << 1),
				MWM_FUNC_MOVE = (1L << 2),
				MWM_FUNC_MINIMIZE = (1L << 3),
				MWM_FUNC_MAXIMIZE = (1L << 4),
				MWM_FUNC_CLOSE = (1L << 5)
			};
			Atom mwmHintsProperty = XInternAtom(display, "_MOTIF_WM_HINTS", 0);
			struct MwmHints hints;
			hints.flags = MWM_HINTS_DECORATIONS;
			hints.decorations = 1;
			XChangeProperty(display, window, mwmHintsProperty, mwmHintsProperty, 32,
		    PropModeReplace, (unsigned char *)&hints, 5);
		}
		
	}
	
	#if defined TL_USE_OPENGL
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,800.0,600.0,0.0,0.0,1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	#endif
}
void TWindow::setVsync(bool enable){
	vsync = enable;
	GLXDrawable drawable = glXGetCurrentDrawable();
	PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
	PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
	PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
	if(enable){
		glXSwapIntervalEXT(display,drawable,1);
		glXSwapIntervalMESA(1);
		glXSwapIntervalSGI(1);
	}else{
		glXSwapIntervalEXT(display,drawable,0);
		glXSwapIntervalMESA(0);
		glXSwapIntervalSGI(0);
	}
}
void TWindow::setTitle(const char* title){
	XStoreName(display,window,title);
}
void TWindow::setIcon(const char* file){
	//Nothing in linux (without assurance)
}
void TWindow::setBigIconSize(int w, int h){
	//Nothing in linux
}
void TWindow::setSmallIconSize(int w, int h){
	//Nothing in linux
}
void TWindow::setResizable(bool enable){
	this->resizable = enable;
	if(!fullscreen){
		if(enable){
			XSizeHints sizehints;
			sizehints.flags = PMinSize|PMaxSize;
			sizehints.flags = PMinSize|PMaxSize;
			sizehints.min_width = 100;
			sizehints.min_height= 100;
			sizehints.max_width = DESKTOP_RESOLUTION_X;
			sizehints.max_height= DESKTOP_RESOLUTION_Y;
			XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
		}else{
			XSizeHints sizehints;
			sizehints.flags = PMinSize|PMaxSize;
			sizehints.min_width = 800;
			sizehints.min_height= 600;
			sizehints.max_width = 800;
			sizehints.max_height= 600;
			XSetWMSizeHints(display,window,&sizehints,XA_WM_NORMAL_HINTS);
		}
		resizable = enable;
	}else{
		TL_ERROR_LOG("You only can use setResizable(bool enable) method if you window is windowed\n");
	}
}

void TWindow::setBorderless(bool enable){
	this->borderless = enable;
	if(enable){
		struct MwmHints{
			unsigned long flags;
			unsigned long functions;
			unsigned long decorations;
			long input_mode;
			unsigned long status;
		};
		enum{
			MWM_HINTS_FUNCTIONS = (1L << 0),
			MWM_HINTS_DECORATIONS =  (1L << 1),
			MWM_FUNC_ALL = (1L << 0),
			MWM_FUNC_RESIZE = (1L << 1),
			MWM_FUNC_MOVE = (1L << 2),
			MWM_FUNC_MINIMIZE = (1L << 3),
			MWM_FUNC_MAXIMIZE = (1L << 4),
			MWM_FUNC_CLOSE = (1L << 5)
		};
		Atom mwmHintsProperty = XInternAtom(display, "_MOTIF_WM_HINTS", 0);
		struct MwmHints hints;
		hints.flags = MWM_HINTS_DECORATIONS;
		hints.decorations = 0;
		XChangeProperty(display, window, mwmHintsProperty, mwmHintsProperty, 32,
        PropModeReplace, (unsigned char *)&hints, 5);
	}else{
		struct MwmHints{
			unsigned long flags;
			unsigned long functions;
			unsigned long decorations;
			long input_mode;
			unsigned long status;
		};
		enum{
			MWM_HINTS_FUNCTIONS = (1L << 0),
			MWM_HINTS_DECORATIONS =  (1L << 1),
			MWM_FUNC_ALL = (1L << 0),
			MWM_FUNC_RESIZE = (1L << 1),
			MWM_FUNC_MOVE = (1L << 2),
			MWM_FUNC_MINIMIZE = (1L << 3),
			MWM_FUNC_MAXIMIZE = (1L << 4),
			MWM_FUNC_CLOSE = (1L << 5)
		};
		Atom mwmHintsProperty = XInternAtom(display, "_MOTIF_WM_HINTS", 0);
		struct MwmHints hints;
		hints.flags = MWM_HINTS_DECORATIONS;
		hints.decorations = 1;
		XChangeProperty(display, window, mwmHintsProperty, mwmHintsProperty, 32,
        PropModeReplace, (unsigned char *)&hints, 5);
	}
}
void TWindow::setFixedViewScale(bool enable){
	fixed_view_scale = enable;
}
void TWindow::showCursor(bool enable){
	if(enable){
		XUndefineCursor(display,window);
	}else{
		XColor color;
		char data[1] = {0};
		Pixmap pixmap = XCreateBitmapFromData(display, window, data, 1, 1);
		Cursor cursor = XCreatePixmapCursor(display, pixmap, pixmap, &color, &color, 0, 0);
		XFreePixmap(display, pixmap);
		XDefineCursor(display, window, cursor);
	}
}
void TWindow::setCursor(const char* file){
  //Not avalible in linux
  //for now, try use "showCursor(false)" and draw a image in mouse coordnates
}
void TWindow::shutdown(){
	tl_is_display_active = false;
	if(this->fullscreen)setFullscreen(false);
	glXMakeCurrent(display,0,0);
  XUnmapWindow(display,window);
	XDestroyWindow(display,window);
  //For some reason, this function causes crash:
  //XCloseDisplay(display);
}
void TWindow::show(){

	if(tl_window_sized){
		width = tl_x11_width_after_resize;
		height = tl_x11_height_after_resize;
		if(fixed_view_scale){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0,view_width,view_height,0.0,0.0,1.0);
			glMatrixMode(GL_MODELVIEW);
			glViewport(0.0,0.0,width,height);
		}
		tl_window_sized = false;
	}

	#if defined TL_USE_OPENGL
	
		glXSwapBuffers(display,window);
		glClear(GL_COLOR_BUFFER_BIT);
		
	#elif defined TL_USE_OPENGL_CONTEXT
	
		glXSwapBuffers(display,window);
		
	#endif
	
	tl_call_input(display);
	mouse_position_view.x = (float)mouse_position.x/width*view_width;
	mouse_position_view.y = (float)mouse_position.y/height*view_height;
	
	fps_counter++;
	current_time = time(0);
	if(current_time - last_time > 0){
		last_time = current_time;
		fps = fps_counter;
		fps_counter = 0;
	}
	
}
double getTime(){
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME,&ts);
	//return (ts.tv_sec*1000)+(ts.tv_nsec/1.0e6);
  return (((ts.tv_sec-tl_init_time)*1000.0f)+ts.tv_nsec/1.0e6)/1000;
}

#if defined TL_USE_OPENGL
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
  void flip_x(bool flip);
  void flip_y(bool flip);
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

	unsigned int texture;
	
};
Image::Image(const char* file){

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
	
}
Image::Image(const char* file, int x, int y){

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
	
}
Image::Image(const char* file, int x, int y, int w, int h){

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
	
}
Image::~Image(){

}
void Image::draw(){

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
	
}
void Image::draw(float a){

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
	
}
void Image::draw(int x, int y){

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
	
}
void Image::draw(int x, int y, int w, int h){

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

}
void Image::draw(int x, int y, int w, int h, float a){

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
void drawText(const char* text){
	int x = 0, y = 0;
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

void resetMatrix(){
	glLoadIdentity();
}
void translate(float x, float y){
	glTranslatef(x,y,0.0);
}
void rotate(float a){
	glRotatef(a,0.0,0.0,1.0);
}
void scale(float x, float y){
	glScalef(x,y,0.0);
}
void setColor(int r, int g, int b){
	glColor3f((float)r/255.0f,(float)g/255.0f,(float)b/255.0f);
}
void setLineSize(int size){
	glLineWidth(size);
}
void fillRect(int x, int y, int w, int h){
	glBegin(GL_QUADS);
		glVertex2f(x,y);
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glVertex2f(x+w,y);
	glEnd();
}
void fillEllipse(int x, int y, int r){
	glBegin(GL_POLYGON);
		for(int i = 0; i < 360; i+=360/tl_ellipse_sides){
			glVertex2f(x+cos(i*3.14159265/180)*r,y+sin(i*3.14159265/180)*r);
		}
	glEnd();
}
void fillPolygon(int point[], int points_count){
	glBegin(GL_POLYGON);
		for(int i = 0; i < points_count; i++){
			glVertex2f(point[i*2],point[(i*2)+1]);
		}
	glEnd();
}
void drawPixel(int x, int y){
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}
void drawRect(int x, int y, int w, int h){
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x,y+h);
		glVertex2f(x+w,y+h);
		glVertex2f(x+w,y);
	glEnd();
}
void drawEllipse(int x, int y, int r){
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 360; i+=360/tl_ellipse_sides){
			glVertex2f(x+cos(i*3.14159265/180)*r,y+sin(i*3.14159265/180)*r);
		}
	glEnd();
}
void drawLine(int x, int y, int final_x, int final_y){
	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(final_x,final_y);
	glEnd();
}
void drawPolygon(int point[], int points_count){
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < points_count; i++){
			glVertex2f(point[i*2],point[(i*2)+1]);
		}
	glEnd();
}

#endif

#endif

#endif
