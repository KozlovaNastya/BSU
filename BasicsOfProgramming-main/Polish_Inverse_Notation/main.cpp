#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct TStack {
    int n;
    string* items;
    int top;
};

TStack stack;

void createStack(TStack& stack, int count) {
    stack.items = new string[count];
    stack.top = 0;
    stack.n = count;
}

void deleteStack(TStack& stack) {
    delete[] stack.items;
    stack.items = nullptr;
}

void push(TStack& stack, const string& k) {
    if (stack.top > stack.n - 1) {
        throw "Stack is full!";
    }
    stack.items[stack.top++] = k;
}

string pop(TStack& stack) {
    if (stack.top == 0) {
        throw "Stack is empty!";
    }
    string k = stack.items[--stack.top];
    return k;
}

bool isEmpty(TStack stack) {
    return (stack.top == 0);
}

int priority(string x) {
    if (x == "*" || x == "/") return 2;
    if (x == "+" || x == "-") return 1;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    createStack(stack, 40);
    string str, subs, subst, sf;
    int op;
    cout << "Введите выражение:" << endl;
    getline(cin, str);
    int pos1 = 0, pos2;
    while ((pos1 = str.find_first_not_of(" ", pos1)) != -1) {
        pos2 = str.find_first_of(" ", pos1);
        subs = str.substr(pos1, pos2 - pos1);
        try {
            stoi(subs);
            sf += " " + subs;
        }
        catch (invalid_argument) {
            if (subs == "(") {
                push(stack, subs);
            }
            else if (subs == ")") {
                while ((subs = pop(stack)) != "(") {
                    sf += " " + subs;
                }
            }
            else {
                if (isEmpty(stack)) {
                    push(stack, subs);
                }
                else {
                    do {
                        subst = pop(stack);
                        if (subst == "(" || priority(subs) > priority(subst)) {
                            push(stack, subst);
                            break;
                        }
                        else {
                            sf += " " + subst;
                        }
                    } while (!isEmpty(stack));
                    push(stack, subs);
                }
            }
        }
        pos1 = pos2;
    }
    while (!isEmpty(stack)) {
        sf += " " + pop(stack);
    }
    cout << sf << endl;

    pos1 = 0;
    int res = 0;
    while ((pos1 = sf.find_first_not_of(" ", pos1)) != -1) {
        pos2 = sf.find_first_of(" ", pos1);
        subs = sf.substr(pos1, pos2 - pos1);
        try {
            stoi(subs);
            push(stack, subs);
        }
        catch (invalid_argument) {
            int x = stoi(pop(stack)), y = stoi(pop(stack));
            if (subs == "+") {
                res = y + x;
            }
            else if (subs == "-") {
                res = y - x;
            }
            else if (subs == "*") {
                res = y * x;
            }
            else {
                res = y / x;
            }
            push(stack, to_string(res));
        }
        pos1 = pos2;
    }
    cout << pop(stack) << endl;

    deleteStack(stack);
    return 0;
}
