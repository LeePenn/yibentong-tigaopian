#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int T;
LL m, X, Y, D;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0, d = a;
        return;
    }
    
    Exgcd(b, a % b, d, x, y);
    LL t = x;
    x = y, y = t - a / b * y;
}

void Calc() {
    cin >> m >> D >> X >> Y;
    LL a = D, b = Y - X, d, x, y;
    Exgcd(a, m, d, x, y);
    if (b % d != 0) {
        cout << "Impossible" << endl;
        return;
    } 
    
    x = x * b / d;
    x = (x % (m / d) + (m / d)) % (m / d);
    cout << x << endl;
    
}

int main() {
    cin >> T;
    while (T--) {
        Calc();
    }
    
    return 0;
}