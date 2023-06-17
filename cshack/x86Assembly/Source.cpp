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
        push ebp
        mov ebp, esp

        mov eax, hardcoded_string
        mov ebx, 1

        mov esp, ebp
        pop ebp
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
            mov cl, [eax]   //move one letter
            cmp cl, 0       //see if letter is null terminator
            je reverse_string
            inc eax     //next letter
            inc ebx     //increment length
            jmp length_loop

        reverse_string:
            mov eax, string
            dec ebx
            xor esi, esi

        lp:
            mov cl, byte ptr[eax + esi]   
            mov dl, byte ptr[eax + ebx]   
            mov byte ptr[eax + esi], dl     
            mov byte ptr[eax + ebx], cl
            inc esi     //increase start pointer
            dec ebx     //decrease end length pointer
            cmp esi, ebx
            jle lp

        end:
            mov esp, ebp
            pop ebp
            ret
    }
}

//char str[] = "hello";
//
//int end = strlen(str) - 1;
//for (int start = 0; start <= end; start++, end--)
//{
//    char temp = str[start];
//    str[start] = str[end];
//    str[end] = temp;
//}

//eax = start
//ebx = end
//ecx = temp

//mov eax, str; Moves in address of str
//mov ebx, [eax]; Moves 'H' to ebx
//inc eax; Increments to next address
//mov ebx, [eax]; Moves 'e' to ebx

int main(int argc, char* argv[])
{
    printf("7 x 3 = %i\n", Multiply(7, 3));
    printf("5 Flipped is %i\n", FlipSign(5));
    //CallMessageBoxA(nullptr, "Hello", "Caption", MB_YESNO);
    char str[] = {'a','b','c','d','e','f','g','\0'};
    
    ReverseString(str);
    //CReverseString(str);
    printf(str);
    ReverseStringHardcoded();

    return 0;
}