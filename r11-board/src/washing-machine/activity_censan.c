#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "resource.h"
#include "headbar_view.h"
#include "bottombar_view.h"
#include "rotate_add_view.h"
#include "washing_res_cn.h"
#include "WifiWindow.h"
static HeadBarView *headBarData = NULL;
static BITMAP bmp_bottom_fun;

static DoubleTextView* DoubleTextDataInit(DoubleTextView *doubleTextData,
		int num) {
	doubleTextData = (DoubleTextView*) malloc(sizeof(DoubleTextView));
	if (NULL == doubleTextData) {
		sm_error("malloc DoubleTextView data error\n");
		return NULL;
	}
	memset((void *) doubleTextData, 0, sizeof(DoubleTextView));

	doubleTextData->bmpBg = bmp_bottom_fun;
	doubleTextData->currentPage = PAGE_ONE;
	doubleTextData->slideDistance = 0;
	doubleTextData->logfontUnit = getLogFont(ID_FONT_SIMSUN_25);
	doubleTextData->logfontDes = getLogFont(ID_FONT_SIMSUN_30);

	switch (num) {
	case 1:
		doubleTextData->valueUnitDes[0] = "8";
		doubleTextData->valueUnitDes[1] = FEN;
		doubleTextData->valueUnitDes[2] = XIDI;
		doubleTextData->valueUnitDes[3] = DI;
		doubleTextData->valueUnitDes[4] = NULL;
		doubleTextData->valueUnitDes[5] = SHUIWEI;

		doubleTextData->enableClick[0] = ENABLE_CLICK_YES;
		doubleTextData->enableClick[1] = ENABLE_CLICK_YES;
		break;
	case 2:
		doubleTextData->valueUnitDes[0] = "1";
		doubleTextData->valueUnitDes[1] = CI;
		doubleTextData->valueUnitDes[2] = PIAOXI;
		doubleTextData->valueUnitDes[3] = "20";
		doubleTextData->valueUnitDes[4] = DU;
		doubleTextData->valueUnitDes[5] = WENDU;

		doubleTextData->enableClick[0] = ENABLE_CLICK_YES;
		doubleTextData->enableClick[1] = ENABLE_CLICK_YES;
		break;
	case 3:
		doubleTextData->valueUnitDes[0] = "8";
		doubleTextData->valueUnitDes[1] = FEN;
		doubleTextData->valueUnitDes[2] = TUOSHUI;
		doubleTextData->valueUnitDes[3] = MIANTUOSHUI;
		doubleTextData->valueUnitDes[4] = ZHUAN;
		doubleTextData->valueUnitDes[5] = ZHUANSU;

		doubleTextData->enableClick[0] = ENABLE_CLICK_YES;
		doubleTextData->enableClick[1] = ENABLE_CLICK_YES;
		break;
	}
	return doubleTextData;
}

static SlideTextView* SlideTextDataInit(SlideTextView *slideTextData, int num) {
	slideTextData = (SlideTextView*) malloc(sizeof(SlideTextView));
	if (NULL == slideTextData) {
		sm_error("malloc SlideNumberView data error\n");
		return NULL;
	}
	memset((void *) slideTextData, 0, sizeof(SlideTextView));

	slideTextData->bmpBg = bmp_bottom_fun;
	slideTextData->selectIndex1 = 0;
	slideTextData->selectIndex2 = 0;
	slideTextData->currentPage = PAGE_ONE;
	slideTextData->logfontSelect = getLogFont(ID_FONT_SIMSUN_55);

	switch (num) {
	case 1:
		slideTextData->listData1[0] = "8";
		slideTextData->listData1[1] = "11";
		slideTextData->listData1[2] = "14";
		slideTextData->listData1[3] = "19";
		slideTextData->listData1[4] = "24";

		slideTextData->listData2[0] = DI;
		slideTextData->listData2[1] = ZHONG;
		slideTextData->listData2[2] = GAO;

		slideTextData->listSize1 = 5;
		slideTextData->listSize2 = 3;
		break;
	case 2:
		slideTextData->listData1[0] = "1";
		slideTextData->listData1[1] = "2";
		slideTextData->listData1[2] = ZIDONG;

		slideTextData->listData2[0] = "20";
		slideTextData->listData2[1] = "30";
		slideTextData->listData2[2] = "40";
		slideTextData->listData2[3] = "60";

		slideTextData->listSize1 = 3;
		slideTextData->listSize2 = 4;
		break;
	case 3:
		slideTextData->listData1[0] = "8";
		slideTextData->listData1[1] = "9";
		slideTextData->listData1[2] = "10";
		slideTextData->listData1[3] = "11";
		slideTextData->listData1[4] = "12";

		slideTextData->listData2[0] = MIANTUOSHUI;
		slideTextData->listData2[1] = "400";
		slideTextData->listData2[2] = "600";
		slideTextData->listData2[3] = "800";

		slideTextData->listSize1 = 5;
		slideTextData->listSize2 = 4;
		break;
	}

	return slideTextData;
}

