#include <windows.h> 
#include <tlhelp32.h> 
#include <tchar.h> 
#include <stdio.h>

BOOL ListProcessModules(DWORD dwPID) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE) { return FALSE; }
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);
		return(FALSE);
	}

	do
	{
		if (strncmp(me32.szModule, "client.dll", sizeof(me32.szModule)) == 0) {
			HANDLE hClient = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, NULL, me32.th32ProcessID);
			unsigned char newBytes[] = { 0x39, 0xD2, 0x90 }; 
			BOOL bProcess = WriteProcessMemory(hClient, (char*)me32.modBaseAddr + 0x1D1384, newBytes, sizeof(newBytes), NULL);
			if (bProcess == 0) { _tprintf(TEXT("\n\n     MODULE NAME FAILED:     %s"), me32.szModule); }
		}

	} while (Module32Next(hModuleSnap, &me32));

	_tprintf(TEXT("\n"));

	CloseHandle(hModuleSnap);
	return TRUE;
}

DWORD GetProcessIdFromName(const char * processName) {
	PROCESSENTRY32 pe32;
	HANDLE hProcessSnap;
	
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) { return (FALSE); }

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		if (strncmp(pe32.szExeFile, processName, sizeof(pe32.szExeFile)) == 0) { 
			_tprintf(TEXT("\nprocessID:  %lu"), pe32.th32ProcessID);
			return (pe32.th32ProcessID); 
		}

	} while (Process32Next(hProcessSnap, &pe32));

	_tprintf(TEXT("\nNO PROCESS FOUND:  %s"), processName);
	CloseHandle(hProcessSnap);
	return TRUE;
}

CHAR* GetDllBaseAddressInProcess(DWORD processId) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
	if (hModuleSnap == INVALID_HANDLE_VALUE) { return FALSE; }
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);
		return FALSE;
	}

	do
	{
		if (strncmp(me32.szModule, "client.dll", sizeof(me32.szModule)) == 0) {
			_tprintf(TEXT("\nmodBaseAddr:  %s"), (char*)me32.modBaseAddr);
			return ((char*)me32.modBaseAddr);
		}

	} while (Module32Next(hModuleSnap, &me32));

	_tprintf(TEXT("\nNO PROCESS FOUND WITH PROCESS ID:  %lu"), processId);
	CloseHandle(hModuleSnap);
	return 0;
}

CHAR* SaveOldInstructionBytes(DWORD processId, char* instructionAddress, char* oldInstructions) {
	return 0;
}

BOOL EnableWallhack(DWORD processId, char* instructionAddress) {

}

BOOL DisableWallhack(DWORD processId, char* instructionAddress, char* oldInstructions) {

}

int main(int argc, char* argv[]) {
	DWORD processId = GetProcessIdFromName("csgo.exe");
	char* dllBaseAddress = GetDllBaseAddressInProcess(processId); //works i think but only with everything else
	char* instructionAddress = dllBaseAddress + 0x1D1384;
	char oldInstructions[8] = { 0 };
	SaveOldInstructionBytes(processId, instructionAddress, oldInstructions);
	/*
	oldInstructions = SaveOldInstructionBytes(processId, instructionAddress, oldInstructions); ??
	*/
	int HOTKEY_ENABLE = VK_INSERT;
	int HOTKEY_DISABLE = VK_DELETE;
	while (true) {
		if (GetAsyncKeyState(HOTKEY_ENABLE)) {
			EnableWallhack(processId, instructionAddress);
		}
		else if (GetAsyncKeyState(HOTKEY_DISABLE)) {
			DisableWallhack(processId, instructionAddress, oldInstructions);
		}
	}

	ListProcessModules(processId);

	/*
	* DWORD processId = GetProcessIdFromName("csgo.exe");
	* char* dllBaseAddress = GetDllBaseAddressInProcess(processId);
	* char* dllBaseAddress = GetDllBaseAddressInProcess(processId);
	* char* instructionAddress = dllBaseAddress + [RVA]
	* char oldInstructions[8] = {0};
	* SaveOldInstructionBytes(processId, instructionAddress, oldInstructions);
	* while(true) {
	*     if (GetAsyncKeyState([HOTKEY_ENABLE])) {
	*         EnableWallhack(processId, instructionAddress);
	*     } else if (GetAsyncKeyState([HOTKEY_DISABLE])) {
	*         DisableWallhack(processId, instructionAddress, oldInstructions);
	*     }
	* }
	*/
	return 0;
}