#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pi acos(-1)
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 505;
const int length = 25;
ll n, m, p;
char s[N];
int nxt[N];
struct node {
    ll matrix[length + 5][length + 5] = {0};
    node(int x = 0) {
        for (int i = 0; i < length; i++) {
            matrix[i][i] = x;
        }
    }
};
node mul(node a, node b) {
    node ans;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                ans.matrix[i][j] = (ans.matrix[i][j] + a.matrix[i][k] * b.matrix[k][j] % p) % p;
            }
        }
    }

    return ans;
}
node pow(node a, ll k) {
    node ans(1);

    while (k) {
        if (k & 1) {
            ans = mul(ans, a);
        }

        k >>= 1;
        a = mul(a, a);
    }

    return ans;
}
int main() {
    scanf("%lld%lld%lld", &n, &m, &p);
    scanf("%s", s + 1);
    node ans, base;
    nxt[1] = 0;
    int pre = 0, slen = strlen(s + 1);

    for (int i = 2; i <= slen; i++) {
        while (pre && s[pre + 1] != s[i])
            pre = nxt[pre];

        if (s[pre + 1] == s[i]) {
            ++pre;
        }

        nxt[i] = pre;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= 9; j++) {
            pre = i;

            while (pre && s[pre + 1] != j + '0')
                pre = nxt[pre];

            if (s[pre + 1] == j + '0') {
                ++pre;
            }

            if (i != m) {
                base.matrix[i][pre] = (base.matrix[i][pre] + 1) % p;
            }
        }
    }

    ans.matrix[0][0] = 1;
    ans = mul(ans, pow(base, n));
    ll sum = 0;

    for (int i = 0; i < m; i++) {
        sum = (sum + ans.matrix[0][i]) % p;
    }

    printf("%lld\n", sum);
    return 0;
}