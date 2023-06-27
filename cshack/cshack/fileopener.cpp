#include <Windows.h>
#include <string>

void openFile(HANDLE file) {
    STARTUPINFOA si{};
    si.cb = sizeof(STARTUPINFOA);
    PROCESS_INFORMATION pi{};

    char buffer[1024]{};
    GetFinalPathNameByHandleA(file, buffer, sizeof(buffer), 0);

    std::string path = "C:\\Windows\\system32\\Notepad.exe";
    std::string args = path;
    args += " "; //adds a space for second path
    args += buffer;

    CreateProcessA(path.c_str(),
        (char*)args.c_str(),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi);

    Sleep(1000);

    HWND notepadWindow = FindWindowA(NULL, "test.txt - Notepad");
    SetWindowTextA(notepadWindow, "New Text File");
}

int main(int argc, char* argv[])
{
    int mboxCreate = MessageBoxA(
        nullptr,
        "Do you want to create the file test.txt?",
        "Create",
        MB_ICONINFORMATION | MB_YESNO
    );

    if (mboxCreate == IDYES) {
        HANDLE f = CreateFileA(
            "test.txt",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_DELETE | FILE_SHARE_READ,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        char str[] = "This text should be written to the file 12345678AAAAAAAAAAAAAAAAA";
        DWORD dwBytesWritten;

        WriteFile(
            f,
            str,
            strlen(str),
            &dwBytesWritten,
            NULL
        );

        openFile(f);


        int mboxDelete = MessageBoxA(
            nullptr,
            "Do you want to delete the file test.txt?",
            "Delete",
            MB_ICONINFORMATION | MB_YESNO
        );

        if (mboxDelete == IDYES) {
            BOOL fileDeleted = DeleteFileA("test.txt");
            if (fileDeleted != 0) {
                int mboxCompleted = MessageBoxA(
                    nullptr,
                    "test.txt has been deleted.",
                    "Action Completed",
                    0
                );
            }
        }
    }

    return 0;
}