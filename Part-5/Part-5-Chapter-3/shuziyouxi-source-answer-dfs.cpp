//This Code was made by Jim_Franklin.
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ri register
#define pii pair<int,int>
const int inf = 0x3f3f3f3f;
inline int rd() {
    int x = 0, y = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            y = -1;

    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);

    return x * y;
}
int x, y, n, a[25], c, f[25][120];
int dfs(int len, int sum, int high) {
    if (!len)
        return sum % n == 0;

    if (!high && f[len][sum] != -1)
        return f[len][sum];

    int Max = high ? a[len] : 9, ans = 0;

    for (int i = 0; i <= Max; i++)
        ans += dfs(len - 1, sum + i, high && i == Max);

    if (!high)
        f[len][sum] = ans;

    return ans;
}
int solve(int k) {
    c = 0;

    while (k)
        a[++c] = k % 10, k /= 10;

    return dfs(c, 0, 1);
}
signed main() {
    while (cin >> x >> y >> n) {
        memset(f, 255, sizeof f);
        cout << solve(y) - solve(x - 1) << '\n';
    }

    return 0;
}