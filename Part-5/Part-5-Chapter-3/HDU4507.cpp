#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20, MOD = 1e9 + 7;
// i位最高位为j，数字mod7为a，各位数字和mod7为b
struct node {
    // s0 个数，s1 和，s2 平方和
    int s0, s1, s2;
    node() { s0 = s1 = s2 = 0; }
    node(int _s0, int _s1, int _s2) {
        s0 = _s0;
        s1 = _s1;
        s2 = _s2;
    }
}f[N][10][7][7];
LL power10[N], power7[N], power9[N];
int T;
LL l, r;
vector<int> num;

int Mod(LL x, int y) {
    return (x % y + y) % y;
}

void init() {
    for (int i = 0; i < 10; ++i) {
        if (i == 7) continue;
        
        node &v = f[1][i][i % 7][i % 7];
        v.s0++;
        v.s1 += i;
        v.s2 += i * i;
    }
    
    power10[0] = 1;
    for (int i = 1; i < N; ++i) power10[i] = power10[i - 1] * 10;
    
    for (int i = 2; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j == 7) continue;
            
            for (int a = 0; a < 7; ++a) {
                for (int b = 0; b < 7; ++b) {
                    for (int k = 0; k <= 9; ++k) {
                        if (k == 7) continue;
                        
                        node &v1 = f[i][j][a][b];
                        node &v2 = f[i - 1][k][Mod(a - j * (power10[i - 1] % 7), 7)][Mod(b - j, 7)];
                        
                        v1.s0 = Mod(v1.s0 + v2.s0, MOD);
                        v1.s1 = Mod(v1.s1 + j * (power10[i - 1] % MOD) % MOD * v2.s0 + v2.s1, MOD);
                        // (j + x)^2 = j^2 + 2 * j *(sum(x)) + x^2
                        v1.s2 = Mod(v1.s2 + j * j % MOD * (power10[i - 1] % MOD) % MOD * (power10[i - 1] % MOD) % MOD * v2.s0 + v2.s2 + 2 * j % MOD * 
                                    (power10[i - 1] % MOD) % MOD * v2.s1 % MOD, MOD);
                    }
                }
            }
        }
    }
        
    power7[0] = power9[0] = 1;
    for (int i = 1; i < N; ++i) {
        power7[i] = Mod(power7[i - 1] * 10, 7);
        power9[i] = Mod(power9[i - 1] * 10, MOD);
    }
}

node Get(int i, int j, int a, int b) {
    int s0 = 0, s1 = 0, s2 = 0;
    // exclude mod 7 == 0
    for (int p = 0; p < 7; ++p) {
        for (int q = 0; q < 7; ++q) {
            if (a != p && b != q) {
                node &v = f[i][j][p][q];
                s0 = Mod(s0 + v.s0, MOD);
                s1 = Mod(s1 + v.s1, MOD);
                s2 = Mod(s2 + v.s2, MOD);
            }
        }
    }
    
    return {s0, s1, s2};
}

int DP(LL x) {
    if (!x) return 0;
    
    LL t = x % MOD;
    int ans = 0;
    LL last_a = 0, last_b = 0;
    num.clear();
    
    while (x) {
        num.push_back(x % 10);
        x /= 10;
    }
    
    for (int i = num.size() - 1; i >= 0; --i) {
        int c = num[i];
        
        for (int j = 0; j < c; ++j) {
            if (j == 7) continue;
            
            int a = Mod(-last_a * power7[i + 1], 7);
            int b = Mod(-last_b, 7);
            node v = Get(i + 1, j, a, b);
            // power9 防止溢出
            ans = Mod(ans + (last_a % MOD) * power9[i + 1] % MOD * (last_a % MOD) % MOD * power9[i + 1] % MOD * v.s0 % MOD + 2 *
                      (last_a % MOD) % MOD * power9[i + 1] % MOD * v.s1 % MOD + v.s2, MOD);
        }
        
        if (c == 7) break;
        
        last_a = last_a * 10 + c;
        last_b += c;
        
        if (!i && last_a % 7 && last_b % 7) {
            ans = Mod(ans + t * t % MOD, MOD);
        }
    }
    
    return ans % MOD;
}

int main() {
    init();
    
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &l, &r);
        printf("%d\n", Mod(DP(r) - DP(l - 1), MOD));
    }

    return 0;
}