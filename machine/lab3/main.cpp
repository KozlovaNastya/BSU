#include <iostream>
using namespace std;
int main() {
    int array1[20], array2[20], minValue, N;
    bool found;
    cout << "Enter 0 < N < 21: ";
    cin >> N;
    while (N > 20 || N < 1) {
        cout << "incorect N: try again " << endl;
        cin >> N;
    }
    cout << "Enter elements of array1" << endl;
    for (int i = 0; i < N; i++)
        cin >> array1[i];
    cout << "Enter elements of array2" << endl;
    for (int i = 0; i < N; i++)
        cin >> array2[i];
    __asm {
        lea esi, array1
        lea edi, array2
        mov ecx, N
        mov minValue, INT_MAX
        cycle1 :
            mov eax, [esi]
            mov ebx, 0
            mov found, 0
            cycle2 :
                cmp ebx, N
                jge check
                mov edx, [edi + ebx * 4]
                cmp eax, edx
                je find_elem
                inc ebx
                jmp cycle2
            find_elem :
            mov found, 1
            check :
            cmp found, 1
            je skip
            cmp eax, minValue
            jge skip
            mov minValue, eax
            skip:
            add esi, 4         
            loop cycle1
    }
    if (minValue == INT_MAX)
        cout << "No such element found" << endl;
    else
        cout << "Minimum number in array1 not in array2: " << minValue << endl;
    return 0;
}