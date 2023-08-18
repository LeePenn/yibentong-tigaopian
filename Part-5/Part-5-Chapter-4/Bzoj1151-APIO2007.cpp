#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e4 + 10;
LL n, m;
LL f[N][40], ans;
LL num[N][40];

void Init() {
    cin >> n >> m;
    LL x, y, z, t, a, b;
    
    for (LL i = 1; i <= m; ++i) {
        a = b = 0;
        cin >> x >> y >> z;
        // not like
        for (LL j = 1; j <= y; ++j) {
            cin >> t;
            t = (t - x + n) % n;
            a |= (1 << (4 - t));
        }
        // like
        for (LL j = 1; j <= z; ++j) {
            cin >> t;
            t = (t - x + n) % n;
            b |= (1 << (4 - t));
        }
        // 1 => open, 0 => close
        for (LL j = 0; j < 32; ++j) {
            if ((a & (~j)) || (b & j)) {
                num[x][j]++;
            }
        }
    }
}

void DP() {
    for (LL i = 0; i < 32; ++i) {
        memset(f[0], -0x3f, sizeof(f[0]));
        f[0][i] = 0;
        
        for (LL j = 1; j <= n; ++j) {
            for (LL k = 0; k < 32; ++k) {
                f[j][k] = max(f[j - 1][(k >> 1) | (1 << 4)], f[j - 1][k >> 1]) + num[j][k];
            }
        }
        
        ans = max(f[n][i], ans);
    }
    
    printf("%lld\n", ans);
}

/*
观察到 一个小朋友只能观察5个围栏 那么我们状压
dp[i][s] 表示 从围栏 1- i [i-i+4] 的围栏移走状态为 s 所能收获的最大满意人数
num[i][s] 表示 围栏 从 i 开始的5个围栏移走状态为s的满意人数
预处理 num[i][s]
转移显然
dp[i][s]=max(dp[i−1][(s&15)<<1],dp[i−1][(s&15)<<1|1])+num[i][s]
即枚举 i-1 个围栏放不放
要注意的是在dp之前先枚举前五个的状态state，
因为围栏是一个环，最后枚举第n+1个围栏时，其实就相当于又回到了第一个围栏，
那么此时必须满足s=state才是有效状态，更新答案。
*/
int main() {
    Init();

    DP();
}