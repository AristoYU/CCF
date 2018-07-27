/*
 试题编号：    201409-2
 试题名称：    画图
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　在一个定义了直角坐标系的纸上，画一个(x1,y1)到(x2,y2)的矩形指将横坐标范围从x1到x2，纵坐标范围从y1到y2之间的区域涂上颜色。
 　　下图给出了一个画了两个矩形的例子。第一个矩形是(1,1) 到(4, 4)，用绿色和紫色表示。第二个矩形是(2, 3)到(6, 5)，用蓝色和紫色表示。图中，一共有15个单位的面积被涂上颜色，其中紫色部分被涂了两次，但在计算面积时只计算一次。在实际的涂色过程中，所有的矩形都涂成统一的颜色，图中显示不同颜色仅为说明方便。
 
 　　给出所有要画的矩形，请问总共有多少个单位的面积被涂上颜色。
 输入格式
 　　输入的第一行包含一个整数n，表示要画的矩形的个数。
 　　接下来n行，每行4个非负整数，分别表示要画的矩形的左下角的横坐标与纵坐标，以及右上角的横坐标与纵坐标。
 输出格式
 　　输出一个整数，表示有多少个单位的面积被涂上颜色。
 样例输入
 2
 1 1 4 4
 2 3 6 5
 样例输出
 15
 评测用例规模与约定
 　　1<=n<=100，0<=横坐标、纵坐标<=100。
 */

#include <iostream>
#include <string.h>
#define EMPTY 0
#define FULL 1
#define LEN 101

using namespace std;

int coordinate_system[LEN][LEN];
int cou = 0;

class point {
public:
    int x, y;
    point() {}
    point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class rectangle {
public:
    point p1, p2;
    rectangle() {}
    rectangle(point p1, point p2) {
        this->p1 = p1;
        this->p2 = p2;
    }
};

void run(rectangle rec[], int n) {
    for (int k = 0; k < n; k++) {
        point p1 = rec[k].p1;
        point p2 = rec[k].p2;
        for (int i = p1.x; i < p2.x; i++) {
            for (int j = p1.y; j < p2.y; j++) {
                if (coordinate_system[i][j] == EMPTY) {
//                    printf("( %d , %d)\n", i, j);
                    coordinate_system[i][j] = FULL;
                    cou++;
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    rectangle rec[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        point p1 = point(x, y);
        cin >> x >> y;
        point p2 = point(x, y);
        rec[i] = rectangle(p1, p2);
    }
    memset(coordinate_system, EMPTY, LEN * LEN);
    run(rec, n);
    cout << cou;
    return 0;
}
