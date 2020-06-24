#ifndef TEARS_WINDOW_PROC_H
#define TEARS_WINDOW_PROC_H

bool tl_window_sized = false;

bool key_w = 0,key_d = 0,key_a = 0,key_s = 0,key_shift = 0,key_ctrl = 0,key_e = 0,key_q = 0,key_space = 0,key_escape = 0,key_up = 0,key_down = 0,key_right = 0,key_left = 0,key_1 = 0,key_2 = 0,key_3 = 0,key_4 = 0,key_5 = 0,key_6 = 0,key_7 = 0,key_8 = 0,key_9 = 0,key_0 = 0,key_r = 0,key_f = 0,key_z = 0,key_x = 0,key_c = 0,key_v = 0,key_b = 0,key_n = 0,key_m = 0,key_t = 0,key_g = 0,key_y = 0,key_h = 0,key_u = 0,key_j = 0,key_i = 0,key_k = 0,key_o = 0,key_l = 0,key_p = 0,key_tab = 0,key_enter = 0;
bool mb_left = 0, mb_right = 0, mb_middle = 0;

POINT mouse_position;
POINT mouse_position_view;

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
			mb_right = true;
		break;
		
		case WM_RBUTTONUP:
			mb_right = false;
		break;
		
		case WM_LBUTTONDOWN:
			mb_left = true;
		break;
		
		case WM_LBUTTONUP:
			mb_left = false;
		break;
		
		case WM_MBUTTONDOWN:
			mb_middle = true;
		break;
		
		case WM_MBUTTONUP:
			mb_middle = false;
		break;
		
	}
	
	GetCursorPos(&mouse_position);
	ScreenToClient(hwnd,&mouse_position);
	
	return DefWindowProc(hwnd,msg,wparam,lparam);
}

#endif