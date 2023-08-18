#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 4;

int T, dist[N][N];
int n, m1, m2;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m1, &m2);
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= n; i++) dist[i][i] = 0;
        for (int i = 1; i <= m1; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dist[u][v] = dist[v][u] = min(dist[u][v], w);;
        }
        for (int i = 1; i <= m2; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            dist[u][v] = -w;
        }
        
        bool NC = false;
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] != 0x3f3f3f3f && dist[k][j] != 0x3f3f3f3f) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
                if (dist[i][i] < 0) {
                    NC = true;
                    break;
                }
            }
            if (NC) break;
        }
        if (NC) printf("YES\n");
        else printf("NO\n");
    }
    

    return 0;
}