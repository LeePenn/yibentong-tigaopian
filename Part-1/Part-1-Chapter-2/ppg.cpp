#include <bits/stdc++.h>

using namespace std;

const int N = 52;
int n;
struct P {
    int x, y;
}p[N];
int f[N];

int find(int x) {
    if (x != f[x]) x = find(f[x]);
    return f[x];
}

void uni(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) f[fy] = fx;
}

bool can_reach(int i, int j, int m) {
    return abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y) <= 2 * m;
}

bool check(int m) {
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (can_reach(i, j, m)) uni(i, j);
        }
    }
    
    for (int i = 1; i < n; i++) {
        if (find(i) != find(i + 1)) return false;
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    
    int l = 1, r = 1000000000;
    int ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    cout << ans << endl;
    
    return 0;
}