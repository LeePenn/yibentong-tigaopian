#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 500004;
int n;
LL p[N], sum[N], rsum[N], b = 13331;
char s1[N], s2[N];

void init1() {
    p[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * b;
    }
}

void init2() {
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] * b + (s1[i] - '0' + 1);
    }
    
    rsum[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        rsum[i] = rsum[i + 1] * b + (s2[i] - '0' + 1);
    }
}

LL get_hash(int l, int r) {
    return sum[r] - sum[l - 1] * p[r - l + 1];
}

LL get_rhash(int l, int r) {
    return rsum[l] - rsum[r + 1]  * p[r - l + 1];
}

bool check(int k, int m) {
    if (k + m > n || k - m + 1 < 1) return false;
    return get_hash(k - m + 1, k) == get_rhash(k + 1, k + m);
}

int calc(int k) {
    int l = 1, r = n;
    int ret = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(k, m)) {
            ret = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ret;
}

int main() {
    init1();

    scanf("%d", &n);
    scanf("%s", s1 + 1);
    
    for (int i = 1; i <= n; i++) {
        s2[i] = '0' + '1' - s1[i];
    }
    
    init2();
    
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        // int t = calc(i);
        ans += calc(i);
        // printf("%d\n", t);
    }
    
    printf("%lld\n", ans);

    return 0;
}