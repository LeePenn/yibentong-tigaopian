#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;

int m, p, ed;
int a[N], Max[N << 2];
int last = 0;

void build(int k, int l, int r) {
    if (l == r) {
        Max[k] = a[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    Max[k] = max(Max[k << 1], Max[k << 1 | 1]);
}

void modify(int k, int l, int r, int i, int v) {
    if (i < l || i > r) return;
    if (l == r && l == i) {
        Max[k] = v;
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= i) modify(k << 1, l, mid, i, v);
    if (i > mid) modify(k << 1 | 1, mid + 1, r, i, v);
    Max[k] = max(Max[k << 1], Max[k << 1 | 1]);
}

int query(int k, int l, int r, int li, int ri) {
    if (l > ri || r < li) return 0;
    if (l >= li && r <= ri) return Max[k];
    
    int mid = (l + r) >> 1;
    int res = 0;
    if (mid >= li) res = max(res, query(k << 1, l, mid, li, ri));
    if (mid < ri) res = max(res, query(k << 1 | 1, mid + 1, r, li, ri));
    return res;
}
    
int main() {    
    scanf("%d%d\n", &m, &p);
    ed = 0;
    build(1, 1, N - 1);
    
    char ch;
    int x;
    for (int i = 1; i <= m; i++) {
        scanf("%c %d\n", &ch, &x);
        if (ch == 'A') {
            ++ed;
            modify(1, 1, N - 1, ed, (x + last) % p);
        } else if (ch == 'Q') {
            last = query(1, 1, N - 1, ed - x + 1, ed);
            printf("%d\n", last);
        }
    }

    return 0;
}