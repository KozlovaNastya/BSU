#include <iostream>
#include <array>
#include <cmath>

int main() {
    int N;
    std::cout << "Enter number: ";
    std::cin >> N;
    N = std::abs(N);
    int numPovtor[10] = {}; // ������ ��� �������� ������ ����
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
        mov ecx, 10          // ������������� ������� ����� (10 ���������)
        lea esi, numPovtor    // ��������� ����� ������� numPovtor � ESI
        xor eax, eax         // �������� eax (���������� ��� maxEl)
        xor ebx, ebx         // �������� ebx (���������� ��� maxCount)
        xor edx, edx         // �������� edx (���������� ��� ������ i)

        cycle1 :
            mov edi, [esi + edx * 4]  // ��������� numPovtor[i] � edi
            cmp edi, ebx              // ���������� numPovtor[i] � maxCount
            jle skip_update           // ���� numPovtor[i] <= maxCount, ���������� ����������
            mov ebx, edi              // ��������� maxCount
            mov eax, edx              // ��������� maxEl (������ = i)

            skip_update :
            inc edx                   // ����������� i (index)
            loop cycle1            // ���������, ���� �� ���������� ��� 10 ����

            mov maxEl, eax             // ��������� ��������� �������� maxEl
            mov maxCount, ebx          // ��������� ��������� �������� maxCount
    }
    std::cout << "Most common digit: " << maxEl << std::endl;
    return 0;
}
