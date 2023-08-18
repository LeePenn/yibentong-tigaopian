#include <bits/stdc++.h>

using namespace std;

int N, M;
int ans;
int sumV[22], sumS[22];
const int MAX = 1000000000;

void init() {
    for (int i = 1; i <= M; i++) {
        sumV[i] = sumV[i - 1] + i * i * i;
        sumS[i] = sumS[i - 1] + 2 * i * i;
    }
}

void dfs(int d, int tot_v, int tot_s, int r, int h) {
    if (d == 0) {
        if (tot_v == N) {
            ans = min(ans, tot_s);
        }
        return;
    }
    
    if (tot_v + sumV[d - 1] > N) return;
    if (tot_s + sumS[d - 1] > ans) return;
    
    for (int i = r - 1; i >= d; --i) {
        if (2 * (N - tot_v) / i + tot_s > ans) return;
        for (int j = h - 1; j >= d; --j) {
            int cur_v = i * i * j;
            int cur_s = 2 * i * j;
            if (d == M) cur_s += i * i;
            dfs(d - 1, tot_v + cur_v, tot_s + cur_s, i, j);
        }
    }

}

int main() {
    cin >> N >> M;
    init();
    ans = MAX;
    dfs(M, 0, 0, sqrt(N), N);
    if (ans == MAX) cout << 0 << endl;
    else cout << ans << endl;

    return 0;
}