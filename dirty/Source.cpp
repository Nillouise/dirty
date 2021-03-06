/*---------------------------------------
BITBLT.C -- BitBlt Demonstration
(c) Charles Petzold, 1998
---------------------------------------*/
//功能：
//0.1秒检测是否存在客户端（利用客户端大小检测），然后决定是否覆盖脚本。
//10分钟同步账号数据到ftp服务器里。

#include <windows.h>
#include<tchar.h>
#include<time.h>
#include<string>
#include<Strsafe.h>
#include<sstream>
using namespace std;
int picposx = 0;
int picposy = 601;
int picwidth = 1024;
int picheight = 123;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL LoadBitmapFromBMPFile(LPTSTR szFileName, HBITMAP *phBitmap,
	HPALETTE *phPalette);
void synchroFile(TCHAR* source, TCHAR* dest)
{
	TCHAR szDir[MAX_PATH];
	TCHAR totalPath[MAX_PATH];
	StringCchCopy(szDir, MAX_PATH, dest);
	StringCchCat(szDir, MAX_PATH, TEXT("*"));
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(szDir, &FindFileData);

	FindNextFile(hFind, &FindFileData);
	FindNextFile(hFind, &FindFileData);
	//跳过前两个文件. 和..

	StringCchCopy(totalPath, MAX_PATH, dest);
	StringCchCat(totalPath, MAX_PATH, FindFileData.cFileName);

	DeleteFile(totalPath); //删除文件夹内第一文件。

	const time_t t = time(NULL);
	string curTime;
	stringstream ss;

	/*本地时间：日期，时间 年月日，星期，时分秒*/
	struct tm* current_time = localtime(&t);
	curTime.c_str();
	ss << current_time->tm_hour << "." << current_time->tm_min << "." << current_time->tm_sec << " " << current_time->tm_mon << "-" << current_time->tm_mday;
	getline(ss, curTime);


	curTime = curTime + ".bmp";
	wstring wcurTime(curTime.begin(), curTime.end());
	wcurTime = dest + wcurTime;
	TCHAR *str = (wchar_t *)wcurTime.c_str();;
	CopyFile(source, str, TRUE);
	FindClose(hFind);
}
int intervalCheckDNF(DWORD interval)
{
	static DWORD lastLaunch = 0;
	if (GetTickCount() - lastLaunch > interval)
	{
		lastLaunch = GetTickCount();
		HWND hwnd = GetForegroundWindow();
		RECT rc;
		GetWindowRect(hwnd, &rc);

		if (rc.right - rc.left == 800 && rc.bottom - rc.top == 600)
		{
			return 1;
		}
		else {
			return 0;
		}

	}

	return 2;
}
int checkDNFRunning()
{
	return 1;

	HWND hwnd = GetForegroundWindow();
	RECT rc;
	GetWindowRect(hwnd, &rc);

	if (rc.right - rc.left == 800 && rc.bottom - rc.top == 600)
	{
		return 1;
	}
	else {
		return 0;
	}
}

