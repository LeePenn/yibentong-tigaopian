#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 13;
int a, b;
LL power[N];
int f[N][10];

void Read() {
    scanf("%d%d", &a, &b);
}   

void init() {
    for (int i = 0; i < 10; ++i) f[1][i] = 1;
    
    for (int i = 2; i <= 11; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                if (abs(j - k) >= 2) f[i][j] += f[i - 1][k];
            }
        }
    }
    
    power[0] = 1;
    for (int i = 1; i <= 12; ++i) {
        power[i] = power[i - 1] * 10;
    }
}

int Calc(int x) {
    int ans = 0;
    int w = 0;
    while (power[w] <= x) w++;
    
    for (int i = 1; i < w; ++i) {
        for (int j = 1; j < 10; ++j)
            ans += f[i][j];
    }
    
    int y = x / power[w - 1];
    for (int i = 1; i < y; ++i) ans += f[w][i];
    
    int pre = y;
    x %= power[w - 1];
    for (int i = w - 1; i >= 1; --i) {
        y = x / power[i - 1];
        for (int j = 0; j < y; ++j) {
            if (abs(pre - j) >= 2) ans += f[i][j];
        }
        
        if (abs(pre - y) < 2) break;
        
        pre = y;
        x %= power[i - 1];
    }
    
    return ans;

}

int main() {
    init();
    
    Read();
    
    printf("%d\n", Calc(b + 1) - Calc(a));

    return 0;
}