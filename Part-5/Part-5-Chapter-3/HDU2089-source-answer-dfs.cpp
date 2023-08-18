#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
int n, m, p[10], f[10][11], q[10];
int dfs(int pos, int pre, int lead, int lim) {
    if (pos > p[0])
        return 1;

    if (!lead && !lim && f[pos][pre] != -1)
        return f[pos][pre];

    int x = lim ? p[p[0] - pos + 1] : 9;
    int ans = 0;

    for (int i = 0; i <= x; i++) {
        if (!i && lead)
            ans += dfs(pos + 1, 0, lead, (i == x) && lim);

        if (i && lead || !lead) {
            if (i == 4 || i == 2 && pre == 6)
                continue;

            ans += dfs(pos + 1, i, 0, (i == x) && lim);
        }
    }

    return !lim && !lead ? f[pos][pre] = ans : ans;
}

int Solve(int x) {
    p[0] = 0;

    while (x)
        p[++p[0]] = x % 10, x /= 10;

    memset(f, -1, sizeof(f));
    return dfs(1, 10, 1, 1);
}

int main() {
    while (~scanf("%d%d", &n, &m) && n && m)
        printf("%d\n", Solve(m) - Solve(n - 1));

    return 0;
}