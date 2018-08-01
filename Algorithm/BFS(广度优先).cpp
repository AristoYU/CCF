/*
 * 广度优先本质上使用队列进行计算。每次加入节点的都为当前处理节点的子节点（相关节点）。以层级的模式进行处理.
 * 模版
 * void BFS(* 需要进行计算的参数 *) {
 *      queue<int> q;
 *      q.push(* 将根节点入队 *);
 *      while(!q.empty()) {         //当队列不为空时
 *          //取出队首元素 top
 *          //访问队首元素 top
 *          //将队首元素出队
 *          //将 top 的下一层级所有未入队的节点全部入队，并标记已入队
 *      }
 * }
 */
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 100;

struct node {
    int x, y;                                       //位置(x,y)
} Node;

int n, m;                                           //矩阵大小
int matrix[maxn][maxn];                             //01矩阵
bool inq[maxn][maxn] = {false};                     //记录(x,y)是否入过队
int X[4] = {0, 0, 1, -1};                           //增量数组
int Y[4] = {1, -1, 0, 0};                           //通过提取相同增量来简化工程

bool judge(int x, int y) {                          //判断(x,y)是否需要访问
    if (x >= n || x < 0 || y > m || y < 0)          //越界!!!!
        return false;
    if (matrix[x][y] == 0 || inq[x][y] == true)     //在矩阵中为0 或者 被访问过
        return false;
    return true;
}

void BFS(int x, int y) {
    queue<node> Q;                                  //定义队列
    Node.x = x;                                     //设定节点坐标
    Node.y = y;
    Q.push(Node);                                   //入队
    inq[x][y] = true;                               //记录(x,y)已经入队
    while (!Q.empty()) {
        node top = Q.front();                       //取队头
        Q.pop();                                    //队首出队
        for (int i = 0; i < 4; i++) {
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            if (judge(newX, newY)) {                //判断新的节点是否需要访问
                Node.x = newX;                      //设定节点坐标
                Node.y = newY;
                Q.push(Node);                       //坐标入队
                inq[newX][newY] = true;             //记录新的节点
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    int ans = 0;
    for (int x = 0; x < n; x++) {                   //枚举所有位置
        for (int y = 0; y < m; y++) {
            if (matrix[x][y] == 1 && inq[x][y] == false) {
                ans++;
                BFS(x, y);                          //将所有可以与其成为“块”的节点标记
            }
        }
    }
    cout << ans << endl;
    return 0;
}
