#include <iostream>
#include <string>
using namespace std;
int f[105][65][65], map[105], sit[65], num[65], cnt;
int count(int s) {
    int ans = 0;

    while (s) {
        if (s & 1)
            ans++;

        s = s >> 1;
    }

    return ans;
}
int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < m; j++) {
            if (s[j] == 'H')
                map[i] += 1 << j;
        }
    }

    int t = (1 << m) - 1;

    for (int i = 0; i <= t; i++) {
        if (!(i & (i << 1)) && !(i & (i << 2)) && !(i & (i >> 2)) && !(i & (i >> 1))) {
            sit[++cnt] = i;
            num[cnt] = count(i);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (!(sit[i]&map[1]))
            f[1][0][i] = num[i];
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (!(sit[i]&map[2]) && !(sit[i]&sit[j]))
                f[2][j][i] = max(f[2][j][i], f[1][0][j] + num[i]);
        }
    }

    for (int i = 3; i <= n; ++i) {
        for (int j = 1; j <= cnt; j++) {
            if (!(map[i]&sit[j])) {
                for (int k = 1; k <= cnt; k++) {
                    if (!(sit[j]&sit[k])) {
                        for (int v = 1; v <= cnt; v++) {
                            if (!(sit[v]&sit[k]) && !(sit[v]&sit[j])) {
                                f[i][k][j] = max(f[i][k][j], f[i - 1][v][k] + num[j]);

                            }
                        }
                    }
                }
            }

        }
    }

    int ans = 0;

    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++)
            ans = max(ans, f[n][i][j]);

    cout << ans << endl;

}