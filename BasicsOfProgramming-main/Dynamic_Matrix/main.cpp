#include <iostream>
#include <stdexcept>

using namespace std;

class Stack {
private:
    double* arr;
    int obem;
    int sizeArr;

    void resize() {
        int newObem = obem * 2;
        double* newArr = new double[newObem];
        for (int i = 0; i < sizeArr; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        obem = newObem;
    }

public:
    Stack(int polObem = 10) : obem(polObem), sizeArr(0) {
        arr = new double[obem];
    }

    ~Stack() {
        delete[] arr;
    }

    void push(double value) {
        if (sizeArr == obem) {
            resize();
        }
        arr[sizeArr++] = value;
    }

    double pop() {
        if (isEmpty()) {
            throw runtime_error("Error: Stack is empty! Cannot remove element.");
        }
        return arr[--sizeArr];
    }

    double top() const {
        if (isEmpty()) {
            throw runtime_error("Error: Stack is empty! Cannot access top element.");
        }
        return arr[sizeArr - 1];
    }

    bool isEmpty() const {
        return sizeArr == 0;
    }

    int GetSizeArr() const {
        return sizeArr;
    }

    void SetSizeArr(int value) {
        if (value < 0 || value > obem) {
            throw invalid_argument("Error: Invalid stack size value.");
        }
        sizeArr = value;
    }

    void printStack() const {
        if (isEmpty()) {
            throw runtime_error("Error: Stack is empty! Cannot print elements.");
        }
        cout << "Stack elements (top to bottom):" << endl;
        for (int i = sizeArr; i > 0; --i) {
            cout << arr[i - 1] << endl;
        }
    }
};

int main() {
    try {
        Stack stack;
        stack.push(13.5);
        stack.push(1.11);
        stack.push(9.18);

        cout << "full stack:" << endl;
        stack.printStack();

        stack.pop();
        cout << "After removing 1 element:" << endl;
        stack.printStack();

        cout << "Top element: " << stack.top() << endl;

    }
    catch (const exception& e) {
        cerr << "Error occurred: " << e.what() << endl;
    }

    return 0;
}
