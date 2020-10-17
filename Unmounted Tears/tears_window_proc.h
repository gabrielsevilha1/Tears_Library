bool tl_window_sized = false;

bool vk_w = 0,vk_d = 0,vk_a = 0,vk_s = 0,vk_shift = 0,vk_ctrl = 0,vk_e = 0,vk_q = 0,vk_space = 0,vk_escape = 0,vk_up = 0,vk_down = 0,vk_right = 0,vk_left = 0,vk_1 = 0,vk_2 = 0,vk_3 = 0,vk_4 = 0,vk_5 = 0,vk_6 = 0,vk_7 = 0,vk_8 = 0,vk_9 = 0,vk_0 = 0,vk_r = 0,vk_f = 0,vk_z = 0,vk_x = 0,vk_c = 0,vk_v = 0,vk_b = 0,vk_n = 0,vk_m = 0,vk_t = 0,vk_g = 0,vk_y = 0,vk_h = 0,vk_u = 0,vk_j = 0,vk_i = 0,vk_k = 0,vk_o = 0,vk_l = 0,vk_p = 0,vk_tab = 0,vk_enter = 0;
bool left_click = 0, right_click = 0, middle_click = 0;

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
		case WM_vkDOWN:
			if(wparam == 'Q')vk_q = true;
			if(wparam == 'W')vk_w = true;
			if(wparam == 'E')vk_e = true;
			if(wparam == 'R')vk_r = true;
			if(wparam == 'T')vk_t = true;
			if(wparam == 'Y')vk_y = true;
			if(wparam == 'U')vk_u = true;
			if(wparam == 'I')vk_i = true;
			if(wparam == 'O')vk_o = true;
			if(wparam == 'P')vk_p = true;
			if(wparam == 'A')vk_a = true;
			if(wparam == 'S')vk_s = true;
			if(wparam == 'D')vk_d = true;
			if(wparam == 'F')vk_f = true;
			if(wparam == 'G')vk_g = true;
			if(wparam == 'H')vk_h = true;
			if(wparam == 'J')vk_j = true;
			if(wparam == 'K')vk_k = true;
			if(wparam == 'L')vk_l = true;
			if(wparam == 'Z')vk_z = true;
			if(wparam == 'X')vk_x = true;
			if(wparam == 'C')vk_c = true;
			if(wparam == 'V')vk_v = true;
			if(wparam == 'B')vk_b = true;
			if(wparam == 'N')vk_n = true;
			if(wparam == 'M')vk_m = true;
			if(wparam == VK_ESCAPE)vk_escape = true;
			if(wparam == VK_TAB)vk_tab == true;
			if(wparam == VK_SHIFT)vk_shift = true;
			if(wparam == VK_CONTROL)vk_ctrl = true;
			if(wparam == 0x30)vk_0 = true;
			if(wparam == 0x31)vk_1 = true;
			if(wparam == 0x32)vk_2 = true;
			if(wparam == 0x33)vk_3 = true;
			if(wparam == 0x34)vk_4 = true;
			if(wparam == 0x35)vk_5 = true;
			if(wparam == 0x36)vk_6 = true;
			if(wparam == 0x37)vk_7 = true;
			if(wparam == 0x38)vk_8 = true;
			if(wparam == 0x39)vk_9 = true;
			if(wparam == VK_UP)vk_up = true;
			if(wparam == VK_DOWN)vk_down = true;
			if(wparam == VK_LEFT)vk_left = true;
			if(wparam == VK_RIGHT)vk_right = true;
			if(wparam == VK_RETURN)vk_enter = true;
			if(wparam == VK_SPACE)vk_space = true;
		break;
			
		case WM_vkUP:
			if(wparam == 'Q')vk_q = false;
			if(wparam == 'W')vk_w = false;
			if(wparam == 'E')vk_e = false;
			if(wparam == 'R')vk_r = false;
			if(wparam == 'T')vk_t = false;
			if(wparam == 'Y')vk_y = false;
			if(wparam == 'U')vk_u = false;
			if(wparam == 'I')vk_i = false;
			if(wparam == 'O')vk_o = false;
			if(wparam == 'P')vk_p = false;
			if(wparam == 'A')vk_a = false;
			if(wparam == 'S')vk_s = false;
			if(wparam == 'D')vk_d = false;
			if(wparam == 'F')vk_f = false;
			if(wparam == 'G')vk_g = false;
			if(wparam == 'H')vk_h = false;
			if(wparam == 'J')vk_j = false;
			if(wparam == 'K')vk_k = false;
			if(wparam == 'L')vk_l = false;
			if(wparam == 'Z')vk_z = false;
			if(wparam == 'X')vk_x = false;
			if(wparam == 'C')vk_c = false;
			if(wparam == 'V')vk_v = false;
			if(wparam == 'B')vk_b = false;
			if(wparam == 'N')vk_n = false;
			if(wparam == 'M')vk_m = false;
			if(wparam == VK_ESCAPE)vk_escape = false;
			if(wparam == VK_TAB)vk_tab == false;
			if(wparam == VK_SHIFT)vk_shift = false;
			if(wparam == VK_CONTROL)vk_ctrl = false;
			if(wparam == 0x30)vk_0 = false;
			if(wparam == 0x31)vk_1 = false;
			if(wparam == 0x32)vk_2 = false;
			if(wparam == 0x33)vk_3 = false;
			if(wparam == 0x34)vk_4 = false;
			if(wparam == 0x35)vk_5 = false;
			if(wparam == 0x36)vk_6 = false;
			if(wparam == 0x37)vk_7 = false;
			if(wparam == 0x38)vk_8 = false;
			if(wparam == 0x39)vk_9 = false;
			if(wparam == VK_UP)vk_up = false;
			if(wparam == VK_DOWN)vk_down = false;
			if(wparam == VK_LEFT)vk_left = false;
			if(wparam == VK_RIGHT)vk_right = false;
			if(wparam == VK_RETURN)vk_enter = false;
			if(wparam == VK_SPACE)vk_space = false;
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