static ButtonView* ButtonDataInit(ButtonView *buttonData, int num) {
	buttonData = (ButtonView*) malloc(sizeof(ButtonView));
	if (NULL == buttonData) {
		sm_error("malloc ButtonView data error\n");
	}
	memset((void *) buttonData, 0, sizeof(ButtonView));

	switch (num) {
	case 1:
		setCurrentIconValue(ID_FUN_WIN_BTN2, 0);
		getResBmp(ID_FUN_WIN_BTN2, BMPTYPE_BASE, &buttonData->bmpNormal);
		setCurrentIconValue(ID_FUN_WIN_BTN2, 1);
		getResBmp(ID_FUN_WIN_BTN2, BMPTYPE_BASE, &buttonData->bmpSelect);
		buttonData->selectStatus = SELECT_STATUS_NO;
		buttonData->switchMode = SWITCH_MODE_STATIC;
		break;
	case 2:
		setCurrentIconValue(ID_FUN_WIN_BTN3, 0);
		getResBmp(ID_FUN_WIN_BTN3, BMPTYPE_BASE, &buttonData->bmpNormal);
		setCurrentIconValue(ID_FUN_WIN_BTN3, 1);
		getResBmp(ID_FUN_WIN_BTN3, BMPTYPE_BASE, &buttonData->bmpSelect);
		buttonData->textSelect = JIESHU;
		buttonData->selectStatus = SELECT_STATUS_NO;
		buttonData->switchMode = SWITCH_MODE_STATIC;
		buttonData->textX = 30;
		buttonData->textY = 25;
		break;
	}
	return buttonData;
}

static BottomBarView* BottomBarDataInit(BottomBarView *bottomBarData) {
	bottomBarData = (BottomBarView*) malloc(sizeof(BottomBarView));
	if (NULL == bottomBarData) {
		sm_error("malloc BottomBarView data error\n");
	}
	memset((void *) bottomBarData, 0, sizeof(BottomBarView));

	bottomBarData->doubleTextData1 = DoubleTextDataInit(
			bottomBarData->doubleTextData1, 1);
	bottomBarData->doubleTextData2 = DoubleTextDataInit(
			bottomBarData->doubleTextData2, 2);
	bottomBarData->doubleTextData3 = DoubleTextDataInit(
			bottomBarData->doubleTextData3, 3);
	bottomBarData->slideTextData1 = SlideTextDataInit(
			bottomBarData->slideTextData1, 1);
	bottomBarData->slideTextData2 = SlideTextDataInit(
			bottomBarData->slideTextData2, 2);
	bottomBarData->slideTextData3 = SlideTextDataInit(
			bottomBarData->slideTextData3, 3);
	bottomBarData->nextButton = ButtonDataInit(bottomBarData->nextButton, 1);
	bottomBarData->beginButton = ButtonDataInit(bottomBarData->beginButton, 2);
	return bottomBarData;
}

static RotateAddView* RotateAddDataInit(RotateAddView *rotateAddData) {
	rotateAddData = (RotateAddView*) malloc(sizeof(RotateAddView));
	if (NULL == rotateAddData) {
		sm_error("malloc RotateAddView data error\n");
	}
	memset((void *) rotateAddData, 0, sizeof(RotateAddView));

	setCurrentIconValue(ID_FUN_WIN_BTN4, 0);
	getResBmp(ID_FUN_WIN_BTN4, BMPTYPE_BASE, &rotateAddData->bmpBgMin);
	setCurrentIconValue(ID_FUN_WIN_BTN4, 1);
	getResBmp(ID_FUN_WIN_BTN4, BMPTYPE_BASE, &rotateAddData->bmpBgBig);
	setCurrentIconValue(ID_FUN_WIN_ANIM, 0);
	getResBmp(ID_FUN_WIN_ANIM, BMPTYPE_BASE, &rotateAddData->bmpAnim[0]);
	setCurrentIconValue(ID_FUN_WIN_ANIM, 1);
	getResBmp(ID_FUN_WIN_ANIM, BMPTYPE_BASE, &rotateAddData->bmpAnim[1]);
	return rotateAddData;
}

