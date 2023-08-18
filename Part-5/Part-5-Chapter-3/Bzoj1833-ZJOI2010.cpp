#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 15;
LL a, b;
LL f[N][N][10];
LL power[N];
vector<int> num;

// 统计时，统计i位算上前导零的计数
void init() {
    power[0] = 1;
    for (int i = 1; i < N; ++i) power[i] = power[i - 1] * 10;
    
    for (int j = 0; j < 10; ++j) f[1][j][j]++;
    
    for (int i = 2; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                LL &v = f[i][j][k];
                for (int p = 0; p < 10; ++p) {
                    v += f[i - 1][p][k];
                }
                if (j == k) {
                    v += power[i - 1];
                }
            }
        }
    }

}

void Read() {
    scanf("%lld%lld", &a, &b);
}

LL Calc(LL x, int y) {
    if (x == 0) {
        if (y == 0) return 1;
        else return 0;
    }
    
    num.clear();
    LL t = x;
    while (t) {
        num.push_back(t % 10);
        t /= 10;
    }
    
    LL ans = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int c = num[i];
        for (int j = 0; j < c; ++j) {
            ans += f[i + 1][j][y];
        }
        if (c == y) ans += (x % power[i]) + 1;
    }
    // 减去所有带前导零的情况
    if (y == 0) {
        for (int i = num.size() - 1; i >= 1; --i) {
            ans -= power[i];
        }
    }
    
    
    return ans;
}

int main() {
    init();
    
    // for (int j = 0; j < 10; ++j) {
    //     printf("%lld ", f[3][j][0]);
    // }
    // cout << endl;
    // return 0;
    
    Read();
    
    // for (int i = 0; i < 10; ++i) printf("%lld ", Calc(b, i));
    // printf("%lld ", Calc(199, 9));
    // return 0;
    
    for (int i = 0; i < 10; ++i) printf("%lld ", Calc(b, i) - Calc(a - 1, i));
    printf("\n");
    

    return 0;
}