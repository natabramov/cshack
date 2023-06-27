#include <windows.h> 
#include <tlhelp32.h> 
#include <tchar.h> 
#include <stdio.h>

BOOL ListProcessModules(DWORD dwPID) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		printf("Module32First");  // Show cause of failure 
		CloseHandle(hModuleSnap);     // Must clean up the snapshot object! 
		return(FALSE);
	}

	do
	{
		if (me32.szModule == "client.dll") {
			_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
		}
		_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
		_tprintf(TEXT("\n     executable     = %s"), me32.szExePath);
		_tprintf(TEXT("\n     process ID     = 0x%08X"), me32.th32ProcessID);
		_tprintf(TEXT("\n     ref count (g)  =     0x%04X"), me32.GlblcntUsage);
		_tprintf(TEXT("\n     ref count (p)  =     0x%04X"), me32.ProccntUsage);
		_tprintf(TEXT("\n     base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
		_tprintf(TEXT("\n     base size      = %d"), me32.modBaseSize);

	} while (Module32Next(hModuleSnap, &me32));

	_tprintf(TEXT("\n"));

	//  Do not forget to clean up the snapshot object. 
	CloseHandle(hModuleSnap);
	return(TRUE);
}

int main(int argc, char* argv[]) {
	ListProcessModules(4764); //need to find this using method
	return 0;
}