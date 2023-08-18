#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 10;
LL n, L;
LL c[N], s[N], q[N], f[N];
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

void Read() {
    cin >> n >> L;
    L++;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        s[i] = s[i - 1] + c[i] + 1;
    }
}

LL Gx(int k1, int k2) {
    return s[k1] * 2 - s[k2] * 2;
}

LL Gy(int k1, int k2) {
    return (f[k1] + s[k1] * s[k1] + s[k1] * 2 * L) - (f[k2] + s[k2] * s[k2] + s[k2] * 2 * L);
}

LL Gv(int i, int j) {
    return f[j] + (s[i] - s[j] - L) * (s[i] - s[j] - L);
}

void DP() {
    hh = 1, tt = 1;
    
    for (int i = 1; i <= n; ++i) {
        
        while (hh < tt && Gy(q[hh + 1], q[hh]) <= s[i] * Gx(q[hh + 1], q[hh])) hh++;
        
        f[i] = Gv(i, q[hh]);
        
        while (hh < tt && Gx(q[tt], q[tt - 1]) * Gy(i, q[tt]) <= Gx(i, q[tt]) * 
        Gy(q[tt], q[tt - 1]))
            --tt;
            
        q[++tt] = i;
    }
    
    cout << f[n] << endl;
}

int main() {
    Read();
    
    DP();

    return 0;
}