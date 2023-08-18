#include <bits/stdc++.h>
using namespace std;
const int N = 13, MOD = 100 + 3;
int a, b, mod;
int f[N][N][MOD];
vector<int> num;

int Mod(int x, int y) {
    return (x % y + y) % y;
}

void init() {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < 10; ++i) f[1][i][i % mod]++;
    
    for (int i = 2; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < mod; ++k) {
                for (int j1 = 0; j1 < 10; ++j1) {
                    f[i][j][k] += f[i - 1][j1][Mod(-j + k, mod)];
                }
            }
        }
    }
}

int DP(int x) {
    if (!x) return 1;
    
    num.clear();
    while (x) {
        num.push_back(x % 10);
        x /= 10;
    }
    
    int ans = 0;
    int last = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int c = num[i];
        for (int j = 0; j < c; ++j) {
            ans += f[i + 1][j][Mod(-last, mod)];
        }
        
        last += c;
        if (!i && !Mod(last, mod)) ans++;
    }
    return ans;
}

int main() {
    
    while (scanf("%d%d%d", &a, &b, &mod) == 3) {
        init();
        
        printf("%d\n", DP(b) - DP(a - 1));
    }

    return 0;
}