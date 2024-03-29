/*
 ** washing-machine.c 2017-09-09 14:00:18
 **
 ** washing-machine: Washing machine control UI
 **
 **
 ** Copyright (C) 2017 ~ 2020 Allwinnertech.
 **
 ** License: GPL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ioctl.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "washing_machine.h"
#include "win_pop_menu.h"
#include "many_win_view.h"
#include "washing_res_cn.h"
#include "resource.h"
#include "WifiWindow.h"

#include "light_menu.h"
#include "headbar_view.h"
#include "wifiactivity.h"
#include "volume.h"
#include "include.h"

#define MACHINE_TITLE "Washing machine"

extern int ActivityZNXYZJ(HWND hosting, HeadBarView *headBarData);
extern int ActivityMianMa(HWND hosting, HeadBarView *headBarData);
extern int ActivityHunHeXi(HWND hosting, HeadBarView *headBarData);
extern int ActivityKuaiXi(HWND hosting, HeadBarView *headBarData);
extern int ActivityDaJian(HWND hosting, HeadBarView *headBarData);
extern int ActivityCenSan(HWND hosting, HeadBarView *headBarData);
extern int ActivityHouXinMei(HWND hosting, HeadBarView *headBarData);
extern int ActivityYanMao(HWND hosting, HeadBarView *headBarData);
extern int ActivityTonZhuan(HWND hosting, HeadBarView *headBarData);
extern int ActivityNeiYi(HWND hosting, HeadBarView *headBarData);
extern int ActivityYuRonFu(HWND hosting, HeadBarView *headBarData);
extern int ActivityJieNen(HWND hosting, HeadBarView *headBarData);
extern int ActivityPiaoXiTouShui(HWND hosting, HeadBarView *headBarData);
extern int ActivityDanTuoShui(HWND hosting, HeadBarView *headBarData);
extern int ActivityDanHonGan(HWND hosting, HeadBarView *headBarData);
extern int ActivityXiHong(HWND hosting, HeadBarView *headBarData);
extern int ActivityKongQiXi(HWND hosting, HeadBarView *headBarData);
extern int ActivityJianZiJie(HWND hosting, HeadBarView *headBarData);

extern int ActivityVideo(HWND hosting, HeadBarView *myHeadBarData);
extern int ActivitySensor(HWND hosting, HeadBarView *myHeadBarData);

void pthread_wifi_off(void);

//extern const aw_wifi_interface_t * wifi_interface;
WinDataType *mwd;

WinDataType *g_win_data = NULL;
ManyWinView *manyWinData1 = NULL;
ManyWinView *manyWinData2 = NULL;
ManyWinView *manyWinData3 = NULL;
HeadBarView *headBarData = NULL;

static ButtonView* HeadButtonDataInit(ButtonView *buttonData, int num) {
	int err_code;

	buttonData = (ButtonView*) malloc(sizeof(ButtonView));
	if (NULL == buttonData) {
		sm_error("malloc ButtonView data error\n");
	}
	memset((void *) buttonData, 0, sizeof(ButtonView));

	buttonData->selectStatus = SELECT_STATUS_NO;
	buttonData->switchMode = SWITCH_MODE_NORMAL;

	switch (num) {
	case 1:
		setCurrentIconValue(ID_FAST_WIN_FAVOR, 0);
		getResBmp(ID_FAST_WIN_FAVOR, BMPTYPE_BASE, &buttonData->bmpNormal);
		setCurrentIconValue(ID_FAST_WIN_FAVOR, 1);
		getResBmp(ID_FAST_WIN_FAVOR, BMPTYPE_BASE, &buttonData->bmpSelect);
		break;
	case 2:
		setCurrentIconValue(ID_FAST_WIN_HOME, 0);
		getResBmp(ID_FAST_WIN_HOME, BMPTYPE_BASE, &buttonData->bmpNormal);
		setCurrentIconValue(ID_FAST_WIN_HOME, 1);
		getResBmp(ID_FAST_WIN_HOME, BMPTYPE_BASE, &buttonData->bmpSelect);
		break;
	case 3:
		setCurrentIconValue(ID_FAST_WIN_SETUP, 0);
		getResBmp(ID_FAST_WIN_SETUP, BMPTYPE_BASE, &buttonData->bmpNormal);
		setCurrentIconValue(ID_FAST_WIN_SETUP, 1);
		getResBmp(ID_FAST_WIN_SETUP, BMPTYPE_BASE, &buttonData->bmpSelect);
		break;
	case 4:
		err_code = LoadBitmapFromFile(HDC_SCREEN, &buttonData->bmpNormal, "/usr/res/other/video.png");
		if (err_code != ERR_BMP_OK) {
			app_error("load bitmap failed\n");
		}
		err_code = LoadBitmapFromFile(HDC_SCREEN, &buttonData->bmpSelect, "/usr/res/other/video.png");
		if (err_code != ERR_BMP_OK) {
			app_error("load bitmap failed\n");
		}
		break;
	case 5:
		err_code = LoadBitmapFromFile(HDC_SCREEN, &buttonData->bmpNormal, "/usr/res/other/sensor.png");
		if (err_code != ERR_BMP_OK) {
			app_error("load bitmap failed\n");
		}
		err_code = LoadBitmapFromFile(HDC_SCREEN, &buttonData->bmpSelect, "/usr/res/other/sensor.png");
		if (err_code != ERR_BMP_OK) {
			app_error("load bitmap failed\n");
		}
		break;
	}
	return buttonData;
}

static HeadBarView* HeadBarDataInit(HeadBarView *headBarData) {
	headBarData = (HeadBarView*) malloc(sizeof(HeadBarView));
	if (NULL == headBarData) {
		sm_error("malloc HeadBarView data error\n");
	}
	memset((void *) headBarData, 0, sizeof(HeadBarView));

	headBarData->favorData = HeadButtonDataInit(headBarData->favorData, 1);
	headBarData->homeData = HeadButtonDataInit(headBarData->homeData, 2);
	headBarData->setupData = HeadButtonDataInit(headBarData->setupData, 3);
	headBarData->videoData = HeadButtonDataInit(headBarData->videoData, 4);
	headBarData->sensorData = HeadButtonDataInit(headBarData->sensorData, 5);
	LoadBitmapFromFile(HDC_SCREEN, &headBarData->no_bmpWifi, "/usr/res/menu/no_wifi.png");
	LoadBitmapFromFile(HDC_SCREEN, &headBarData->bmpWifi, "/usr/res/menu/wifi.png");
	LoadBitmapFromFile(HDC_SCREEN, &headBarData->time_wait, "/usr/res/menu/time_wait.png");
	LoadBitmapFromFile(HDC_SCREEN, &headBarData->mediafile, "/usr/res/other/mediafile.png");
	getResBmp(ID_FAST_WIN_BG, BMPTYPE_BASE, &headBarData->bmpBg);

	headBarData->winDes = WIN_DES_MAIN;

	return headBarData;
}

static ManyWinView* ManyWinDataInit(ManyWinView *manyWinData, int num) {
	manyWinData = (ManyWinView*) malloc(sizeof(ManyWinView));
	if (NULL == manyWinData) {
		sm_error("malloc slideWinData data error\n");
	}
	memset((void *) manyWinData, 0, sizeof(ManyWinView));

	int i;
	switch (num) {
	case 1:
		for (i = 0; i < 6; i++) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 0);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData->bmpFun[i]);
		}
		manyWinData->nameFun[0] = ZNXIZJ;
		manyWinData->nameFun[1] = MIANMA;
		manyWinData->nameFun[2] = HUNHEXI;
		manyWinData->nameFun[3] = KUAIXI15;
		manyWinData->nameFun[4] = DAJIAN;
		manyWinData->nameFun[5] = CENSAN;
		break;
	case 2:
		for (i = 0; i < 6; i++) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 1);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData->bmpFun[i]);
		}
		manyWinData->nameFun[0] = HOUXINMEI;
		manyWinData->nameFun[1] = YANMAO;
		manyWinData->nameFun[2] = TONZHUAN;
		manyWinData->nameFun[3] = NEIYI;
		manyWinData->nameFun[4] = YURONFU;
		manyWinData->nameFun[5] = JIENEN;
		break;
	case 3:
		for (i = 0; i < 6; i++) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 2);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData->bmpFun[i]);
		}
		manyWinData->nameFun[0] = PIAOXITUOSHUI;
		manyWinData->nameFun[1] = DANTUOSHUI;
		manyWinData->nameFun[2] = DANHONGAN;
		manyWinData->nameFun[3] = XIHONG60;
		manyWinData->nameFun[4] = KONGQIXI;
		manyWinData->nameFun[5] = JIANZIJIE;
		break;
	}
	return manyWinData;
}

void loadManyViewBitMap() {
	int i;
	getResBmp(ID_SCREEN_BG, BMPTYPE_BASE, &g_win_data->s_Main_bg);
	for (i = 0; i < 6; i++) {
		if (!manyWinData1->bmpFun[i].bmBits) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 0);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData1->bmpFun[i]);
		}
		if (!manyWinData2->bmpFun[i].bmBits) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 1);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData2->bmpFun[i]);
		}
		if (!manyWinData3->bmpFun[i].bmBits) {
			setCurrentIconValue(ID_ACT_SUB1_WIN_ITEM0 + i, 2);
			getResBmp(ID_ACT_SUB1_WIN_ITEM0 + i, BMPTYPE_BASE,
					&manyWinData3->bmpFun[i]);
		}
	}
}

void unloadManyViewBitMap() {
	int i;
	unloadBitMap(&g_win_data->s_Main_bg);
	for (i = 0; i < 6; i++) {
		unloadBitMap(&manyWinData1->bmpFun[i]);
		unloadBitMap(&manyWinData2->bmpFun[i]);
		unloadBitMap(&manyWinData3->bmpFun[i]);
	}
}

#define __ID_TIMER_SLIDER 100
static int WashingWindowProc(HWND hWnd, int nMessage, WPARAM wParam, LPARAM lParam) {
//	WinDataType *mwd;
	mwd = (WinDataType*) GetWindowAdditionalData(hWnd);
	static BITMAP bmp_point_n;
	static BITMAP bmp_point_p;
	static BOOL isOpenOtherActivity = FALSE;
	switch (nMessage) {
	case MSG_CREATE: {
		getResBmp(ID_SCREEN_BG, BMPTYPE_BASE, &g_win_data->s_Main_bg);

		headBarData = HeadBarDataInit(headBarData);
		manyWinData1 = ManyWinDataInit(manyWinData1, 1);
		manyWinData2 = ManyWinDataInit(manyWinData2, 2);
		manyWinData3 = ManyWinDataInit(manyWinData3, 3);

		setCurrentIconValue(ID_BM_STAT_WIN_PAGE_INDEX, 0);
		getResBmp(ID_BM_STAT_WIN_PAGE_INDEX, BMPTYPE_BASE, &bmp_point_p);
		setCurrentIconValue(ID_BM_STAT_WIN_PAGE_INDEX, 1);
		getResBmp(ID_BM_STAT_WIN_PAGE_INDEX, BMPTYPE_BASE, &bmp_point_n);

		SetTimer(hWnd, __ID_TIMER_SLIDER, 1);
		break;
	}
	case MSG_TIMER: {
		KillTimer(hWnd, __ID_TIMER_SLIDER);
		bool_connect = 1;
		mwd->fastMenuHwnd = HeadBarViewInit(hWnd, 0, headBarData);
		ManyWinViewInit(hWnd, manyWinData1, manyWinData2, manyWinData3,
				bmp_point_n, bmp_point_p);
		SendMessage(mwd->fastMenuHwnd, MSG_UPDATETIME, NULL, NULL);
		if(mwd->getActivityID != -1 && mwd->getWhichPage >= 1 && mwd->getWhichPage <= 3){
			PostMessage(hWnd, MSG_MANY_WIN_CLICK, mwd->getWhichPage, mwd->getActivityID);
		}
		break;
	}
	case MSG_KEYUP:{
		switch (wParam){
			case KEY_ENTER:
				PostMessage(GetMainWnd(), MSG_BOOTPLAY_CLOSE, NULL, NULL);
				SendMessage(hWnd, MSG_CLOSE, NULL, NULL);
				break;
		}
		return 0;
	}
	case MSG_ERASEBKGND: {
		HDC hdc;
		hdc = (HDC) wParam;
		const RECT* clip = (const RECT*) lParam;
		BOOL fGetDC = FALSE;
		RECT rcTemp;

		if (hdc == 0) {
			hdc = GetSecondaryClientDC(hWnd);
			fGetDC = TRUE;
		}

		if (clip) {
			rcTemp = *clip;
			ScreenToClient(hWnd, &rcTemp.left, &rcTemp.top);
			ScreenToClient(hWnd, &rcTemp.right, &rcTemp.bottom);
			IncludeClipRect(hdc, &rcTemp);
		}

		FillBoxWithBitmap(hdc, 0, 0, 0, 0, &g_win_data->s_Main_bg);
		if (fGetDC) {
			ReleaseSecondaryDC(hWnd, hdc);
		}
		return 0;
	}
	case MSG_HOME_CLICK: {
		isOpenOtherActivity = FALSE;
		app_debug("Des=%s\n", (char*) lParam);
		if (strcmp((char*) lParam, WIN_DES_MAIN) == 0) {
			OnePageSwitch();
		} else {
			//reload picture
			//loadManyViewBitMap();
			ManyWinAppear();
			wifi_icon_change = TRUE;
			//InvalidateRect(mwd->fastMenuHwnd, NULL, TRUE);
			ShowWindow(mwd->fastMenuHwnd, SW_SHOWNORMAL);
			if(!IsWindowVisible(mwd->ParentHwnd)){
				ShowWindow(mwd->ParentHwnd, SW_SHOWNORMAL);
			}
			InvalidateRect(mwd->fastMenuHwnd, NULL, TRUE);
		}
		break;
	}
	case MSG_HOME_SETUP:
		if (!GetSlideStatus() && strcmp((char*) lParam, WIN_DES_MAIN) == 0) {
			//free the memory
			//unloadManyViewBitMap();
			WinPopMenuWin(hWnd);
		}
		break;
	case MSG_HOME_VIDEO:
		if (!isOpenOtherActivity)
		{
			isOpenOtherActivity = TRUE;
			//free the memory
			//unloadManyViewBitMap();
			ShowWindow(mwd->fastMenuHwnd, SW_HIDE);

			headBarData->winDes = WIN_DES_VIDEO;
			ActivityVideo(GetParent(hWnd), headBarData);
		}
		break;

	case MSG_HOME_SENSOR:
		if (!isOpenOtherActivity)
		{
			isOpenOtherActivity = TRUE;
			//free the memory
			//unloadManyViewBitMap();
			ShowWindow(mwd->fastMenuHwnd, SW_HIDE);

			headBarData->winDes = WIN_DES_SENSOR;
			ActivitySensor(GetParent(hWnd), headBarData);
		}
		break;
	case MSG_WIN_POP_CLOSE:
		//reload picture
		//loadManyViewBitMap();
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case MSG_LBUTTONDOWN: {

		{
			printf("washing newX=%d, newY=%d\n", LOWORD(lParam), HIWORD(lParam));
		}

		if (LOWORD(lParam) < 416 && IsWindowVisible(GetPopMenuHwnd())
				&& IsWindowEnabled(GetPopMenuHwnd())) {
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
				PostMessage(GetPopMenuHwnd(), MSG_CLOSE, 0, 0);
			}
			return 0;
		}
		break;
	}
#ifdef ALLWINNERTECH_R6
		case MSG_MOUSE_FLING:
		PostMessage(GetFunHwnd(), MSG_MOUSE_FLING, wParam, lParam);
		break;
		case MSG_MOUSE_SCROLL:
		PostMessage(GetFunHwnd(), MSG_MOUSE_SCROLL, wParam, lParam);
		break;
#endif
	case MSG_MANY_WIN_CLICK: {
		printf("____MSG_MANY_WIN_CLICK:\n");
		if (!isOpenOtherActivity) {
			printf("!isOpenOtherActivity\n");
			isOpenOtherActivity = TRUE;
			//free the memory
			//unloadManyViewBitMap();
			ShowWindow(mwd->fastMenuHwnd, SW_HIDE);
			//ShowWindow(mwd->ParentHwnd, SW_HIDE);
			int ctrlID = (int) lParam;
			printf("currentPage = %d id = %d\n", (int) wParam, ctrlID);
			switch ((int) wParam) {
			case 1:
				switch (ctrlID) {
				case 0:
					headBarData->winDes = WIN_DES_ZNXYZJ;
					ActivityZNXYZJ(GetParent(hWnd), headBarData);
					break;
				case 1:
					headBarData->winDes = WIN_DES_MIANMA;
					ActivityMianMa(GetParent(hWnd), headBarData);
					break;
				case 2:
					headBarData->winDes = WIN_DES_HUNHEXI;
					ActivityHunHeXi(GetParent(hWnd), headBarData);
					break;
				case 3:
					headBarData->winDes = WIN_DES_KUAIXI;
					ActivityKuaiXi(GetParent(hWnd), headBarData);
					break;
				case 4:
					headBarData->winDes = WIN_DES_DAJIAN;
					ActivityDaJian(GetParent(hWnd), headBarData);
					break;
				case 5:
					headBarData->winDes = WIN_DES_CENSAN;
					ActivityCenSan(GetParent(hWnd), headBarData);
					break;
				}
				break;
			case 2:
				switch (ctrlID) {
				case 0:
					headBarData->winDes = WIN_DES_HOUXINMEI;
					ActivityHouXinMei(GetParent(hWnd), headBarData);
					break;
				case 1:
					headBarData->winDes = WIN_DES_YANMAO;
					ActivityYanMao(GetParent(hWnd), headBarData);
					break;
				case 2:
					headBarData->winDes = WIN_DES_TONZHUAN;
					ActivityTonZhuan(GetParent(hWnd), headBarData);
					break;
				case 3:
					headBarData->winDes = WIN_DES_NEIYI;
					ActivityNeiYi(GetParent(hWnd), headBarData);
					break;
				case 4:
					headBarData->winDes = WIN_DES_YURONFU;
					ActivityYuRonFu(GetParent(hWnd), headBarData);
					break;
				case 5:
					headBarData->winDes = WIN_DES_JIENEN;
					ActivityJieNen(GetParent(hWnd), headBarData);
					break;
				}
				break;
			case 3:
				switch (ctrlID) {
				case 0:
					headBarData->winDes = WIN_DES_PIAOXITUOSHUI;
					ActivityPiaoXiTouShui(GetParent(hWnd), headBarData);
					break;
				case 1:
					headBarData->winDes = WIN_DES_DANTUOSHUI;
					ActivityDanTuoShui(GetParent(hWnd), headBarData);
					break;
				case 2:
					headBarData->winDes = WIN_DES_DANHONGAN;
					ActivityDanHonGan(GetParent(hWnd), headBarData);
					break;
				case 3:
					headBarData->winDes = WIN_DES_XIHONG;
					ActivityXiHong(GetParent(hWnd), headBarData);
					break;
				case 4:
					headBarData->winDes = WIN_DES_KONGQIXI;
					ActivityKongQiXi(GetParent(hWnd), headBarData);
					break;
				case 5:
					headBarData->winDes = WIN_DES_JIANZIJIE;
					ActivityJianZiJie(GetParent(hWnd), headBarData);
					break;
				}
				break;
			}
		}
		break;
	}
	case MSG_DESTROY:
		unloadBitMap(&headBarData->favorData->bmpNormal);
		unloadBitMap(&headBarData->favorData->bmpSelect);
		unloadBitMap(&headBarData->homeData->bmpNormal);
		unloadBitMap(&headBarData->homeData->bmpSelect);
		unloadBitMap(&headBarData->setupData->bmpNormal);
		unloadBitMap(&headBarData->setupData->bmpSelect);
		unloadBitMap(&headBarData->bmpBg);
		unloadBitMap(&headBarData->bmpWifi);
		unloadBitMap(&headBarData->no_bmpWifi);
		unloadBitMap(&headBarData->time_wait);
		unloadBitMap(&headBarData->mediafile);
		int i = 0;
		unloadBitMap(&bmp_point_n);
		unloadBitMap(&bmp_point_p);
		unloadManyViewBitMap();
		if (headBarData->favorData)
			free(headBarData->favorData);
		if (headBarData->homeData)
			free(headBarData->homeData);
		if (headBarData->setupData)
			free(headBarData->setupData);
		if (headBarData)
			free(headBarData);
		if (manyWinData1)
			free(manyWinData1);
		if (manyWinData2)
			free(manyWinData2);
		if (manyWinData3)
			free(manyWinData3);
		if (g_win_data)
			free(g_win_data);
		TIMER_UPDATETIME_STATUS = STATUS_OFF;
		pthread_create(&pthread_wifioff, NULL, &pthread_wifi_off, NULL);
		DestroyAllControls(hWnd);
		return 0;
	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		MainWindowThreadCleanup(hWnd);
		return 0;
	}
	return DefaultMainWinProc(hWnd, nMessage, wParam, lParam);
}

void HardwareInit(void) {
	/*get hardware volume light value, please add 40 to the actual value*/
	g_win_data->volumelen = 80;
	g_win_data->lightlen = 40;
}
void pthread_wifion(void)
{
//        pthread_mutex_lock(&mutex);
        wifi_interface = wifi_on(wifi_interface);
        if(aw_wifi_get_wifi_state() == CONNECTED){
                wlan_disconnect(wifi_interface, event_label);
        }
//        pthread_mutex_unlock(&mutex);
        if(wifi_readonwnd != 0){
                ShowWindow(wifi_readonwnd, SW_HIDE);
        }
        EnableWindow(switch_button, TRUE);
        pthread_exit(NULL);
}
void pthread_wifi_off(void)
{
	wifi_off(wifi_interface);
        pthread_exit(NULL);
}
void pthreadResourceInit(void)
{
	pthread_cond_init(&mutex, NULL);
	pthread_cond_init(&mutex1, NULL);
	pthread_cond_init(&mutex2, NULL);
	pthread_cond_init(&mutex3, NULL);
	pthread_cond_init(&mutex4, NULL);
	pthread_cond_init(&cond, NULL);
        pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_cond_init(&cond3, NULL);
	pthread_cond_init(&cond4, NULL);
}

