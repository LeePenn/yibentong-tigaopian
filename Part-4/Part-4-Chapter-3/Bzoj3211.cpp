#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e6 + 10;

int n, m;
LL a[N], sum[N << 2], mx[N << 2];

void initRead1() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    scanf("%d", &m);
}

void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = a[l];
        mx[k] = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
    mx[k] = max(mx[k << 1], mx[k << 1 | 1]);
}

void modify(int k, int l, int r, int li, int ri) {
    if (l == r) {
        sum[k] = mx[k] = sqrt(sum[k]);
        return;
    }
    
    int mid = (l + r) >> 1;
    
    if (mid >= li && mx[k << 1] > 1) modify(k << 1, l, mid, li, ri);
    
    if (mid < ri && mx[k << 1 | 1] > 1) modify(k << 1 | 1, mid + 1, r, li, ri);
    
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
    mx[k] = max(mx[k << 1], mx[k << 1 | 1]);
}

LL query(int k, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return sum[k];
    }
    
    int mid = (l + r) >> 1;
    LL res = 0;
    if (mid >= li) res += query(k << 1, l, mid, li, ri);
    if (mid < ri) res += query(k << 1 | 1, mid + 1, r, li, ri);
    return res;
}

int main() {
    initRead1();
    build(1, 1, n);
    
    int t, l, r;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &t, &l, &r);
        if (l > r) swap(l, r);
        
        if (t == 1) {
            printf("%lld\n", query(1, 1, n, l, r));
        } else if (t == 2) {
            modify(1, 1, n, l, r);
        }
    }

    return 0;
}