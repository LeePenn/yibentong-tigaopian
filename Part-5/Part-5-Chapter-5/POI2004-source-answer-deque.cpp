#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define db double
#define ld long double
#define pii pair<int,int>
#define pdd pair<db,db>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
//cout<<setiosflags(ios::fixed)<<setprecision(K);
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const double eps = 1e-9;
const double PI = acos(-1.0);
const int inf = 1e9 + 7;
const int mod = 998244353;
const int N = 2e5 + 10, M = N << 1;

void solve() {
    int n;
    cin >> n;
    int t = 2 * n + 1;
    vector<int>dis(t), sup(t), s(t);

    for (int i = 1; i <= n; i++)
        cin >> sup[i] >> dis[i];

    vector<bool>f(n + 1, 0);

    for (int i = 1; i <= n; i++)
        s[i] = s[i + n] = sup[i] - dis[i];

    for (int i = 1; i <= 2 * n; i++)
        s[i] += s[i - 1]; //前缀和

    deque<int>q;

    for (int i = 2 * n; i >= 1; i--) { //当前算的是i
        while (!q.empty() && s[q.back()] >= s[i])
            q.pop_back();

        q.push_back(i);

        if (q.front() > i + (n - 1))
            q.pop_front();

        if (i <= n && s[q.front()] >= s[i - 1])
            f[i] = 1;
    }

    //逆时针
    q.clear();
    dis[0] = dis[n];

    for (int i = n; i >= 1; i--)
        s[i] = s[i + n] = sup[i] - dis[i - 1];

    for (int i = 2 * n; i >= 1; i--)
        s[i] += s[i + 1]; //后缀和

    for (int i = 1; i <= 2 * n; i++) { //当前算的是i
        while (!q.empty() && s[q.back()] >= s[i])
            q.pop_back();

        q.push_back(i);

        if (q.front() < i - (n - 1))
            q.pop_front();

        if (i > n && s[q.front()] >= s[i + 1])
            f[i - n] = 1;
    }

    for (int i = 1; i <= n; i++)
        cout << (f[i] ? "TAK" : "NIE") << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;

    //cin>>T;
    while (T--) {
        solve();
    }

    return 0;
}