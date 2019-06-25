#include "main.h"
#include "washing_machine.h"
HWND hMainWnd;
extern HWND GetBootplayWnd(void);
int flag;
int dwdata;
int pagenum;

int getdwdata(void)
{
	int dwdata = -1;
	return dwdata;
}
int getpagenum(void){
	int pagenum = 0;
	return pagenum;
}
static int MainWindowProc(HWND hWnd, int nMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (nMessage){
	case MSG_KEYUP:{
		printf("wParam=[%d]\n", wParam);
		switch (wParam){
			printf("wParam=[%d]\n", wParam);
			case KEY_MENU:
			//开机动画
			flag = BOOTPLAY_START;
			BootplayWnd(hWnd, flag);
			dwdata = getdwdata();
			pagenum = getpagenum();
			//dwdata = -1;
			break;
			case KEY_ENTER:
			//关机动画
			flag = BOOTPLAY_CLOSE;
			BootplayWnd(hWnd, flag);
			dwdata = -1;
			break;
		}
		return 0;
	}
#if 0
	case MSG_LBUTTONUP:{
		flag = BOOTPLAY_START;
		BootplayWnd(hWnd, flag);
		dwdata = 1;
		return 0;
	}
#endif
	case MSG_PLAYER_COMPLETE:{
		SendMessage(GetBootplayWnd(), MSG_CLOSE, NULL, NULL);
		if(flag == BOOTPLAY_START){
			washing_machine(hWnd, pagenum, dwdata);
		}else if(flag = BOOTPLAY_CLOSE){

		}
		return 0;
	}
	case MSG_BOOTPLAY_CLOSE:{
		flag = BOOTPLAY_CLOSE;
		SendMessage(GetmainWND(), MSG_CLOSE, NULL, NULL);
		BootplayWnd(hWnd, flag);
		return 0;
	}
	case MSG_DESTROY:
		DestroyAllControls(hWnd);
		return 0;
	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(0);
                return 0;
	}
	return DefaultMainWinProc(hWnd, nMessage, wParam, lParam);
}

HWND GetMainWnd(void)
{
	return hMainWnd; 
}

int MiniGUIMain(int argc, const char* argv[])
{
	MSG Msg;
        MAINWINCREATE CreateInfo;
        ncsInitialize();
        ncs4TouchInitialize();

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
        CreateInfo.hHosting = HWND_DESKTOP;
	
	hMainWnd = CreateMainWindow(&CreateInfo);
        if (hMainWnd == HWND_INVALID)
                return -1;
        ShowWindow(hMainWnd, SW_SHOWNORMAL);

        while (GetMessage(&Msg, hMainWnd)) {
                DispatchMessage(&Msg);
        }

        MainWindowThreadCleanup(hMainWnd);
        ncs4TouchUninitialize();
        ncsUninitialize();

	return 0;
}
#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
