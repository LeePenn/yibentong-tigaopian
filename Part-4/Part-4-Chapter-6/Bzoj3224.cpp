#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n;
struct Node {
    int lc, rc, val, cnt, pr, sz;
    #define lc(x) t[x].lc
    #define rc(x) t[x].rc
    #define val(x) t[x].val
    #define c(x) t[x].cnt
    #define pr(x) t[x].pr
    #define sz(x) t[x].sz
}t[N];
int op, x;
int rt, T;

void pushUp(int k) {
    sz(k) = c(k) + sz(lc(k)) + sz(rc(k));
}

void Zig(int &k) {
    int y = lc(k);
    lc(k) = rc(y);
    rc(y) = k;
    sz(y) = sz(k);
    pushUp(k);
    k = y;
}

void Zag(int &k) {
    int y = rc(k);
    rc(k) = lc(y);
    lc(y) = k;
    sz(y) = sz(k);
    pushUp(k);
    k = y;
}

void Insert(int &k, const int val) {
    if (!k) {
        k = ++T;
        val(k) = val;
        lc(k) = rc(k) = 0;
        sz(k) = c(k) = 1;
        pr(k) = rand();
        return;
    }
    
    if (val == val(k)) {
        ++c(k);
    } else if (val < val(k)) {
        Insert(lc(k), val);
        if (pr(lc(k)) < pr(k)) {
            Zig(k);
        }
    } else {
        Insert(rc(k), val);
        if (pr(rc(k)) < pr(k)) {
            Zag(k);
        }
    }
    
    pushUp(k);
}

void Remove(int &k, const int val) {
    if (val(k) == val) {
        if (c(k) > 1) {
            --c(k), --sz(k);
        } else if (!lc(k) || !rc(k)) {
            k = lc(k) + rc(k);
        } else if (pr(lc(k)) < pr(rc(k))) {
            Zig(k);
            Remove(k, val);
        } else {
            Zag(k);
            Remove(k, val);
        }
        return;
    }
    
    
    --sz(k);
    if (val < val(k)) Remove(lc(k), val);
    else Remove(rc(k), val);
}

int QueryRank(int k, int val) {
    int ret = 0;
    while (k) {
        if (val == val(k)) return ret + sz(lc(k)) + 1;
        else if (val < val(k)) k = lc(k);
        else {
            ret += sz(lc(k)) + c(k);
            k = rc(k);
        }
    }
    
    return ret;
}

int QueryKth(int k, int rk) {
    if (!k) return INF;
    
    if (sz(lc(k)) >= rk) return QueryKth(lc(k), rk);
    else if (sz(lc(k)) + c(k) >= rk) return val(k);
    else return QueryKth(rc(k), rk - sz(lc(k)) - c(k));
}

int QueryPre(int k, int val) {
    int ret = -INF;
    while (k) {
        // 不能 <= 特别注意
        if (val(k) < val) {
            ret = val(k);
            k = rc(k);
        } else k = lc(k);
    }
    return ret;
}

int QuerySuf(int k, int val) {
    int ret = INF;
    while (k) {
        // 不能 >= 特别注意
        if (val(k) > val) {
            ret = val(k);
            k = lc(k);
        } else k = rc(k);
    }
    return ret;
}

void work() {
    while (n--) {
        scanf("%d%d", &op, &x);
        if (op == 1) Insert(rt, x);
        
        if (op == 2) Remove(rt, x);
        
        if (op == 3) printf("%d\n", QueryRank(rt, x));
        
        if (op == 4) printf("%d\n", QueryKth(rt, x));
        
        if (op == 5) printf("%d\n", QueryPre(rt, x));
        
        if (op == 6) printf("%d\n", QuerySuf(rt, x));
    }
}

int main() {
    scanf("%d", &n);
    work();


    return 0;
}