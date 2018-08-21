/*
 * 狄杰斯特拉
 * 测试数据
 * 4 4
 * 0 2 1
 * 2 1 2
 * 2 3 4
 * 1 3 1
 * 0 3
 */
#include <iostream>
#include <vector>
#include <map>
#define INF 1000000

using namespace std;

struct Node {
    int No;
    bool isVisited = false;
    int lenToSource = INF;
    int pre = -1;
    map<int, int> Edge;
};

vector<Node> node;

void Dijkstra(int beg) {
    Node &begin = node[beg];
    begin.isVisited = true;
    int no = -1, w = INF;
    for (map<int, int>::iterator it = begin.Edge.begin(); it != begin.Edge.end(); it++) {
        if (it->second != INF && !node[it->first].isVisited && it->second < w) {
            no = it->first;
            w = it->second;
        }
    }
    if (no == -1) {
        return;
    }
    Node &next = node[no];
    int w_after = begin.lenToSource + w;
    if (w_after <= next.lenToSource) {
        next.lenToSource = w_after;
        next.pre = begin.No;
    }
    return Dijkstra(no);
}

void MakeMap(vector<map<int, int> > set) {
    for (int i = 0; i < set.size(); i++) {
        map<int, int> t = set[i];
        Node temp;
        temp.No = i;
        temp.Edge = t;
        node.push_back(temp);
    }
}

void Init(int beg) {
    vector<Node>::iterator it;
    for (it = node.begin(); it != node.end(); it++) {
        map<int, int>::iterator mit = it->Edge.find(beg);
        if (mit != it->Edge.end()) {
            it->lenToSource = mit->second;
        }
        if (it->No == beg) {
            it->lenToSource = 0;
            it->pre = beg;
        }
    }
}

void PrintRoad(int end) {
    Node temp = node[end];
    int pre = temp.pre;
    if (pre == temp.No) {
        printf("%d", pre);
        return;
    }
    PrintRoad(pre);
    printf(" -> %d", temp.No);
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<map<int, int> > set(m);
    for (int i = 0; i < n; i++) {
        int n1, n2, w;
        cin >> n1 >> n2 >> w;
        set[n1].insert(make_pair(n2, w));
        set[n2].insert(make_pair(n1, w));
    }
    int beg, end;
    cin >> beg >> end;
    MakeMap(set);
    Init(beg);
    Dijkstra(beg);
    PrintRoad(end);
    cout << endl;
    return 0;
}
