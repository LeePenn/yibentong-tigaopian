#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, M = 4e5 + 9;
int type, n, m;
int din[N], dout[N], ans[M], cnt;
bool vst[M];

int h[N], to[M], ne[M], idx = 1;
void add(int u, int v) {
    ++ idx;
    to[idx] = v;
    ne[idx] = h[u];
    h[u] = idx;
}

stack <pair <int, int>> stk;
void euler(int u) {                             //用栈模拟深搜的过程
    stk.push({u, 0});                           //第一层递归的入口

    while (stk.size()) {
        int u = stk.top().first;                //取出递归栈顶部存储的信息

        bool flag = false;

        for (int i = h[u]; i; i = ne[i]) {
            if (vst[i]) {                       //如果访问过这条边，将其删除
                h[u] = ne[i];                   //h[u]始终指向未访问过的第一条边。如果是无向边，另一条边在这里删除
            } else {
                vst[i] = true;

                if (type == 1)
                    vst[i ^ 1] = true;

                h[u] = ne[i];                   //h[u]始终指向未访问过的第一条边

                int t;

                if (type == 2)
                    t = i - 1;

                if (type == 1 && i % 2 == 1)
                    t = -i / 2;

                if (type == 1 && i % 2 == 0)
                    t = i / 2;             //如果是无向边，且编号为奇数，则记录负数

                stk.push({to[i], t});           //入栈，准备进入下一层递归
                flag = true;
                break;
            }
        }

        if (!flag) {                            //如果没有未访问的出边，意味着应该返回上一层递归(回溯)
            ans[++ cnt] = stk.top().second;     //取出递归栈顶部存储的信息
            stk.pop();                          //返回上一层递归
        }
    }

    //栈空时，相当于返回到第一层递归的入口

    cnt --;
}

int main() {
    scanf("%d %d %d", &type, &n, &m);

    for (int i = 1; i <= m; i ++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        din[v] ++;
        dout[u] ++;

        if (type == 1) {
            add(v, u);
            din[u] ++;
            dout[v] ++;
        }
    }

    for (int u = 1; u <= n; u ++) {
        if (type == 1 && (din[u] + dout[u]) / 2 % 2 == 1) {     //无向图，度数为奇数(进出不相等)
            puts("NO");
            return 0;
        }

        if (type == 2 && din[u] != dout[u]) {                   //无向图，入度 != 出度(进出不相等)
            puts("NO");
            return 0;
        }
    }

    for (int u = 1; u <= n; u ++) {
        if (!h[u])
            continue;        //题目中不要求环经过所有点，所以可以有孤立点
        else {
            euler(u);
            break;
        }
    }

    if (cnt < m) {                  //环的长度 < m，说明没有经过所有的边
        puts("NO");
        return 0;
    }

    puts("YES");

    for (int i = cnt; i >= 1 ; i --)
        printf("%d ", ans[i]);

    return 0;
}