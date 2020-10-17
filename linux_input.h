bool tl_window_sized = false;

bool vk_w = 0,vk_d = 0,vk_a = 0,vk_s = 0,vk_shift = 0,vk_ctrl = 0,vk_e = 0,vk_q = 0,vk_space = 0,vk_escape = 0,vk_up = 0,vk_down = 0,vk_right = 0,vk_left = 0,vk_1 = 0,vk_2 = 0,vk_3 = 0,vk_4 = 0,vk_5 = 0,vk_6 = 0,vk_7 = 0,vk_8 = 0,vk_9 = 0,vk_0 = 0,vk_r = 0,vk_f = 0,vk_z = 0,vk_x = 0,vk_c = 0,vk_v = 0,vk_b = 0,vk_n = 0,vk_m = 0,vk_t = 0,vk_g = 0,vk_y = 0,vk_h = 0,vk_u = 0,vk_j = 0,vk_i = 0,vk_k = 0,vk_o = 0,vk_l = 0,vk_p = 0,vk_tab = 0,vk_enter = 0;
bool left_click = 0, right_click = 0, middle_click = 0;

int tl_x11_width_after_resize, tl_x11_height_after_resize;

typedef struct{
	int x, y;
}tl_point;

tl_point mouse_position;
tl_point mouse_position_view;

