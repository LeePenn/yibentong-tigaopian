#include <iostream>

using namespace std;

struct str {
    double v;
    int to, next;
} a[10005];

int n, m, g, head[3005];
bool vis[3005], f;
double mid, dis[3005];

void add(int x, int y) {
    g++;
    cin >> a[g].v;
    a[g].to = y;
    a[g].next = head[x];
    head[x] = g;
}

void spfa(int i) {
    vis[i] = 1;

    for (int j = head[i]; j; j = a[j].next) {
        if (dis[a[j].to] > dis[i] + a[j].v - mid) {
            dis[a[j].to] = dis[i] + a[j].v - mid;

            if (vis[a[j].to])
                return void(f = 1);
            else
                spfa(a[j].to);
        }
    }

    vis[i] = 0;
}

bool check() {
    int i;

    for (i = 1; i <= n; ++i)
        dis[i] = vis[i] = f = 0;

    for (i = 1; i <= n; i++)
        if (!vis[i] && !f)
            spfa(i);

    return f;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }

    double l = -1e7, r = 1e7;

    while (l <= r) {
        mid = (l + r) / 2;

        if (check())
            r = mid - 1e-9;
        else
            l = mid + 1e-9;
    }

    printf("%.8lf\n", l);
    return 0;
}