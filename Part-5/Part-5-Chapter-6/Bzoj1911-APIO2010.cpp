#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n;
LL a, b, c;
LL x[N], s[N], f[N], q[N];
int hh, tt;

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

void Read() {
    // 不使用加速读，性能差接近8倍
    n = ReadLL();
    a = ReadLL(), b = ReadLL(), c = ReadLL();
    for (int i = 1; i <= n; ++i) {
        x[i] = ReadLL();
        s[i] = s[i - 1] + x[i];
    }
}   

LL Gx(int k1, int k2) {
    return s[k1] - s[k2];
}

LL Gy(int k1, int k2) {
    return (f[k1] + a * s[k1] * s[k1] - b * s[k1]) - (f[k2] + a * s[k2] * s[k2] - b * s[k2]);
}

LL Gv(int i, int j) {
    return f[j] + a * (s[i] - s[j]) * (s[i] - s[j]) + b * (s[i] - s[j]) + c;
}

void DP() {
    f[0] = 0;
    hh = 1, tt = 1;
    for (int i = 1; i <= n; ++i) {
        // a < 0 不等号取反
        while (hh < tt && Gy(q[hh + 1], q[hh]) > 2 * a * s[i] * Gx(q[hh + 1], q[hh])) hh++;
        
        f[i] = Gv(i, q[hh]);
        // a < 0 不等号取反
        while (hh < tt && Gy(q[tt], q[tt - 1]) * Gx(i, q[tt]) < Gy(i, q[tt]) * Gx(q[tt], q[tt - 1])) tt--;
        
        q[++tt] = i;
    }
    
    printf("%lld\n", f[n]);
}

int main() {
    Read();
    
    DP();

    return 0;
}