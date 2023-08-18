#include <cfloat>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
struct EDGE {
    int to, w, Next;
    EDGE() {
        to = w = Next = 0;
    }
    EDGE(int To, int W, int NEXT) {
        to = To;
        w = W;
        Next = NEXT;
    }
} edge[10005];
int head[10005], total;
inline void add_edge(int x, int y, int w) {
    edge[++total] = EDGE(y, w, head[x]);
    head[x] = total;
}
int T;
int n, t[1005];
int cnt[100], R[100], Pre[100];
inline void add(int mid) {
    total = 0;
    memset(head, 0, sizeof(head));

    for (int i = 1; i <= 24; i++)
        add_edge(i - 1, i, 0);

    for (int i = 1; i <= 24; i++)
        add_edge(i, i - 1, -cnt[i]);

    for (int i = 9; i <= 24; i++)
        add_edge(i - 8, i, R[i]);

    for (int i = 1; i <= 8; i++)
        add_edge(i + 16, i, R[i] - mid);

    add_edge(0, 24, mid);
}
bool inq[100];
int dis[100], in[100];
inline bool spfa(int mid) {
    for (int i = 0; i <= 50; i++)
        dis[i] = -0x3f3f3f3f;

    memset(inq, false, sizeof(inq));
    memset(in, 0, sizeof(in));
    queue<int>q;
    dis[0] = 0;
    inq[0] = true;
    in[0]++;
    q.push(0);
    int pos;

    while (!q.empty()) {
        pos = q.front();
        q.pop();
        inq[pos] = false;

        for (int e = head[pos], Next; e; e = edge[e].Next) {
            Next = edge[e].to;

            if (dis[Next] < dis[pos] + edge[e].w) {
                dis[Next] = dis[pos] + edge[e].w;

                if (!inq[Next]) {
                    inq[Next] = true;
                    q.push(Next);
                    in[Next]++;

                    if (in[Next] > 24 + 1)
                        return false;
                }
            }
        }
    }

    return dis[24] == mid;
}
inline bool check(int mid) {
    add(mid);
    return spfa(mid);
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> T;

    while (T--) {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= 24; i++)
            cin >> R[i];

        cin >> n;

        for (int i = 1; i <= n; i++) {
            cin >> t[i];
            t[i]++;
            cnt[t[i]]++;
        }

        bool Sol = false;

        for (int i = 0; i <= n; i++) {
            if (check(i)) {
                Sol = true;
                cout << i << '\n';
                break;
            }
        }

        if (!Sol)
            cout << "No Solution\n";
    }

    return 0;
}