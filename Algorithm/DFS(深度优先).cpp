#include <iostream>
#include <vector>
#define MAX 10

using namespace std;

int RES = 0;
vector<int> ans;

void DFS(int arr[], //数组
         int total, //数组总数
         int sel,   //选择数
         int index, //索引
         int res,   //结果
         int nowSel,//已经选择数
         vector<int> &temp   //暂存向量
) {
    if (nowSel == sel && res > RES) {
        RES = res;
        ans = temp;
        return;
    }
    if (nowSel > sel || index == total) {
        return;
    }
    //选
    temp.push_back(arr[index]);
    //树的分支1
    DFS(arr, total, sel, index + 1, res * arr[index], nowSel + 1, temp);
    //不选
    temp.pop_back();
    //数的分支2
    DFS(arr, total, sel, index + 1, res, nowSel, temp);
}

int main() {
    int sel = 3;
    int total;
    cin >> total;
    int arr[total];
    for (int i = 0; i < total; i++) {
        cin >> arr[i];
    }
    vector<int> temp;
    DFS(arr, total, sel, 0, 1, 0, temp);
    cout << "RES:" << RES << endl;
    for (vector<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        cout << *it << " ";
    }
    return 0;
}