int intervalSynchroFile(DWORD interval)
{
	static DWORD lastLaunch = 0;
	if (GetTickCount() - lastLaunch > interval)
	{
		lastLaunch = GetTickCount();

		synchroFile(_T("dfsfd"),_T("fdsfd"));
		return 1;
	}

	return 0;
}
int intervaltest(DWORD interval)
{
	static DWORD last = 0;
	if (GetTickCount() - last > interval)
	{
		last = GetTickCount();
		return 1;
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("BitBlt");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
//	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, TEXT("a.bmp"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);



	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("BitBlt Demo"),
		WS_POPUP,
		picposx, picposy,
		picwidth, picheight,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_DRAWFRAME | SWP_NOSIZE);


	SetTimer(hwnd, 1, 100, NULL);//定义0.1秒检测一次DNF窗口
	SetTimer(hwnd, 2, 600000, NULL);//定义10分钟同步一次配置

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
BOOL LoadBitmapFromBMPFile(LPTSTR szFileName, HBITMAP *phBitmap,
	HPALETTE *phPalette)
{

	BITMAP  bm;

	*phBitmap = NULL;
	*phPalette = NULL;

	// Use LoadImage() to get the image loaded into a DIBSection
	*phBitmap = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (*phBitmap == NULL)
		return FALSE;

	// Get the color depth of the DIBSection
	GetObject(*phBitmap, sizeof(BITMAP), &bm);
	// If the DIBSection is 256 color or less, it has a color table
	if ((bm.bmBitsPixel * bm.bmPlanes) <= 8)
	{
		HDC           hMemDC;
		HBITMAP       hOldBitmap;
		RGBQUAD       rgb[256];
		LPLOGPALETTE  pLogPal;
		WORD          i;

		// Create a memory DC and select the DIBSection into it
		hMemDC = CreateCompatibleDC(NULL);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, *phBitmap);
		// Get the DIBSection's color table
		GetDIBColorTable(hMemDC, 0, 256, rgb);
		// Create a palette from the color tabl
		pLogPal = (LOGPALETTE *)malloc(sizeof(LOGPALETTE) + (256 * sizeof(PALETTEENTRY)));
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;
		for (i = 0;i<256;i++)
		{
			pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
			pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
			pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		*phPalette = CreatePalette(pLogPal);
		// Clean up
		free(pLogPal);
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	else   // It has no color table, so use a halftone palette
	{
		HDC    hRefDC;

		hRefDC = GetDC(NULL);
		*phPalette = CreateHalftonePalette(hRefDC);
		ReleaseDC(NULL, hRefDC);
	}
	return TRUE;

}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxClient, cyClient, cxSource, cySource;
	HDC         hdcClient, hdcWindow;
	int         x, y;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		cxSource = GetSystemMetrics(SM_CXSIZEFRAME) +
			GetSystemMetrics(SM_CXSIZE);

		cySource = GetSystemMetrics(SM_CYSIZEFRAME) +
			GetSystemMetrics(SM_CYCAPTION);
		return 0;
	case WM_TIMER:
		switch (wParam)
		{

		case 1:
			if (checkDNFRunning() == 1)
			{
				ShowWindow(hwnd, SW_SHOWNOACTIVATE);
			}
			else 
			{
				ShowWindow(hwnd, SW_MINIMIZE);
			}
			break;
		case 2:
//			synchroFile(_T("fdsfd"), _T("fdsfdsf"));
			break;
		}


	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

		//case WM_PAINT:
		//	hdcClient = BeginPaint(hwnd, &ps);
		//	hdcWindow = GetWindowDC(hwnd);

		//	for (y = 0; y < cyClient; y += cySource)
		//		for (x = 0; x < cxClient; x += cxSource)
		//		{
		//			BitBlt(hdcClient, x, y, cxSource, cySource,
		//				hdcWindow, 0, 0, SRCCOPY);
		//		}

		//	ReleaseDC(hwnd, hdcWindow);
		//	EndPaint(hwnd, &ps);
		//	return 0;


	case WM_PAINT:
	{
		PAINTSTRUCT   ps;
		HBITMAP       hBitmap, hOldBitmap;
		HPALETTE      hPalette, hOldPalette;
		HDC           hDC, hMemDC;
		BITMAP        bm;

		hDC = BeginPaint(hwnd, &ps);

		if (LoadBitmapFromBMPFile(_T("c.bmp"), &hBitmap, &hPalette))
		{
			GetObject(hBitmap, sizeof(BITMAP), &bm);
			hMemDC = CreateCompatibleDC(hDC);
			hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
			hOldPalette = SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);

			BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight,
				hMemDC, 0, 0, SRCCOPY);

			SelectObject(hMemDC, hOldBitmap);
			DeleteObject(hBitmap);
			SelectPalette(hDC, hOldPalette, FALSE);
			DeleteObject(hPalette);
		}
		EndPaint(hwnd, &ps);

	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hwnd, 1);
		KillTimer(hwnd, 2);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
