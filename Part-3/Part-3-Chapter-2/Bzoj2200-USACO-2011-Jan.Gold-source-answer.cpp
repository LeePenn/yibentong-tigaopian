#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

long long head[25100], n, m, m1, s, g = 0, dis[25100], vis[25010];

struct str {
    long long u, v, w, next;
} e[400100];

deque<int> q;

void addedge(int u, int v, int w) {
    g++;
    e[g].u = u;
    e[g].v = v;
    e[g].w = w;
    e[g].next = head[u];
    head[u] = g;
}

int main() {
    int i;
    cin >> n >> m >> m1 >> s;

    for (i = 1; i <= m; i++) {
        long long u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }

    for (i = 1; i <= m1; i++) {
        long long u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        addedge(u, v, w);
    }

    for (i = 1; i <= 25010; i++)
        dis[i] = 1e18;

    q.push_back(s);
    vis[s] = 1;
    dis[s] = 0;

    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        vis[x] = 0;

        for (i = head[x]; i; i = e[i].next) {
            if (dis[e[i].v] > dis[x] + e[i].w) {
                dis[e[i].v] = dis[x] + e[i].w;

                if (!vis[e[i].v]) {
                    if (e[i].v <= q.front())
                        q.push_front(e[i].v);
                    else
                        q.push_back(e[i].v);

                    vis[e[i].v] = 1;
                }
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (dis[i] == 1e18)
            printf("NO PATH\n");
        else
            printf("%lld\n", dis[i]);
    }

    return 0;
}