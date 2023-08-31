#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 110;
LL a[N][N], b[N][N], c[N][N];
int n, m, p;

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
    n = ReadInt(), m = ReadInt();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] = ReadLL();
        }
    }
    p = ReadInt();
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= p; ++j) {
            b[i][j] = ReadLL();
        }
    }
}

void Calc() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= p; ++j) {
            for (int k = 1; k <= m; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= p; ++j) {
            printf("%lld ", c[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Read();
    
    Calc();
    
    return 0;
}