#include <bits/stdc++.h>

typedef long long lld;

const int N = 5011, M = 100011;
int n, m;
struct Edge {
    int v, nex;
    lld w;
} edge[M << 1];
int pedge = 1, head[N];
void add(int u, int v, lld w) {
    edge[++pedge] = (Edge) {
        v, head[u], w
    };
    head[u] = pedge;
}

struct Node {
    int id;
    lld dis;
    bool operator< (const Node &nd) const {
        return dis > nd.dis;
    }
};
std::priority_queue<Node> heap;
bool vis[N];
lld dis[N], sdis[N];
void dijk(int st) {
    memset(dis, 0x3f, sizeof dis), memset(sdis, 0x3f, sizeof dis);
    dis[st] = 0;
    heap.push({st, dis[st]});

    while (!heap.empty()) {
        int u = heap.top().id;
        lld d = heap.top().dis;
        heap.pop();

        if (d > sdis[u])
            continue;

        for (int i = head[u]; i; i = edge[i].nex) {
            Edge &e = edge[i];
            lld nd = d + e.w, &dv = dis[e.v], &sdv = sdis[e.v];

            if (nd < dv)
                sdv = dv, dv = nd;

            if (dv < nd && nd < sdv)
                sdv = nd;

            heap.push({e.v, nd});
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }

    dijk(1);
    printf("%lld\n", sdis[n]);
    return 0;
}