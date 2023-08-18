#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int a[N], s[N];
int f[N], num[N], q[N], head, tail;
int ans;

void Read() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
}

void DP() {
    ans = -0x7fffffff;
    head = 1, tail = 1;
    for (int i = 1; i <= n; ++i) {
        while (num[head] < i - m && head <= tail) head++;
        ans = max(ans, s[i] - q[head]);
        while (s[i] <= q[tail] && head <= tail) tail--;
        num[++tail] = i;
        q[tail] = s[i];
    }
    printf("%d\n", ans);
}

int main() {
    Read();
    
    DP();

    return 0;
}