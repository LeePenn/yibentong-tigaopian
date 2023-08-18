#include <bits/stdc++.h>
using namespace std;

const int N = 505;
int n, k;
int px[N], py[N];
struct Edge {
    int x, y;
    double d;
}e[N * N];
int fa[N];
double ans[N];
int cnt = 0;

double dist(int ax, int ay, int bx, int by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

bool comp(const Edge &a, const Edge &b) {
    return a.d < b.d;
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void uni(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) fa[fy] = fx;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> px[i] >> py[i];
        fa[i] = i;
    }
    
    int m = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            e[++m] = (Edge){i, j, dist(px[i], py[i], px[j], py[j])};
        }
    }
    
    sort(e + 1, e + m + 1, comp);
    for (int i = 1; i <= m; i++) {
        int x = e[i].x, y = e[i].y;
        double d = e[i].d;
        int fx = find(x), fy = find(y);
        if (fx == fy) continue;
        ans[++cnt] = d;
        uni(x, y);
    }
    
    printf("%.2lf\n", ans[cnt - k + 1]);
    
    
    return 0;
}