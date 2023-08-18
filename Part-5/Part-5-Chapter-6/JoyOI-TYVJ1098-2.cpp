#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 3e6 + 10;
LL n, S, t[N], c[N];
LL sumT[N], sumC[N];
LL f[N], q[N];

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
    cin >> n >> S;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        sumT[i] = sumT[i - 1] + t[i];
        sumC[i] = sumC[i - 1] + c[i];
    }
}

void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    int hh = 1, tt = 1;
    q[1] = 0;
    for (int i = 1; i <= n; ++i) {
        while (hh < tt && (f[q[hh + 1]] - f[q[hh]]) <= 
        (S + sumT[i]) * (sumC[q[hh + 1]] - sumC[q[hh]])) hh++;
        
        f[i] = f[q[hh]] - (S + sumT[i]) * sumC[q[hh]] + sumT[i] * sumC[i] + S * sumC[n];
        
        while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (sumC[i] - sumC[q[tt]]) >= 
        (f[i] - f[q[tt]]) * (sumC[q[tt]] - sumC[q[tt - 1]])) tt--;
        
        q[++tt] = i;
    }
    
    printf("%lld\n", f[n]);
}

int main() {
    Read();
    
    DP();

    return 0;
}