#include <windows.h>
#include <conio.h>
#include<iostream>
using namespace std;
#pragma warning(disable : 4996)

int main(int argc, char* argv[])
{
	char* name = (char*)"Project1.exe";
	int n = strlen(name);
	for (int i = 1; i < argc - 1; i++)
		n += strlen(argv[i]);
	char* lpszCommandLine = new char[n];
	strcpy(lpszCommandLine, name);
	STARTUPINFO si;
	for (int i = 1; i < argc - 1; i++)
	{
		strcat(lpszCommandLine, " ");
		strcat(lpszCommandLine, (char*)argv[i]);
	}

	
	PROCESS_INFORMATION piCom;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USECOUNTCHARS;
	si.dwXCountChars = 150;

	CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
		NULL, NULL, NULL, &si, &piCom);

	while (true)
	{
		char c;
		_cputs("Input 't' to terminate the new console process: ");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			// завершаем новый процесс
			TerminateProcess(piCom.hProcess, 1);
			break;
		}
	}

	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

	PROCESS_INFORMATION piCom2;
	STARTUPINFO si2;
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);

	char lpszCommandLine2[] = "Count.exe";

	CreateProcess(NULL, lpszCommandLine2, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si2, &piCom2);
	SetPriorityClass(piCom.hProcess, HIGH_PRIORITY_CLASS);

	WaitForSingleObject(&piCom2, INFINITE);
	CloseHandle(piCom2.hThread);
	CloseHandle(piCom2.hProcess);

	_cputs("The new process is created.\n");
	_cputs("Press any key to finish.\n");
	_getch();
	ExitProcess(0);
}
