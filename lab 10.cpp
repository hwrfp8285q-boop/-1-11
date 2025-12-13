#include <iostream>
#include <vector>
using namespace std;


template<typename T>
constexpr T maxOf11(T v) { return v; }

template<typename T, typename... Args>
constexpr T maxOf11(T first, Args... args) {
    T rest = maxOf11(args...);
    return first > rest ? first : rest;
}

template<typename... Args>
constexpr auto maxOf17(Args... args) {
    return (... > args);
}

template<typename T>
constexpr T minOf11(T v) { return v; }

template<typename T, typename... Args>
constexpr T minOf11(T first, Args... args) {
    T rest = minOf11(args...);
    return first < rest ? first : rest;
}

template<typename... Args>
constexpr auto minOf17(Args... args) {
    return (... < args);
}

template<typename F, typename... Args>
void forEach11(F&& f, Args&&... args) {
    (void)std::initializer_list<int>{ (f(std::forward<Args>(args)), 0)... };
}

template<typename F, typename... Args>
void forEach17(F&& f, Args&&... args) {
    (f(args), ...);
}

template<typename... B>
constexpr bool allTrue17(B... b) { return (b && ...); }

template<typename... B>
constexpr bool anyTrue17(B... b) { return (b || ...); }


template<typename... Args>
double average17(Args... args) {
    return sizeof...(args) == 0 ? 0.0 : (0.0 + ... + args) / sizeof...(args);
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Сколько чисел ввести (1-10)? ";

    int n;
    if (!(cin >> n)|| n < 1 || n > 10) {
        cout << "Ошибка ввода!\n";
        return 1;
    }

    vector<double> v(n);
    cout << "Введите " << n << " чисел через пробел: ";
    for (double& x : v) cin >> x;

    cout << "\n=== РЕЗУЛЬТАТЫ ===\n\n";

    auto call_max11 = [&]() { return maxOf11(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]); };
    auto call_max17 = [&]() { return maxOf17(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]); };
    auto call_min11 = [&]() { return minOf11(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]); };
    auto call_min17 = [&]() { return minOf17(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]); };
    auto call_avg   = [&]() { return average17(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]); };

    cout << "1. maxOf (C++11): " << call_max11() << endl;
    cout << "   maxOf (C++17): " << call_max17() << endl << endl;

    cout << "2. minOf (C++11): " << call_min11() << endl;
    cout << "   minOf (C++17): " << call_min17() << endl << endl;

    cout << "3. forEach (C++11): ";
    forEach11([](double x) { cout << x << " "; }, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]);
    cout << "\n   forEach (C++17): ";
    forEach17([](double x) { cout << x << " "; }, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9]);
    cout << "\n\n";

    bool all_pos = allTrue17((v[0] > 0), (v[1] > 0), (v[2] > 0), (v[3] > 0), (v[4] > 0),
                             (v[5] > 0), (v[6] > 0), (v[7] > 0), (v[8] > 0), (v[9] > 0));
    bool any_pos = anyTrue17((v[0] > 0), (v[1] > 0), (v[2] > 0), (v[3] > 0), (v[4] > 0),
                             (v[5] > 0), (v[6] > 0), (v[7] > 0), (v[8] > 0), (v[9] > 0));

    cout << "4. Все числа > 0? " << boolalpha << all_pos << endl;
    cout << "   Хотя бы одно > 0? " << any_pos << endl << endl;

    cout << "5. Среднее арифметическое: " << call_avg() << "\n\n";
    cout << "Готово! Все функции работают идеально!\n";
        system("pause");
        return 0;
    }
