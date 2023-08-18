#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 200005;
int n;
LL a[N], b = 13331;
LL p[N], sum[N], rsum[N];
map<LL, LL> m;
int ans[N];

LL get_hash(int l, int r) {
    return sum[r] - sum[l] * p[r - l];
}

LL get_rhash(int l, int r) {
    return rsum[l] - rsum[r] * p[r - l];
}

int main() {
    scanf("%d", &n);
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * b;
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] * b + a[i];
    }
    
    for (int i = n; i >= 0; i--) {
        rsum[i] = rsum[i + 1] * b + a[i];
    }
    
    int maxn = 0, tot = 0;
    for (int k = 1; k <= n; k++) {
        m.clear();
        if (k * maxn > n) break;
        int cur = 0;
        for (int i = k; i <= n; i += k) {
            LL n1 = get_hash(i - k, i);
            LL n2 = get_rhash(i - k + 1, i + 1);
            LL n3 = n1 * n2;
            if (m[n3]) {
                continue;
            }
            m[n3]++;
            cur++;
        }
        if (cur == maxn) {
            ans[++tot] = k;
        }
        
        if (cur > maxn) {
            tot = 0;
            maxn = cur;
            ans[++tot] = k;
        }
    }
    printf("%d %d\n", maxn, tot);
    for (int i = 1; i <= tot; i++) printf("%d ", ans[i]);
    printf("\n");


    return 0;
}