#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;
// struct Edge {
//     int nxt, v;
//     Edge() { nxt = v = 0; }
//     Edge(int _nxt, int _v) {
//         nxt = _nxt;
//         v = _v;
//     }
// }edge[M];
// int hd[30], etot;
int g[30][30];
string s[N];
int T, n;
int in[30], out[30];
int st, ed;
bool vis[30];

void init() {
    memset(g, 0, sizeof(g));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(vis, 0, sizeof(vis));
}

void add_edge(int u, int v) {
    g[u][v] = g[v][u] = 1;
    in[v]++, out[u]++;
}

bool Euler_loop() {
    for (int i = 1; i <= 26; i++) {
        if (in[i] != out[i]) return false;
    }
    return true;
}

bool Euler_path() {
    int s0, s1, s2;
    s0 = s1 = s2 = 0;
    for (int i = 1; i <= 26; i++) {
        if (in[i] == out[i]) s0++;
        if (in[i] - out[i] == 1) s2++;
        if (out[i] - in[i] == 1) s1++;
    }
    return s0 == 24 && s1 == 1 && s2 == 1;
}

void dfs(int u) {
    vis[u] = 1;
    for (int v = 1; v <= 26; v++) {
        if (g[u][v] && !vis[v]) dfs(v);
    }
}

bool Connected() {
    for (int i = 1; i <= 26; i++) {
        if (in[i] + out[i] != 0) {
            dfs(i);
            break;
        }
    }
    for (int i = 1; i <= 26; i++) {
        if (in[i] != 0 && out[i] != 0 && !vis[i]) return false;
    }
    return true;
}

int main() {    
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            int u = s[i][0] - 'a' + 1;
            int v = s[i][s[i].length() - 1] - 'a' + 1;
            add_edge(u, v);
        }
        
        if (!Euler_loop() && !Euler_path()) {
            printf("The door cannot be opened.\n");
            continue;
        }
        
        if (!Connected()) {
            printf("The door cannot be opened.\n");
            continue;
        }
        
        printf("Ordering is possible.\n");
    }
    
    return 0;
}