#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 500 + 10;
int f[N][N], len = 1, n;

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

void Add(int u) {
    
}

int main() {
    cin >> n;
    f[1][1] = 1;
    for (int i = 2; i <= n + 1; ++i) {
        for (int j = 1; j <= i; ++j) {
            Add(j);
        }
    }
    
    return 0;
}

