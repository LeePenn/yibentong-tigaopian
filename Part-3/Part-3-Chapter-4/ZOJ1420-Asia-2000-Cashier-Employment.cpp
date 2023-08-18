#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 10, INF = 0x3f3f3f3f;

int T, r[30], n, num[30];
struct Edge {
    int v, nxt;
    int c;
    Edge() {
        v = nxt = c = 0;
    }
    Edge(int V, int NXT, int C) {
        v = V;
        nxt = NXT;
        c = C;
    }
}edge[N * 2];
int hd[N], tot;
int dist[N];
bool vis[N];
int in[30];

void add_edge(int u, int v, int c) {
    edge[++tot] = Edge(v, hd[u], c);
    hd[u] = tot;
}

void build(int m) {
    memset(hd, 0, sizeof(hd));
    tot = 0;
    for (int i = 1; i <= 24; i++) {
        add_edge(i - 1, i, 0);
        add_edge(i, i - 1, -num[i]);
    }
    for (int i = 9; i <= 24; i++) {
        add_edge(i - 8, i, r[i]);
    }
    for (int i = 1; i <= 8; i++) {
        add_edge(i + 16, i, r[i] - m);
    }
    add_edge(0, 24, m);
}

bool check(int m) {
    build(m);
    
    for (int i = 0; i < N; i++) dist[i] = -INF;
    memset(vis, 0, sizeof(vis));
    memset(in, 0, sizeof(in));
    queue<int> que;
    que.push(0);
    dist[0] = 0;
    in[0]++;
    vis[0] = true;
    
    while (!que.empty()) {
        int u = que.front(); que.pop(); 
        // printf("%d\n", u);
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dist[u] + edge[i].c > dist[v]) {
                dist[v] = dist[u] + edge[i].c;
                if (!vis[v]) {
                    que.push(v);
                    vis[v] = true;
                    in[v]++;
                    if (in[v] > 24) return false;
                }
            }
        }
        vis[u] = false;
    }

    return dist[24] == m;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        for (int i = 1; i <= 24; i++) scanf("%d", &r[i]);
        scanf("%d", &n);
        memset(num, 0, sizeof(num));
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            x++;
            num[x]++;
        }
        
        
        // for (int i = 1; i <= 24; i++) printf("%d ", r[i]);
        // cout << endl;
        // for (int i = 1; i <= 24; i++) printf("%d ", num[i]);
        // return 0;
        
        bool ok = false;
        for (int i = 0; i <= n; i++) {
            if (check(i)) {
                ok = true;
                printf("%d\n", i);
                break;
            }
        }
        
        if (!ok) printf("No Solution\n");
    }

    return 0;
}