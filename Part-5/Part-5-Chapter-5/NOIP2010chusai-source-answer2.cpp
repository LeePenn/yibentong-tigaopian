#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <climits>
#include <deque>

using namespace std;

int N, M;

array < int, 200000 + 1 > costs;
array < int, 200000 + 1 > dp;

int main() {
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> costs.at(i);
    }

    deque<int> dq;

    dp.at(0) = 0;

    for (int i = 1; i <= N; i++) {
        if (!dq.empty() && i - dq.front() > M) {
            dq.pop_front();
        }

        while (!dq.empty() && dp.at(dq.back()) > dp.at(i - 1)) {
            dq.pop_back();
        }

        dq.push_back(i - 1);
        dp.at(i) = costs.at(i) + dp.at(dq.front());
    }

    int ans = INT_MAX;

    for (int i = max(0, N + 1 - M); i <= N; i++) {
        ans = min(ans, dp.at(i));
    }

    cout << ans << endl;
}