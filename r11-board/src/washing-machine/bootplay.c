#include "main.h"
#include "washing_machine.h"
HWND hbootplayWnd;
int bootplay_flag;
static int MainWindowProc(HWND hWnd, int nMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (nMessage){
	case MSG_CREATE:{
		int ret = tplayer_init(TPLAYER_VIDEO_ROTATE_DEGREE_0);
		if(ret != 0){
			printf("tplay init error\n");
			return -1;
		}
		if(bootplay_flag == BOOTPLAY_START){
			tplayer_play_url("/mnt/UDISK/AopenCN.mkv");
		}else if(bootplay_flag == BOOTPLAY_CLOSE){
			tplayer_play_url("/mnt/UDISK/close.mkv");
		}
		tplayer_play();
	}
	case MSG_DESTROY:
		DestroyAllControls(hWnd);
		return 0;
	case MSG_CLOSE:
                tplayer_exit();
		DestroyMainWindow(hWnd);
		PostQuitMessage(0);
                return 0;
	}
	return DefaultMainWinProc(hWnd, nMessage, wParam, lParam);
}

HWND GetBootplayWnd(void)
{
	return hbootplayWnd;
}
int BootplayWnd(HWND hosting, int flag)
{
	MSG Msg;
        MAINWINCREATE CreateInfo;
	bootplay_flag = flag;
	CreateInfo.dwStyle = WS_NONE;
        CreateInfo.dwExStyle = WS_EX_NONE;
        CreateInfo.spCaption = "";
        CreateInfo.hMenu = 0;
        CreateInfo.hCursor = 0; /*GetSystemCursor (0);*/
        CreateInfo.hIcon = 0;
        CreateInfo.MainWindowProc = MainWindowProc;
        CreateInfo.lx = 0;
        CreateInfo.ty = 0;
        CreateInfo.rx = g_rcScr.right;
        CreateInfo.by = g_rcScr.bottom;
        CreateInfo.iBkColor = PIXEL_black;
        CreateInfo.hHosting = hosting;
	
	hbootplayWnd = CreateMainWindow(&CreateInfo);
        if (hbootplayWnd == HWND_INVALID)
                return -1;
        ShowWindow(hbootplayWnd, SW_SHOWNORMAL);
	return 0;
}
#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
