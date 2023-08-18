#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL p[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
LL n;
LL ans, s;

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
        if (b & 1) ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}

void DFS(LL dep, LL j, LL num, LL cnt) {
    if (dep > 10) return;
    
    LL k = 1;
    for (LL i = 1; i <= j; ++i) {
        k *= p[dep];
        if (num * k > n) return;
        
        if (cnt * (i + 1) > s || (cnt * (i + 1) == s && num * k < ans)) {
            ans = num * k;
            s = cnt * (i + 1);
        }
        
        DFS(dep + 1, i, num * k, cnt * (i + 1));
    }
}

void Work() {
    n = ReadLL();
    
    DFS(1, 31, 1, 1);
    
    printf("%lld\n", ans);
}

int main() {
    Work();

    return 0;
}