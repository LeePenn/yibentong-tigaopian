#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL n, m;
LL mod = 100003;

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
    m = ReadLL(), n = ReadLL();
}

LL ksm(LL a, LL b, LL m) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = (ret * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    
    return ret;
}

void Work() {
    // m ^ n - m * ((m - 1) ^ n - 1)
    printf("%lld\n", (ksm(m, n, mod) - ((m * ksm(m - 1, n - 1, mod)) % mod) + mod) % mod);
}

int main() {
    Read();
    
    Work();


    return 0;
}