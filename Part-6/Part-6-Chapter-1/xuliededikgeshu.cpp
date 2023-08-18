#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int T;
LL a, b, c, k, d, Mod = 200907;

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

LL dengcha() {
    d = b - a;
    return (a + ((k - 1) * d % Mod)) % Mod;
}   

LL ksm(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = (ret * a) % Mod;
        a = (a * a) % Mod;
        b >>= 1;
    }
    
    return ret;
}

LL dengbi() {
    d = b / a;
    return (a * ksm(d, k - 1)) % Mod;
}

void Work() {
    // 不使用加速读，性能差接近8倍
    T = ReadInt();
    while (T--) {
        a = ReadLL(), b = ReadLL(), c = ReadLL(), k = ReadLL();
        if (b - a == c - b) {
            printf("%lld\n", dengcha());
        } else {
            printf("%lld\n", dengbi());
        }
    }
}   


int main() {
    Work();

    return 0;
}