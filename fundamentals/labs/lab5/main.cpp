#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

bool checkAlone(string text, int i, const int n) {
    if (n == 1) {
        return 0;
    }
    if (i == 0) {
        if (text[i + 1] == ' ')
            return 0;
        return 1;
    }
    if (i == n - 1) {
        if (text[i - 1] == ' ')
            return 0;
        return 1;
    }
    if (text[i + 1] != ' ' || text[i - 1] != ' ')
        return 1;
    return 0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string text, letter, replace;
    string result = "";
    //Data entry
    cout << "Enter string: ";
    getline(cin, text);
    cout << "Enter letter to replace: ";
    getline(cin, letter);
    cout << "Enter a replacement word: ";
    getline(cin, replace);
    int n = text.length();
    //Carry out replacement
    for (int i = 0; i < n; i++) {
        if (text[i] == letter[0]) {
            if (checkAlone(text, i, n))
                result += replace;
            else result += text[i];
        }
        else {
            result += text[i];
        }
    }
    //Output of the result
    cout << "Result: " << result << endl;
    return 0;
}
