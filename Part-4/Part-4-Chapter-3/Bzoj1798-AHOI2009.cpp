#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;

int n, P, m;
int a[N], add[N << 2], mul[N << 2], sum[N << 2];

int Add(int a, int b) {
    return ((LL)a + b) % P;
}

int Mul(int a, int b) {
    return (LL)1 * a * b % P;
}

void build(int k, int l, int r) {
    add[k] = 0;
    mul[k] = 1;
    if (l == r) {
        sum[k] = a[l] % P;
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    sum[k] = Add(sum[k << 1], sum[k << 1 | 1]);
}

void pushdown(int k, int l, int r, int mid) {
    if (add[k] != 0 || mul[k] != 1) {
        mul[k << 1] = Mul(mul[k], mul[k << 1]);
        add[k << 1] = Add(Mul(add[k << 1], mul[k]), add[k]);
        
        mul[k << 1 | 1] = Mul(mul[k], mul[k << 1 | 1]);
        add[k << 1 | 1] = Add(Mul(add[k << 1 | 1], mul[k]), add[k]);
        
        sum[k << 1] = Add(Mul(sum[k << 1], mul[k]), Mul(add[k], mid - l + 1));
        sum[k << 1 | 1] = Add(Mul(sum[k << 1 | 1], mul[k]), Mul(add[k], r - mid));
        
        add[k] = 0;
        mul[k] = 1;
    }
}

void modify_add(int k, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        add[k] = Add(add[k], v);
        sum[k] = Add(sum[k], Mul(r - l + 1, v));
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(k, l, r, mid);
    if (mid >= li) modify_add(k << 1, l, mid, li, ri, v);
    if (mid < ri) modify_add(k << 1 | 1, mid + 1, r, li, ri, v);
    sum[k] = Add(sum[k << 1], sum[k << 1 | 1]);
}

void modify_multi(int k, int l, int r, int li, int ri, int v) {
    if (l >= li && r <= ri) {
        mul[k] = Mul(mul[k], v);
        add[k] = Mul(add[k], v);
        sum[k] = Mul(sum[k], v);
        return;
    }
    
    int mid = (l + r) >> 1;
    pushdown(k, l, r, mid);
    if (mid >= li) modify_multi(k << 1, l, mid, li, ri, v);
    if (mid < ri) modify_multi(k << 1 | 1, mid + 1, r, li, ri, v);
    sum[k] = Add(sum[k << 1], sum[k << 1 | 1]);
}

int query(int k, int l, int r, int li, int ri) {
    if (l >= li && r <= ri) {
        return sum[k];
    }
    int mid = (l + r) >> 1;
    pushdown(k, l, r, mid);
    int res = 0;
    if (mid >= li) res = Add(res, query(k << 1, l, mid, li, ri));
    if (mid < ri) res = Add(res, query(k << 1 | 1, mid + 1, r, li, ri));
    
    return res;
}

int main() {
    scanf("%d%d", &n, &P);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    
    build(1, 1, n);
    
    scanf("%d", &m);
    int t, l, r, c;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d%d", &l, &r, &c);
            modify_multi(1, 1, n, l, r, c);
        } 
        if (t == 2) {
            scanf("%d%d%d", &l, &r, &c);
            modify_add(1, 1, n, l, r, c);
        }
        if (t == 3) {
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, 1, n, l, r));
        }
    }
    
    
    return 0;
}