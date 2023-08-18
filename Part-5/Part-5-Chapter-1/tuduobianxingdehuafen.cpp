#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100 + 10, BASE = 10000;

LL F[N][N][N], a[N];
LL s1[N], s2[N], s3[N];
int n;

void Read() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            F[i][j][0] = 0;
        }
    }
}

void Num2Arr(LL c[]) {
    for (int i = 1; i <= c[0]; i++) {
        c[i + 1] += c[i] / BASE;
        c[i] %= BASE;
    }
    
    while (c[c[0] + 1]) {
        ++c[0];
        c[c[0] + 1] += c[c[0]] / BASE;
        c[c[0]] %= BASE;
    }
}

void Mul(LL c1, LL c2, LL c3, LL c[]) {
    c[0] = c[1] = 1;
    for (int i = 1; i <= c[0]; ++i) c[i] *= c1;
    Num2Arr(c);
    for (int i = 1; i <= c[0]; ++i) c[i] *= c2;
    Num2Arr(c);
    for (int i = 1; i <= c[0]; ++i) c[i] *= c3;
    Num2Arr(c);
}

void Add(LL c1[], LL c2[], LL c[]) {
    c[0] = max(c1[0], c2[0]);
    for (int i = 1; i <= c[0]; i++) {
        c[i] = c1[i] + c2[i];
    }
    Num2Arr(c);
}

bool Compare(LL c1[], LL c2[]) {
    if (c2[0] < c1[0]) return true;
    if (c2[0] > c1[0]) return false;
    for (int i = c1[0]; i >= 1; --i) {
        if (c1[i] < c2[i]) return false;
        if (c1[i] > c2[i]) return true;
    }
    return false;
}

void DP() {
    for (int t = 2; t <= n - 1; ++t) {
        for (int i = 1; i + t <= n; ++i) {
            int j = i + t;
            F[i][j][0] = 60;
            for (int k = i + 1; k < j; ++k) {
                memset(s1, 0, sizeof(s1));
                memset(s2, 0, sizeof(s2));
                memset(s3, 0, sizeof(s3));
                Mul(a[i], a[k], a[j], s1);
                Add(F[i][k], F[k][j], s2);
                Add(s1, s2, s3);
                if (Compare(F[i][j], s3)) {
                    memcpy(F[i][j], s3, sizeof(s3));
                }
            }
        }
    }
}   

void Print() {
    printf("%lld", F[1][n][F[1][n][0]]);
    for (int i = F[1][n][0] - 1; i >= 1; --i) {
        printf("%lld", F[1][n][i] / 1000);
        printf("%lld", F[1][n][i] / 100 % 10);
        printf("%lld", F[1][n][i] / 10 % 10);
        printf("%lld", F[1][n][i] % 10);
    }
    
    printf("\n");
}

int main() {
    Read();
    
    DP();
    
    Print();

    return 0;
}