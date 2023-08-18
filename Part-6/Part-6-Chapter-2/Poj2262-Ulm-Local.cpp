#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, v[N], prime[N], tot;
bool isPrime[N];

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
    for (int i = 2; i < N; ++i) {
        if (!v[i]) {
            v[i] = i;
            prime[++tot] = i;
            isPrime[i] = 1;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i > N) break;
            
            v[prime[j] * i] = prime[j];
        }
    }
}

void Work() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 1; i <= tot; ++i) {
            if (isPrime[n - prime[i]]) {
                printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
                break;
            }
        }
    }
}

int main() {
    Init();
    
    Work();

    return 0;
}