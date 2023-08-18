#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
int n, m;
int c1[N], c2[N];

int lowbit(int i) {
    return i & (-i);
}

void update(int a[], int i, int x) {
    while (i < N) {
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

int main() {
    scanf("%d%d", &n, &m);
    int k, l, r;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &k, &l, &r);
        if (k == 1) {
            update(c1, r, 1);
            update(c2, l, 1);
        } else if (k == 2) {
            printf("%d\n", sum(c2, r) - sum(c1, l - 1));
        }
    }
    

    return 0;
}