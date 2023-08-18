#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <queue>
#define pi 3.1415926535
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
typedef pair<int, int> pii;
const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx, w[N];
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

int n, m;
int id[N];
int dis[6][N];
bool st[N];

void dijkstra(int x, int dis[]) {
    memset(dis, 0x3f, N * 4);
    memset(st, false, sizeof st);
    dis[x] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> heap;
    heap.push({ 0, x });

    while (heap.size()) {
        pii t = heap.top();
        heap.pop();
        int ver = t.second;

        if (st[ver])
            continue;

        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];

            if (dis[j] > dis[ver] + w[i]) {
                dis[j] = dis[ver] + w[i];
                heap.push({ dis[j], j });
            }
        }
    }
}
int dfs(int num, int start, int dist) {
    if (num > 5)
        return dist;

    int res = 0x3f3f3f3f;

    for (int i = 1; i <= 5; i++) {

        if (!st[i]) {
            st[i] = true;
            res = min(res, dfs(num + 1, i, dist + dis[start][id[i]]));
            st[i] = false;
        }
    }

    return res;

}
int main() {
    cin >> n >> m;
    id[0] = 1;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= 5; i++)
        cin >> id[i];

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    for (int i = 0; i < 6; i++)
        dijkstra(id[i], dis[i]);

    memset(st, false, sizeof st);
    cout << dfs(1, 0, 0) << endl;
}