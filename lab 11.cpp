#include <iostream>
#include <array>
#include <string_view>
#include <algorithm>
#include <cmath>
using namespace std;

constexpr auto is_prime = [](int n) constexpr -> bool {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
};

constexpr auto gcd = [](int a, int b) constexpr -> int {
    a = a < 0 ? -a : a; b = b < 0 ? -b : b;
    while (b) { int t = b; b = a % b; a = t; }
    return a;
};

constexpr auto lcm = [](int a, int b) constexpr -> int {
    return a / gcd(a, b) * b;
};

constexpr auto fib = [](int n) constexpr -> long long {
    if (n <= 1) return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) { long long c = a + b; a = b; b = c; }
    return b;
};

constexpr auto binom = [](int n, int k) constexpr -> long long {
    if (k < 0 || k > n) return 0;
    k = min(k, n - k);
    long long res = 1;
    for (int i = 1; i <= k; ++i) { res *= (n - k + i); res /= i; }
    return res;
};

constexpr auto is_palindrome_num = [](int n) constexpr -> bool {
    if (n < 0) return false;
    int rev = 0, x = n;
    while (x > 0) { rev = rev * 10 + x % 10; x /= 10; }
    return rev == n;
};

constexpr auto sin_approx = [](double x) constexpr -> double {
    double res = x, term = x;
    for (int i = 1; i < 10; ++i) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        res += term;
    }
    return res;
};

constexpr auto c_to_f = [](double c) constexpr { return c * 9.0 / 5.0 + 32.0; };
constexpr auto f_to_c = [](double f) constexpr { return (f - 32.0) * 5.0 / 9.0; };

constexpr auto str_hash = [](string_view s) constexpr -> unsigned long long {
    unsigned long long h = 5381;
    for (char c : s) h = ((h << 5) + h) + static_cast<unsigned char>(c);
    return h;
};

constexpr auto is_palindrome_str = [](string_view s) constexpr -> bool {
    size_t l = 0, r = s.size();
    while (l < r) if (s[l++] != s[--r]) return false;
    return true;
};

constexpr auto reverse_str = [](string_view s) constexpr {
    array<char, 100> buf{};
    size_t i = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it)
        if (i < buf.size() - 1) buf[i++] = *it;
    buf[i] = '\0';
    return string_view(buf.data(), i);
};

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "выберите задание (1-11):\n"
    << "1. Простое число\n2. НОД\n3. НОК\n4. Фибоначчи\n"
    << "5. C(n,k)\n6. Число-палиндром\n7. sin(x)\n"
    << "8. Температура\n9. Хеш строки\n10. Палиндром строки\n"
    << "11. Реверс строки\n"
    << "Ваш выбор: ";
    
    int choice;
    cin >> choice;
    cout << "\n";
}
