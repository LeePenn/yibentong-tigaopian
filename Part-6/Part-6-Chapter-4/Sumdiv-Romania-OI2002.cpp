#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 50000, MOD = 9901;
LL A, B;
LL p[N], v[N], tot, a[N], c[N], m;

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

LL ksm(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

void Init() {
    for (int i = 2; i < N; ++i) {
        if (!v[i]) {
            v[i] = i;
            p[++tot] = i;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (p[j] > v[i] || p[j] * i >= N) break;
            
            v[p[j] * i] = p[j];
        }
    }
}

void Div() {
    for (int i = 1; i <= tot; ++i) {
        if (p[i] > A) break;
        if (A % p[i] == 0) {
            c[++m] = 0;
            a[m] = p[i];
            while (A % p[i] == 0) {
                c[m]++;
                A /= p[i];
            }
        }
    }
    if (A > 1) {
        c[++m] = 1;
        a[m] = A;
    }
}

void Calc() {
    LL ans = 1;
    for (int i = 1; i <= m; ++i) {
        if ((a[i] - 1) % MOD == 0) {
            ans = ((c[i] * B + 1) % MOD) * ans % MOD;
            continue;
        }
        
        LL t1 = (ksm(a[i], c[i] * B + 1) - 1 + MOD) % MOD;
        LL t2 = ksm(a[i] - 1, MOD - 2) % MOD;
        ans = ans * t1 % MOD * t2 % MOD;
    }
    
    cout << ans << endl;
}

int main() {
    Init();
    cin >> A >> B;
    Div();
    
    Calc();
    
    return 0;
}