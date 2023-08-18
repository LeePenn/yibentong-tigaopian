#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 200005;
int h[N], ne[N], w[N], e[N], n, idx, hu[N];
int dis[N], st[N], a, b, c, ml, md;
queue<int> q;
void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}
int spfa(int s) {
    memset(dis, 0x3f, sizeof dis);
    memset(st, 0, sizeof st);
    memset(hu, 0, sizeof hu);
    q.push(s);
    dis[s] = 0;
    st[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        st[u] = 0;
        hu[u]++;

        if (hu[u] > n)
            return -1;

        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];

            if (dis[j] > dis[u] + w[i]) {
                dis[j] = dis[u] + w[i];

                if (!st[j]) {
                    st[j] = 1;
                    q.push(j);
                }
            }
        }
    }

    if (dis[n] > 0x3f3f3f3f / 2)
        return -2;

    return dis[n];
}
int main() {
    scanf("%d%d%d", &n, &ml, &md);

    for (int i = 1; i <= n; i++)
        add(0, i, 0);

    memset(h, -1, sizeof h);

    for (int i = 1; i <= ml; i++) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    for (int i = 1; i <= md; i++) {
        scanf("%d%d%d", &a, &b, &c);
        add(b, a, -c);
    }

    for (int i = 1; i < n; i++)
        add(i + 1, i, 0);

    for (int i = 1; i <= n; i++)
        add(0, i, 0);

    int flag = spfa(0);

    if (flag <= -1) {
        printf("%d", flag);
        return 0;
    }

    printf("%d", spfa(1));
    return 0;
}