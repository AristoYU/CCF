/*
 试题编号：    201604-2
 试题名称：    俄罗斯方块
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　俄罗斯方块是俄罗斯人阿列克谢·帕基特诺夫发明的一款休闲游戏。
 　　游戏在一个15行10列的方格图上进行，方格图上的每一个格子可能已经放置了方块，或者没有放置方块。每一轮，都会有一个新的由4个小方块组成的板块从方格图的上方落下，玩家可以操作板块左右移动放到合适的位置，当板块中某一个方块的下边缘与方格图上的方块上边缘重合或者达到下边界时，板块不再移动，如果此时方格图的某一行全放满了方块，则该行被消除并得分。
 　　在这个问题中，你需要写一个程序来模拟板块下落，你不需要处理玩家的操作，也不需要处理消行和得分。
 　　具体的，给定一个初始的方格图，以及一个板块的形状和它下落的初始位置，你要给出最终的方格图。
 输入格式
 　　输入的前15行包含初始的方格图，每行包含10个数字，相邻的数字用空格分隔。如果一个数字是0，表示对应的方格中没有方块，如果数字是1，则表示初始的时候有方块。输入保证前4行中的数字都是0。
 　　输入的第16至第19行包含新加入的板块的形状，每行包含4个数字，组成了板块图案，同样0表示没方块，1表示有方块。输入保证板块的图案中正好包含4个方块，且4个方块是连在一起的（准确的说，4个方块是四连通的，即给定的板块是俄罗斯方块的标准板块）。
 　　第20行包含一个1到7之间的整数，表示板块图案最左边开始的时候是在方格图的哪一列中。注意，这里的板块图案指的是16至19行所输入的板块图案，如果板块图案的最左边一列全是0，则它的左边和实际所表示的板块的左边是不一致的（见样例）
 输出格式
 　　输出15行，每行10个数字，相邻的数字之间用一个空格分隔，表示板块下落后的方格图。注意，你不需要处理最终的消行。
 样例输入
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 1 0 0
 0 0 0 0 0 0 1 0 0 0
 0 0 0 0 0 0 1 0 0 0
 1 1 1 0 0 0 1 1 1 1
 0 0 0 0 1 0 0 0 0 0
 0 0 0 0
 0 1 1 1
 0 0 0 1
 0 0 0 0
 3
 样例输出
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 0 0 0
 0 0 0 0 0 0 0 1 0 0
 0 0 0 0 0 0 1 0 0 0
 0 0 0 0 0 0 1 0 0 0
 1 1 1 1 1 1 1 1 1 1
 0 0 0 0 1 1 0 0 0 0
 */
#include <iostream>
#define ROW 15
#define COL 10
#define LEN 4

using namespace std;

bool canTake(int i, int j, int init[][COL], const int pat[][LEN]) {
    for (int ii = i; ii < LEN + i; ii++) {
        for (int jj = j; jj < LEN + j; jj++) {
            if (init[ii][jj] == 1 && pat[ii - i][jj - j] == 1) {
                return false;
            }
        }
    }
    return true;
}

void take(int i, int j, int init[][COL], const int pat[][LEN]) {
    for (int ii = i; ii < i + LEN; ii++) {
        for (int jj = j; jj < j + LEN; jj++) {
            if (pat[ii - i][jj - j] == 1) {
                init[ii][jj] = 1;
            }
        }
    }
}

void run(int init[][COL], int pat[][LEN], int offset) {
    int r = 0;
    for (int i = 0; i < ROW; i++) {
        if (canTake(i, offset, init, pat)) {
            r = i;
        }
        else {
            break;
        }
    }
    take(r, offset, init, pat);
}

void print(int init[][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", init[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int init[ROW + 3][COL];
    int pat[LEN][LEN];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cin >> init[i][j];
        }
    }
    for (int i = ROW; i < ROW + 2; i++) {
        for (int j = 0; j < COL; j++) {
            init[i][j] = 1;
        }
    }
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            cin >> pat[i][j];
        }
    }
    int offset;
    cin >> offset;
    offset--;
    run(init, pat, offset);
    print(init);
    return 0;
}
