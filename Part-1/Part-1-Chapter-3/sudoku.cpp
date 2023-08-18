#include <bits/stdc++.h>

using namespace std;

const int SUDOKU_N = 9;
int sudoku[SUDOKU_N][SUDOKU_N];
const int score[SUDOKU_N][SUDOKU_N] = {
    {6,6,6,6, 6, 6,6,6,6},
    {6,7,7,7, 7, 7,7,7,6},
    {6,7,8,8, 8, 8,8,7,6},
    {6,7,8,9, 9, 9,8,7,6},
    {6,7,8,9,10, 9,8,7,6},
    {6,7,8,9, 9, 9,8,7,6},
    {6,7,8,8, 8, 8,8,7,6},
    {6,7,7,7, 7, 7,7,7,6},
    {6,6,6,6, 6, 6,6,6,6},
};
int row[SUDOKU_N], col[SUDOKU_N], box[SUDOKU_N];
int left_fill = SUDOKU_N * SUDOKU_N;
bool can;
int max_score;

void add(int i, int j, int x) {
    row[i] |= 1 << x;
    col[j] |= 1 << x;
    box[i / 3 * 3 + j / 3] |= 1 << x;
}

void rm(int i, int j, int x) {
    row[i] ^= 1 << x;
    col[j] ^= 1 << x;
    box[i / 3 * 3 + j / 3] ^= 1 << x;
}

void init() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &sudoku[i][j]);
            if (sudoku[i][j] != 0) {
                add(i, j, sudoku[i][j] - 1);
                left_fill--;
            }
        }
    }
}

void calc_score() {
    int cur_score = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cur_score += score[i][j] * sudoku[i][j];
        }
    }
    max_score = max(max_score, cur_score);
}

int get_bit(int x) {
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

void dfs() {
    if (left_fill == 0) {
        can = true;
        /* for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) printf("%d ", sudoku[i][j]);
            printf("\n");
        } */
        calc_score();
        return;
    }
    
    int x, y, max_fill_cnt = 0, max_bits = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != 0) continue;
            
            int bi = i / 3 * 3 + j / 3;
            int bits = row[i] | col[j] | box[bi];
            int cur_fill_cnt = get_bit(bits);
            if (cur_fill_cnt > max_fill_cnt) {
                x = i, y = j, max_fill_cnt = cur_fill_cnt, max_bits = bits;
            }
            
            if (cur_fill_cnt == 9) return;
        }
    }
    
    for (int i = 8; i >= 0; i--) {
        if ((max_bits & (1 << i)) == 0) {
            sudoku[x][y] = i + 1;
            add(x, y, i);
            left_fill--;
            dfs();
            sudoku[x][y] = 0;
            rm(x, y, i);
            left_fill++;
        }
    }
    
}

int main() {
    init();
    /* for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) printf("%d ", sudoku[i][j]);
        printf("\n");
    }
    return 0; */
    /* for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", (box[i] & (1 << j)));
        }
        printf("\n");
    }
    return 0; */
    can = false;
    max_score = 0;
    dfs();
    
    if (!can) printf("-1\n");
    else printf("%d\n", max_score);
    
    return 0;
}