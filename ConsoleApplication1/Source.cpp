
#include<string>
#include <iostream>
#include <sstream>
#include<windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
using namespace std;


//void synchroFile(TCHAR* source, TCHAR* dest);
//
//void _tmain(int argc, TCHAR* argv[])
//{
//	WIN32_FIND_DATA FileData;
//	HANDLE          hSearch;
//	DWORD           dwAttrs;
//	TCHAR           szNewPath[MAX_PATH];
//
//	BOOL            fFinished = FALSE;
//
//	if (argc != 2)
//	{
//		_tprintf(TEXT("Usage: %s <dir>\n"), argv[0]);
//		return;
//	}
//
//	 Create a new directory. 
//
//	if (!CreateDirectory(argv[1], NULL))
//	{
//		printf("CreateDirectory failed (%d)\n", GetLastError());
//		return;
//	}
//
//	 Start searching for text files in the current directory. 
//
//	hSearch = FindFirstFile(TEXT("*.txt"), &FileData);
//	if (hSearch == INVALID_HANDLE_VALUE)
//	{
//		printf("No text files found.\n");
//		return;
//	}
//
//	 Copy each .TXT file to the new directory 
//	 and change it to read only, if not already. 
//
//	while (!fFinished)
//	{
//		StringCchPrintf(szNewPath, sizeof(szNewPath) / sizeof(szNewPath[0]), TEXT("%s\\%s"), argv[1], FileData.cFileName);
//
//		if (CopyFile(FileData.cFileName, szNewPath, FALSE))
//		{
//			dwAttrs = GetFileAttributes(FileData.cFileName);
//			if (dwAttrs == INVALID_FILE_ATTRIBUTES) return;
//
//			if (!(dwAttrs & FILE_ATTRIBUTE_READONLY))
//			{
//				SetFileAttributes(szNewPath,
//					dwAttrs | FILE_ATTRIBUTE_READONLY);
//			}
//		}
//		else
//		{
//			printf("Could not copy file.\n");
//			return;
//		}
//
//		if (!FindNextFile(hSearch, &FileData))
//		{
//			if (GetLastError() == ERROR_NO_MORE_FILES)
//			{
//				_tprintf(TEXT("Copied *.txt to %s\n"), argv[1]);
//				fFinished = TRUE;
//			}
//			else
//			{
//				printf("Could not find next file.\n");
//				return;
//			}
//		}
//	}
//
//	 Close the search handle. 
//
//	FindClose(hSearch);
//}

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

int main()
{
	//TCHAR *source = _T("C:\\local\\bmp\\a.bmp");
	//TCHAR *dest = _T("C:\\local\\bmp1\\");
	//synchroFile(source, dest);
//	synchroFile(source, dest);

	
	RECT rc;




	while (true)
	{
		HWND hwnd = GetForegroundWindow();
		Sleep(1000);
		GetWindowRect(hwnd, &rc);

		cout << rc.right - rc.left << " " << rc.bottom - rc.top<<"   ";
	}
	return 0;
}
//
//void deleteFirstFile(TCHAR *directory)
//{
//	TCHAR totalPath[MAX_PATH];
//	StringCchCopy(totalPath, MAX_PATH, directory);
//	HANDLE hFind;
//	WIN32_FIND_DATA FindFileData;
//	hFind = FindFirstFile(directory, &FindFileData);
//	FindNextFile(hFind, &FindFileData);
//	FindNextFile(hFind, &FindFileData);
//	StringCchCat(totalPath, MAX_PATH, FindFileData.cFileName);
//	DeleteFile(totalPath);
//	FindClose(hFind);
//}
////同步配置文件到ftp里，source是要同步的文件名，dest是同步到的目录，注意同步时会删除目录内第一个文件，而且路径目录必须已经建立。
//void synchroFile(TCHAR* source, TCHAR* dest)
//{
//	TCHAR szDir[MAX_PATH];
//	TCHAR totalPath[MAX_PATH];
//	StringCchCopy(szDir, MAX_PATH, dest);
//	StringCchCat(szDir, MAX_PATH, TEXT("*"));
//	WIN32_FIND_DATA FindFileData;
//	HANDLE hFind;
//	hFind = FindFirstFile(szDir, &FindFileData);
//
//	FindNextFile(hFind, &FindFileData);
//	FindNextFile(hFind, &FindFileData);
//	//跳过前两个文件. 和..
//	
//	StringCchCopy(totalPath, MAX_PATH, dest);
//	StringCchCat(totalPath, MAX_PATH, FindFileData.cFileName);
//
//	DeleteFile(totalPath); //删除文件夹内第一文件。
//
//	const time_t t = time(NULL);
//	string curTime;
//	stringstream ss;
//
//	/*本地时间：日期，时间 年月日，星期，时分秒*/
//	struct tm* current_time = localtime(&t);
//	curTime.c_str();
//	ss << current_time->tm_hour << "." << current_time->tm_min << "." << current_time->tm_sec << " " << current_time->tm_mon << "-" << current_time->tm_mday;
//	getline(ss, curTime);
//
//
//	curTime = curTime + ".bmp";
//	wstring wcurTime(curTime.begin(), curTime.end());
//	wcurTime = dest + wcurTime;
//	TCHAR *str = (wchar_t *)wcurTime.c_str();;
//	CopyFile(source, str, TRUE);
//	FindClose(hFind);
//}