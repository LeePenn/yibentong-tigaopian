#include <bits/stdc++.h>

using namespace std;

const int N = 63;
int n, a[N];
int len;
bool v[N];

bool dfs(int last, int l, int cnt) {
    if (cnt == 0) return true;
    if (l == len) return dfs(1, 0, cnt - 1);
    
    int i;
    for (i = last; i <= n; i++) {
        if (!v[i] && a[i] + l <= len) {
            v[i] = true;
            if (dfs(i, l + a[i], cnt)) return true;
            v[i] = false;
            
            if (l == 0 || l + a[i] == len) return false;
            int j = i;
            while (i <= n && a[i] == a[j]) i++;
        }
    }
    return false;
}

int main() {
    cin >> n;
    int tot = 0, maxL = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
        maxL = max(maxL, a[i]);
    }
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = maxL; i <= tot; i++) {
        if (tot % i == 0) {
            len = i;
            memset(v, 0, sizeof(v));
            if (dfs(1, 0, tot / i)) {
                cout << i << endl;
                return 0;
            }
        }
    }

    return 0;
}