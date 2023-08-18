#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, minn;
struct Node {
    int lc, rc, val, pr, sz, cnt;
    #define lc(x) t[x].lc
    #define rc(x) t[x].rc
    #define val(x) t[x].val
    #define pr(x) t[x].pr
    #define sz(x) t[x].sz
    #define c(x) t[x].cnt
}t[N];
int rt, T;

void Create(const int x) {
    val(++T) = x;
    lc(T) = rc(T) = 0;
    pr(T) = rand();
    sz(T) = c(T) = 1;
}

void pushUp(int k) {
    sz(k) = c(k) + sz(lc(k)) + sz(rc(k));
}

void Build() {
    Create(INF);
    Create(-INF);
    rt = 1;
    lc(1) = 2;
    pushUp(1);
}

void Zig(int &k) {
    int x = lc(k);
    lc(k) = rc(x);
    rc(x) = k;
    sz(x) = sz(k);
    pushUp(k);
    k = x;
}

void Zag(int &k) {
    int x = rc(k);
    rc(k) = lc(x);
    lc(x) = k;
    sz(x) = sz(k);
    pushUp(k);
    k = x;
}

void Insert(int &k, const int val) {
    if (!k) {
        k = ++T;
        val(k) = val;
        pr(k) = rand();
        lc(k) = rc(k) = 0;
        sz(k) = c(k) = 1;
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

int QueryMinKth(int k, const int rk) {
    if (!k) return INF;
    
    if (sz(lc(k)) >= rk) return QueryMinKth(lc(k), rk);
    else if (sz(lc(k)) + c(k) >= rk) return val(k);
    else return QueryMinKth(rc(k), rk - sz(lc(k)) - c(k));
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

void work() {
    char op;
    int x;
    int s = 0, ans = 0;
    int tot = 0;
    while (n--) {
        op = getchar();
        scanf("%d\n", &x);
        
        if (op == 'I' && x >= minn) {
            Insert(rt, x - s);
            ++tot;
        } 
        
        if (op == 'A') s += x;
        
        if (op == 'S') s -= x;
        
        if (op == 'F') {
            printf("%d\n", x <= tot ? QueryMinKth(rt, tot - x + 2) + s : -1);
        }
        
        int now = QueryMinKth(rt, 2);
        
        while (tot && now + s < minn) {
            --tot;
            ++ans;
            Remove(rt, now);
            now = QueryMinKth(rt, 2);
        }
    }
    
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d", &n, &minn);
    Build();
    
    string line;
    getline(cin, line);
    work();


    return 0;
}