#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1000004;
const int P = 133331;
int n;
LL a[N];
LL hd[N], ne[N], num[N], tot;


LL get_hash(LL a) {
    return a % P;
}

void Remove(LL a) {
    LL h = get_hash(a);
    hd[h] = 0;
}

bool Find(LL b) {
    LL h = get_hash(b);
    for (LL i = hd[h]; i; i = ne[i]) {
        if (num[i] == b) return true;
    }
    return false;
}

void Insert(LL a) {
    LL h = get_hash(a);
    ne[++tot] = hd[h];
    hd[h] = tot;
    num[tot] = a;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    int l = 1, r = 0;
    int ans = 0;
    while (r <= n) {
        r++;
        if (!Find(a[r])) {
            Insert(a[r]);
        } else {
            ans = max(ans, r - l);
            while (a[r] != a[l]) {
                Remove(a[l]);
                l++;
            }
            Remove(a[l]);
            l++;
            Insert(a[r]);
        }
    }
    
    printf("%d\n", ans);

    return 0;
}