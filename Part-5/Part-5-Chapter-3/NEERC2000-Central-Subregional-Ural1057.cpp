#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int f[N][N];
int l, r, k, b;
int num[N];

void Read() {
    cin >> l >> r >> k >> b;
    f[0][0] = 1;
    for (int i = 1; i <= 32; ++i) {
        f[i][0] = f[i - 1][0];
        for (int j = 1; j <= i; ++j) {
            f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
        }
    }
}

int Calc(int n) {
    if (n == 0) return 0;
    
    int cnt = 0;
    while (n) {
        num[++cnt] = n % b;
        n /= b;
    }
    
    int ans = 0, tot = 0;
    for (int i = cnt; i >= 1; --i) {
        if (num[i] != 0) {
            if (num[i] == 1) {
                ans += f[i - 1][k - tot];
                if (tot == k) break;
                tot++;
            } else {
                ans += f[i - 1][k - tot];
                if (k - 1 - tot > 0) {
                    ans += f[i - 1][k - 1 - tot];
                }
                break;
            }
        }
        if (i == 1 && tot == k) ans++;
    }
    
    return ans;
}

int main() {
    Read();
    printf("%d\n", Calc(r) - Calc(l - 1));
    
    return 0;
}