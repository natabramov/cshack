#include <Windows.h>

#include <cstdio>

#include <string>

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
        push ebp
        mov ebp, esp

        mov eax, [ebp+0x8]
        neg eax

        mov esp, ebp
        pop ebp
        ret
    }
}

// Calls the MessageBoxA function in the Windows API
__declspec(naked) void CallMessageBoxA(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
    __asm
    {
        push ebp
        mov ebp, esp

        push [ebp+0x14] //uType
        push [ebp+0x10] //lpCaption
        push [ebp+0xC]  //lpText
        push [ebp+0x8] //hwnd

        mov eax, MessageBoxA
        call eax

        mov esp, ebp
        pop ebp
        ret
    }
}

// Returns the reversed hardcoded string
// Output: "olleH"
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
        push ebp
        mov ebp, esp

        mov ebx, 0 //length

        mov eax, string //move string into eax

        length_loop:
            mov edx, [eax + ebx]
            cmp [eax+ebx], 0
            jz reverse_string
            inc ebx
            loop length_loop

        reverse_string:
            mov ecx, 1 //placeholder

        mov esp, ebp
        pop ebp
        ret
    }
}

int main(int argc, char* argv[])
{
    printf("7 x 3 = %i\n", Multiply(7, 3));
    printf("5 Flipped is %i\n", FlipSign(5));
    //CallMessageBoxA(nullptr, "Hello", "Caption", MB_YESNO);
    char hello[] = {'h','e','l','l','o'};
    
    ReverseString(hello);

    return 0;
}