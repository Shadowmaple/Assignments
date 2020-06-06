// 给定一个正整数集合 X = {x1,x2..,xn}，和一个正整数 y，设计回溯算法，
// 求集合 X 的一个子集 Y，使得 Y 中元素之和等于 y

# include <iostream>
# include <vector>
using namespace std;

int n, y;
vector<vector<int>> Y;
vector<int> v;

void backtracking(int i, int *x, int y, int sum, int *cur) {
    if (i == n) return ;
    // 不符合，直接回溯返回
    if (sum + x[i] > y) return ;

    if (sum + x[i] == y) {
        cur[i] = 1;

        for (int j = 0; j < n; j++)
            if (cur[j] == 1) v.push_back(x[j]);

        Y.push_back(v);
        v.clear();
    }

    cur[i] = 1;
    backtracking(i+1, x, y, sum+x[i], cur);
    cur[i] = 0;
    backtracking(i+1, x, y, sum, cur);
}

int main() {
    n = 5;
    y = 7;
    int x[20] = {2, 1, 4, 5, 3};
    int cur[n];

    backtracking(0, x, y, 0, cur);

    for (vector<int> v : Y) {
        for (int m : v) {
            cout << m << ' ';
        }
        cout << endl;
    }

    return 0;
}
