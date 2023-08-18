#include <stdio.h>
#include <algorithm>//简约头文件 
int p[500050]/*线筛中记录质数*/, len/*线筛中质数个数*/, m/*题目中m个等的人*/,
    a[500050]/*记录m个人的号码牌*/, s/*自己的号码牌上写着的数字*/;
bool v[500050];//线筛中记录是否为质数
inline void prime() {
    v[1] = 1;

    for (int i = 2; i <= 100000; i++) {
        if (!v[i])
            p[++len] = i;

        for (int j = 1; j <= len; ++j) {
            if (p[j]*i > 100000) {
                break;
            }

            v[i * p[j]] = 1;

            if (!(i % p[j])) { //i%p[j]==0
                break;
            }
        }
    }
}//线筛模板，求100000以内质数
inline bool is_prime(int
                     n) { //由于v数组的范围有限，不能判断大于100000的数，所以得再写一个判质数的程序
    if (n < 100000) {
        return!v[n];
    }//在这里做了一个小小的优化，巧妙利用v数组

    for (int i = 1; p[i]*p[i] <= n; i++) { //这里又做了一个优化，只枚举质数
        if (!(n % p[i])) { //n%p[i]==0
            return 0;
        }
    }

    return 1;
}//判质数
inline void dfs(int x/*第x个质数*/, int k/*还剩k能够分解*/,
                int num/*当前数为num*/) { //功能详见前文
    if (k == 1) {
        a[++m] = num;
        return;
    }

    if (k > p[x] && is_prime(k - 1)) {
        a[++m] = (k - 1) * num;
    }//特判

    for (int j = x; p[j]*p[j] <= k; j++) { //枚举下一次选的质数因子
        int cnt = p[j] + 1, tmp = p[j]; //cnt为总次方和，tmp为次方和的最后一个数

        for (; cnt <= k; tmp *= p[j], cnt += tmp) { //枚举有多少个因子
            if (k % cnt == 0) {
                dfs(j + 1, k / cnt, num * tmp);
            }
        }
    }//实现分解
}
signed main() { //因为“#define int long long”
    prime();//筛质数

    while (~scanf("%lld", &s)) { //用于读入本题数据
        m = 0; //每次赋初值
        dfs(1, s, 1); //实现分解n（详见上文分析）
        printf("%lld\n", m);
        std::sort(a + 1, a + m + 1); //为符合题目要求，将a数组排序

        for (int i = 1; i <= m; i++) {
            printf("%lld ", a[i]);
        }//输出a数组

        if (m) {
            printf("\n");
        }//本题逐行评测，没有这一句会全部WA掉
    }

    return 0;
}