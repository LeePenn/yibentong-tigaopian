#include <iostream>

const int N = 8e+4;
const int INF = 0x3f3f3f3f;
int rt, tt;
struct node {
    int lc, rc, pos, vis;
#define lc( x ) t[x].lc
#define rc( x ) t[x].rc
#define p( x ) t[x].pos
#define v( x ) t[x].vis
} t[N + 1];

void rz(int &k) {
    int y = lc(k);
    lc(k) = rc(y);
    rc(y) = k;
    k = y;
}

void lz(int &x) {
    int y = rc(x);
    rc(x) = lc(y);
    lc(y) = x;
    x = y;
}

void insert(int &x, int vi) {
    if (! x) {
        x = ++ tt;
        v(x) = vi;
        p(x) = rand();
        return;
    } else if (vi < v(x)) {
        insert(lc(x), vi);

        if (p(lc(x)) < p(x)) {
            rz(x);
        }
    } else {
        insert(rc(x), vi);

        if (p(rc(x)) < p(x)) {
            lz(x);
        }
    }

}

int querypr(int vi) {
    int x = rt, pr = - INF;

    while (x) {
        if (vi >= v(x)) {
            pr = v(x), x = rc(x);
        } else {
            x = lc(x);
        }
    }

    return pr;
}

int querysf(int vi) {
    int x = rt, pr = INF;

    while (x) {
        if (vi <= v(x)) {
            pr = v(x), x = lc(x);
        } else {
            x = rc(x);
        }
    }

    return pr;
}

void deltreap(int &x, int vi) {
    if (v(x) == vi) {
        if (! lc(x) || ! rc(x)) {
            x = lc(x) + rc(x);
        } else {
            if (p(lc(x)) < p(rc(x))) {
                rz(x);
                deltreap(x, vi);
            } else {
                lz(x), deltreap(x, vi);
            }
        }
    } else if (vi < v(x)) {
        deltreap(lc(x), vi);
    } else {
        deltreap(rc(x), vi);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin . tie(0);
    long long n, k, v, answer = 0, number = 0, pr, sf;
    std::cin >> n;

    for (int i = 1 ; i <= n ; ++ i) {
        std::cin >> k >> v;

        if (k == 0) {
            if (number <= 0) {
                insert(rt, v);
                -- number;
            } else {
                -- number;
                pr = querypr(v);
                sf = querysf(v);

                if (v - pr <= sf - v) {
                    answer += v - pr;
                    deltreap(rt, pr);
                } else {
                    answer += sf - v;
                    deltreap(rt, sf);
                }
            }
        } else {
            if (number >= 0) {
                insert(rt, v);
                ++ number;
            } else {
                ++ number;
                pr = querypr(v);
                sf = querysf(v);

                if (v - pr <= sf - v) {
                    answer += v - pr;
                    deltreap(rt, pr);
                } else {
                    answer += sf - v;
                    deltreap(rt, sf);
                }
            }
        }

        answer %= 1000000;
    }

    std::cout << answer << std::endl;
    return 0;
}