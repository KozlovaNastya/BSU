#include <iostream> 

class MethodIterator;

class Deque
{
private:
    int* items;
    int sp;
public:

    friend class DequeIter;
    friend class MethodIterator;
    
    Deque(): items(nullptr), sp(0){}
    Deque(const int* in, int s) : items(nullptr), sp(s) {
        if (s > 0) {
            items = new int[s];
            for (int i = 0; i < s; i++)
                items[i] = in[i];
        }
    }
    Deque(const Deque& other) : items(nullptr), sp(other.sp){
        if (sp > 0) {
            items = new int[sp];
            for (int i = 0; i < sp; i++) 
                items[i] = other.items[i];
        }
    }
    Deque(Deque&& other) : items(other.items), sp(other.sp) {
        other.items = nullptr;
        other.sp = 0;
    }
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            delete[] items;
            sp = other.sp;
            if (sp > 0) items = new int[sp];
            else items = nullptr;
            for (int i = 0; i < sp; i++) items[i] = other.items[i];
        }
        return *this;
    }
    Deque& operator=(Deque&& other) {
        if (this != &other) {
            delete[] items;
            sp = other.sp;
            items = other.items;
            other.items = nullptr;
            other.sp = 0;
        }
        return *this;
    }
    int Size() {
        return sp;
    }
    void Clear() {
        sp = 0;
    }
    bool isEmpty()
    {
        return (sp == 0);
    }
    bool IsFull() {
        try {
            int* test = new int[sp + 1];
            delete[] test;
            return false;
        }
        catch (std::bad_alloc&) {
            return true;
        }
    }
    int Front() {
        if(isEmpty()) throw std::out_of_range("Deque is empty");
        return items[0];
    }
    int Back() {
        if (isEmpty()) throw std::out_of_range("Deque is empty");
        return items[sp-1];
    }
    void PushFront(int in) {
        int* temp = new int[++sp];
        temp[0] = in;
        for (int i = 1; i < sp; i++) temp[i] = items[i - 1];
        delete[] items;
        items = new int[sp];
        for (int i = 0; i < sp; i++) items[i] = temp[i];
        delete[] temp;
    }
    void PushBack(int in)
    {
        int* temp = new int[++sp];
        for (int i = 0; i < sp - 1; i++) temp[i] = items[i];
        temp[sp - 1] = in;
        if (items != nullptr) {
            delete[] items;
        }
        items = new int[sp];
        for (int i = 0; i < sp; i++) items[i] = temp[i];
        delete[] temp;
    }
    int popFront() {
        if (isEmpty()) throw std::out_of_range("Deque is empty");
        int* temp = new int[--sp];
        int ret = items[0];
        for (int i = 0; i < sp; i++) temp[i] = items[i+1];
        delete[] items;
        items = new int[sp];
        for (int i = 0; i < sp; i++) items[i] = temp[i];
        delete[] temp;
        return ret;
    }
    int popBack()
    {
        if (isEmpty()) throw std::out_of_range("Deque is empty");
        int ret = items[sp - 1];
        int* temp = new int[--sp];
        for (int i = 0; i < sp; i++) temp[i] = items[i];
        delete[] items;
        items = new int[sp];
        for (int i = 0; i < sp; i++) items[i] = temp[i];
        delete[] temp;
        return ret;
    }
    ~Deque() {
        delete[] items;
    }
    friend std::ostream& operator<<(std::ostream& os, const Deque & other) {
        for (int i = 0; i < other.sp; i++) {
            if (i != other.sp - 1)
                os << other.items[i] << " ";
            else os << other.items[i] << std::endl;
        }
        return os;
    }

    
    MethodIterator* getMethodIterator() const;
};

class MethodIterator {
    const Deque& deque_ref;
    int current_index;
public:
    MethodIterator(const Deque& d) : deque_ref(d), current_index(0) {}
    bool hasNext() const {
        return current_index < deque_ref.sp;
    }
    int current() const {
        if (current_index >= deque_ref.sp)
            throw std::out_of_range("Iterator out of range");
        return deque_ref.items[current_index];
    }
    void next() {
        if (current_index >= deque_ref.sp)
            throw std::out_of_range("Iterator out of range");
        current_index++;
    }
    int position() const {
        return current_index;
    }
};

MethodIterator* Deque::getMethodIterator() const {
    return new MethodIterator(*this);
}

class DequeIter {
    const Deque& deq;
    int index;
public:
    DequeIter(const Deque& s) : deq(s)
    {
        index = 0;
    }
    void operator++()
    {
        index++;
    }
    bool operator()()
    {
        return index != deq.sp + 1;
    }
    int operator *()
    {
        return deq.items[index];
    }
    int getIndex() {
        return index;
    }
};

int find1(const Deque& deq, const int& elem) {
    DequeIter it(deq);
    for (it; it(); ++it) {
        if (*it == elem) return it.getIndex();
    }
    return -1;
}
int find2(const Deque& deq, const int& elem) {
    MethodIterator* it = deq.getMethodIterator();
    while (it->hasNext()) {
        if (it->current() == elem) {
            return it->position();
        }
        it->next();
    }
    return -1;
}
int main() {
    std::cout << "constructor without parameteres" << std::endl;
    Deque deq1, deq2;
    for (int i = 0; i < 6; i++) deq1.PushBack(i + 1);
    std::cout << "deq1 with PushBack" << std::endl << deq1;
    for (int i = 0; i < 6; i++) deq2.PushFront(i + 1);
    std::cout << "deq2 with PushFront" << std::endl << deq2;
    std::cout << "deq1 with popBack : " << deq1.popBack() << std::endl;
    std::cout << "deq2 with popFront : " << deq2.popFront() << std::endl;
    std::cout << "deq2 with Front : " << deq2.Front() << std::endl;
    std::cout << "deq2 with Back : " << deq2.Back() << std::endl;
    std::cout << "deq2 with isEmpty : " << deq2.isEmpty() << std::endl;
    std::cout << "deq2 with Size : " << deq2.Size() << std::endl;
    std::cout << "deq2 with IsFull : " << deq2.IsFull() << std::endl;
    std::cout << "constructor with parameteres for deq3" << std::endl;
    int* ar = new int[3];
    ar[0] = 7; 
    ar[1] = 8;
    ar[2] = 9;
    Deque deq3(ar, 3);
    std::cout << deq3;
    deq3.Clear();
    std::cout << "deq3 with Clear : " << deq3;
    deq3 = deq2;
    std::cout << "operator deq3 = deq2" << std::endl << deq3;
    deq3.Clear();
    deq3 = std::move(deq2);
    std::cout << "operator deq3 = deq2 with move" << std::endl << deq3;
    std::cout << "deq2 : " << deq2;
    Deque deq4(deq1);
    std::cout << "copy constructor for deq4" << std::endl << deq4;
    Deque deq5(std::move(deq1));
    std::cout << "copy constructor for deq5 with move" << std::endl << deq5;
    std::cout << "deq1 : " << deq1 << std::endl;
    std::cout << "find1 in deq5 elem 3 : " << find1(deq5, 3) << std::endl;
    std::cout << "find1 in deq5 elem 9 : " << find1(deq5, 9) << std::endl;
    std::cout << "find2 in deq5 elem 1 : " << find1(deq5, 1) << std::endl;
    std::cout << "find2 in deq5 elem 7 : " << find1(deq5, 7) << std::endl;
    return 0;
}