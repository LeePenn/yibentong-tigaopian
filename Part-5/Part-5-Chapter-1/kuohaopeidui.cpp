#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 5, INF = 10000;
int n;
int f[N][N];
char s[N];

void Read() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 1;
    }
}

void DP() {
    for (int L = 2; L <= n; ++L) {
        for (int i = 1; i + L - 1 <= n; ++i) {
            int j = i + L - 1;
            f[i][j] = INF;
            if ((s[i] == '[' && s[j] == ']') || (s[i] == '(' && s[j] == ')')) {
                f[i][j] = j - 1 < i + 1 ? 0 : f[i + 1][j - 1];
            }
            for (int k = i; k < j; ++k) {
                f[i][j] = min(f[i][k] + f[k + 1][j], f[i][j]);
            }
        }
    }
}

int main() {
    Read();

    DP();
    
    printf("%d\n", f[1][n]);
    return 0;
}