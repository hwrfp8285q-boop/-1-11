#include <iostream>
#include <cstdlib>

using namespace std;

struct Para {
    int first;
    int second;

    void init(int f, int s);
    void read();
    void display();
    int nod();
};

Para make_para(int a, int b) {
    if (a == 0 && b == 0) {
        cout << "Ошибка: оба числа нулевые, НОД не определён" << endl;
        exit(1);
    }
    Para c;
    c.first = a;
    c.second = b;
    return c;
}

void Para::init(int f, int s) {
    first = f;
    second = s;
}

void Para::read() {
    cout << "first: ";
    cin >> first;
    cout << "second: ";
    cin >> second;
}

void Para::display() {
    cout << "first: " << first << "\nsecond: " << second << endl;
}

int Para::nod() {
    int a = first;
    int b = second;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    int remainder = 0;
    do {
        remainder = a % b;
        a = b;
        b = remainder;
    } while (remainder != 0);
    return a;
}

int main() {
    Para x, y;

    x.read();
    x.display();
    int a = x.nod();
    cout << "\nNOD dlya " << x.first << " i " << x.second << " = " << a << endl;

    y.init(34, 25);
    y.display();
    int b = y.nod();
    cout << "\nNOD dlya " << y.first << " i " << y.second << " = " << b << endl;

    Para z = make_para(54, 9);
    z.display();
    int c = z.nod();
    cout << "\nNOD dlya " << z.first << " i " << z.second << " = " << c << endl;

    cin >> a;
    return 0;
}
