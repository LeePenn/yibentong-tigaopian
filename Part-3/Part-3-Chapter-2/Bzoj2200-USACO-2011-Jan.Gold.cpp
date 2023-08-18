#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int T = 25000 + 5, R = 400100;
const LL INF = 1e18;
int n, r, p, s;
LL hd[T], nxt[R], to[R], tot;
LL c[R];
LL dist[T];
deque<int> q;
bool vis[T];

void add(LL a, LL b, LL d) {
    nxt[++tot] = hd[a];
    to[tot] = b;
    c[tot] = d;
    hd[a] = tot;
}

void SPFA() {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[s] = 0;
    q.push_back(s);
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (int i = hd[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dist[v] > dist[u] + c[i]) {
                dist[v] = dist[u] + c[i];
                if (!vis[v]) {
                    if (v <= q.front()) q.push_front(v);
                    else q.push_back(v);
                    vis[v] = true;
                }
            }
        }
        
        vis[u] = false;
    }
}

int main() {
    scanf("%d%d%d%d", &n, &r, &p, &s);
    for (int i = 1; i <= r; i++) {
        LL u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    for (int i = 1; i <= p; i++) {
        LL u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
    }
    
    SPFA();
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) printf("NO PATH\n");
        else printf("%lld\n", dist[i]);
    }
    
    return 0;
}
