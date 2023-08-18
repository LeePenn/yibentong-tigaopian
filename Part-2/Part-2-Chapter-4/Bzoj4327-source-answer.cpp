#include <bits/stdc++.h>
using namespace std;
const int MaxN = 1e7 + 10;
const int MaxM = 1e5 + 10;
const int MaxLM = 1e2 + 10;
inline int modify(char s) {
    if (s == 'E')
        return 0;

    if (s == 'S')
        return 1;

    if (s == 'W')
        return 2;

    if (s == 'N')
        return 3;

}
int n, m;
char s[MaxN], s2[MaxM][MaxLM];
int ch[MaxLM * MaxM][4], tot;
int fail[MaxN], bo[MaxN];
queue <int> que;
void insert(int num) {
    //建树
    int len = strlen(s2[num]), u = 0;

    for (int i = 0; i < len; i++) {
        int c = modify(s2[num][i]);

        if (!ch[u][c])
            ch[u][c] = ++tot;

        u = ch[u][c];
    }
}
void getfail() {
    ////第零个结点
    //for (int i = 0; i < 4; i++)
    //{
    //  ch[0][i] = 1;
    //}
    /*que.push(1), fail[0] = 0;*/
    for (int c = 0; c <= 3; c++) {
        int u = ch[0][c];

        if (u) {
            fail[u] = 0;
            que.push(u);
        }
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = 0; i <= 3; i++) {
            //没有儿子的话自己建立转移边
            if (!ch[u][i])
                ch[u][i] = ch[fail[u]][i];
            else {
                //有儿子的话把儿子压入队
                que.push(ch[u][i]);
                //取出父亲结点的fail数值
                int v = fail[u];

                //判断父亲的转移边下是否有符合的结点,没有的话继续深入寻找
                while (v  && !ch[v][i])
                    v = fail[v];

                //建立儿子的转移边
                fail[ch[u][i]] = ch[v][i];
            }
        }
    }
}
//把在 Trie 树上与 s 串匹配的位置打上标记
void s_find() {
    int u = 0;

    for (int i = 0; i < n; i++) {
        //逐个取出S串中每一个
        int str = modify(s[i]);
        //
        u = ch[u][str];
        //不可以改变u
        int k = u;

        //如果k结点被标记过，那么k的每一个fail指针都被打上标记
        while (k  && !bo[k]) {
            bo[k] = 1;
            k = fail[k];
        }
    }
}
//找出前缀最大匹配
int solve(int num) {
    int len = strlen(s2[num]), u = 0;
    int ans = 0;

    //遍历当前字符串在Trie字符串的每一个结点
    for (int i = 0; i < len; i++) {
        int str = modify(s2[num][i]);
        u = ch[u][str];

        if (bo[u]) {
            ans = i + 1;
        }
    }

    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s);

    //利用char数组的特点
    for (int i = 0; i < m; i++) {
        scanf("%s", s2[i]);
        //插入建立Tire数组
        insert(i);
    }

    //获取fail数组
    getfail();
    //把字符串放在AC自动机上跑一遍，标记相关点
    s_find();

    for (int i = 0; i < m; i++) {
        printf("%d\n", solve(i));
    }

    return 0;
}