#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e6 + 10, K = 1e4 + 2;

int n, k, p;
vector<int> ht[K];
int last[N];

int main() {
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 0; i < k; i++) {
        ht[i].push_back(0);
    }
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (b <= p) {
            last[i] = i;
        } else {
            last[i] = last[i - 1];
        }
        ht[a].push_back(i);
    }
    
    LL ans = 0;
    for (int i = 0; i < k; i++) {
        int len = ht[i].size();
        LL l = 0;
        for (int j = 1; j < len; j++) {
            while (l + 1 < j && ht[i][l + 1] <= last[ht[i][j]]) {
                l++;
            }
            ans += l;
        }
    }
    
    printf("%lld\n", ans);

    return 0;
}