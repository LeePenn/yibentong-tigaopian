#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000 + 4, P = 10007;
LL a, b, k, n, m;
LL c[N][N];

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
    for (int i = 1; i <= k; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j <= i - 1; ++j) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
        }
    }
}

int main() {
    cin >> a >> b >> k >> n >> m;
    Init();
    a = a % P, b = b % P;
    LL ans = c[k][m];
    LL ansa = 1, ansb = 1;
    for (int i = 1; i <= n; ++i) ansa = (ansa * a) % P;
    for (int i = 1; i <= m; ++i) ansb = (ansb * b) % P;
    ans = (ans * ansa) % P * ansb % P;
    cout << ans << endl;    
    
    return 0;
}

