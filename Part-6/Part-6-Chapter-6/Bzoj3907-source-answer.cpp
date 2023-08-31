#include <cstdio>
#include <vector>
using namespace std;

// n+m 最大 10000
const int N = 10010;
int primes[N], cnt;
bool st[N];
int n, m;

void getprimes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i])
            primes[cnt++] = i;

        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;

            if (i % primes[j] == 0)
                break;
        }
    }
}

int factorize(int n, int p) {
    int res = 0;

    while (n) {
        res += n / p;
        n /= p;
    }

    return res;
}

vector<int> mul(const vector<int> &a, int b) {
    vector<int> res;
    int t = 0;

    for (int i = 0; i < a.size() || t; i++) {
        if (i < a.size())
            t += a[i] * b;

        res.push_back(t % 10);
        t /= 10;
    }

    return res;
}

vector<int> sub(const vector<int> &a, const vector<int> &b) {
    vector<int> res;

    for (int i = 0, t = 0; i < a.size(); i++) {
        t = a[i] - t;

        if (i < b.size())
            t -= b[i];

        res.push_back((t + 10) % 10);

        if (t < 0)
            t = 1;
        else
            t = 0;
    }

    while (res.size() && res.back() == 0)
        res.pop_back();

    return res;
}

vector<int> C(int a, int b) {
    vector<int> res;
    res.push_back(1);

    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int s = factorize(a, p) - factorize(a - b, p) - factorize(b, p);

        while (s--)
            res = mul(res, p);
    }

    return res;
}

int main() {
    getprimes(N - 1);
    scanf("%d%d", &n, &m);
    vector<int> res = sub(C(n + m, m), C(n + m, m - 1));

    for (int i = res.size() - 1; i >= 0; i--)
        printf("%d", res[i]);

    puts("");
    return 0;
}