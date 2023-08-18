#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int n, m;
int a1[N], a2[N];
int t, l, r;

int lowbit(int i) {
    return i & (-i);
}

void update(int a[], int i, int x) {
    while (i <= n) {
        a[i] += x;
        i += lowbit(i);
    }
}

int sum(int a[], int i) {
    int ans = 0;
    while (i) {
        ans += a[i];
        i -= lowbit(i);
    }
    return ans;
}

int calc(int x) {
    return x & 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &l, &r);
            update(a1, r, 1);
            update(a2, l, 1);
        } else if (t == 2) {
            scanf("%d", &l);
            printf("%d\n", calc(sum(a2, l) - sum(a1, l - 1)));
        }
    }
    return 0;
}