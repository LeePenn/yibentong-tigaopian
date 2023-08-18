#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define int128 __int128
#define FOR(i, m, n) for(int i=(m);i<=(n);i++)
#define ROF(i, m, n) for(int i=(m);i>=(n);i--)
#define REP(i, n) for(int i=0;i<(n);i++)
#define BG(v) v.begin()
#define ED(v) v.end()
#define ALL(v) (v).begin(), (v).end()
#define SZ(v) v.size()
#define FI(v) v.first
#define SE(v) v.second
#define func(v) function<v>
#define DFS func(void(int, int))
#define PII pair<int,int>
#define PLL pair<ll, ll>
const int INF = 1e9 + 7;
const ll LINF = 1e18 + 7;
const double EPS = 1e-8;
const int P = 998244353;
const int G = 3;
const int GI = 332748118;
template <typename T, typename U>
inline bool chmax(T &a, U b) {
    return a < b ? (a = b, true) : false;
}
template <typename T, typename U>
inline bool chmin(T &a, U b) {
    return a > b ? (a = b, true) : false;
}
void IOSinit() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
int fp(int x, int y) {
    int res = 1;

    for (; y; y >>= 1) {
        if (y & 1)
            res = (1ll * res * x) % P;

        x = (1ll * x * x) % P;
    }

    return res;
}
struct Graph {
    vector<int> fi, to, ne;
    vector<int> ru, ch;
    vector<int> vis, ans;
    int cnt, n, m, T;
    void add(int u, int v) {
        ne[++cnt] = fi[u];
        to[cnt] = v;
        fi[u] = cnt;
        ru[v]++;
        ch[u]++;
    }
    void dfs(int u) {
        for (int i = fi[u]; i; i = fi[u]) {
            if (vis[i]) {
                fi[u] = ne[i];
                continue;
            }

            int v = to[i];
            vis[i] = 1;

            if (T == 1)
                vis[i ^ 1] = 1;

            dfs(v);

            if (T == 2)
                ans.push_back(i - 1);
            else {
                if (i % 2)
                    ans.push_back(-(i / 2));
                else
                    ans.push_back(i / 2);
            }
        }
    }
    Graph(int x, int y, int t) {
        n = x;
        m = y;
        T = t;
        cnt = 1;
        fi.resize(n + 5);
        ne.resize(2 * m + 5);
        to.resize(2 * m + 5);
        ru.resize(n + 5);
        ch.resize(n + 5);
        vis.resize(2 * m + 5);
    }
};
void solve() {
    int T, n, m;
    cin >> T >> n >> m;
    Graph g = Graph(n, m, T);
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        g.add(u, v);

        if (T == 1)
            g.add(v, u);
    }
    auto check = [&]() {
        FOR(i, 1, n) {
            if (T == 1 && g.ru[i] % 2)
                return 0;

            if (T == 2 && g.ru[i] != g.ch[i])
                return 0;
        }
        FOR(i, 1, n) {
            if (g.fi[i]) {
                g.dfs(i);
                break;
            }
        }

        if (g.ans.size() < m)
            return 0;

        return 1;
    };

    if (!check()) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    reverse(ALL(g.ans));

    for (int i : g.ans)
        cout << i << " ";
}
int main() {
    IOSinit();
    solve();
    return 0;
}