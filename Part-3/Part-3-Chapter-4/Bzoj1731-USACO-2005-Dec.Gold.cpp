#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 4, M = 10000 + 10;

int n, ml, md;
struct Edge {
    int nxt, v, c;
    Edge() { nxt = v = c = 0; }
    Edge(int NXT, int V, int C) {
        nxt = NXT;
        v = V;
        c = C;
    }
}edge[M * 5];
int hd[N], tot;

void add_edge(int u, int v, int z) {
    edge[++tot] = Edge(hd[u], v, z);
    hd[u] = tot;
}

int dist[N];
bool vis[N];
int in[N];

int SPFA(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(in, 0, sizeof(in));
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    vis[s] = true;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dist[u] + edge[i].c < dist[v]) {
                dist[v] = dist[u] + edge[i].c;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                    in[v]++;
                    if (in[v] >= n + 1) {
                        return -1;
                    }
                }
            }
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2) return -2;
    
    return dist[n];
}

int main() {
    cin >> n >> ml >> md;
    for (int i = 1; i <= ml; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        if (u > v) swap(u, v);
        add_edge(u, v, z);
    }
    for (int i = 1; i <= md; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        if (u > v) swap(u, v);
        add_edge(v, u, -z);
    }
    for (int i = 1; i <= n; i++) {
        // add_edge(i, 0, 0);
        add_edge(0, i, 0);
    }
    
    for (int i = 1; i < n; i++) {
        add_edge(i + 1, i, 0);
    }
    
    int flag = SPFA(0);
    if (flag <= -1) {
        printf("%d\n", flag);
    } else {
        printf("%d\n", SPFA(1));
    }

    return 0;
}