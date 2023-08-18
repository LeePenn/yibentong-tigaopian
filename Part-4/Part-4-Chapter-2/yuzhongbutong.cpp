#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOGN = 18, MAXN = 2e6 + 10, M = 1e6 + 5                                  ;

int n, m;
int a[N], Log[N];
int st[N], f[N], last[MAXN];
int mx[N][LOGN + 5];

int Find(int li, int ri) {
    if (st[li] == li) return li;
    if (st[ri] < li) return ri + 1;
    int ans = li;
    int l = li, r = ri;
    while (l <= r) {
        int mi = (l + r) >> 1;
        if (st[mi] >= li) {
            ans = mi;
            r = mi - 1;
        } else l = mi + 1;
    }
    
    return ans;
}

int Query(int li, int ri) {
    int s = Log[ri - li + 1];
    return max(mx[li][s], mx[ri - (1 << s) + 1][s]);

}

int main() {
    scanf("%d%d", &n, &m);
    Log[0] = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        Log[i] = Log[i >> 1] + 1;
    }
    
    st[0] = 0;
    for (int i = 1; i <= n; i++) {
        st[i] = max(st[i - 1], last[a[i] + M] + 1);
        f[i] = i - st[i] + 1;
        last[a[i] + M] = i;
    }
    
    // for (int i = 1; i <= n; i++) {
    //     printf("%d %d\n", st[i], f[i]);
    // }
    
    for (int i = 1; i <= n; i++) mx[i][0] = f[i];
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        int li, ri;
        scanf("%d%d", &li, &ri);
        ++li, ++ri;
        
        int mi = Find(li, ri), ans = 0, tmp;
        if (mi > li) ans = mi - li;
        if (mi <= ri) {
            tmp = Query(mi, ri);
            ans = max(ans, tmp);
        }
        printf("%d\n", ans);
    }
    
    
    
    
    return 0;
}