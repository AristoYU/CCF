/*
 试题编号：    201512-2
 试题名称：    消除类游戏
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　消除类游戏是深受大众欢迎的一种游戏，游戏在一个包含有n行m列的游戏棋盘上进行，棋盘的每一行每一列的方格上放着一个有颜色的棋子，当一行或一列上有连续三个或更多的相同颜色的棋子时，这些棋子都被消除。当有多处可以被消除时，这些地方的棋子将同时被消除。
 　　现在给你一个n行m列的棋盘，棋盘中的每一个方格上有一个棋子，请给出经过一次消除后的棋盘。
 　　请注意：一个棋子可能在某一行和某一列同时被消除。
 输入格式
 　　输入的第一行包含两个整数n, m，用空格分隔，分别表示棋盘的行数和列数。
 　　接下来n行，每行m个整数，用空格分隔，分别表示每一个方格中的棋子的颜色。颜色使用1至9编号。
 输出格式
 　　输出n行，每行m个整数，相邻的整数之间使用一个空格分隔，表示经过一次消除后的棋盘。如果一个方格中的棋子被消除，则对应的方格输出0，否则输出棋子的颜色编号。
 样例输入
 4 5
 2 2 3 1 2
 3 4 5 1 4
 2 3 2 1 3
 2 2 2 4 4
 样例输出
 2 2 3 0 2
 3 4 5 0 4
 2 3 2 0 3
 0 0 0 4 4
 样例说明
 　　棋盘中第4列的1和第4行的2可以被消除，其他的方格中的棋子均保留。
 样例输入
 4 5
 2 2 3 1 2
 3 1 1 1 1
 2 3 2 1 3
 2 2 3 3 3
 样例输出
 2 2 3 0 2
 3 0 0 0 0
 2 3 2 0 3
 2 2 0 0 0
 样例说明
 　　棋盘中所有的1以及最后一行的3可以被同时消除，其他的方格中的棋子均保留。
 评测用例规模与约定
 　　所有的评测用例满足：1 ≤ n, m ≤ 30。
 */

#include <iostream>
#include <string.h>
#define LEN 30

using namespace std;

void input(int board[][LEN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }
}

bool canRowBeMoved(const int board[][LEN], const int i, const int j, int m) {
    int temp = board[i][j];
    //在中间
    if (board[i][j - 1] == temp && board[i][j + 1] == temp && j - 1 >= 0 && j + 1 < m) {
        return true;
    }
    //在左边
    if (board[i][j + 1] == temp && board[i][j + 2] == temp && j + 2 < m) {
        return true;
    }
    //在右边
    if (board[i][j - 1] == temp && board[i][j - 2] == temp && j - 2 >= 0) {
        return true;
    }
    return false;
}

bool canColBeRemoved(const int board[][LEN], const int i, const int j, int n) {
    int temp = board[i][j];
    //在中间
    if (board[i - 1][j] == temp && board[i + 1][j] == temp && i - 1 >= 0 && i + 1 < n) {
        return true;
    }
    //在下面
    if (board[i - 1][j] == temp && board[i - 2][j] == temp && i - 2 >= 0) {
        return true;
    }
    //在上面
    if (board[i + 1][j] == temp && board[i + 2][j] == temp && i + 2 < n) {
        return true;
    }
    return false;
}

bool canBeRemoved(const int board[][LEN], const int i, const int j, const int n, const int m) {
    //行可消？？
    if (canRowBeMoved(board, i, j, m)) {
        return true;
    }
    //列可消？？
    if (canColBeRemoved(board, i, j, n)) {
        return true;
    }
    return false;
}

void log(int remove[][LEN], const int i, const int j) {
    remove[i][j] = 1;
}

void eliminate(int board[][LEN], const int remove[][LEN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (remove[i][j] == 1) {
                board[i][j] = 0;
            }
        }
    }
}

void run(int board[][LEN], int remove[][LEN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (canBeRemoved(board, i, j, n, m)) {
                log(remove, i, j);
            }
        }
    }
    eliminate(board, remove, n, m);
}

void print(const int board[][LEN], const int n, const int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, m, board[LEN][LEN], remove[LEN][LEN];
    memset(board, 0, sizeof(board));
    memset(remove, 0, sizeof(remove));
    cin >> n >> m;
    input(board, n, m);
    run(board, remove, n, m);
    print(board, n, m);
    return 0;
}
