#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return result;
}

int main() {
    setlocale(LC_ALL, ".1251");  // Set encoding for correct text display

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    if (inputFile.peek() == EOF) {
        cerr << "File is empty" << endl;
        return 1;
    }

    set<string> uniqueWords;
    map<string, int> wordCount;
    string word;

    while (inputFile >> word) {
        word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) {
            return ispunct(c);
        }), word.end());

        uniqueWords.insert(toLowerCase(word));
        wordCount[toLowerCase(word)]++;
    }

    inputFile.close();

    cout << "Unique words (case insensitive):" << endl;
    for (const auto& w : uniqueWords) {
        cout << w << endl;
    }

    cout << "\nWord frequency count:" << endl;
    for (const auto& entry : wordCount) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}
