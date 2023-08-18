#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;

int n, m;
LL a[N], sum[4 * N];

void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build((k << 1) + 1, mid + 1, r);
    sum[k] = sum[k << 1] + sum[(k << 1) + 1];
}

void update(int k, int l, int r, int i, int x) {
    if (l > i || r < i) return;
    if (l == r && l == i) {
        sum[k] += x;
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid) update(k << 1, l, mid, i, x);
    if (i > mid) update((k << 1) + 1, mid + 1, r, i, x);
    sum[k] = sum[k << 1] + sum[(k << 1) + 1];
}

LL query(int k, int l, int r, int li, int ri) {
    if (l > ri || r < li) return 0;
    if (l >= li && r <= ri) return sum[k];
    int mid = (l + r) >> 1;
    return query(k << 1, l, mid, li, ri) + query((k << 1) + 1, mid + 1, r, li, ri);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    
    for (int i = 1; i <= m; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int a, b;
            scanf("%d%d", &a, &b);
            update(1, 1, n, a, b);
        } else if (t == 2) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }

    return 0;
}