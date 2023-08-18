#include <bits/stdc++.h>

using namespace std;

const int N = 100000;
int sum, start;
int prime[1000][6], prime_cnt;
int high1[10], prime1[10][10000][6]; // 高位为x的质数
int high2[100], prime2[100][1000][6]; 
int high3[1000], prime3[1000][100][6];
int high4[10000], prime4[10000][10][6];

bool need_prime[100000];
bool found;
int ans[6][6], cp[15][6][6];

bool vis[N];
int pre_prime[N], cnt;

string final_ans[1000];
int ans_cnt;

void save_ans() {
    ans_cnt++;
    final_ans[ans_cnt] = "";
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            final_ans[ans_cnt] += ans[i][j] + '0';
        }
    }
}

void print_ans() {
    for (int i = 1; i <= ans_cnt; i++) {
        for (int j = 1; j <= 5; j++) {
            for (int k = 1; k <= 5; k++) {
                printf("%c", final_ans[i][5 * (j - 1) + k - 1]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void prep_prime(int n) {

    vis[0] = vis[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            pre_prime[++cnt] = i;
        }

        for (int j = 1; pre_prime[j] <= n / i; ++j) {
            vis[pre_prime[j]*i] = 1;

            if (i % pre_prime[j] == 0) {
                break;
            }
        }
    }
}

inline int calc2_digit(int a, int b) {
    return a * 10 + b;
}

inline int calc3_digit(int a, int b, int c) {
    return a * 100 + b * 10 + c;
} 

inline int calc4_digit(int a, int b, int c, int d) {
    return a * 1000 + b * 100 + c * 10 + d;
} 

inline int calc5_digit(int a, int b, int c, int d, int e) {
    return a * 10000 + b * 1000 + c * 100 + d * 10 + e;
} 

int get_sum(int p) {
    int ret = 0;
    while (p) {
        ret += p % 10;
        p /= 10;
    }
    return ret;
}

void add(int p) {
    need_prime[p] = true;
    int t = 5;
    prime_cnt++;
    while (t) {
        prime[prime_cnt][t] = p % 10;
        p /= 10;
        t--;
    }
}

void add1(int p) {
    int h = p / 10000;
    // cout << h << endl;
    high1[h]++;
    int ex = 10000;
    for (int i = 1; i <= 5; i++) {
        int cur = (p / ex) % 10;
        prime1[h][high1[h]][i] = cur;
        ex /= 10;
    }
}

void add2(int p) {
    int h = p / 1000;
    // cout << h << endl;
    high2[h]++;
    int ex = 10000;
    for (int i = 1; i <= 5; i++) {
        int cur = (p / ex) % 10;
        prime2[h][high2[h]][i] = cur;
        ex /= 10;
    }
}

void add3(int p) {
    int h = p / 100;
    high3[h]++;
    int ex = 10000;
    for (int i = 1; i <= 5; i++) {
        int cur = (p / ex) % 10;
        prime3[h][high3[h]][i] = cur;
        ex /= 10;
    }
}

void add4(int p) {
    int h = p / 10;
    high4[h]++;
    int ex = 10000;
    for (int i = 1; i <= 5; i++) {
        int cur = (p / ex) % 10;
        prime4[h][high4[h]][i] = cur;
        ex /= 10;
    }
}

void init() {
    for (int i = 10000; i < N; i++) {
        if (vis[i]) continue;
        if (get_sum(i) == sum) {
            add(i);
            add1(i);
            add2(i);
            add3(i);
            add4(i);
        }
    }
    
}

int get_high_digit(int p) {
    int ret = 0;
    while (p) {
        ret = p % 10;
        p /= 10;
    }
    return ret;
}

bool check_high_digit(int p, int c) {
    return get_high_digit(p) == c;
}

bool has_zero(int idx) {
    for (int i = 1; i <= 5; i++) {
        if (prime[idx][i] == 0) return true;
    }
    return false;
}

bool check_can_be_first_digit(int idx) {
    for (int i = 1; i <= 5; i++) {
        if (high1[prime[idx][i]] == 0) return false;
    }
    return true;
}

void dfs8() {
    int cur_pre4 = calc4_digit(ans[5][1], ans[5][2], ans[5][3], ans[5][4]);
    for (int i = 1; i <= high4[cur_pre4]; i++) {
        int pre5 = calc5_digit(ans[5][1], ans[5][2], ans[5][3], ans[5][4], prime4[cur_pre4][i][5]);
        // printf("%d\n", pre5);
        if (!need_prime[pre5]) continue;
        
        pre5 = calc5_digit(ans[1][1], ans[2][2], ans[3][3], ans[4][4], prime4[cur_pre4][i][5]);
        // printf("%d\n", pre5);
        if (!need_prime[pre5]) continue;
        
        ans[5][5] = prime4[cur_pre4][i][5];
        
        found = true;
        
        save_ans();
    }
}

void dfs7() {
    memcpy(cp[7], ans, sizeof(cp[7]));
    int cur_pre4 = calc4_digit(ans[1][4], ans[2][4], ans[3][4], ans[4][4]);
    for (int i = 1; i <= high4[cur_pre4]; i++) {
        int pre4 = calc4_digit(ans[5][1], ans[5][2], ans[5][3], prime4[cur_pre4][i][5]);
        if (high4[pre4] == 0) continue;
        
        // printf("dfs7\n");
        ans[5][4] = prime4[cur_pre4][i][5];
        // printf("%d", ans[5][4]);
        // printf("\n");
        dfs8();
        memcpy(ans, cp[7], sizeof(ans));
    }
}

void dfs6() {
    memcpy(cp[6], ans, sizeof(cp[6]));
    int cur_pre3 = calc3_digit(ans[4][1], ans[4][2], ans[4][3]);
    for (int i = 1; i <= high3[cur_pre3]; i++) {
        int pre4 = calc4_digit(ans[1][4], ans[2][4], ans[3][4], prime3[cur_pre3][i][4]);
        if (high4[pre4] == 0) continue;
        pre4 = calc4_digit(ans[1][5], ans[2][5], ans[3][5], prime3[cur_pre3][i][5]);
        if (high4[pre4] == 0) continue;
        
        pre4 = calc4_digit(ans[1][1], ans[2][2], ans[3][3], prime3[cur_pre3][i][4]);
        if (high4[pre4] == 0) continue;
        
        // printf("dfs6\n");
        for (int j = 4; j <= 5; j++) {
            ans[4][j] = prime3[cur_pre3][i][j];
            // printf("%d", ans[4][j]);
        }
        // printf("\n");
        
        dfs7();
        memcpy(ans, cp[6], sizeof(ans));
    }
}

void dfs5() {
    memcpy(cp[5], ans, sizeof(cp[5]));
    int cur_pre3 = calc3_digit(ans[1][3], ans[2][3], ans[3][3]);
    for (int i = 1; i <= high3[cur_pre3]; i++) {
        int pre3 = calc3_digit(ans[4][1], ans[4][2], prime3[cur_pre3][i][4]);
        if (high3[pre3] == 0) continue;
        pre3 = calc3_digit(ans[5][1], ans[5][2], prime3[cur_pre3][i][5]);
        if (high3[pre3] == 0) continue;
        
        // if (prime3[cur_pre3][i][4] == 6 && prime3[cur_pre3][i][5] == 1) {
            // printf("dfs5\n");
        for (int j = 4; j <= 5; j++) {
            ans[j][3] = prime3[cur_pre3][i][j];
            // printf("%d", ans[j][3]);
        }
        // printf("\n");
        dfs6();
        memcpy(ans, cp[5], sizeof(ans));
        // }
        
    }
}

void dfs4() {
    memcpy(cp[4], ans, sizeof(cp[4]));
    int cur_pre2 = calc2_digit(ans[3][1], ans[3][2]);
    for (int i = 1; i <= high2[cur_pre2]; i++) {
        int pre3 = calc3_digit(ans[1][3], ans[2][3], prime2[cur_pre2][i][3]);
        if (high3[pre3] == 0) continue;
        pre3 = calc3_digit(ans[1][4], ans[2][4], prime2[cur_pre2][i][4]);
        if (high3[pre3] == 0) continue;
        pre3 = calc3_digit(ans[1][5], ans[2][5], prime2[cur_pre2][i][5]);
        if (high3[pre3] == 0) continue;
        
        pre3 = calc3_digit(ans[1][1], ans[2][2], prime2[cur_pre2][i][3]);
        if (high3[pre3] == 0) continue;
        
        int pre5 = calc5_digit(ans[5][1], ans[4][2], prime2[cur_pre2][i][3], ans[2][4], ans[1][5]);
        if (!need_prime[pre5]) continue;
        
        // if (prime2[cur_pre2][i][3] == 1 && prime2[cur_pre2][i][4] == 0 && prime2[cur_pre2][i][5] == 1) {
            // printf("dfs4\n");
        for (int j = 3; j <= 5; j++) {
            ans[3][j] = prime2[cur_pre2][i][j];
            // printf("%d", ans[3][j]);
        }
        // printf("\n");
        dfs5();
        memcpy(ans, cp[4], sizeof(ans));
        // }
        
    }
}

void dfs3() {
    memcpy(cp[3], ans, sizeof(cp[3]));
    int cur_pre2 = calc2_digit(ans[1][2], ans[2][2]);
    for (int i = 1; i <= high2[cur_pre2]; i++) {
        int pre2 = calc2_digit(ans[3][1], prime2[cur_pre2][i][3]);
        if (high2[pre2] == 0) continue;
        pre2 = calc2_digit(ans[4][1], prime2[cur_pre2][i][4]);
        if (high2[pre2] == 0) continue;
        pre2 = calc2_digit(ans[5][1], prime2[cur_pre2][i][5]);
        if (high2[pre2] == 0) continue;
        
        pre2 = calc2_digit(ans[1][1], prime2[cur_pre2][i][2]);
        if (high2[pre2] == 0) continue;
        
        
        // if (prime2[cur_pre2][i][3] == 4 && prime2[cur_pre2][i][4] == 1 && prime2[cur_pre2][i][5] == 1) {
            // printf("dfs3\n");
        for (int j = 3; j <= 5; j++) {
            ans[j][2] = prime2[cur_pre2][i][j];
            // printf("%d", ans[j][2]);
        }
        // printf("\n");
        dfs4();
        memcpy(ans, cp[3], sizeof(ans));
        // }
        
    }
}

void dfs2() {
    memcpy(cp[2], ans, sizeof(cp[2]));
    for (int i = 1; i <= prime_cnt; i++) {
        
        if (prime[i][1] != ans[2][1]) continue;
        
        int pre2 = calc2_digit(ans[1][2], prime[i][2]);
        if (high2[pre2] == 0) continue;
        pre2 = calc2_digit(ans[1][3], prime[i][3]);
        if (high2[pre2] == 0) continue;
        pre2 = calc2_digit(ans[1][4], prime[i][4]);
        if (high2[pre2] == 0) continue;
        pre2 = calc2_digit(ans[1][5], prime[i][5]);
        if (high2[pre2] == 0) continue;
        
        pre2 = calc2_digit(ans[1][1], prime[i][2]);
        if (high2[pre2] == 0) continue;
        
        // if (prime[i][2] == 0 && prime[i][3] == 2 && prime[i][4] == 7 && prime[i][5] == 1) {
            // printf("dfs2\n");
        for (int j = 2; j <= 5; j++) {
            ans[2][j] = prime[i][j];
            // printf("%d", ans[2][j]);
        }
        // printf("\n");
        dfs3();
        memcpy(ans, cp[2], sizeof(ans));
        // }
        
    }
}

void dfs1() {
    memcpy(cp[1], ans, sizeof(cp[1]));
    for (int i = 1; i <= prime_cnt; i++) {
        if (!has_zero(i) && prime[i][1] == ans[1][1] && check_can_be_first_digit(i)) {
            // if (prime[i][2] == 1 && prime[i][3] == 5 && prime[i][4] == 2 && prime[i][5] == 1) {
                // printf("dfs1\n");
            for (int j = 2; j <= 5; j++) {
                ans[j][1] = prime[i][j];
                // printf("%d", ans[j][1]);
            }
            // printf("\n");
            dfs2();
            memcpy(ans, cp[1], sizeof(ans));
            // }
        }
    }
}

// row, col, row, col... dfs, then sort, print
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    scanf("%d%d", &sum, &start);
    
    prep_prime(N);
    init();
    
    /* int test = 0;
    for (int i = 1; i <= prime_cnt; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("%d", prime[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    return 0; */
    
    found = false;
    for (int i = 1; i <= prime_cnt; i++) {
        if (prime[i][1] == start && !has_zero(i) && check_can_be_first_digit(i)) {
            // if (i == 69) {
                // printf("dfs0\n");
            for (int j = 1; j <= 5; j++) {
                ans[1][j] = prime[i][j];
                // printf("%d", ans[1][j]);
            }
            // printf("\n");
            dfs1();
            // }
        }
    }
    
    if (!found) printf("NONE\n");
    
    sort(final_ans + 1, final_ans + ans_cnt + 1);
    print_ans();
    

    return 0;
}