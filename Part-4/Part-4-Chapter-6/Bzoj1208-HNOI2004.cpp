#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f, MOD = 1e6;
int n;
int type, x;
struct Node {
    int lc, rc, val, pr;
    #define lc(x) t[x].lc
    #define rc(x) t[x].rc
    #define val(x) t[x].val
    #define pr(x) t[x].pr
}t[N];
int rt, T;
int number;

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
        val(k) = val, pr(k) = rand();
        return;
    }
    
    if (val <= val(k)) {
        Insert(lc(k), val);
        if (pr(lc(k)) < pr(k)) Zig(k);
    } 
    if (val > val(k)) {
        Insert(rc(k), val);
        if (pr(rc(k)) < pr(k)) Zag(k);
    }
}

int QueryPre(int k, int val) {
    int pre = -INF;
    while (k) {
        if (val(k) <= val) {
            pre = val(k);
            k = rc(k);
        } else k = lc(k);
    }
    return pre;
}

int QuerySuf(int k, int val) {
    int suf = INF;
    while (k) {
        if (val(k) > val) {
            suf = val(k);
            k = lc(k);
        } else k = rc(k);
    }
    return suf;
}

void DelTreap(int &k, int vi) {
    if (val(k) == vi) {
        if (!lc(k) || !rc(k)) {
            k = lc(k) + rc(k);
        } else {
            if (pr(lc(k)) < pr(rc(k))) {
                Zig(k);
                DelTreap(k, vi);
            } else {
                Zag(k);
                DelTreap(k, vi);
            }
        }
    } else if (vi < val(k)) {
        DelTreap(lc(k), vi);
    } else {
        DelTreap(rc(k), vi);
    }
} 

void work() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &type, &x);
        if (type == 0) {
            if (number >= 0) {
                Insert(rt, x);
            } else {
            
                int pre = QueryPre(rt, x), suf = QuerySuf(rt, x);
                if (x - pre <= suf - x) {
                    ans += x - pre;
                    DelTreap(rt, pre);
                } else {
                    ans += suf - x;
                    DelTreap(rt, suf);
                }
            }
            ++number;
        } else {
            if (number <= 0) {
                Insert(rt, x);
            } else {
                int pre = QueryPre(rt, x), suf = QuerySuf(rt, x);
                if (x - pre <= suf - x) {
                    ans += x - pre;
                    DelTreap(rt, pre);
                } else {
                    ans += suf - x;
                    DelTreap(rt, suf);
                }
            }
            --number;
        }
        ans %= MOD;
    }
    
    printf("%d\n", ans);
}

// 感觉需要用2个Treap，但是有这个条件：同一时间呆在收养所中的，要么全是宠物，要么全是领养者，可以用一个做
int main() {
    scanf("%d", &n);
    work();

    return 0;
}