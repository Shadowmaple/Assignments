# include <iostream>
using namespace std;

int main() {
    int n = 10, m = 10;
    int block[n][m];
    block[n-1][0] = 1;
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (i < n-1 && j)
                block[i][j] = block[i+1][j] + block[i][j-1];
            else if (i < n-1)
                block[i][j] = block[i+1][j];
            else if (j)
                block[i][j] = block[i][j-1];
        }
    }
    cout << block[0][m-1] << endl;
    return 0;
}