#include <iostream>
#include <array>
#include <cmath>

int main() {
    int N;
    std::cout << "Enter number: ";
    std::cin >> N;
    N = std::abs(N);
    int numPovtor[10] = {};
    _asm {
        mov eax, N
        test eax, eax
        jz end_cycle
        lea esi, numPovtor

        cycle :
            xor edx, edx
            mov ecx, 10
            div ecx
            mov ebx, edx
            lea edi, [esi + ebx * 4]
            inc [edi]
            test eax, eax
            jnz cycle
            end_cycle :

    }
    int maxEl = 0, maxCount = 0;
    __asm {
        mov ecx, 10          
        lea esi, numPovtor   
        xor eax, eax         
        xor ebx, ebx         
        xor edx, edx         

        cycle1 :
            mov edi, [esi + edx * 4]  
            cmp edi, ebx              
            jle skip_update           
            mov ebx, edi              
            mov eax, edx              

            skip_update :
            inc edx                   
            loop cycle1            

            mov maxEl, eax         
            mov maxCount, ebx      
    }
    std::cout << "Most common digit: " << maxEl << std::endl;
    return 0;
}
