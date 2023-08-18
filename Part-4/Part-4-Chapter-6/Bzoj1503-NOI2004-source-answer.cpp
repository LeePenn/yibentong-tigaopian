#include <bits/stdc++.h>
#define inf 1e9
using namespace std;
const int N = 1e5 + 10;
int n, m, k;
struct point {
    int val, rank;
    int lson, rson;
    int sz, cnt;
} t[N];
int idx, root;
inline void pushup(int x) {
    t[x].sz = t[x].cnt + t[t[x].lson].sz + t[t[x].rson].sz;
}
inline int create(int x) {
    t[++idx] = (point) {
        x, rand(), 0, 0, 1, 1
    };
    return idx;
}
void build() {
    create(inf);
    create(-inf);
    root = 1;
    t[1].lson = 2;
    pushup(root);
}
void zig(int &x) {
    int y = t[x].lson;
    t[x].lson = t[y].rson;
    t[y].rson = x;
    x = y;
    pushup(t[x].rson);
    pushup(x);
}
void zag(int &x) {
    int y = t[x].rson;
    t[x].rson = t[y].lson;
    t[y].lson = x;
    x = y;
    pushup(t[x].lson);
    pushup(x);
}
void insert(int &x, int v) {
    if (!x) {
        x = create(v);
        pushup(x);
        return;
    }

    if (v == t[x].val)
        t[x].cnt++;
    else if (v < t[x].val) {
        insert(t[x].lson, v);

        if (t[x].rank < t[t[x].lson].rank)
            zig(x);
    } else {
        insert(t[x].rson, v);

        if (t[x].rank < t[t[x].rson].rank)
            zag(x);
    }

    pushup(x);
}
void remove(int &x, int v) {
    if (!x)
        return;

    if (v == t[x].val) {
        if (t[x].cnt > 1)
            t[x].cnt--;
        else if (t[x].lson || t[x].rson) {
            if (!t[x].rson || t[t[x].lson].rank > t[t[x].rson].rank) {
                zig(x);
                remove(t[x].rson, v);
            } else {
                zag(x);
                remove(t[x].lson, v);
            }
        } else
            x = 0;
    } else if (v < t[x].val)
        remove(t[x].lson, v);
    else
        remove(t[x].rson, v);

    pushup(x);
}
int get_num(int x, int v) {
    if (!x)
        return inf;

    if (v <= t[t[x].lson].sz)
        return get_num(t[x].lson, v);
    else if (v <= t[t[x].lson].sz + t[x].cnt)
        return t[x].val;
    else
        return get_num(t[x].rson, v - t[t[x].lson].sz - t[x].cnt);
}
char opt;
int x;
int main() {
    scanf("%d%d", &n, &k);
    build();
    int s = 0, ans = 0;

    while (n--) {
        cin >> opt;
        scanf("%d", &x);

        if (opt == 'I' && x >= k) {
            insert(root, x - s);
            m++;
        }

        if (opt == 'A') {
            s += x;
        }

        if (opt == 'S') {
            s -= x;
        }

        if (opt == 'F') {
            printf("%d\n", x <= m ? get_num(root, m - x + 2) + s : -1);
        }

        int now = get_num(root, 2);

        while (m && now + s < k) {
            m--;
            ans++;
            // printf("erase:%d\n",now);
            remove(root, now);
            now = get_num(root, 2);
        }
    }

    printf("%d\n", ans);
    return 0;
}