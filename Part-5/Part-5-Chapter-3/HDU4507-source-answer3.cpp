#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 25;
const ll MOD = 1000000007;

struct Node {
    ll sum, sumpow, cnt;
    Node(ll sum = 0, ll sumpow = 0, ll cnt = 0):
        sum(sum), sumpow(sumpow), cnt(cnt) {}
};

int num[MAXN];
ll p[MAXN];
Node f[MAXN][MAXN][MAXN][2];

inline Node dfs(int pos, int sum, int now, bool limit) {
    Node &ans = f[pos][sum][now][limit];

    if (ans.cnt != -1)
        return ans;

    if (pos == 0)
        return (sum && now) ? Node(0, 0, 1) : Node(0, 0, 0);

    ans = Node(0, 0, 0);
    int up = limit ? num[pos] : 9;

    for (int i = 0; i <= up; ++i) {
        if (i == 7)
            continue;

        Node t = dfs(pos - 1, (sum + i) % 7, (now * 10 + i) % 7, limit && i == up);
        ans.cnt = (ans.cnt + t.cnt) % MOD;
        ans.sum = (ans.sum + t.sum + p[pos] * i % MOD * t.cnt % MOD) % MOD;
        ans.sumpow += ((t.cnt * p[pos] % MOD * p[pos] % MOD * i % MOD * i % MOD + 2 * t.sum * p[pos] % MOD * i % MOD)
                       % MOD + t.sumpow % MOD) % MOD;
        ans.sumpow %= MOD;
    }

    return ans;
}

inline ll calc(ll x) {
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            for (int k = 0; k < MAXN; ++k)
                for (int t = 0; t <= 1; ++t)
                    f[i][j][k][t] = Node(0, 0, -1);

    int tot = 0;

    while (x)
        num[++tot] = x % 10, x /= 10;

    return dfs(tot, 0, 0, 1).sumpow;
}

int main() {
    int T;
    cin >> T;
    p[1] = 1;

    for (int i = 2; i < MAXN; ++i)
        p[i] = p[i - 1] * 10 % MOD;

    while (T--) {
        ll a, b;
        cin >> a >> b;
        printf("%lld\n", ((calc(b) - calc(a - 1)) % MOD + MOD) % MOD);
    }

    return 0;
}