void FreepthreadResource(void)
{
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);
	pthread_mutex_destroy(&mutex3);
	pthread_mutex_destroy(&mutex4);
	pthread_cond_destroy(&cond);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_cond_destroy(&cond3);
	pthread_cond_destroy(&cond4);
}

void SystemInit(void) {
	/*HardwareInit();*/
	ResourceInit();
	pthread_create(&pthread_time, NULL, &update_time, NULL);
	pthread_create(&pthread_wifi_on, NULL, &pthread_wifion, NULL);
	first_wifion = TRUE;
}

void SystemUninit(void) {
	ResourceUninit();
	system("ubus call boot-play boot_complete '{\"stop\":true}'");
}

HWND GetmainWND (void)
{
	return g_win_data->ParentHwnd;
}

int washing_machine(HWND hosting, int pagenum, int dwdata)
{
	MSG Msg;
	MAINWINCREATE CreateInfo;

#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER , MACHINE_TITLE , 0 , 0);
#endif

	pthreadResourceInit();
	SystemInit();
	g_win_data = (WinDataType*) malloc(sizeof(WinDataType));
	if (NULL == g_win_data) {
		printf("malloc window data error\n");
		return -1;
	}
	memset((void *) g_win_data, 0, sizeof(WinDataType));
	HardwareInit();
	/*register window ctrl*/
	RegisterHeadBarView();
	RegisterButtonView();
	RegisterManyWinView();
	RegisterStaticView();
	RegisterBottomBarView();
	RegisterSlideTextView();
	RegisterDoubleTextView();
	RegisterRotateAddView();
	SetDefaultWindowElementRenderer("classic");
	CreateInfo.dwStyle = WS_NONE;
	CreateInfo.dwExStyle = WS_EX_AUTOSECONDARYDC;
	CreateInfo.spCaption = MACHINE_TITLE;
	CreateInfo.hMenu = 0;
	CreateInfo.hCursor = 0; /*GetSystemCursor (0);*/
	CreateInfo.hIcon = 0;
	CreateInfo.MainWindowProc = WashingWindowProc;
	CreateInfo.lx = 0;
	CreateInfo.ty = 0;
	CreateInfo.rx = g_rcScr.right;
	CreateInfo.by = g_rcScr.bottom;
	CreateInfo.iBkColor = PIXEL_lightwhite;
	CreateInfo.hHosting = hosting;
	CreateInfo.dwAddData = (DWORD) g_win_data;
	g_win_data->ParentHwnd = CreateMainWindow(&CreateInfo);
	g_win_data->getActivityID = dwdata;
	g_win_data->getWhichPage = pagenum;
	if (g_win_data->ParentHwnd == HWND_INVALID)
		return -1;
	if(g_win_data->getActivityID != -1 && g_win_data->getWhichPage >= 1 && g_win_data->getWhichPage <= 3){
		ShowWindow(g_win_data->ParentHwnd, SW_HIDE);
	}else{
		ShowWindow(g_win_data->ParentHwnd, SW_SHOWNORMAL);
	}
	while (GetMessage(&Msg, g_win_data->ParentHwnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	UnregisterButtonView();
	UnregisterHeadBarView();
	UnregisterManyWinView();
	UnregisterStaticView();
	UnregisterBottomBarView();
	UnregisterSlideTextView();
	UnregisterDoubleTextView();
	UnregisterRotateAddView();
	FreepthreadResource();
	SystemUninit();
	return 0;
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif
