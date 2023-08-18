#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 5e5 + 10, Z = 27;
int n, ch[N][Z], tot = 1, ed[N];
string s[N];

void insert(int id) {
    int r = 1, len = s[id].length();
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'a';
        if (!ch[r][c]) ch[r][c] = ++tot;
        r = ch[r][c];
    }
    ed[r] = id;
}


vector<int> g[N];

void build_graph(int id) {
    int r = 1, len = s[id].length(), cur = 0;
    for (int i = 0; i < len - 1; i++) {
        int c = s[id][i] - 'a';
        r = ch[r][c];
        if (ed[r]) cur = ed[r];
    }
    
    g[cur].push_back(id);
}

int sz[N];

bool cmp(int a, int b) {
    return sz[a] < sz[b];
}

void dfs1(int node) {
    sz[node] = 1;
    for (int v : g[node]) {
        dfs1(v);
        sz[node] += sz[v];
    }
    
    sort(g[node].begin(), g[node].end(), cmp);
}

LL ans;
int idx[N], num;

void dfs2(int node) {
    idx[node] = num;
    for (int v : g[node]) {
        num++;
        ans += num - idx[node];
        dfs2(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        reverse(s[i].begin(), s[i].end());
        insert(i);
    }
    
    for (int i = 1; i <= n; i++) {
        build_graph(i);
    }
    
    dfs1(0);
    dfs2(0);
    printf("%lld\n", ans);
    
    return 0;
}