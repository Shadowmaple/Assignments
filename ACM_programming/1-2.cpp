// 排列
// 用1,2,3...9组成三个三位数，且n1:n2:n3=1:2:3，输出所有解

# include <iostream>
using namespace std;

void DFS(bool *visited, int n[3], int idx) {
    if (idx == 9) {
        // n[0]:n[1]:n[2]=1:2:3
        if (n[0] * 2 == n[1] && n[0] * 3 == n[2])
            cout << n[0] << " " << n[1] << " " << n[2] << endl;
        return ;
    }
    for (int i = 1; i <= 9; i++) {
        if (visited[i-1]) continue;
        visited[i-1] = true;
        n[idx/3] = n[idx/3] * 10 + i;
        DFS(visited, n, idx+1);
        n[idx/3] = (n[idx/3] - i) / 10;
        visited[i-1] = false;
    }
}

int main() {
    int n[3] = {0};
    bool visited[9] = {false};
    DFS(visited, n, 0);
    return 0;
}