#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 10, Z = 2;
int n;
int ch[N][Z], tot = 0;
bool b[N];
queue<int> q;
int nxt[N];
string s[N];
bool vis[N], v[N], ans;

void build_trie(int id) {
    int u = 0, len = s[id].length();
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - '0';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    b[u] = true;
}

void bfs() {
    for (int i = 0; i < Z; i++) if (ch[0][i]) q.push(ch[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        b[u] |= b[nxt[u]];
        for (int i = 0; i < Z; i++) {
            if (!ch[u][i]) ch[u][i] = ch[nxt[u]][i];
            else {
                q.push(ch[u][i]);
                int v = nxt[u];
                while (v && !ch[v][i]) v = nxt[v];
                nxt[ch[u][i]] = ch[nxt[u]][i];
            }
        }
    }
}

void dfs(int u) {
    if (b[u] || ans) return;
    
    if (vis[u]) {
        ans = v[u];
        return;
    }
    vis[u] = v[u] = 1;
    for (int i = 0; i < Z; i++) {
        if (ch[u][i]) dfs(ch[u][i]);
    }
    v[u] = 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        build_trie(i);
    }
    bfs();
    dfs(0);
    if (ans) printf("TAK");
    else printf("NIE");
    printf("\n");

    return 0;
}