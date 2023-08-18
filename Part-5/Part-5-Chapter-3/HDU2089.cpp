#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 15;
LL n, m;
LL f[N][N];
vector<int> num;

void init() {
    for (int j = 0; j < 10; ++j) 
        if (j != 4) f[1][j]++;

    for (int i = 2; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                if (j != 4 && k != 4 && j != 6) {
                    f[i][j] += f[i - 1][k];
                } else if (j == 6 && k != 2) {
                    f[i][j] += f[i - 1][k];
                }
            }
        }
    }
}

LL DP(LL x) {
    if (!x) return 1;
    
    num.clear();
    while (x) {
        num.push_back(x % 10);
        x /= 10;
    }
    
    LL ans = 0;
    LL last = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int c = num[i];
        for (int j = 0; j < c; ++j) {
            if (last == 6 && j == 2) continue;
            if (j == 4) continue;
            ans += f[i + 1][j];
        }
        
        if (c == 4) break;
        
        if (last == 6 && c == 2) break;
        
        last = c;
        
        if (!i) ans++;
    }
    
    return ans;
}

int main() {
    init();
    while (scanf("%lld%lld", &n, &m) == 2 && (n || m)) {
        printf("%lld\n", DP(m) - DP(n - 1));
    }
    
    return 0;
}