static void my_notif_proc(HWND hwnd, int id, int nc, DWORD add_data) {
	if (nc == STN_CLICKED) {
		features_menu(hwnd, 5);
	}
}

#define __ID_TIMER_SLIDER 100
static int ActivityCenSanProc(HWND hWnd, int message, WPARAM wParam,
		LPARAM lParam) {

	static BottomBarView *bottomBarData = NULL;
	static RotateAddView *rotateAddData = NULL;
	static PLOGFONT logfontStart;
	static PLOGFONT logfontDes;
	static PLOGFONT logfontTime;
	static BITMAP bmpBg;

	switch (message) {
	case MSG_TIMER: {
		KillTimer(hWnd, __ID_TIMER_SLIDER);
		HWND bottomBar = BottomBarViewInit(hWnd, bottomBarData);
		headbarbtnwifi[5] = HeadBarViewInit(hWnd, bottomBar, headBarData);

		SendMessage(headbarbtnwifi[5], MSG_UPDATETIME, NULL, NULL);
		HWND rotateHwnd = CreateWindowEx(ROTATE_ADD_VIEW, GONNENG,
		WS_CHILD | WS_VISIBLE | SS_NOTIFY, WS_EX_TRANSPARENT, 0, 545, 150, 248,
				122, hWnd, (DWORD) rotateAddData);
		SetWindowFont(rotateHwnd, getLogFont(ID_FONT_SIMSUN_50));
		SetNotificationCallback(rotateHwnd, my_notif_proc);
		break;
	}
	case MSG_CREATE: {
		setCurrentIconValue(ID_FUN_SCREEN_BG1, 5);
		getResBmp(ID_FUN_SCREEN_BG1, BMPTYPE_BASE, &bmpBg);
		setCurrentIconValue(ID_FUN_WIN_BTN1, 0);
		getResBmp(ID_FUN_WIN_BTN1, BMPTYPE_BASE, &bmp_bottom_fun);

		bottomBarData = BottomBarDataInit(bottomBarData);
		rotateAddData = RotateAddDataInit(rotateAddData);

		logfontStart = getLogFont(ID_FONT_SIMSUN_50);
		logfontDes = getLogFont(ID_FONT_SIMSUN_25);
		logfontTime = getLogFont(ID_FONT_SIMSUN_120);

		SetTimer(hWnd, __ID_TIMER_SLIDER, 1);
		return 0;
	}
	case MSG_PAINT: {
		HDC hdc = BeginPaint(hWnd);
		SetBkMode(hdc, BM_TRANSPARENT);
		SetTextColor(hdc, COLOR_lightwhite);
		SelectFont(hdc, logfontStart);
		TextOut(hdc, 10, 150, CENSAN);

		SelectFont(hdc, logfontDes);
		RECT rcClient;
		rcClient.left = 10;
		rcClient.top = 240;
		rcClient.right = 400;
		rcClient.bottom = 400;
		DrawText(hdc, CHENSHAN_N, -1, &rcClient,
				DT_NOCLIP | DT_LEFT | DT_WORDBREAK);

		SelectFont(hdc, logfontTime);
		TextOut(hdc, 250, 140, "2:45");
		EndPaint(hWnd, hdc);
		return 0;
	}
	case MSG_ERASEBKGND: {
		HDC hdc = (HDC) wParam;
		const RECT* clip = (const RECT*) lParam;
		BOOL fGetDC = FALSE;
		RECT rcTemp;
		if (hdc == 0) {
			hdc = GetClientDC(hWnd);
			fGetDC = TRUE;
		}
		if (clip) {
			rcTemp = *clip;
			ScreenToClient(hWnd, &rcTemp.left, &rcTemp.top);
			ScreenToClient(hWnd, &rcTemp.right, &rcTemp.bottom);
			IncludeClipRect(hdc, &rcTemp);
		}
		FillBoxWithBitmap(hdc, 0, 0, 0, 0, &bmpBg);
		if (fGetDC)
			ReleaseDC(hdc);
		return 0;
	}
	case MSG_HOME_SETUP:
		if (strcmp((char*) lParam, WIN_DES_MAIN) != 0
				&& GetBottomBarDistance() >= 100) {
			//unloadBitMap(&bmpBg);
			WinPopMenuWin(hWnd);
		}
		break;
	case MSG_WIN_POP_CLOSE:
		setCurrentIconValue(ID_FUN_SCREEN_BG1, 5);
		//getResBmp(ID_FUN_SCREEN_BG1, BMPTYPE_BASE, &bmpBg);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case MSG_LBUTTONDOWN: {
		if (LOWORD(lParam) < 416 && IsWindowVisible(GetPopMenuHwnd())
				&& IsWindowEnabled(GetPopMenuHwnd())) {
			return 0;
		}
		if (LOWORD(lParam) < 516 && IsWindowVisible(GetfetureMenuHwnd())
				&& IsWindowEnabled(GetfetureMenuHwnd())) {
			return 0;
		}
		break;
	}
	case MSG_LBUTTONUP: {
		if (LOWORD(lParam) < 416 && IsWindowVisible(GetPopMenuHwnd())
				&& IsWindowEnabled(GetPopMenuHwnd())) {
			if(WIFIWIN_OPEN == TRUE){
                                WIFIWIN_OPEN = FALSE;
                        }else{
				headBarData->winDes = WIN_DES_CENSAN;
                                PostMessage(GetPopMenuHwnd(), MSG_CLOSE, 0, 0);
                        }
			//PostMessage(GetPopMenuHwnd(), MSG_CLOSE, 0, 0);
			return 0;
		}
		if (LOWORD(lParam) < 516 && IsWindowVisible(GetfetureMenuHwnd())
				&& IsWindowEnabled(GetfetureMenuHwnd())) {
			PostMessage(GetfetureMenuHwnd(), MSG_CLOSE, 0, 0);
			return 0;
		}
		break;
	}
	case MSG_SLIDE_TEXT_CHANGE: {
		int id = (int) wParam;
		if (id == ID_SLIDE_TEXT_VIEW_ONE) {
			printf("selece text %s\n", (char *) lParam);
		} else if (id == ID_SLIDE_TEXT_VIEW_TOW) {
			printf("selece text %s\n", (char *) lParam);
		} else if (id == ID_SLIDE_TEXT_VIEW_THR) {
			printf("selece text %s\n", (char *) lParam);
		}
		break;
	}
	case MSG_DESTROY:
		unloadBitMap(&bmpBg);
		unloadBitMap(&bmp_bottom_fun);
		unloadBitMap(&bottomBarData->nextButton->bmpNormal);
		unloadBitMap(&bottomBarData->nextButton->bmpSelect);
		unloadBitMap(&bottomBarData->beginButton->bmpNormal);
		unloadBitMap(&bottomBarData->beginButton->bmpSelect);
		unloadBitMap(&rotateAddData->bmpBgMin);
		unloadBitMap(&rotateAddData->bmpBgBig);
		unloadBitMap(&rotateAddData->bmpAnim[0]);
		unloadBitMap(&rotateAddData->bmpAnim[1]);
		if (bottomBarData){
		if (bottomBarData->doubleTextData1)
			free(bottomBarData->doubleTextData1);
		if (bottomBarData->doubleTextData2)
			free(bottomBarData->doubleTextData2);
		if (bottomBarData->doubleTextData3)
			free(bottomBarData->doubleTextData3);
		if (bottomBarData->slideTextData1)
			free(bottomBarData->slideTextData1);
		if (bottomBarData->slideTextData2)
			free(bottomBarData->slideTextData2);
		if (bottomBarData->slideTextData3)
			free(bottomBarData->slideTextData3);
		if (bottomBarData->nextButton)
			free(bottomBarData->nextButton);
		if (bottomBarData->beginButton)
			free(bottomBarData->beginButton);
			free(bottomBarData);
		}
		if (rotateAddData)
			free(rotateAddData);
		DestroyAllControls(hWnd);
		return 0;
	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		break;
	}

	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int ActivityCenSan(HWND hosting, HeadBarView *myHeadBarData) {
	MSG Msg;
	HWND hMainWnd;
	MAINWINCREATE CreateInfo;

	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = "";
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = GetSystemCursor(0);
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = ActivityCenSanProc;
	CreateInfo.lx = 0;
	CreateInfo.ty = 0;
	CreateInfo.rx = g_rcScr.right;
	CreateInfo.by = g_rcScr.bottom;
	CreateInfo.iBkColor = PIXEL_lightgray;
	CreateInfo.dwAddData = 0;
	CreateInfo.hHosting = hosting;

	headBarData = myHeadBarData;

	hMainWnd = CreateMainWindow(&CreateInfo);

	if (hMainWnd == HWND_INVALID)
		return -1;

	ShowWindow(hMainWnd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hMainWnd);
	return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