void tl_call_input(Display* display){
	XEvent event;
	while(XPending(display)){
		XNextEvent(display,&event);
		if(event.type == ConfigureNotify){
			XConfigureEvent xce = event.xconfigure;
            if (xce.width != tl_x11_width_after_resize || xce.height != tl_x11_height_after_resize) {
                tl_x11_width_after_resize = xce.width;
                tl_x11_height_after_resize = xce.height;
                tl_window_sized = true;
            }
		}
		if(event.type == MotionNotify){
			mouse_position.x = event.xbutton.x;
			mouse_position.y = event.xbutton.y;
		}
		if(event.type == ButtonPress){
			XButtonEvent bt = event.xbutton;
			if(bt.button == 1)
				left_click = true;
			if(bt.button == 2)
				middle_click = true;
			if(bt.button == 3)
				right_click = true;
		}
		if(event.type == ButtonRelease){
			XButtonEvent bt = event.xbutton;
			if(bt.button == 1)
				left_click = false;
			if(bt.button == 2)
				middle_click = false;
			if(bt.button == 3)
				right_click = false;
		}
		if(event.type == KeyPress){
			if(XLookupKeysym(&event.xkey,0)==XK_a)vk_a = true;
			if(XLookupKeysym(&event.xkey,0)==XK_b)vk_b = true;
			if(XLookupKeysym(&event.xkey,0)==XK_c)vk_c = true;
			if(XLookupKeysym(&event.xkey,0)==XK_d)vk_d = true;
			if(XLookupKeysym(&event.xkey,0)==XK_e)vk_e = true;
			if(XLookupKeysym(&event.xkey,0)==XK_f)vk_f = true;
			if(XLookupKeysym(&event.xkey,0)==XK_g)vk_g = true;
			if(XLookupKeysym(&event.xkey,0)==XK_h)vk_h = true;
			if(XLookupKeysym(&event.xkey,0)==XK_i)vk_i = true;
			if(XLookupKeysym(&event.xkey,0)==XK_j)vk_j = true;
			if(XLookupKeysym(&event.xkey,0)==XK_k)vk_k = true;
			if(XLookupKeysym(&event.xkey,0)==XK_l)vk_l = true;
			if(XLookupKeysym(&event.xkey,0)==XK_m)vk_m = true;
			if(XLookupKeysym(&event.xkey,0)==XK_n)vk_n = true;
			if(XLookupKeysym(&event.xkey,0)==XK_o)vk_o = true;
			if(XLookupKeysym(&event.xkey,0)==XK_p)vk_p = true;
			if(XLookupKeysym(&event.xkey,0)==XK_q)vk_q = true;
			if(XLookupKeysym(&event.xkey,0)==XK_r)vk_r = true;
			if(XLookupKeysym(&event.xkey,0)==XK_s)vk_s = true;
			if(XLookupKeysym(&event.xkey,0)==XK_t)vk_t = true;
			if(XLookupKeysym(&event.xkey,0)==XK_u)vk_u = true;
			if(XLookupKeysym(&event.xkey,0)==XK_v)vk_v = true;
			if(XLookupKeysym(&event.xkey,0)==XK_w)vk_w = true;
			if(XLookupKeysym(&event.xkey,0)==XK_x)vk_x = true;
			if(XLookupKeysym(&event.xkey,0)==XK_y)vk_y = true;
			if(XLookupKeysym(&event.xkey,0)==XK_z)vk_z = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Escape)vk_escape = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Tab)vk_tab = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Shift_L)vk_shift = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Control_L)vk_ctrl = true;
			if(XLookupKeysym(&event.xkey,0)==XK_space)vk_space = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Right)vk_right = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Left)vk_left = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Up)vk_up = true;
			if(XLookupKeysym(&event.xkey,0)==XK_Down)vk_down = true;
			if(XLookupKeysym(&event.xkey,0)==XK_KP_Enter)vk_enter = true;
			if(XLookupKeysym(&event.xkey,0)==XK_0)vk_0 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_1)vk_1 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_2)vk_2 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_3)vk_3 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_4)vk_4 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_5)vk_5 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_6)vk_6 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_7)vk_7 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_8)vk_8 = true;
			if(XLookupKeysym(&event.xkey,0)==XK_9)vk_9 = true;
		}
		if(event.type == KeyRelease){
			if(XLookupKeysym(&event.xkey,0)==XK_a)vk_a = false;
			if(XLookupKeysym(&event.xkey,0)==XK_b)vk_b = false;
			if(XLookupKeysym(&event.xkey,0)==XK_c)vk_c = false;
			if(XLookupKeysym(&event.xkey,0)==XK_d)vk_d = false;
			if(XLookupKeysym(&event.xkey,0)==XK_e)vk_e = false;
			if(XLookupKeysym(&event.xkey,0)==XK_f)vk_f = false;
			if(XLookupKeysym(&event.xkey,0)==XK_g)vk_g = false;
			if(XLookupKeysym(&event.xkey,0)==XK_h)vk_h = false;
			if(XLookupKeysym(&event.xkey,0)==XK_i)vk_i = false;
			if(XLookupKeysym(&event.xkey,0)==XK_j)vk_j = false;
			if(XLookupKeysym(&event.xkey,0)==XK_k)vk_k = false;
			if(XLookupKeysym(&event.xkey,0)==XK_l)vk_l = false;
			if(XLookupKeysym(&event.xkey,0)==XK_m)vk_m = false;
			if(XLookupKeysym(&event.xkey,0)==XK_n)vk_n = false;
			if(XLookupKeysym(&event.xkey,0)==XK_o)vk_o = false;
			if(XLookupKeysym(&event.xkey,0)==XK_p)vk_p = false;
			if(XLookupKeysym(&event.xkey,0)==XK_q)vk_q = false;
			if(XLookupKeysym(&event.xkey,0)==XK_r)vk_r = false;
			if(XLookupKeysym(&event.xkey,0)==XK_s)vk_s = false;
			if(XLookupKeysym(&event.xkey,0)==XK_t)vk_t = false;
			if(XLookupKeysym(&event.xkey,0)==XK_u)vk_u = false;
			if(XLookupKeysym(&event.xkey,0)==XK_v)vk_v = false;
			if(XLookupKeysym(&event.xkey,0)==XK_w)vk_w = false;
			if(XLookupKeysym(&event.xkey,0)==XK_x)vk_x = false;
			if(XLookupKeysym(&event.xkey,0)==XK_y)vk_y = false;
			if(XLookupKeysym(&event.xkey,0)==XK_z)vk_z = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Escape)vk_escape = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Tab)vk_tab = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Shift_L)vk_shift = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Control_L)vk_ctrl = false;
			if(XLookupKeysym(&event.xkey,0)==XK_space)vk_space = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Right)vk_right = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Left)vk_left = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Up)vk_up = false;
			if(XLookupKeysym(&event.xkey,0)==XK_Down)vk_down = false;
			if(XLookupKeysym(&event.xkey,0)==XK_KP_Enter)vk_enter = false;
			if(XLookupKeysym(&event.xkey,0)==XK_0)vk_0 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_1)vk_1 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_2)vk_2 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_3)vk_3 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_4)vk_4 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_5)vk_5 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_6)vk_6 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_7)vk_7 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_8)vk_8 = false;
			if(XLookupKeysym(&event.xkey,0)==XK_9)vk_9 = false;
		}
	}
}
