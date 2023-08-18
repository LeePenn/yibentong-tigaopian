#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 510005, Z = 27;
int n;
int ch[N][Z], tot = 1;
string s[N];
int ed[N];

void insert(int id) {
    int r = 1, len = s[id].length();

    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'a';

        if (!ch[r][c])
            ch[r][c] = ++tot;

        r = ch[r][c];
    }

    ed[r] = id;
}

int hd[N], nx[N], to[N], tot2 = 0;

void insert_edge(int from, int t) {
    nx[++tot2] = hd[from];
    to[tot2] = t;
    hd[from] = tot2;
}

void build_graph(int id) {
    int r = 1, len = s[id].length();
    int cur = 0;

    for (int i = 0; i < len - 1; i++) {
        int c = s[id][i] - 'a';
        r = ch[r][c];

        if (ed[r])
            cur = ed[r];
    }

    // printf("%d %d\n", cur, id);
    insert_edge(cur, id);
}

int sz[N];

void dfs1(int node) {
    sz[node] = 1;

    for (int i = hd[node]; i; i = nx[i]) {
        dfs1(to[i]);
        sz[node] += sz[to[i]];
    }
}

int idx[N], num;
LL ans;

bool cmp(int a, int b) {
    return sz[a] < sz[b];
}

void dfs2(int node) {
    int cnt = 0, temp[N];

    for (int i = hd[node]; i; i = nx[i]) {
        temp[++cnt] = to[i];
    }

    sort(temp + 1, temp + cnt + 1, cmp);
    idx[node] = num;

    for (int i = 1; i <= cnt; i++) {
        num++;
        ans += num - idx[node];
        dfs2(temp[i]);
    }
}

int main() {
    scanf("%d", &n);

    // build tree
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        reverse(s[i].begin(), s[i].end());
        insert(i);
    }

    // build graph
    for (int i = 1; i <= n; i++) {
        build_graph(i);
    }

    dfs1(0);
    dfs2(0);
    printf("%lld\n", ans);
    // for (int i = )

    return 0;
}