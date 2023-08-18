#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n;
int v[N], prime[N], tot;

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
    // pow(46340, 2) = 2147395600
    for (int i = 2; i <= 46340; ++i) {
        if (!v[i]) {
            v[i] = i;
            prime[++tot] = i;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i > 46340) break;
            v[prime[j] * i] = prime[j];
        }
    }
}

void Work() {
    n = ReadLL();
    for (int i = 1; i <= tot; ++i) {
        if (n % prime[i] == 0) {
            printf("%lld\n", n / prime[i]);
            return;
        }
    }
}

int main() {
    Init();
    
    Work();


    return 0;
}