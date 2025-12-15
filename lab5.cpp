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

    friend istream& operator>>(istream& in, Car& c) {
        cout << "Марка машины: ";
        in >> c.brand;
        cout << "Кол-во цилиндров: ";
        in >> c.cylinders;
        cout << "Мощность (л.с.): ";
        in >> c.power;

        if (c.cylinders <= 0 || c.power <= 0) {
            cout << "Ошибка!\n";
            exit(1);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Car& c) {
        out << "Машина: " << c.brand
            << ", цилиндры: " << c.cylinders
            << ", мощность: " << c.power << " л.с.\n";
        return out;
    }

    virtual ~Car() {}
};

class Lorry : public Car {
    double loadCapacity;

public:
    Lorry() : Car(), loadCapacity(0) {}

    // ОПЕРАЦИЯ ВВОДА
    friend istream& operator>>(istream& in, Lorry& l) {
        in >> static_cast<Car&>(l);
        cout << "Грузоподъёмность (тонн): ";
        in >> l.loadCapacity;

        if (l.loadCapacity < 0) {
            cout << "Ошибка!\n";
            exit(1);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Lorry& l) {
        out << static_cast<const Car&>(l);
        out << "Грузоподъёмность: " << l.loadCapacity << " тонн\n";
        return out;
    }
};

int main() {
    Car car;
    Lorry truck;

    cout << "Ввод обычной машины:\n";
    cin >> car;

    cout << "\nВвод грузовика:\n";
    cin >> truck;

    cout << "\nОбычная машина:\n";
    cout << car;

    cout << "\nГрузовик:\n";
    cout << truck;

    Car* ptr = &truck;
    cout << "\nЧерез указатель на Car:\n";
    cout << *ptr;

    return 0;
}

