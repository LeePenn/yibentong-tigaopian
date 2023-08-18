#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n, w[N], d[N];
LL sw[N], sd[N];
LL f[N], q[N];
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
        w[i] = ReadLL(), d[i] = ReadLL();
        sw[i] = sw[i - 1] + w[i];
    }
    
    for (int i = n; i >= 1; --i) {
        sd[i] = sd[i + 1] + d[i];
        f[0] += sd[i] * w[i];
    }
}   

LL Gx(int k1, int k2) {
    return sw[k1] - sw[k2];
}

LL Gy(int k1, int k2) {
    return f[k1] - f[k2];
}

LL Gv(int i, int j) {
    return f[j] - sd[i] * (sw[i] - sw[j]);
}

void DP() {
    hh = 1, tt = 1;
    LL ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; ++i) {
        f[i] = f[0] - sd[i] * sw[i];
        while (hh < tt && Gy(q[hh + 1], q[hh]) <= -sd[i] * Gx(q[hh + 1], q[hh])) hh++;
        
        if (i > 1) ans = min(ans, Gv(i, q[hh]));
        
        while (hh < tt && Gy(q[tt], q[tt - 1]) * Gx(i, q[tt]) >= 
        Gy(i, q[tt]) * Gx(q[tt], q[tt - 1])) tt--;
        
        q[++tt] = i;
    }
    
    printf("%lld\n", ans);
}

int main() {
    Read();
    
    DP();
    

    return 0;
}