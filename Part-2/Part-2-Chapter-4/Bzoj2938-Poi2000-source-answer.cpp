#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 10, C = 2;

int n;
char s[N];
int tot, tr[N][C], ed[N], fail[N];
int a[N];
bool ans, tag[N], vis[N];
inline void insert(char *s) {
    int u = 0, len = strlen(s + 1);

    for (int i = 1; i <= len; i++) {
        if (!tr[u][s[i] - '0'])
            tr[u][s[i] - '0'] = ++tot;

        u = tr[u][s[i] - '0'];
    }

    ed[u] = 1;
}
inline void build() {
    queue<int>q;

    for (int i = 0; i < C; i++)
        if (tr[0][i])
            q.push(tr[0][i]);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ed[u] |= ed[fail[u]];

        for (int i = 0; i < C; i++) {
            if (tr[u][i])
                fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
            else
                tr[u][i] = tr[fail[u]][i];
        }
    }
}
void dfs(int x) {
    if (ed[x] || ans)
        return ;

    if (vis[x])
        return ans = tag[x], void();

    tag[x] = vis[x] = 1;

    for (int i = 0; i < C; i++)
        if (tr[x][i])
            dfs(tr[x][i]);

    tag[x] = 0;
}
int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%s", s + 1), insert(s);

    build();
    dfs(0);
    ans ? puts("TAK") : puts("NIE");
    return 0;
}