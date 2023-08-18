#include <bits/stdc++.h>
using namespace std;
const int N = 50, M = 4010;
struct Edge {
    int nxt, v, id;
    Edge() { nxt = v = id = 0; }
    Edge(int _nxt, int _v, int _id) {
        nxt = _nxt;
        v = _v;
        id = _id;
    }
}edge[M];
int hd[N], etot;
int st;
int in[N], out[N];
// euler is edge loop!!
bool vis[M];
int ans[M], cnt;

void init() {
    etot = 1, cnt = 0;
    memset(hd, 0, sizeof(hd));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(vis, 0, sizeof(vis));
}

void add_edge(int u, int v, int z) {
    edge[++etot] = Edge(hd[u], v, z);
    hd[u] = etot;
    // in[v]++;
}

bool Euler_loop() {
    for (int i = 1; i <= 44; i++) {
        if ((in[i] + out[i]) & 1) return false;
    }
    return true;
}

void dfs(int u, int p) {
    for (int i = hd[u]; i; i = edge[i].nxt) {
        if (vis[i]) continue;
        vis[i] = vis[i ^ 1] = true;
        
        // printf("%d %d\n", i, i ^ 1);
        int v = edge[i].v;
        dfs(v, edge[i].id);
    }
    
    if (p) {
        ans[++cnt] = p;
    }
        
}

int main() {
    int u, v, z;
    while (1) {
        scanf("%d%d", &u, &v);
        if (u && v) {
            init();
            st = min(u, v);
            scanf("%d", &z);
            add_edge(u, v, z);
            add_edge(v, u, z);
            in[v]++, out[u]++;
            while (scanf("%d%d", &u, &v) == 2 && u && v) {
                scanf("%d", &z);
                add_edge(u, v, z);
                add_edge(v, u, z);
                in[v]++, out[u]++;
            }
            if (!Euler_loop()) {
                printf("Round trip does not exist.\n");
                continue;
            }
            // printf("%d\n", etot);
            // return 0;
            // printf("%d\n", st);
            dfs(st, 0);
            // printf("%d %d\n", etot, cnt);
            for (int i = cnt; i > 1; i--) {
                printf("%d ", ans[i]);
            }
            printf("%d\n", ans[1]);
        } else {
            break;
        }
    }
    
    
    return 0;
}