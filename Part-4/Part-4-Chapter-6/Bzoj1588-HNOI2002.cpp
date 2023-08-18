#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f;

int n, ans;
struct Node {
    int lc, rc, val, pr, fa;
    #define lc(x) t[x].lc
    #define rc(x) t[x].rc
    #define val(x) t[x].val
    #define pr(x) t[x].pr
    #define fa(x) t[x].fa;
}t[N];
int rt, T;

void Zig(int &k) {
    int x = lc(k);
    lc(k) = rc(x);
    rc(x) = k;
    k = x;
}

void Zag(int &k) {
    int x = rc(k);
    rc(k) = lc(x);
    lc(x) = k;
    k = x;
}

void Insert(int &k, const int val) {
    if (!k) {
        ++T;
        k = T;
        val(k) = val;
        pr(k) = rand();
        return;
    }
    
    if (val(k) > val) {
        Insert(lc(k), val);
        if (pr(lc(k)) < pr(k)) Zig(k);
    }
    if (val(k) < val) {
        Insert(rc(k), val);
        if (pr(rc(k)) < pr(k)) Zag(k);
    }
}

int QueryPre(int k, const int val) {
    int pre = -INF;
    while (k) {
        if (val(k) <= val) {
            pre = val(k);
            k = rc(k);
        } else k = lc(k);
    }
    return pre;
}

int QuerySuf(int k, const int val) {
    int suf = INF;
    while (k) {
        if (val(k) > val) {
            suf = val(k);
            k = lc(k);
        } else k = rc(k);
    }
    return suf;
}

void work() {
    int v, pre, suf;
    for (int i = 1; i < n; i++) {
        scanf("%d", &v);
        pre = QueryPre(rt, v), suf = QuerySuf(rt, v);
        ans += min(v - pre, suf - v);
        Insert(rt, v);
    }
    
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &n);
    scanf("%d", &ans);
    Insert(rt, ans);
    
    work();

    return 0;
}