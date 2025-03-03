#include <iostream>
#include <array>
#include <cmath>

int main() {
    int N;
    std::cout << "Enter number: ";
    std::cin >> N;
    N = std::abs(N);
    int numPovtor[10] = {}; // Массив для хранения частот цифр
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
        mov ecx, 10          // Устанавливаем счетчик цикла (10 элементов)
        lea esi, numPovtor    // Загружаем адрес массива numPovtor в ESI
        xor eax, eax         // Обнуляем eax (используем для maxEl)
        xor ebx, ebx         // Обнуляем ebx (используем для maxCount)
        xor edx, edx         // Обнуляем edx (используем как индекс i)

        cycle1 :
            mov edi, [esi + edx * 4]  // Загружаем numPovtor[i] в edi
            cmp edi, ebx              // Сравниваем numPovtor[i] и maxCount
            jle skip_update           // Если numPovtor[i] <= maxCount, пропускаем обновление
            mov ebx, edi              // Обновляем maxCount
            mov eax, edx              // Обновляем maxEl (индекс = i)

            skip_update :
            inc edx                   // Увеличиваем i (index)
            loop cycle1            // Повторяем, пока не обработаем все 10 цифр

            mov maxEl, eax             // Сохраняем найденное значение maxEl
            mov maxCount, ebx          // Сохраняем найденное значение maxCount
    }
    std::cout << "Most common digit: " << maxEl << std::endl;
    return 0;
}
