#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

struct ComplexStruct {
    double re, im;
};

void init(ComplexStruct& c, double r, double i) { c.re = r; c.im = i; }
void read(ComplexStruct& c) { cout << "Re: "; cin >> c.re; cout << "Im: "; cin >> c.im; }
void display(const ComplexStruct& c) { cout << c.re << (c.im >= 0 ? "+" : "") << c.im << "i\n"; }
char* toString(const ComplexStruct& c, char* buf) {
    sprintf(buf, "%.2f%+.2fi", c.re, c.im);
    return buf;
}

void add(ComplexStruct& c1, const ComplexStruct& c2) { c1.re += c2.re; c1.im += c2.im; }
void sub(ComplexStruct& c1, const ComplexStruct& c2) { c1.re -= c2.re; c1.im -= c2.im; }
void mul(ComplexStruct& c1, const ComplexStruct& c2) {
    double t = c1.re * c2.re - c1.im * c2.im;
    c1.im = c1.re * c2.im + c1.im * c2.re;
    c1.re = t;
}
void div(ComplexStruct& c1, const ComplexStruct& c2) {
    double d = c2.re * c2.re + c2.im * c2.im;
    if (d < 1e-9) { cout << "Деление на 0!\n"; exit(1); }
    double t = (c1.re * c2.re + c1.im * c2.im) / d;
    c1.im = (c1.im * c2.re - c1.re * c2.im) / d;
    c1.re = t;
}
bool equ(const ComplexStruct& c1, const ComplexStruct& c2) { return fabs(c1.re - c2.re) < 1e-9 && fabs(c1.im - c2.im) < 1e-9; }
void conj(ComplexStruct& c) { c.im = -c.im; }

class Complex {
private:
    double re, im;
public:
    void init(double r, double i) { re = r; im = i; }
    void read() { cout << "Re: "; cin >> re; cout << "Im: "; cin >> im; }
    void display() const { cout << re << (im >= 0 ? "+" : "") << im << "i\n"; }
    char* toString(char* buf) const {
        sprintf(buf, "%.2f%+.2fi", re, im);
        return buf;
    }
    void add(const Complex& c) { re += c.re; im += c.im; }
    void sub(const Complex& c) { re -= c.re; im -= c.im; }
    void mul(const Complex& c) {
        double t = re * c.re - im * c.im;
        im = re * c.im + im * c.re;
        re = t;
    }
    void div(const Complex& c) {
        double d = c.re * c.re + c.im * c.im;
        if (d < 1e-9) { cout << "Деление на 0!\n"; exit(1); }
        double t = (re * c.re + im * c.im) / d;
        im = (im * c.re - re * c.im) / d;
        re = t;
    }
    bool equ(const Complex& c) const { return fabs(re - c.re) < 1e-9 && fabs(im - c.im) < 1e-9; }
    void conj() { im = -im; }
};

int main() {
    char buf[50];
    cout << "Комплексные числа\n";

    cout << "\nСтруктура:\n";
    ComplexStruct s1, s2;
    read(s1); read(s2);
    cout << "Числа: "; display(s1); display(s2);
    ComplexStruct sum_s = s1; add(sum_s, s2); cout << "Сумма: "; display(sum_s);
    ComplexStruct diff_s = s1; sub(diff_s, s2); cout << "Разность: "; display(diff_s);
    ComplexStruct prod_s = s1; mul(prod_s, s2); cout << "Произведение: "; display(prod_s);
    ComplexStruct quot_s = s1; div(quot_s, s2); cout << "Частное: "; display(quot_s);
    cout << "Равны: " << (equ(s1, s2) ? "Да" : "Нет") << "\n";
    conj(s1); cout << "Сопряжённое: "; display(s1);
    cout << "toString: " << toString(s1, buf) << "\n";

    cout << "\nКласс:\n";
    Complex c1, c2;
    c1.read(); c2.read();
    cout << "Числа: "; c1.display(); c2.display();
    Complex sum = c1; sum.add(c2); cout << "Сумма: "; sum.display();
    Complex diff = c1; diff.sub(c2); cout << "Разность: "; diff.display();
    Complex prod = c1; prod.mul(c2); cout << "Произведение: "; prod.display();
    Complex quot = c1; quot.div(c2); cout << "Частное: "; quot.display();
    cout << "Равны: " << (c1.equ(c2) ? "Да" : "Нет") << "\n";
    c1.conj(); cout << "Сопряжённое: "; c1.display();
    cout << "toString: " << c1.toString(buf) << "\n";

    system("pause");
    return 0;
}
