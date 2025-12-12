#include <iostream>
#include <cstring>
using namespace std;

class PNumber {
    char num[200];
    unsigned int base;

    long long to_dec() const {
        long long res = 0;
        for (int i = 0; num[i]; ++i) {
            int d = num[i] - '0';
            if (d < 0 || d >= (int)base) return 0;
            res = res * base + d;
        }
        return res;
    }

    void from_dec(long long v) {
        if (v == 0) { strcpy(num, "0"); return; }
        char t[200]; int i = 0;
        while (v) { t[i++] = '0' + (v % base); v /= base; }
        for (int j = 0; j < i; ++j) num[j] = t[i-1-j];
        num[i] = '\0';
    }

public:
    // 1. По умолчанию
    PNumber() : base(3) { strcpy(num, "0"); cout << "Конструктор по умолчанию\n"; }

    // 2. Инициализации
    PNumber(const char* s, unsigned int b = 3) : base(b) {
        if (base < 3 || base > 9) base = 3;
        strcpy(num, s); cout << "Конструктор инициализации: " << num << " (base " << base << ")\n";
    }

    // 3. Копирования
    PNumber(const PNumber& p) : base(p.base) {
        strcpy(num, p.num); cout << "Конструктор копирования\n";
    }

    void add(const PNumber& p) { if (base == p.base) from_dec(to_dec() + p.to_dec()); }
    void sub(const PNumber& p) { if (base == p.base) from_dec(to_dec() - p.to_dec() < 0 ? 0 : to_dec() - p.to_dec()); }
    void mul(const PNumber& p) { if (base == p.base) from_dec(to_dec() * p.to_dec()); }
    void div(const PNumber& p) { if (base == p.base && p.to_dec()) from_dec(to_dec() / p.to_dec()); }

    bool equal(const PNumber& p) const { return base == p.base && to_dec() == p.to_dec(); }
    bool greater(const PNumber& p) const { return base == p.base && to_dec() > p.to_dec(); }

    void show() const { cout << num << " (base " << base << ")\n"; }
};

int main() {
    PNumber a;
    PNumber b("123", 5);
    PNumber c = b;
    PNumber d(b);

    PNumber arr[2];
    arr[0] = PNumber("20", 6);

    a.show(); b.show(); c.show(); arr[0].show();

    // тесты операций
    PNumber x("20", 5), y("3", 5);
    x.add(y); x.show();  

    system("pause");
    return 0;
}
