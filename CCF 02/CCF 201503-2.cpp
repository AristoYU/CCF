 /*
 试题编号：    201503-2
 试题名称：    数字排序
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　给定n个整数，请统计出每个整数出现的次数，按出现次数从多到少的顺序输出。
 输入格式
 　　输入的第一行包含一个整数n，表示给定数字的个数。
 　　第二行包含n个整数，相邻的整数之间用一个空格分隔，表示所给定的整数。
 输出格式
 　　输出多行，每行包含两个整数，分别表示一个给定的整数和它出现的次数。按出现次数递减的顺序输出。如果两个整数出现的次数一样多，则先输出值较小的，然后输出值较大的。
 样例输入
 12
 5 2 3 3 1 3 4 2 5 2 3 5
 样例输出
 3 4
 2 3
 5 3
 1 1
 4 1
 评测用例规模与约定
 　　1 ≤ n ≤ 1000，给出的数都是不超过1000的非负整数。
 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Num {
    int Snum;
    int count;
} Num;

Num num_count[1001];

void Init() {
    for (int i = 1; i <= 1001; i++) {
        num_count[i].Snum = i;
        num_count[i].count = 0;
    }
}

void Count(const int *arr, int num) {
    for (int i = 0; i < num; i++) {
        num_count[arr[i]].count++;
    }
}

bool cmp(Num n1, Num n2) {
    return (n1.count > n2.count || (n1.count == n2.count && n1.Snum < n2.Snum));
}

bool isExist(int *arr, int num, int Snum) {
    for (int i = 0; i < num; i++) {
        if (arr[i] == Snum) {
            return true;
        }
    }
    return false;
}

void Output(int *arr, int num) {
    for (int i = 1; i <= num; i++) {
        if (isExist(arr, num, num_count[i].Snum)) {
            cout << num_count[i].Snum << " " << num_count[i].count << endl;
        }
    }
}

int main() {
    int num;
    cin >> num;
    int arr[num];
    for (int i = 0; i < num; i++) {
        cin >> arr[i];
    }
    Init();
    Count(arr, num);
    sort(num_count + 1, num_count + 1001, cmp);
    Output(arr, num);
    return 0;
}
