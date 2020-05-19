# include <iostream>
# include <string>
# include <vector>
# include <math.h>
# include <algorithm>
using namespace std;

class Planet {
public:
    char name;
    float value;
    int road;
    float factValue;
    string pass;
    void init(char n, float v, string p) {
        name = n;
        value = v;
        factValue = road = 0;
        pass = p;
    };

    void countFactValue() {
        if (!road) factValue = value;
        else factValue = value * (1 - pow(0.05, road));
    };
};

bool cmp(Planet p1, Planet p2) {
    if (p1.factValue > p2.factValue) return true;
    else if (p1.factValue < p2.factValue) return false;
    if (p1.name < p2.name) return true;
    return false;
};

// DFS，计算中转站数量
int countRoad(vector<vector<int>>& matrix, int idx, int n) {
    // 直连地球
    if (matrix[idx][0]) return 0;

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!matrix[idx][i]) continue;
        int num = countRoad(matrix, i, n) + 1;
        if (num == 1) return 1;
        count = min(count, num);
    }
    return count;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (!n) cout << endl;
        Planet node[n];
        // int matrix[n][n];
        vector<vector<int>> matrix(n+1, vector<int>(n+1));
        int mp[100] = {0}; // 映射：字母->下表
        char name;
        float value;
        string pass;
        // 输入
        for (int i = 0; i < n; i++) {
            cin >> name >> value >> pass;
            node[i].init(name, value, pass);
            mp[name] = i + 1; // i=0属于*，连接地球
        }
        mp['*'] = 0;

        // 构建邻接矩阵
        for (int i = 0; i < n; i++) {
            pass = node[i].pass;
            for (char c : pass) {
                int idx = mp[c];
                matrix[idx][i+1] = matrix[i+1][idx] = 1;
            }
        }

        // 矩阵输出
        // for (int i = 0; i <= n; i++) {
        //     for (int j = 0; j <= n; j++) {
        //         printf("%d ", matrix[i][j]);
        //     }
        //     cout << endl;
        // }

        // 计算实际的价格
        for (int i = 0; i < n; i++) {
            node[i].road = countRoad(matrix, i+1, n);
            node[i].countFactValue();
        }

        sort(node, node + n, cmp);

        // for (int i = 0; i < n; i++) {
        //     printf("%c %d %.5f\n", node[i].name, node[i].road, node[i].factValue);
        // }

        cout << node[0].name << endl;
    }
    return 0;
}

// examples
/*
1
F 0.81 *
5
E 0.01 *A
D 0.01 A*
C 0.01 *A
A 1.00 EDCB
B 0.01 A*

5
E 0.01 *B
D 0.01 B*
C 0.01 *B
B 1.00 EDCA
A 0.95 B*
*/
