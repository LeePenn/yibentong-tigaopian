#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;

int n, q;
LL c[N];

int lowbit(int i) {
    return i & (-i);
}

void update(int i, LL x) {
    while (i <= n) {
        c[i] += x;
        i += lowbit(i);
    }
}

LL sum(int i) {
    LL ans = 0;
    while (i) {
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        LL x;
        scanf("%lld", &x);
        update(i, x);
    }
    
    for (int i = 1; i <= q; i++) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) {
            update(a, b);
        } else {
            printf("%lld\n", sum(b) - sum(a - 1));
        }
    }

    return 0;
}