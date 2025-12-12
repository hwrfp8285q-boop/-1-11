#include <iostream>
#include <string>
using namespace std;

class Car {
protected:
    string brand;
    int cylinders;
    double power;
public:
    Car() : brand("Unknown"), cylinders(4), power(100) {}
    Car(string b, int c, double p) : brand(b), cylinders(c), power(p) {
        if (c <= 0 || p <= 0) { cout << "Ошибка в машине!\n"; exit(1); }
    }

    void input() {
        cout << "Марка машины: "; cin >> brand;
        cout << "Кол-во цилиндров: "; cin >> cylinders;
        cout << "Мощность (л.с.): "; cin >> power;
        if (cylinders <= 0 || power <= 0) { cout << "Ошибка!\n"; exit(1); }
    }

    void setPower(double p) { if (p > 0) power = p; else exit(1); }

    void show() const {
        cout << "Машина: " << brand << ", цилиндры: " << cylinders << ", мощность: " << power << " л.с.\n";
    }

    string getBrand() const { return brand; }
};

class Lorry : public Car {
    double loadCapacity;
public:
    Lorry() : Car(), loadCapacity(0) {}
    Lorry(string b, int c, double p, double l) : Car(b, c, p), loadCapacity(l) {
        if (l < 0) { cout << "Ошибка грузоподъёмности!\n"; exit(1); }
    }

    void input() {
        Car::input();
        cout << "Грузоподъёмность (тонн): "; cin >> loadCapacity;
        if (loadCapacity < 0) { cout << "Ошибка!\n"; exit(1); }
    }

    void show() const {
        Car::show();
        cout << "Грузоподъёмность: " << loadCapacity << " тонн\n\n";
    }
};

int main() {
    cout << "Лабораторная №1:\n";

    Car car;
    Lorry truck;

    cout << "Ввод обычной машины:\n";
    car.input();

    cout << "\nВвод грузовика:\n";
    truck.input();

    cout << "\n--- Результат ---\n";
    car.show();
    truck.show();

    Car* ptr = &truck;
    cout << "Через указатель на Car:\n";
    ptr->show();

    system("pause");
    return 0;
}
