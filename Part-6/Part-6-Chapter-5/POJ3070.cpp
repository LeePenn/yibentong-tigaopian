#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2;
LL n, m, f1, f2;

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

struct Node {
    LL g[N + 1][N + 2];
}f, ans;

void matrixI(Node &x) {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) x.g[i][j] = 1LL;
            else x.g[i][j] = 0LL;
        }
    }
}

void matrixMultiple(Node &x, Node &y, Node &z) {
    memset(z.g, 0, sizeof(z.g));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = 1; k <= N; ++k) {
                z.g[i][j] += x.g[i][k] * y.g[k][j];
                z.g[i][j] %= m;
            }
        }
    }
}

void matrixMulti(LL k) {
    matrixI(ans);
    Node tmp = f, t;
    while (k) {
        if (k & 1) {
            matrixMultiple(ans, tmp, t);
            ans = t;
        }
        matrixMultiple(tmp, tmp, t);
        tmp = t;
        k >>= 1;
    }
}

LL Solve() {
    if (n == 0) return 0LL;
    if (n == 1) return 1LL;
    matrixMulti(n - 2);
    LL res = (ans.g[1][1] * f2 + ans.g[1][2] * f1) % m;
    return res;
}

int main() {
    f1 = f2 = 1;
    m = 10000;
    while (scanf("%lld", &n) == 1 && n != -1) {
        memset(f.g, 0, sizeof(f.g));
        memset(ans.g, 0, sizeof(ans.g));
        f.g[1][1] = 1; f.g[1][2] = 1;
        f.g[2][1] = 1;
        printf("%lld\n", Solve());
    }
    
    return 0;
}