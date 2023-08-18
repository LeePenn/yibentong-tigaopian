#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
struct node {
    int cnt;  // 与7无关的数的个数
    int sum1; // 与7无关的数的和
    int sum2; // 与7无关的数的平方和
} f[20][10][10];
int pw[30];
string s;
int n;

node dfs(int i, int rem1, int rem2, bool is_limit) {
    if (i == n) {
        return {rem1 &&rem2, 0, 0};
    }

    if (f[i][rem1][rem2].cnt > 0 && !is_limit) {
        return f[i][rem1][rem2];
    }

    node ans = {0, 0, 0};

    for (int d = 0, up = is_limit ? (s[i] - '0') : 9; d <= up; d++) {
        if (d == 7)
            continue;

        node J = dfs(i + 1, (rem1 + d) % 7, (rem2 * 10 + d) % 7, is_limit && d == up);
        int base = d * pw[n - i - 1] % MOD;
        ans.cnt = (ans.cnt + J.cnt) % MOD;
        ans.sum1 = (ans.sum1 + J.cnt * base % MOD + J.sum1) % MOD;
        ans.sum2 = (ans.sum2 + J.cnt * base % MOD * base % MOD + J.sum2 + 2 * base % MOD * J.sum1 % MOD) % MOD;
    }

    if (!is_limit) {
        f[i][rem1][rem2] = ans;
    }

    return ans;
}

int cal(int x) {
    memset(f, -1, sizeof f);
    s = to_string(x);
    n = s.size();
    return dfs(0, 0, 0, true).sum2;
}

void solve(int T) {

    int a, b;
    cin >> a >> b;
    cout << (cal(b) - cal(a - 1) + MOD) % MOD << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    pw[0] = 1;

    for (int i = 1; i < 21; i++)
        pw[i] = pw[i - 1] * 10 % MOD;

    int T = 1;
    cin >> T;

    for (int i = 1; i <= T; i++)
        solve(i);

    return 0;
}