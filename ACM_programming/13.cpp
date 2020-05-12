# include <iostream>
# include <math.h>
# include <algorithm>
using namespace std;

class Edge {
public:
    int v1, v2;
    float value;
};

bool cmp(Edge e1, Edge e2) {
    return e1.value > e2.value;
};

int main() {
    int n;
    cin >> n;
    while (n--) {
        int s, p;
        cin >> s >> p;
        int x[p], y[p];
        for (int i = 0; i < p; i++)
            cin >> x[i] >> y[i];

        float matrix[p][p];
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                if (i == j) matrix[i][j] = 0;
                else matrix[i][j] = sqrt((pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2)));
            }
        }

        // 最小路径，连通图
        Edge e[p-1];
        int k = 0;
        bool visited[p] = {false};
        for (int i = 0; i < p; i++) {
            float distMin = 999999;
            int v = i;
            for (int j = i+1; j < p; j++) {
                if (!visited[j] && distMin > matrix[i][j] && matrix[i][j]) {
                    v = j;
                    distMin = matrix[i][j];
                }
            }
            if (v == i) continue;

            for (int j = i+1; j < p; j++)
                if (j != v) matrix[i][j] = matrix[j][i] = 0;

            visited[i] = visited[v] = true;
            e[k].v1 = i;
            e[k].v2 = v;
            e[k].value = matrix[i][v];
            k++;
        }

        sort(e, e+p-1, cmp);
        // for (int i = 0; i < p-1; i++) {
        //     printf("%d %d %f\n", e[i].v1, e[i].v2, e[i].value);
        // }

        if (s < 2) {
            printf("%.2f\n", e[0].value);
            continue;
        }
        k = 0;
        bool flag[p] = {false};
        while (s > 0) {
            if (!flag[e[k].v1] && !flag[e[k].v2]) {
                s -= 2;
            } else s--;
            flag[e[k].v1] = flag[e[k].v2] = true;
            k++;
        }
        printf("%.2f\n", e[k].value);
    }
    return 0;
}