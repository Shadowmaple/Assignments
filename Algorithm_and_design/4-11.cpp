// 设 M 是一个 n×n 的整数矩阵, 其中每一行（从左到右）和每一列（从上到下）的元素
// 都按升序排列。设计分治算法确定一个给定的整数 x 是否在 M 中。

# include <iostream>
using namespace std;

# define n 4

int x;

bool search(int M[][n], int row_l, int row_r, int col_l, int col_r) {
    if (row_l > row_r || col_l > col_r)
        return false;

    int row_mid = (row_l + row_r) / 2;
    int col_mid = (col_l + col_r) / 2;
    int data = M[row_mid][col_mid];

    if (data == x) return true;

    bool s1, s2, s3;
    if (data < x) {
        // 左下
        s1 = search(M, row_mid+1, row_r, col_l, col_mid);
        // 右上
        s2 = search(M, row_l, row_mid, col_mid+1, col_r);
        // 右下
        s3 = search(M, row_mid+1, row_r, col_mid+1, col_r);
    } else {
        // 左上
        s1 = search(M, row_l, row_mid-1, col_l, col_mid-1);
        // 右上
        s2 = search(M, row_l, row_mid-1, col_mid, col_r);
        // 左下
        s3 = search(M, row_mid, row_r, col_l, col_mid-1);
    }

    if (s1 || s2 || s3) return true;
    return false;
}

int main() {
    x = 7;
    int M[n][n] = {
        {1, 2, 3, 5},
        {2, 6, 8, 9},
        {3, 7, 9, 11},
        {4, 10, 12, 15}
    };
    // int M[n][n] = {
    //     {1, 2, 3, 5, 6},
    //     {2, 6, 8, 9, 10},
    //     {3, 7, 9, 11, 12},
    //     {4, 10, 12, 15, 17},
    //     {5, 13, 14, 18, 20}
    // };
    if (search(M, 0, n-1, 0, n-1))
        cout << "存在" << endl;
    else cout << "不存在" << endl;

    return 0;
}