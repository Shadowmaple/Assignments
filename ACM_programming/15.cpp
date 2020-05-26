# include <iostream>
# include <fstream>
# include <vector>
# include <algorithm>
using namespace std;

class Node {
public:
    int linkNum;
};

int n;
int matrix[100][100];
int visited[100];
vector<vector<int>> v;
vector<int> single;

bool DFS(int pre, int cur, int origin, int count) {
    if (origin == cur && count > 1) return true;

    for (int i = 0; i < n; i++) {
        if (cur == i || i == pre) continue;
        if (matrix[cur][i] == 0) continue;

        if (DFS(cur, i, origin, count + 1)) {
            visited[cur] = 1;
            single.push_back(cur);
            return true;
        }
    }
    return false;
}

bool cmp(vector<int> a, vector<int> b) {
    return a[0] < b[0];
}

int main() {
    ifstream f1("input.txt");
    f1 >> n;
    // cin >> n;

    // 初始化
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    Node servers[n];
    int id, no;
    for (int i = 0; i < n; i++) {
        // 服务器编号输入
        // cin >> id;
        f1 >> id;

        // 连接数输入
        // scanf(" (%d)", &servers[id].linkNum);
        f1.ignore(2);
        f1 >> servers[id].linkNum;
        f1.ignore(1);

        // 服务器输入
        for (int j = 0; j < servers[id].linkNum; j++) {
            // cin >> no;
            f1 >> no;
            matrix[id][no] = 1;
        }
    }

    // 矩阵
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++)
    //         cout << matrix[i][j] << ' ';
    //     cout << endl;
    // }

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        // 单点服务器
        if (servers[i].linkNum == 0) {
            single.push_back(i);
            v.push_back(single);
            single.clear();
            visited[i] = 1;

        // 环路
        } else if (servers[i].linkNum > 1) {
            if (DFS(i, i, i, 0)) {
                sort(single.begin(), single.end());
                v.push_back(single);
                single.clear();
            }
        }
    }

    // 剩余的服务器
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        single.push_back(i);
        visited[i] = 1;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) continue;
            single.push_back(j);
            visited[j] = 1;
            break;
        }
        sort(single.begin(), single.end());
        v.push_back(single);
        single.clear();
    }

    // 排序
    sort(v.begin(), v.end(), cmp);

    f1.close();

    // 输出
    ofstream f2("ouput.txt");
    // cout << v.size() << endl;
    f2 << v.size() << endl;
    for (auto x : v) {
        for (int y : x) {
            // cout << y << ' ';
            f2 << y << ' ';
        }
        // cout << endl;
        f2 << endl;
    }

    return 0;
}