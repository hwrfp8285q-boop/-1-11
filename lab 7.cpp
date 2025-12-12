#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <locale>
using namespace std;

class BadTriangle {};

struct TriangleErrorInfo {
    double a, b, c;
    string message;
    TriangleErrorInfo(double aa, double bb, double cc, const string& msg)
        : a(aa), b(bb), c(cc), message(msg) {}
};

class TriangleException : public std::logic_error {
public:
    double a, b, c;
    TriangleException(double aa, double bb, double cc, const string& msg)
        : logic_error(msg), a(aa), b(bb), c(cc) {}
};

double area_no_spec(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) throw BadTriangle();
    if (a + b <= c || a + c <= b || b + c <= a) throw BadTriangle();
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_noexcept(double a, double b, double c) noexcept {
    if (a <= 0 || b <= 0 || c <= 0) {
        cerr << "ОШИБКА: стороны <= 0 — нарушение noexcept! Вызов std::terminate()\n";
        std::terminate();
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        cerr << "ОШИБКА: неравенство треугольника — нарушение noexcept! Вызов std::terminate()\n";
        std::terminate();
    }
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_std(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw std::invalid_argument("Все стороны должны быть положительными");
    if (a + b <= c || a + c <= b || b + c <= a)
        throw std::invalid_argument("Нарушено неравенство треугольника");
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_empty(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) throw BadTriangle();
    if (a + b <= c || a + c <= b || b + c <= a) throw BadTriangle();
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_with_data(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw TriangleErrorInfo(a, b, c, "Нулевая или отрицательная сторона");
    if (a + b <= c || a + c <= b || b + c <= a)
        throw TriangleErrorInfo(a, b, c, "Треугольник с такими сторонами не существует");
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double area_inherited(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0)
        throw TriangleException(a, b, c, "Стороны должны быть положительными");
    if (a + b <= c || a + c <= b || b + c <= a)
        throw TriangleException(a, b, c, "Нарушено неравенство треугольника");
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a, b, c;

    cout << "Задача: площадь треугольника по формуле Герона\n\n";
    cout << "Введите три стороны треугольника: ";
    cin >> a >> b >> c;

    cout << "\n" << string(60, '=') << "\n";
    cout << string(60, '=') << "\n\n";

    try {
        cout << " Без спецификации: площадь = " << area_no_spec(a, b, c) << endl;
    } catch (const BadTriangle&) {
        cout << "ОШИБКА: поймано пустое собственное исключение\n";
    }

    cout << "noexcept (аналог throw()): ";
    try {
        area_noexcept(a, b, c);
        cout << "выполнилось успешно\n";
    } catch (...) {
        cout << "программа уже упала (terminate)\n";
    }

    try {
        cout << " Стандартное исключение: площадь = " << area_std(a, b, c) << endl;
    } catch (const std::invalid_argument& e) {
        cout << " ОШИБКА: " << e.what() << "\n";
    }

    try {
        cout << " Пустое собственное: площадь = " << area_empty(a, b, c) << endl;
    } catch (const BadTriangle&) {
        cout << " ОШИБКА: поймано пустое исключение\n";
    }

    try {
        cout << " Исключение с данными: площадь = " << area_with_data(a, b, c) << endl;
    } catch (const TriangleErrorInfo& e) {
        cout << "ОШИБКА: " << e.message << " (a=" << e.a << " b=" << e.b << " c=" << e.c << ")\n";
    }

   try {
        cout << " Наследник от logic_error: площадь = " << area_inherited(a, b, c) << endl;
    } catch (const TriangleException& e) {
        cout << " ОШИБКА: " << e.what() << " (a=" << e.a << " b=" << e.b << " c=" << e.c << ")\n";
    } catch (const std::exception& e) {
        cout << " Поймано через базовый класс: " << e.what() << "\n";
    }

    system("pause");
    return 0;
}
