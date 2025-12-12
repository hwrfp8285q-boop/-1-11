#include <iostream>
#include <cstring>
using namespace std;

class PNumber {
    char num[200];
    unsigned int base;

    int get_digit(char c) const { return (c>='0'&&c<='8') ? c-'0' : -1; }
    char get_char(int d) const { return (d>=0&&d<=8) ? '0'+d : '?'; }

    long long to_decimal() const {
        long long res = 0;
        int len = strlen(num);
        for (int i = 0; i < len; ++i) {
            int d = get_digit(num[len-1-i]);
            if (d < 0 || d >= (int)base) return 0;
            res = res * base + d;
        }
        return res;
    }

    void from_decimal(long long val) {
        if (val <= 0) { strcpy(num,"0"); return; }
        char t[200]; int i=0;
        while(val>0) { t[i++]=get_char(val%base); val/=base; }
        for(int j=0; j<i; ++j) num[j]=t[i-1-j];
        num[i]='\0';
    }

    void normalize() {
        int i=0;
        while(num[i]=='0' && num[i+1]!='\0') i++;
        memmove(num, num+i, strlen(num+i)+1);
        if(num[0]=='\0') strcpy(num,"0");
    }

public:
    PNumber() : base(3) { strcpy(num,"0"); }
    PNumber(const char* s, unsigned int b=3) : base(b) {
        if(base<3||base>9) base=3;
        strcpy(num,s);
        normalize();
    }
    PNumber(const PNumber& p) : base(p.base) { strcpy(num,p.num); }

    friend PNumber operator+(const PNumber& a, const PNumber& b) {
        if(a.base != b.base) return a;
        PNumber r = a;
        r.from_decimal(a.to_decimal() + b.to_decimal());
        return r;
    }

    friend PNumber operator-(const PNumber& a, const PNumber& b) {
        if(a.base != b.base) return a;
        long long d = a.to_decimal() - b.to_decimal();
        PNumber r = a;
        r.from_decimal(d < 0 ? 0 : d);
        return r;
    }

    friend PNumber operator*(const PNumber& a, const PNumber& b) {
        if(a.base != b.base) return a;
        PNumber r = a;
        r.from_decimal(a.to_decimal() * b.to_decimal());
        return r;
    }

    friend PNumber operator/(const PNumber& a, const PNumber& b) {
        if(a.base != b.base || b.to_decimal()==0) return a;
        PNumber r = a;
        r.from_decimal(a.to_decimal() / b.to_decimal());
        return r;
    }

    friend bool operator==(const PNumber& a, const PNumber& b) {
        return a.base==b.base && a.to_decimal()==b.to_decimal();
    }
    friend bool operator>(const PNumber& a, const PNumber& b) {
        return a.base!=b.base ? a.base>b.base : a.to_decimal()>b.to_decimal();
    }

    friend ostream& operator<<(ostream& os, const PNumber& p) {
        return os << p.num << "_" << p.base;
    }

    friend istream& operator>>(istream& is, PNumber& p) {
        char s[200];
        is >> s >> p.base;
        if(p.base < 3 || p.base > 9) p.base = 3;
        strcpy(p.num, s);
        p.normalize();
        return is;
    }
};

int main() {

    PNumber a, b;
    cout << "Введите первое число и основание: ";
    cin >> a;
    cout << "Введите второе число и то же основание: ";
    cin >> b;

    cout << "\n";
    cout << a << " + " << b << " = " << (a + b) << "\n";
    cout << a << " - " << b << " = " << (a - b) << "\n";
    cout << a << " * " << b << " = " << (a * b) << "\n";
    cout << a << " / " << b << " = " << (a / b) << "\n";

    cout << "\n" << a << " == " << b << " ? " << (a==b?"Да":"Нет") << "\n";
    cout << a << " > " << b << " ? " << (a>b?"Да":"Нет") << "\n";

    return 0;
}
