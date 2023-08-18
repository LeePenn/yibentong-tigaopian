#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
const int N = 1e5 + 10, M = 5e5 + 10;

int n, m;
int cost[N];
int hd[N], nx[M << 1], to[M << 1], tot;
int fhd[N], fnx[M << 1], fto[M << 1], ftot;
int ans;
int minn[N], maxx[N];
int x, y, z;
int dist[N], fdist[N];
priority_queue<pair<int, int> > heap;

void add_edge(int x, int y) {
    nx[++tot] = hd[x];
    to[tot] = y;
    hd[x] = tot;
    
    fnx[++ftot] = fhd[y];
    fto[ftot] = x;
    fhd[y] = ftot;
}

void dijkstra1() {
    minn[1] = cost[1];
    heap.push(MP(-minn[1], 1));
    while (!heap.empty()) {
        int u = heap.top().second; heap.pop();
        for (int i = hd[u]; i; i = nx[i]) {
            int v = to[i];
            if (minn[v] == -1000) {
                minn[v] = cost[v];
                minn[v] = min(minn[v], cost[u]);
                heap.push(MP(-minn[v], v));
            } else if (minn[v] > minn[u]) {
                minn[v] = minn[u];
                heap.push(MP(-minn[v], v));
            }
        }
    }
}

void dijkstra2() {
    maxx[n] = cost[n];
    heap.push(MP(maxx[n], n));
    while (!heap.empty()) {
        int u = heap.top().second; heap.pop();
        for (int i = fhd[u]; i; i = fnx[i]) {
            int v = fto[i];
            if (maxx[v] == -1000) {
                maxx[v] = cost[v];
                maxx[v] = max(maxx[v], maxx[u]);
                heap.push(MP(maxx[v], v));
            } else if (maxx[v] < maxx[u]) {
                maxx[v] = maxx[u];
                heap.push(MP(maxx[v], v));
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> cost[i];
    
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        add_edge(x, y);
        if (z == 2) add_edge(y, x);
    }
    for (int i = 1; i <= n; i++) {
        minn[i] = -1000, maxx[i] = -1000;
    }
    dijkstra1();
    dijkstra2();
    
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d\n", minn[i], maxx[i]);
    // }return 0;
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (minn[i] != -1000 && maxx[i] != -1000 && maxx[i] > minn[i]) {
            ans = max(ans, maxx[i] - minn[i]);
        }
    }
    printf("%d\n", ans);

    return 0;
}