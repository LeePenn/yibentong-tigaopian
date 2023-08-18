#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL T, a0, a1, b0, b1;
LL v[N], prime[N], tot;
LL ans;

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

void Init() {
    for (LL i = 2; i <= 46430; ++i) {
        if (!v[i]) {
            v[i] = i;
            prime[++tot] = i;
        }
        
        for (LL j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i > N) break;
            
            v[prime[j] * i] = prime[j];
        }
    }
}

void Calc(LL p) {
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    while (a0 % p == 0) {
        a0 /= p;
        t1++;
    }
    
    while (a1 % p == 0) {
        a1 /= p;
        t2++;
    }
    
    while (b0 % p == 0) {
        b0 /= p;
        t3++;
    }
    
    while (b1 % p == 0) {
        b1 /= p;
        t4++;
    }
    
    if (t1 < t2 || t2 > t4) ans = 0;
    // r = t2, r = t4
    if (t1 > t2 && t3 < t4 && t2 < t4) ans = 0;
    if (t1 == t2 && t3 == t4) ans *= (t4 - t2 + 1);
}

void Work() {
    T = ReadLL();
    while (T--) {
        ans = 1;
        a0 = ReadLL(), a1 = ReadLL(), b0 = ReadLL(), b1 = ReadLL();
        
        for (int i = 1; i <= tot && ans; ++i) {
            if (b1 % prime[i] == 0) Calc(prime[i]);
        }
        
        if (b1 > 1) Calc(b1);
        
        printf("%lld\n", ans);
    }
}

int main() {
    Init();
    
    Work();

    return 0;
}