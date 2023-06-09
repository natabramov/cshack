#include <Windows.h>

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
            FILE_SHARE_DELETE,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        char str[] = "This text should be written to the file 12345678";
        DWORD dwBytesWritten;

        WriteFile(
            f,
            str,
            strlen(str),
            &dwBytesWritten,
            NULL
        );

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