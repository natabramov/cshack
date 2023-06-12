#include <Windows.h>

#include <cstdio>

__declspec(naked) int Multiply(int first, int second)
{
    __asm
    {
        // Function prologue
        push ebp
        mov ebp, esp

        mov eax, [ebp+0x8]
        mul [ebp+0xC]

        // Function epilogue
        mov esp, ebp
        pop ebp
        ret
    }
}

// Flips the sign of the input
// Input: 5 Output: -5
// Input -10: Output: 10
// Result is expected in the EAX register
__declspec(naked) int FlipSign(int number)
{
    __asm
    {
        ret
    }
}

// Calls the MessageBoxA function in the Windows API
__declspec(naked) void CallMessageBoxA(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
    __asm
    {

    }
}

// Returns the reversed hardcoded string
// Output: "elloH"
__declspec(naked) char* ReverseStringHardcoded()
{
    __asm
    {
        ret

        hardcoded_string:
            _emit 'H'
            _emit 'e'
            _emit 'l'
            _emit 'l'
            _emit 'o'
            _emit '\0'
    }
}

// Reverses an input string in place
// Input: "Hello" Output: "elloH"
__declspec(naked) void ReverseString(char* string)
{
    __asm
    {

    }
}

int main(int argc, char* argv[])
{
    printf("7 x 3 = %i\n", Multiply(7, 3));

    return 0;
}