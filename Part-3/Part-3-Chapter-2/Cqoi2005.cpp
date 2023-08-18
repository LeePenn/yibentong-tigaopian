#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
const int N = 5e4 + 10, M = 1e5 + 10;

int n, m;
int hd[N], nx[M << 1], to[M << 1], w[M << 1], tot;
int x, y, t;
int nei[6];
priority_queue<pair<int, int> > heap;
int d0[N], d1[N], d2[N], d3[N], d4[N], d5[N];
bool vis[N];
bool use[6];
int seq[6];
int ans = 1000000000;

void add_edge(int x, int y, int t) {
    nx[++tot] = hd[x];
    to[tot] = y;
    w[tot] = t;
    hd[x] = tot;
}

void dijkstra(int d[], int s) {
    memset(vis, 0, sizeof(vis));
    d[s] = 0;
    heap.push(MP(0, s));
    while (!heap.empty()) {
        int u = heap.top().second; heap.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = hd[u]; i; i = nx[i]) {
            int v = to[i];
            if (d[v] > d[u] + w[i]) {
                d[v] = d[u] + w[i];
                heap.push(MP(-d[v], v));
            }
        }
    }
}

void dfs(int x, int last, int tot_dist) {
    if (x == 6) {
        if (tot_dist < ans) ans = tot_dist;
        return;
    }
    int *cur_d;
    if (last == 0) {
        cur_d = d0;
    } else if (last == 1) {
        cur_d = d1;
    } else if (last == 2) {
        cur_d = d2;
    } else if (last == 3) {
        cur_d = d3;
    } else if (last == 4) {
        cur_d = d4;
    } else if (last == 5) {
        cur_d = d5;
    }
    for (int i = 1; i <= 5; i++) {
        if (!use[i]) {
            use[i] = true;
            // printf("%d\n", cur_d[nei[i]]);
            dfs(x + 1, i, tot_dist + cur_d[nei[i]]);
            use[i] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    cin >> nei[1] >> nei[2] >> nei[3] >> nei[4] >> nei[5];
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> t;
        add_edge(x, y, t); add_edge(y, x, t);
    }
    memset(d0, 0x3f, sizeof(d0));
    memset(d1, 0x3f, sizeof(d1));
    memset(d2, 0x3f, sizeof(d2));
    memset(d3, 0x3f, sizeof(d3));
    memset(d4, 0x3f, sizeof(d4));
    memset(d5, 0x3f, sizeof(d5));
    dijkstra(d0, 1);
    dijkstra(d1, nei[1]);
    dijkstra(d2, nei[2]);
    dijkstra(d3, nei[3]);
    dijkstra(d4, nei[4]);
    dijkstra(d5, nei[5]);
    
    memset(use, 0, sizeof(use));
    dfs(1, 0, 0);
    printf("%d\n", ans);
}