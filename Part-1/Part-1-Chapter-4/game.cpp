#include <bits/stdc++.h>

using namespace std;

const int N = 1 << 20;
struct Board {
    int a[4][4];
}q[2][N], st, ed;
char line[6];
int dist0[N], dist1[N];
int hd[2], tail[2];


int get_hash(const Board &b) {
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) ret |= b.a[i][j] << ((i * 4) + j);
    }    
    return ret;
}

bool in_board(int a, int b) {
    return a >= 0 && a < 4 && b >= 0 && b < 4;
}

void print_board(const Board &b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) printf("%d", b.a[i][j]);
        printf("\n");
    }  
    printf("\n");
}

void bfs() {
    memset(dist0, -1, sizeof(dist0));
    memset(dist1, -1, sizeof(dist1));
    
    hd[0] = 0, tail[0] = 1, hd[1] = 0, tail[1] = 1;
    q[0][1] = st, q[1][1] = ed;
    dist0[get_hash(q[0][1])] = 0, dist1[get_hash(q[1][1])] = 0;
    int cnt0 = 1, cnt1 = 1;
    while (hd[0] < tail[0] && hd[1] < tail[1]) {
        if (cnt0 <= cnt1) {
            int cur_cnt0 = 0;
            while (cnt0--) {
                hd[0]++;
                Board cur = q[0][hd[0]];
                int cur_hash = get_hash(cur);
                
                if (dist1[cur_hash] != -1) {
                    printf("%d\n", dist0[cur_hash] + dist1[cur_hash]);
                    return;
                }
                
                Board c;
                // swap right
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 3; j++) {
                        int nj = j + 1;
                        memcpy(c.a, cur.a, sizeof(c.a));
                        if (c.a[i][j] != c.a[i][nj]) {
                            swap(c.a[i][j], c.a[i][nj]);
                            if (dist0[get_hash(c)] == -1) {
                                // print_board(c);
                                // printf("----\n");
                                tail[0]++;
                                q[0][tail[0]] = c;
                                dist0[get_hash(c)] = dist0[cur_hash] + 1;
                                cur_cnt0++;
                            }
                        }
                    }
                }
                // swap down
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        int ni = i + 1;
                        memcpy(c.a, cur.a, sizeof(c.a));
                        if (c.a[i][j] != c.a[ni][j]) {
                            swap(c.a[i][j], c.a[ni][j]);
                            if (dist0[get_hash(c)] == -1) {
                                // print_board(c);
                                // printf("----\n");
                                tail[0]++;
                                q[0][tail[0]] = c;
                                dist0[get_hash(c)] = dist0[cur_hash] + 1;
                                cur_cnt0++;
                            }
                        }
                    }
                }
            }
            
            cnt0 = cur_cnt0;
        } else {
            int cur_cnt1 = 0;
            while (cnt1--) {
                hd[1]++;
                Board cur = q[1][hd[1]];
                int cur_hash = get_hash(cur);
                if (dist0[cur_hash] != -1) {
                    printf("%d\n", dist0[cur_hash] + dist1[cur_hash]);
                    return;
                }
                
                Board c;
                // swap right
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 3; j++) {
                        int nj = j + 1;
                        memcpy(c.a, cur.a, sizeof(c.a));
                        if (c.a[i][j] != c.a[i][nj]) {
                            swap(c.a[i][j], c.a[i][nj]);
                            if (dist1[get_hash(c)] == -1) {
                                // print_board(c);
                                // printf("!!!!\n");
                                tail[1]++;
                                q[1][tail[1]] = c;
                                dist1[get_hash(c)] = dist1[cur_hash] + 1;
                                cur_cnt1++;
                            }
                        }
                    }
                }
                // swap down
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        int ni = i + 1;
                        memcpy(c.a, cur.a, sizeof(c.a));
                        if (c.a[i][j] != c.a[ni][j]) {
                            swap(c.a[i][j], c.a[ni][j]);
                            if (dist1[get_hash(c)] == -1) {
                                // print_board(c);
                                // printf("@@@@\n");
                                tail[1]++;
                                q[1][tail[1]] = c;
                                dist1[get_hash(c)] = dist1[cur_hash] + 1;
                                cur_cnt1++;
                            }
                        }
                    }
                }
            }
            cnt1 = cur_cnt1;
        }
        
    }
    
}


int main() {

    for (int i = 0; i < 4; i++) {
        scanf("%s\n", line);
        for (int j = 0; j < 4; j++) {
            st.a[i][j] = line[j] - '0';
        }
    }
    // print_board(st);
    // printf("\n");
    for (int i = 0; i < 4; i++) {
        scanf("%s\n", line);
        for (int j = 0; j < 4; j++) {
            ed.a[i][j] = line[j] - '0';
        }
    }
    // print_board(ed);
    bfs();

    
    return 0;
}

