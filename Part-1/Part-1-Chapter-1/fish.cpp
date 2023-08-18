#include <bits/stdc++.h>

using namespace std;

int n;
struct pond {
    int fish, d;
}p[103];
int t[103];
int H;

int main() {
    cin >> n >> H;
    H *= 12;
    for (int i = 1; i <= n; i++) cin >> p[i].fish;
    for (int i = 1; i <= n; i++) cin >> p[i].d;
    for (int i = 1; i < n; i++) cin >> t[i];

    int cost = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int totTime = H - cost;
        priority_queue<pair<int, int>, vector<pair<int, int>> > pq;
        for (int j = 1; j <= i; j++) {
            pq.push(make_pair(p[j].fish, j));
        }
        int cur = 0;
        while (totTime > 0 && pq.top().first > 0) {
            pair<int, int> cur_pond = pq.top(); pq.pop();
            int idx = cur_pond.second, f = cur_pond.first;
            cur += f; 
            int cur_pond_fish = f - p[idx].d;
            pq.push(make_pair(cur_pond_fish, idx));
            totTime--;
        }
        if (cur > ans) ans = cur;

        cost += t[i];
    }
    cout << ans << endl;
    
    return 0;
}