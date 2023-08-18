#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, M = 5e5, INF = 0x3f3f3f3f;

struct Edge {
    int v, nxt;
    int c;
} edge[M];
int n;
int hd[N], tot;
int MIN, MAX;
int dist[N];
bool vis[N];

void add_edge(int u, int v, int c) {
    edge[++tot].nxt = hd[u];
    edge[tot].v = v;
    edge[tot].c = c;
    hd[u] = tot;
}

void SPFA(int s) {
    for (int i = MIN; i <= MAX; i++) {
        dist[i] = -INF;
    }

    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    vis[s] = 1;
    queue<int> que;
    que.push(s);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;

            if (dist[u] + edge[i].c > dist[v]) {
                dist[v] = dist[u] + edge[i].c;

                if (!vis[v]) {
                    que.push(v);
                    vis[v] = true;
                }
            }
        }

        vis[u] = false;
    }
}

int main() {
    scanf("%d", &n);
    MIN = INF, MAX = -1;
    for (int i = 1; i <= n; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(u - 1, v, c);
        MIN = min(MIN, u - 1);
        MAX = max(MAX, v);
    }
    
    for (int i = MIN; i <= MAX; i++) {
        add_edge(i, i + 1, 0);
        add_edge(i + 1, i, -1);
    }
    
    SPFA(MIN);
    printf("%d\n", dist[MAX]);
    
    
    return 0;
}
