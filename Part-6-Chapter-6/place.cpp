#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2000 + 5, P = 1e5 + 3;
LL a, b, c, d, k, num[N], C[N][N];
LL f[N][N];

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
    C[0][0] = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    }
    // printf("$$ %lld\n", C[3][2]);
    
    for (int i = 1; i <= b + d; ++i) {
        if (i <= b) num[i] = a;
        else num[i] = a + c;
    }
}

void DP() {
    f[0][0] = 1;
    for (int i = 1; i <= b + d; ++i) {
        for (int j = 0; j <= i; ++j) {
            f[i][j] = f[i - 1][j];
            if (num[i] >= j - 1) {
                f[i][j] = (f[i][j] + f[i - 1][j - 1] * C[num[i] - (j - 1)][1]) % P;
            }
            
            // printf("## i = %d, j = %d, f[i][j] = %lld\n", i, j, f[i][j]);
        }
    }
    
    cout << f[b + d][k] << endl;
}

int main() {
    cin >> a >> b >> c >> d >> k;
    Init();
    DP();
    
    return 0;
}

