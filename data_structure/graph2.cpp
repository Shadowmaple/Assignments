// 求单源最短路径，Dijkstra（迪杰斯特拉）算法

# include <iostream>
using namespace std;

# define NUM 5
# define INF 9999 // 表示无穷大

int dist_min(int a[], int flag[]) {
    int min = INF, k;
    for (int i = 0; i < NUM; i++) {
        if (!flag[i] && a[i] < min) {
            min = a[i];
            k = i;
        }
    }
    return k;
}

void dij_search(int matrix[][NUM], int origin) {
    // 保存当前最短路径长度
    int dist[NUM] = {0};
    // 节点是否已求出最短路径
    int flag[NUM] = {0};
    // 路径，保存前驱
    int path[NUM];
    flag[origin] = 1;

    for (int i = 0; i < NUM; i++) {
        dist[i] = matrix[origin][i];
        path[i] = origin;
    }

    for (int i = 0; i < NUM; i++) {
        int k = dist_min(dist, flag);
        flag[k] = 1;
        for (int j = 0; j < NUM; j++) {
            if (!flag[j] && matrix[k][j] < INF && dist[k]+matrix[k][j] < dist[j]) {
                dist[j] = dist[k] + matrix[k][j];
                path[j] = k;
            }
        }
    }

    // 输出路径
    for (int i = 0; i < NUM; i++) {
        if (dist[i] == INF || i == origin) continue;

        for (int k = i; k != origin; k = path[k])
            cout << k << "<-";

        cout << origin << ": " << dist[i] << endl;
    }
}

int main() {
    int matrix[NUM][NUM] = {
        0, 10, INF, 30, 100,
        INF, 0, 50, INF, INF,
        INF, INF, 0, INF, 10,
        INF, INF, 20, 0, 60,
        INF, INF, INF, INF, 0,
    };

    dij_search(matrix, 0);

    return 0;
}