#include <iostream>
using namespace std;

const int MAX = 10;

class Array {
protected:
    int data[MAX];
    int size;
public:
    Array(int s = 5) : size(s) {
        cout << "Ввод " << size << " элементов:\n";
        for(int i = 0; i < size; i++) {
            cout << "Элемент " << i+1 << ": ";
            cin >> data[i];
        }
    }

    virtual void add(const Array& other) = 0;

    void show() const {
        for(int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }

    int getSize() const { return size; }
    int get(int i) const { return data[i]; }
};

class ArraySum : public Array {
public:
    ArraySum(int s = 5) : Array(s) {}
    void add(const Array& other) override {
        int min_s = min(size, other.getSize());
        for(int i = 0; i < min_s; i++)
            data[i] += other.get(i);
    }
};

class ArrayAND : public Array {
public:
    ArrayAND(int s = 5) : Array(s) {}
    void add(const Array& other) override {
        int min_s = min(size, other.getSize());
        for(int i = 0; i < min_s; i++)
            data[i] &= other.get(i);
    }
};

int main() {
    cout << "Лабораторная №2:\n";

    cout << "Массив для обычного сложения:\n";
    ArraySum a1(4);

    cout << "\nМассив для побитового AND:\n";
    ArrayAND a2(4);

    cout << "\nИсходные массивы:\n";
    cout << "a1: "; a1.show();
    cout << "a2: "; a2.show();

    a1.add(a2);
    cout << "\na1 + a2 (обычное сложение): "; a1.show();

    Array* p = new ArrayAND(4);
    cout << "\nЧерез указатель Array вызываем AND:\n";
    p->add(a2);
    p->show();

    
    system("pause");
    return 0;
}
