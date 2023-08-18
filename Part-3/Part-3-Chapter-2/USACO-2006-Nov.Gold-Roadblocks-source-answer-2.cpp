#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3 + 5, M = 1e5 + 5;
int n, m, a, b, c, k;
int head[N], dis[N][3], u[N][3];
struct AB {
    int a, b, c, n;
} d[M * 2];
void cun(int a, int b, int c) {
    d[++k].a = a, d[k].b = b, d[k].c = c;
    d[k].n = head[a], head[a] = k;
}
priority_queue< pair<int, pair<int, int>>>q;
signed main() {
    //  freopen("P2865_8.in","r",stdin);
    scanf("%lld%lld", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld%lld", &a, &b, &c);
        cun(a, b, c);
        cun(b, a, c);
    }

    memset(dis, 0x3f, sizeof dis);
    dis[1][0] = 0;
    q.push(make_pair(0, make_pair(1, 0)));

    while (!q.empty()) {
        int now = q.top().second.first, j = q.top().second.second;
        q.pop();

        //      if(u[now][j]) continue;
        //      u[now][j]=1;
        for (int i = head[now]; i; i = d[i].n) {
            int nxt = d[i].b;

            if (dis[nxt][0] > dis[now][0] + d[i].c) {
                dis[nxt][0] = dis[now][0] + d[i].c;
                q.push(make_pair(-dis[nxt][0], make_pair(nxt, 0)));
            } else if (dis[nxt][1] > dis[now][0] + d[i].c && dis[nxt][0] < dis[now][0] + d[i].c) {
                dis[nxt][1] = dis[now][0] + d[i].c;
                q.push(make_pair(-dis[nxt][1], make_pair(nxt, 1)));
            } else if (dis[nxt][1] > dis[now][1] + d[i].c) {
                dis[nxt][1] = dis[now][1] + d[i].c;
                q.push(make_pair(-dis[nxt][1], make_pair(nxt, 1)));
            }
        }
    }

    printf("%lld", dis[n][1]);
    return 0;
}