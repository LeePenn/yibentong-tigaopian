#include <bits/stdc++.h>

using namespace std;

const int N = 20;
const int MAX = 10000000;
long long a, b, ans[N], t[N];
int min_len;
bool found;

long long gcd(long long a, long long b) {
    return a % b == 0 ? b : gcd(b, a % b);
}

void dfs(int cnt, int from, long long x, long long y) {
    if (x == 1 && y <= from - 1) return;
    if (x == 1) {
        if (!found || y < ans[min_len]) {
            t[cnt] = y;
            memcpy(ans, t, sizeof(ans));
            found = true;
            return;
        }
    }
    
    
    if (cnt >= min_len) return;
    
    for (int i = from; ; i++) {
        if (x * i >= y * (min_len - cnt + 1)) break;
        long long new_x = x * i, ny = y * i;
        if (new_x < y) continue;
        long long nx = new_x - y;
        t[cnt] = i;
        long long d = gcd(nx, ny);
        nx /= d; ny /= d;
        dfs(cnt + 1, i + 1, nx, ny);
    }
    
}

int main() {    
    scanf("%lld%lld", &a, &b);
    for (int i = 1; i < N; i++) ans[i] = MAX;
    
    found = false;
    for (min_len = 1; ; min_len++) {
        dfs(1, 2, a, b);
        if (found) break;
    }
    for (int i = 1; i <= min_len; i++) printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}