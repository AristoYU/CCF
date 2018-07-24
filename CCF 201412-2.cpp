/*
 试题编号：    201412-2
 试题名称：    Z字形扫描
 时间限制：    2.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　在图像编码的算法中，需要将一个给定的方形矩阵进行Z字形扫描(Zigzag Scan)。给定一个n×n的矩阵，Z字形扫描的过程如下图所示：
 
 　　对于下面的4×4的矩阵，
 　　1 5 3 9
 　　3 7 5 6
 　　9 4 6 4
 　　7 3 1 3
 　　对其进行Z字形扫描后得到长度为16的序列：
 　　1 5 3 9 7 3 9 5 4 7 3 6 6 4 1 3
 　　请实现一个Z字形扫描的程序，给定一个n×n的矩阵，输出对这个矩阵进行Z字形扫描的结果。
 输入格式
 　　输入的第一行包含一个整数n，表示矩阵的大小。
 　　输入的第二行到第n+1行每行包含n个正整数，由空格分隔，表示给定的矩阵。
 输出格式
 　　输出一行，包含n×n个整数，由空格分隔，表示输入的矩阵经过Z字形扫描后的结果。
 样例输入
 4
 1 5 3 9
 3 7 5 6
 9 4 6 4
 7 3 1 3
 样例输出
 1 5 3 9 7 3 9 5 4 7 3 6 6 4 1 3
 评测用例规模与约定
 　　1≤n≤500，矩阵元素为不超过1000的正整数。
 */

#include <iostream>
#include <string.h>
#define LEN 500
#define NIL 0 //可以扫描
#define HOLD -1 //不能扫描
#define RIGHT 0
#define LEFT_DOWN 1
#define DOWN 2
#define RIGHT_UP 3

using namespace std;

int matrix[LEN + 2][LEN + 2], input[LEN + 1][LEN + 1];

void Right(int &i, int &j, int &dir) {
    //不能走，换方向
    if (matrix[i][j + 1] == HOLD) {
        dir++;
        return;
    }
    j++;
    cout << input[i][j] << " ";
    matrix[i][j] = HOLD;
    //走一步换方向
    dir++;
}

void Down(int &i, int &j, int &dir) {
    //不能走，换方向
    if (matrix[i + 1][j] == HOLD) {
        dir++;
        return;
    }
    i++;
    cout << input[i][j] << " ";
    matrix[i][j] = HOLD;
    //走一步换方向
    dir++;
}

void leftDown(int &i, int &j, int &dir) {
    //不能走，换方向
    if (matrix[i + 1][j - 1] == HOLD) {
        dir++;
        return;
    }
    i++;
    j--;
    cout << input[i][j] << " ";
    matrix[i][j] = HOLD;
}

void rightUp(int &i, int &j, int &dir) {
    if (matrix[i - 1][j + 1] == HOLD) {
        dir++;
        return;
    }
    i--;
    j++;
    cout << input[i][j] << " ";
    matrix[i][j] = HOLD;
}

void run(int n) {
    int i = 1, j = 1;
    int dir = RIGHT;
    bool flag = true;
    cout << input[i][j] << " ";
    matrix[i][j] = HOLD;
    while (flag) {
        switch (dir % 4) {
            case RIGHT:
                Right(i, j, dir);
                break;
                
            case LEFT_DOWN:
                leftDown(i, j, dir);
                break;
                
            case DOWN:
                Down(i, j, dir);
                break;
                
            case RIGHT_UP:
                rightUp(i, j, dir);
                break;
        }
        if (i == n && j == n) {
            break;
        }
    }
}

int main() {
    //数组分配直接使用 sizeof（）
    memset(matrix, HOLD, sizeof(matrix));
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = NIL;
            cin >> input[i][j];
        }
    }
    run(n);
    return 0;
}
