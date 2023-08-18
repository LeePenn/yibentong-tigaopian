#include <bits/stdc++.h>

using namespace std;

const int N = 104;
int n, a[N], len;
int ans[N];

void dfs(int m) {
    if (a[m - 1] == n) {
        if (m - 1 <= len) {
            len = m - 1;
            memcpy(ans, a, sizeof(ans));
        }
        return;
    }
    
    if (m >= len) return;
    
    int i, j;
    bool v[N];
    memset(v, 0, sizeof(v));
    for (i = m - 1; i >= 1; --i) {
        for (j = i; j >= 1; --j) {
            int cur = a[i] + a[j];
            if (v[cur]) continue;
            if (cur <= n) {
                v[cur] = true;
                a[m] = cur;
                dfs(m + 1);
            }
        }
    }
}

int main() {
    a[1] = 1, a[2] = 2, a[3] = 3;
    while (scanf("%d", &n) == 1 && n) {
        len = n;
        dfs(2);
        sort(ans + 1, ans + len + 1);
        for (int i = 1; i < len; ++i) cout << ans[i] << ' ';
        cout << ans[len] << endl;
    }

    return 0;
}