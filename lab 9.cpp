#include <iostream>
using namespace std;

template<typename T>
class Queue {
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

public:
    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T dequeue() {
        if (head == nullptr) {
            cout << "Очередь пуста!\n";
            return T();
        }
        Node* temp = head;
        T value = head->data;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        count--;
        return value;
    }

    int size() const {
        return count;
    }

    void show() const {
        if (head == nullptr) {
            cout << "Очередь пуста\n";
            return;
        }
        cout << "Очередь: ";
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            cout << curr->data << " ";
        }
        cout << endl;
    }

    // Очистка
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    ~Queue() { clear(); }
};

int main() {
   1Queue<int> q;

    cout << "Вводи числа (0 = стоп):\n";
    int x;
    while (cin >> x && x != 0) {
        q.enqueue(x);
    }

    cout << "\nРазмер очереди: " << q.size() << endl;
    q.show();

    cout << "\nИзвлекаем элементы:\n";
    while (true) {
        int val = q.dequeue();
        if (q.size() == 0) break;
        cout << "Извлечено: " << val << endl;
    }

    cout << "\nГотово!\n";
    return 0;
}
