#include <bits/stdc++.h>
#define MP make_pair
#define FI first
#define SE second
using namespace std;

const int N = 5000 + 10, R = 1e5 + 10;

int n, r;
int hd[N], nx[R << 1], to[R << 1], c[R << 1], tot;
int x, y, z;
int d[N], d1[N];
bool vis[N];
priority_queue<pair<int, int> > q;

void add_edge(int x, int y, int z) {
    nx[++tot] = hd[x];
    to[tot] = y;
    c[tot] = z;
    hd[x] = tot;
}

void dijkstra() {
    memset(d, 0x3f, sizeof(d));
    memset(d1, 0x3f, sizeof(d1));
    d[1] = 0;
    q.push(MP(0, 1));
    while (!q.empty()) {
        int u = q.top().SE, du = -q.top().FI; q.pop();
        if (du > d1[u]) continue;
        
        for (int i = hd[u]; i; i = nx[i]) {
            int v = to[i], &dv = d[v];
            if (dv > du + c[i]) {
                d1[v] = dv;
                dv = du + c[i];
            }
            if (du + c[i] > dv && du + c[i] < d1[v]) {
                d1[v] = du + c[i];
            }
            
            q.push(MP(-(du + c[i]), v));
        }
    }

}

int main() {
    cin >> n >> r;
    for (int i = 1; i <= r; i++) {
        cin >> x >> y >> z;
        add_edge(x, y, z); add_edge(y, x, z);
    }
    dijkstra();
    printf("%d\n", d1[n]);

    return 0;
}