 #include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int P = 2333, N = 2333 + 10;
LL T, n, k, C[N][N], f[N][N];

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
    for (int i = 0; i < N; ++i) C[i][0] = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    }
    
    for (int i = 0; i < N; ++i) f[i][0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j < N; ++j) {
            f[i][j] = (f[i][j - 1] + C[i][j]) % P;
        }
    }
}

LL Lucas(LL n, LL m) {
    if (!m) return 1;
    if (m > n) return 0;
    if (n < P && m < P) return C[n][m];
    
    return Lucas(n % P, m % P) * Lucas(n / P, m / P) % P;
}

LL Solve(LL n, LL m) {
    if (m < 0) return 0;
    if (m == 0 || n == 0) return 1;
    
    if (n < P && m < P) return f[n][m];
    
    return (f[n % P][P - 1] * Solve(n / P, m / P - 1) % P + f[n % P][m % P] * Lucas(n / P, m / P) % P) % P;
}

// 𝑓（𝑛mod𝑝，𝑝−1）×𝑓(𝑛mod𝑝,𝑘/𝑝−1)+𝐶𝑘/𝑝𝑛/𝑝×𝑓(𝑛mod𝑝,𝑘mod𝑝)
int main() {
    cin >> T;
    Init();
    while (T--) {
        cin >> n >> k;
        cout << Solve(n, k) << endl;
    }
    return 0;
}

