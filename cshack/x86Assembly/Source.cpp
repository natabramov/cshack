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

        mov ebx, 0  //length
        mov eax, hardcoded_string

        length_loop:
            mov cl, [eax]           //move one letter
            inc ebx                 //increment length
            cmp cl, 0               //see if letter is null terminator
            je setup
            inc eax                 //next letter
            jmp length_loop
        
        setup:
            push ebx
            call malloc
            mov ecx, hardcoded_string
            dec ebx
            mov esi, eax

        move_loop:
            mov dl, byte ptr [ecx+ebx-1]   //write string into memory one byte at a time
            mov [eax], dl
            inc eax
            dec ebx
            cmp ebx, 0
            mov [eax], 0
            jne move_loop

        mov eax, esi
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
            mov cl, [eax]           //move one letter
            cmp cl, 0               //see if letter is null terminator
            je reverse_string
            inc eax                 //next letter
            inc ebx                 //increment length
            jmp length_loop

        reverse_string:
            mov eax, string
            dec ebx
            xor esi, esi

        lp:
            mov cl, byte ptr[eax + esi] // char temp = str[start]
            mov dl, byte ptr[eax + ebx] // vvvvvvvvvvvvvvvvvvvvv
            mov byte ptr[eax + esi], dl // str[start] = str[end]
            mov byte ptr[eax + ebx], cl // str[end] = str[start]
            inc esi                     // start++
            dec ebx                     // end--
            cmp esi, ebx                // start <= end ?
            jle lp                      // No, continue looping

        mov esp, ebp
        pop ebp
        ret
    }
}

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
    printf(str);
    char*q = ReverseStringHardcoded();
    printf("\n%s",q);
    return 0;
}