#include <bits/stdc++.h>
using namespace std;
const int N = 15000 + 10, M = 32000 + 10;
int n;
int a[M];
int c[M], ans[N];

int lowbit(int i) {
    return i & (-i);
}

void update(int i, int x) {
    while (i <= M) {
        c[i] += x;
        i += lowbit(i);
    }
}

int sum(int i) {
    int res = 0;
    while (i) {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[i] = x + 1;
    }
    
    for (int i = 1; i <= n; i++) {
        ans[sum(a[i])]++;
        update(a[i], 1);
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}