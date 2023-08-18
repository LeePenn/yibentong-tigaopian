#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL a, b, mod;

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
    a = ReadLL(), b = ReadLL(), mod = ReadLL();
}

LL ksm(LL a, LL b, LL m) {
    LL ret = 1;

    while (b) {
        if (b & 1)
            ret = (ret * a) % m;

        a = (a * a) % m;
        b >>= 1;
    }

    return ret;
}

int main() {
    Read();

    printf("%lld\n", ksm(a, b, mod));


    return 0;
}