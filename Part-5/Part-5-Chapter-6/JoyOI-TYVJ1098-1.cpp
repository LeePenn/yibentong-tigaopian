#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5000 + 5;
int n, S, t[N], c[N];
int sumT[N], sumC[N];
int f[N];

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
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            f[i] = min(f[i], f[j] + sumT[i] * (sumC[i] - sumC[j]) + S * (sumC[n] - sumC[j]));
        }
    }
    
    printf("%d\n", f[n]);
}

int main() {
    Read();
    
    DP();

    return 0;
}