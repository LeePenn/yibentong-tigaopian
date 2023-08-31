#include <bits/stdc++.h>
#define endy {cout<<"YES\n";}//return ;}
#define endn {cout<<"NO\n";}//return ;}
#define endl "\n"
#define fr first
#define sc second
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
const int mod = 1e5 + 3;
const int N = 1e5 + 10;
ll n, m, ans = 0;
ll inv[N], fac[N];
ll qpow(ll a, ll n) { //qpow(2,53)
    if (n == 0)
        return 1;
    else if (n & 1ll)
        return qpow(a, n - 1) * a;
    else {
        ll tmp = qpow(a, n / 2);
        return tmp * tmp;
    }
}
ll ksm(ll a, ll n) { //ksm(2,62)
    ll ans = 1;

    while (n) {
        if (n & 1ll)
            ans = ans * a % mod;

        a = a * a % mod;
        n >>= 1ll;
    }

    return ans;
}
void pre() {
    inv[0] = fac[0] = 1;

    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = ksm(fac[i], mod - 2ll);
    }
}
ll C(ll a, ll b) {
    if (b > a)
        return 0;

    return fac[a] * inv[b] % mod * inv[a - b] % mod;
}
ll A(ll a, ll b) {
    if (b > a)
        return 0;

    return fac[a] * inv[a - b] % mod;
}
/*
费马小定理:
gcd(a,p)=1且 p为质数 那么有 a^(p-1) ≡1(mod p)
也就是说a*a^(p-2) ≡1(mod p) 此时 a^(p-2)为 a的逆元
*/
void solve() {
    pre();
    ll a, b, c, d, k;
    cin >> a >> b >> c >> d >> k;

    //C(b,i)*A(b,i)*C(d,k-i)*A(a+c-i,k-i)
    for (int i = 0; i <= k; i++) {
        ans = (ans + (ll)C(b, i) % mod * A(a, i) % mod * C(d, k - i) % mod * A(a + c - i, k - i) % mod) % mod;
    }

    cout << ans << endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //  ll _;cin>>_;
    //  while(_--)
    solve();
    return 0;
}