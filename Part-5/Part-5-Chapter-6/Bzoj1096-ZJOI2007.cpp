#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n;
LL p[N], c[N], sd[N], sp[N], sps[N], q[N], f[N];
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
    for (int i = 1; i <= n; ++i) {
        sd[i] = ReadLL(), p[i] = ReadLL(), c[i] = ReadLL();
        sp[i] = sp[i - 1] + p[i];
        sps[i] = sps[i - 1] + p[i] * sd[i];
    }
}   

LL Gx(int k1, int k2) {
    return sp[k1] - sp[k2];
}

LL Gy(int k1, int k2) {
    return (f[k1] + sps[k1]) - (f[k2] + sps[k2]);
}

LL Gv(int i, int j) {
    return f[j] + c[i] + sd[i] * (sp[i] - sp[j]) - (sps[i] - sps[j]);
}

void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    hh = 1, tt = 1;
    for (int i = 1; i <= n; ++i) {
        while (hh < tt && Gy(q[hh + 1], q[hh]) <= sd[i] * Gx(q[hh + 1], q[hh])) hh++;
        
        f[i] = Gv(i, q[hh]);
        
        while (hh < tt && Gy(q[tt], q[tt - 1]) * Gx(i, q[tt]) >= Gy(i, q[tt]) * Gx(q[tt], q[tt - 1])) tt--;
        
        q[++tt] = i;
    }
    
    printf("%lld\n", f[n]);
}

int main() {
    Read();
    
    DP();

    return 0;
}