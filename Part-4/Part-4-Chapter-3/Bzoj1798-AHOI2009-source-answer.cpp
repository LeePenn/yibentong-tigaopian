#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int mod;
int read() {
    int x = 0, f = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -f;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }

    return x * f;
}
int mul(int x, int y) {
    return 1LL * x * y % mod;
}
int add(int x, int y) {
    return x + y >= mod ? x + y - mod : x + y;
}
int lazy_mul[N << 2], lazy_add[N << 2], f[N << 2];
void build(int l, int r, int k) { //建树
    lazy_add[k] = 0;
    lazy_mul[k] = 1; //初始化，×1+0

    if (l == r) {
        f[k] = read() % mod;
        return;
    }

    int mid = (l + r) >> 1;
    build(l, mid, k << 1);
    build(mid + 1, r, k << 1 | 1);
    f[k] = add(f[k << 1], f[k << 1 | 1]);
}
void down(int k, int l, int r) { //标记下传操作
    if (lazy_add[k] != 0 || lazy_mul[k] != 1) {
        // [down]
        // a = lazy_mul[k<<1], b = lazy_add[k<<1]
        // c = lazy_mul[k], d = lazy_add[k]
        // c' = ac, d' = bc+d
        // left
        lazy_mul[k << 1] = mul(lazy_mul[k], lazy_mul[k << 1]); //ac
        lazy_add[k << 1] = add(mul(lazy_add[k << 1], lazy_mul[k]), lazy_add[k]); //bc+d
        // right
        lazy_mul[k << 1 | 1] = mul(lazy_mul[k], lazy_mul[k << 1 | 1]); //ac
        lazy_add[k << 1 | 1] = add(mul(lazy_add[k << 1 | 1], lazy_mul[k]), lazy_add[k]); //bc+d
        // [update]
        // x = f[k<<1]
        // a = lazy_mul[k], b = lazy_add[k]
        // size = l (or r)
        // x' = x*a+b*size
        // left
        f[k << 1] = add(mul(f[k << 1], lazy_mul[k]), mul(lazy_add[k], l));
        // right
        f[k << 1 | 1] = add(mul(f[k << 1 | 1], lazy_mul[k]), mul(lazy_add[k], r));
        // clear
        lazy_add[k] = 0;
        lazy_mul[k] = 1;
    }
}
int query(int L, int R, int l, int r, int k) { //区间查询
    if (L <= l && r <= R)
        return f[k];

    int mid = (l + r) / 2;
    down(k, mid - l + 1, r - mid);
    int ans = 0;

    if (L <= mid)
        ans = add(ans, query(L, R, l, mid, k << 1));

    if (R > mid)
        ans = add(ans, query(L, R, mid + 1, r, k << 1 | 1));

    return ans;
}
void modify_add(int L, int R, int v, int l, int r, int k) { //区间修改
    if (L <= l && r <= R) {
        f[k] = add(f[k], mul(v, r - l + 1));
        lazy_add[k] = add(lazy_add[k], v);
        return;
    }

    int mid = (l + r) / 2;
    down(k, mid - l + 1, r - mid);

    if (L <= mid)
        modify_add(L, R, v, l, mid, k << 1);

    if (R > mid)
        modify_add(L, R, v, mid + 1, r, k << 1 | 1);

    f[k] = add(f[k << 1], f[k << 1 | 1]);
}
void modify_mul(int L, int R, int v, int l, int r, int k) { //区间修改
    if (L <= l && r <= R) {
        f[k] = mul(f[k], v);
        lazy_mul[k] = mul(lazy_mul[k], v);
        lazy_add[k] = mul(lazy_add[k], v);
        return;
    }

    int mid = (l + r) / 2;
    down(k, mid - l + 1, r - mid);

    if (L <= mid)
        modify_mul(L, R, v, l, mid, k << 1);

    if (R > mid)
        modify_mul(L, R, v, mid + 1, r, k << 1 | 1);

    f[k] = add(f[k << 1], f[k << 1 | 1]);
}
int main() {
    int n = read();
    mod = read();
    build(1, n, 1);
    int m = read();

    while (m -- > 0) {
        int op = read();

        switch (op) {
        case 1: {
            int l = read(), r = read(), v = read();
            modify_mul(l, r, v, 1, n, 1);
            break;
        }

        case 2: {
            int l = read(), r = read(), v = read();
            modify_add(l, r, v, 1, n, 1);
            break;
        }

        case 3: {
            int l = read(), r = read();
            printf("%d\n", query(l, r, 1, n, 1));
            break;
        }
        }
    }

    return 0;
}