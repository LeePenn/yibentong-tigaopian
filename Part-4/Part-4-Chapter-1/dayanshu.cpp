#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5000;

int n, m, t;
LL a[N][N];

int lowbit(int i) {
    return i & (-i);
}

void update(int x, int y, LL z) {
    while (x <= n) {
        int j = y;
        while (j <= m) {
            a[x][j] += z;
            j += lowbit(j);
        }
        x += lowbit(x);
    }
}

LL query(int x, int y) {
    LL ans = 0;
    while (x) {
        int j = y;
        while (j) {
            ans += a[x][j];
            j -= lowbit(j);
        }
        x -= lowbit(x);
    }
    return ans;
}

// 是左下角，右上角
LL sum(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

int main() {
    scanf("%d%d", &n, &m);
    while (scanf("%d", &t) == 1) {
        if (t == 1) {
            int x, y;
            LL k;
            scanf("%d%d%lld", &x, &y, &k);
            update(x, y, k);
        } else if (t == 2) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%lld\n", sum(x1, y1, x2, y2));
        }
    }

    return 0;
}