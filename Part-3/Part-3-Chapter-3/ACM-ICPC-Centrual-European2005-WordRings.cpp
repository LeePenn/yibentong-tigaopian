#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const double EPS = 1e-3;
int n;
string s;
struct E {
    int v, nxt;
    double w;
}e[N];
int tot, E, MaxEdge;
int node[800], hd[677];
bool PC = false;
int vis[677];
double dist[677];

void add_edge(int u, int v, double w) {
    e[++E].nxt = hd[u];
    e[E].v = v;
    e[E].w = w;
    hd[u] = E;
}

void SPFA(int u, int root, double avg) {
    if (PC) return;
    vis[u] = root;
    for (int i = hd[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (dist[u] + e[i].w - avg > dist[v]) {
            dist[v] = dist[u] + e[i].w - avg;
            if (dist[v] > MaxEdge) {
                PC = true;
                return;
            }
            if (!vis[v]) SPFA(v, root, avg);
            if (PC) return;
            else if (vis[v] == root) {
                PC = true;
                return;
            }
        }
    }
    vis[u] = 0;

}

bool check(double mid) {
    PC = false;
    fill(vis, vis + tot + 1, 0);
    fill(dist, dist + tot + 1, 0);
    for (int i = 1; i <= tot; i++) {
        SPFA(i, i, mid);
        if (PC) return true;
    }
    return PC;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        tot = 0, E = 0, MaxEdge = 0;
        memset(node, 0, sizeof(node));
        memset(hd, 0, sizeof(hd));
        for (int i = 1; i <= n; i++) {
            cin >> s;
            int len = s.length();
            if (len > MaxEdge) MaxEdge = len;
            int a = (s[0] - 'a') * 26 + s[1] - 'a';
            if (!node[a]) node[a] = ++tot;
            int id1 = node[a];
            int b = (s[len - 2] - 'a') * 26 + s[len - 1] - 'a';
            if (!node[b]) node[b] = ++tot;
            int id2 = node[b];
            add_edge(id1, id2, (double)len);
        }
        
        MaxEdge *= n;
        double l = 0, r = 1000, ans = -1;
        while (l + EPS < r) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                l = mid;
            } else r = mid;
        }
        if (ans == -1) printf("No solution\n");
        else printf("%.2f\n", ans);
        
    }
}