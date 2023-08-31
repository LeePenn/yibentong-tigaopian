#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pi acos(-1)
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 505;
const int length = 100;
int n, m, t, p = 2009;
struct node {
    int matrix[length + 5][length + 5] = {0};
    node() {
        memset(matrix, 0, sizeof(matrix));
    };
    node operator*(const node &rhs)const {
        node ans;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 1; k <= m; k++) {
                    ans.matrix[i][j] = (ans.matrix[i][j] + matrix[i][k] * rhs.matrix[k][j] % p) % p;
                }
            }
        }

        return ans;
    }
};
node pow(node a, int k) {
    node ans;

    for (int i = 1; i <= m; i++)
        ans.matrix[i][i] = 1;

    while (k) {
        if (k & 1)
            ans = ans * a;

        k >>= 1;
        a = a * a;
    }

    return ans;
}
int main() {
    scanf("%d%d", &n, &t);
    m = 9 * n;
    node ans, base;
    int tmp;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < 9; j++) {
            base.matrix[(i - 1) * 9 + j][(i - 1) * 9 + j + 1] = 1; //连接拆点
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%1d", &tmp);

            if (tmp) {
                base.matrix[(i - 1) * 9 + tmp][(j - 1) * 9 + 1] = 1; //在自己的链上跑tmp次到下个状态
            }
        }
    }

    ans = pow(base, t);
    printf("%d\n", ans.matrix[1][m - 8]);
    return 0;
}