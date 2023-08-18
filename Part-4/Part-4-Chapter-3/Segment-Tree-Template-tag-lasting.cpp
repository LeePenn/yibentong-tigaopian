#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e6 + 10;
int n, m;
LL a[N], sum[N << 2], add[N << 2];

void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void modify(int k, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        add[k] += v;
        return;
    }
    sum[k] += (LL)(min(r, ri) - max(l, li) + 1) * v;
    int mid = (l + r) >> 1;
    if (mid >= li) modify(k << 1, l, mid, li, ri, v);
    if (mid < ri) modify(k << 1 | 1, mid + 1, r, li, ri, v);
}

LL query(int k, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return sum[k] + (r - l + 1) * add[k];
    }
    
    LL res = 0;
    res += (LL)(min(r, ri) - max(l, li) + 1) * add[k];
    int mid = (l + r) >> 1;
    if (mid >= li) res += query(k << 1, l, mid, li, ri);
    if (mid < ri) res += query(k << 1 | 1, mid + 1, r, li, ri);
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    
    build(1, 1, n);
    
    int t, l, r, x;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d%d", &l, &r, &x);
            modify(1, 1, n, l, r, x);
        } else if (t == 2) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        }
    
    }


    return 0;
}