#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long double lond;
bool Mbegin;
void File_Work() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
}
namespace Fast_In_Out {
char buf[1 << 21], *P1 = buf, *P2 = buf;
#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
int read() {
    int f = 1, x = 0;
    char c = gc;

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;

        c = gc;
    }

    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = gc;
    }

    return f * x;
}
void write(int x) {
    if (x < 0)
        x = -x, putchar('-');

    if (x > 9)
        write(x / 10);

    putchar(x % 10 + '0');
}
#undef gc
}
using namespace Fast_In_Out;
/*
求出p的前缀和数组sump，预处理x[i]*p[i]的前缀和sxp。
考虑DP，设dp[i]为在i处建仓库时，处理完[1,i]的最小总代价。
转移：dp[i]=min(0≤j<i)(dp[j]+x[i]*(sump[i]-sump[j])-(sxp[i]-sxp[j]))+c[i]。
若决策j优于k，则有：((dp[j]+sxp[j])-(dp[k]+sxp[k]))/(sump[j]-sump[k])<x[i]。
斜率优化，单调队列维护下凸包即可，时间复杂度O(n)。
注意若最后几处没有货物，不一定要在n处建立仓库。
应该从n往前找，直到找到p[i]≠0处，记为pos。
最终答案为min(pos≤i≤n)dp[i]。
*/
const int N = 1e6 + 7;
const lond oo = 1e18 + 7;
int n, x[N], p[N], c[N], sump[N], sxp[N];
int dp[N], que[N], hd, tl, pos, ans;
int getx(int i) {
    return sump[i];
}
int gety(int i) {
    return dp[i] + sxp[i];
}
lond getslope(int i, int j) {
    if (getx(i) == getx(j))
        return oo;

    lond dx = getx(i) - getx(j);
    lond dy = gety(i) - gety(j);
    return dy / dx;
}
bool Mend;
signed main() {
    //  File_Work();
    fprintf(stderr, "%.3lf MB\n\n\n", (&Mbegin - &Mend) / 1048576.0);
    n = read();

    for (int i = 1; i <= n; i++) {
        x[i] = read(), p[i] = read(), c[i] = read();
        sump[i] = sump[i - 1] + p[i];
        sxp[i] = sxp[i - 1] + x[i] * p[i];
    }

    hd = tl = 1;

    for (int i = 1; i <= n; i++) {
        while (hd < tl && getslope(que[hd], que[hd + 1]) <= 1.0 * x[i])
            hd++;

        dp[i] = dp[que[hd]] + x[i] * (sump[i] - sump[que[hd]]) - (sxp[i] - sxp[que[hd]]) + c[i];

        while (hd < tl && getslope(que[tl - 1], que[tl]) >= getslope(que[tl], i))
            tl--;

        que[++tl] = i;
    }

    pos = n;
    ans = oo;

    while (p[pos] == 0 && pos > 0)
        pos--;

    if (pos == 0)
        putchar('0');
    else {
        for (int i = pos; i <= n; i++)
            ans = min(ans, dp[i]);

        write(ans);
    }

    fprintf(stderr, "\n\n\n%.0lf ms", 1e3 * clock() / CLOCKS_PER_SEC);
    return 0;
}