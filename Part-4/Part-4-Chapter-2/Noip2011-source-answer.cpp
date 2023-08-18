#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define boo(i) bitset<i>
#define ri register int
#define rll register long long
#define ll long long
#define max_(i,j) (i<j?j:i)
#define min_(i,j) (i<j?i:j)
#define abs_(x) (x>0?x:(-x))
using namespace std;
int n, k, p;
vector<int>a[10001];
int lst[2000001];
int main() {
    scanf("%d%d%d", &n, &k, &p);

    for (int i = 0; i < k; i++) {
        a[i].push_back(0);
    }

    for (int i = 1, col, cost; i <= n; i++) {
        scanf("%d%d", &col, &cost);

        if (cost <= p) {
            lst[i] = i;
        } else {
            lst[i] = lst[i - 1];
        }

        a[col].push_back(i);
    }

    int l;
    long long cnt = 0;

    for (int i = 0; i < k; i++) {
        l = 0;

        for (int j = 1; j < a[i].size(); j++) {
            while (l < j - 1 && a[i][l + 1] <= lst[a[i][j]]) {
                l++;
            }

            cnt += l;
        }
    }

    printf("%lld", cnt);
}