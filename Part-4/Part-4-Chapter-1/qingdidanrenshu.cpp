#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 10;

int n, k;
LL a[N];

int lowbit(int i) {
    return i & (-i);
}

void update(int i, LL x) {
    while (i <= n) {
        a[i] += x;
        i += lowbit(i);
    }
}

LL sum(int i) {
    LL ans = 0;
    while (i) {
        ans += a[i];
        i -= lowbit(i);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &k);
    char c;
    string line;
    getline(cin, line);
    for (int i = 1; i <= k; i++) {
        scanf("%c", &c);
        if (c == 'A') {
            int x;
            scanf("%d", &x);
            printf("%lld\n", sum(x));
        } else if (c == 'B') {
            int m;
            LL p;
            scanf("%d%lld", &m, &p);
            update(m, p);
        } else if (c == 'C') {
            int m;
            LL p;
            scanf("%d%lld", &m, &p);
            update(m, -p);
        }
        getline(cin, line);
    }

    return 0;
}