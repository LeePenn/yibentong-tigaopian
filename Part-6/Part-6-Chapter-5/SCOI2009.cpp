#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100, P = 2009;
int n, t, m;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

struct Node {
    LL mat[N + 5][N + 5] = {0};
    Node(int x = 0) {
        for (int i = 0; i <= m; ++i) {
            mat[i][i] = x;
        }
    }
}base, ans;

Node matrixMultiple(Node x, Node y) {
    Node ret(0);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= m; ++k) {
                ret.mat[i][j] = (ret.mat[i][j] + x.mat[i][k] * y.mat[k][j] % P) % P;
            }
        }
    }
    return ret;
}

Node matrixPow(Node a, LL k) {
    Node ret(1), tmp;
    while (k) { 
        if (k & 1) {
            ret = matrixMultiple(ret, a);
        }
        a = matrixMultiple(a, a);
        k >>= 1;
    }
    
    return ret;
}

/*
    这个题初看没有什么头绪(dp失败. 我们联系一下邻接矩阵, 邻接矩阵一个很神奇的性质: 
    表示连通性的邻接矩阵的k次幂后的a[i][j]表示图中i–>j长度为k的路径条数，
    大概理解为: 从第i点出发到任意点的长度k-1道路条数(第i行) 与 任意点到j点的长度1的道路条数(第j列) 乘积和就是i–>j长度为k的路径条数
    但是邻接矩阵只能处理边权为1的点, 这题需要转换. 我们把一个点i拆成更多的虚点，用来抵消部分边权的距离,
    让它实际上以邻接矩阵的方式跑图. 
    假如点1到点2的边权为5, 把这条边拆成边权为1的5条边, 让点1在自己的虚点上先走4步, 最后到达2, 
    路径(1.0)->(1.1)->(1.2)->(1.3)->(1.4)->(2.0), 最后矩阵快速幂一下。
*/
int main() {
    scanf("%d%d", &n, &t);
    m = 9 * n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < 9; ++j) {
            base.mat[(i - 1) * 9 + j][(i - 1) * 9 + j + 1] = 1;
        }
    }
    
    int tmp;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%1d", &tmp);
            if (tmp) {
                base.mat[(i - 1) * 9 + tmp][(j - 1) * 9 + 1] = 1;
            }
        }
    }
    
    ans = matrixPow(base, t);
    printf("%lld\n", ans.mat[1][m - 8]);
    
    return 0;
}

