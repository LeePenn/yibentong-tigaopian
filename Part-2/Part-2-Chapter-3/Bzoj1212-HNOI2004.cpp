#include <bits/stdc++.h>

using namespace std;

const int MAXL = 1000005;
const int N = 22, M = 22, L = 12, Z = 28;
int ch[N * L][Z], tot = 0;
bool ed[N * L];
int n, m;
char s[MAXL];
int maxlen;
int l, ans;
bool v[MAXL];

void insert() {
    int r = 0;
    int len = strlen(s + 1);

    for (int i = 1; i <= len; i++) {
        int c = s[i] - 'a' + 1;

        if (!ch[r][c])
            ch[r][c] = ++tot;

        r = ch[r][c];
    }

    ed[r] = true;
}

void dfs(int idx) {
    if (v[idx])
        return;

    v[idx] = true;
    ans = max(ans, idx - 1);

    if (idx > l) {
        return;
    }

    int r = 0;

    for (int i = idx; i <= min(idx + maxlen - 1, l); i++) {
        int c = s[i] - 'a' + 1;

        if (!ch[r][c])
            break;

        r = ch[r][c];

        if (ed[r]) {
            dfs(i + 1);
        }
    }
}

void work() {
    scanf("%s", s + 1);
    l = strlen(s + 1);
    ans = 0;
    memset(v, 0, sizeof(v));
    dfs(1);
    printf("%d\n", ans);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        int cur = strlen(s + 1);
        maxlen = max(maxlen, cur);
        insert();
    }

    for (int i = 1; i <= m; i++) {
        work();
    }

    return 0;
}