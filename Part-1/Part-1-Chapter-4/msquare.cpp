#include <bits/stdc++.h>

using namespace std;

const int N = 8;
const int MAX = 41000;
int jc[10] = {1, 1, 2, 6, 24, 120, 720, 5040};
int fin_seq;
int dis[MAX];
int pre[MAX];
int road[MAX];
int hd, tail;
struct MB {
    int mb[3][5];
}q[MAX], fin;


int get_cantor_seq(const MB &m) {
    int t[10];
    for (int i = 1; i <= 4; i++) t[i] = m.mb[1][i];
    for (int i = 4; i >= 1; i--) t[8 - i + 1] = m.mb[2][i];
    // for (int i = 1; i <= 8; i++) printf("%d ", t[i]);
    // printf("\n");
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        int cnt = 0;
        for (int j = i + 1; j <= 8; j++) {
            if (t[j] < t[i]) cnt++;
        }
        ret += cnt * jc[N - i];
        // printf("%d ", ret);
    }
    return ret + 1;
}

void add(const MB &nx, int p, int mov) {
    int seq = get_cantor_seq(nx);
    if (dis[seq] == -1 || dis[seq] > dis[p] + 1) {
        /* for (int i = 1; i <= 8; i++) printf("%d ", b[i]);
        printf("\n"); */
        dis[seq] = dis[p] + 1;
        pre[seq] = p;
        road[seq] = mov;
        MB c;
        memcpy(c.mb, nx.mb, sizeof(c.mb));
        q[++tail] = c;
    }
}

void bfs() {
    memset(dis, -1, sizeof(dis));
    int seq = get_cantor_seq(q[1]);
    
    dis[seq] = 0;
    pre[seq] = 0;
    road[seq] = 0;
    hd = 0, tail = 1;
    while (hd < tail) {
        hd++;
        MB cur = q[hd]; 
        seq = get_cantor_seq(cur);
        if (seq == fin_seq) return;
        
        MB nx;
        memcpy(nx.mb, cur.mb, sizeof(nx.mb));
        for (int i = 1; i <= 4; i++) {
            swap(nx.mb[1][i], nx.mb[2][i]);
        }
        add(nx, seq, 1);
        
        memcpy(nx.mb, cur.mb, sizeof(nx.mb));
        int temp = nx.mb[1][1]; 
        nx.mb[1][1] = nx.mb[1][4]; nx.mb[1][4] = nx.mb[1][3]; nx.mb[1][3] = nx.mb[1][2]; nx.mb[1][2] = temp;
        temp = nx.mb[2][1];
        nx.mb[2][1] = nx.mb[2][4]; nx.mb[2][4] = nx.mb[2][3]; nx.mb[2][3] = nx.mb[2][2]; nx.mb[2][2] = temp;
        add(nx, seq, 2);
        
        memcpy(nx.mb, cur.mb, sizeof(nx.mb));
        temp = nx.mb[1][2]; 
        nx.mb[1][2] = nx.mb[2][2]; nx.mb[2][2] = nx.mb[2][3]; nx.mb[2][3] = nx.mb[1][3]; nx.mb[1][3] = temp;
        add(nx, seq, 3);
        // exit(0);
    }
    
}

void print_road(int e) {
    if (e == 1) return;
    print_road(pre[e]);
    printf("%c", road[e] - 1 + 'A');
}

int main() {
    for (int i = 1; i <= 4; i++) q[1].mb[1][i] = i;
    for (int i = 4; i >= 1; i--) q[1].mb[2][i] = 8 - i + 1;
    // for (int i = 1; i <= 2; i++) {
    //     for (int j = 1; j <= 4; j++) printf("%d ", q[1].mb[i][j]);
    //     printf("\n");
    // }
    
    for (int i = 1; i <= 4; i++) scanf("%d", &fin.mb[1][i]);
    for (int i = 4; i >= 1; i--) scanf("%d", &fin.mb[2][i]);
    
    // for (int i = 1; i <= 2; i++) {
    //     for (int j = 1; j <= 4; j++) printf("%d ", fin.mb[i][j]);
    //     printf("\n");
    // }
    // exit(0);
    bfs();
    int e = get_cantor_seq(fin);
    printf("%d\n", dis[e]);
    print_road(e);
    
    // printf("%d %d\n", road[e], pre[e]);
    // printf("%d %d\n", road[29908], pre[29908]);
    // printf("%d %d\n", road[27748], pre[27748]);
    // printf("%d %d\n", road[28590], pre[28590]);
    // printf("%d %d\n", road[23960], pre[23960]);
    // printf("%d %d\n", road[19478], pre[19478]);
    // printf("%d %d\n", road[15130], pre[15130]);
    
    
    /* for (i = e; i != 0; i = pre[e]) {
        printf("%c", road[i] - 1 + 'A');
    } */
    // for (int i = )
    
    return 0;
}