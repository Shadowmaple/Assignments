# include <iostream>
# include <set>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m;
    char land[n][m];
    for (int i = 0; i < n; i++) {
        scanf("%s", land[i]);
    }
    cin >> k;
    set<int> s;
    while (k--) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (land[i][j] == '.') continue;
                if (i > 0) s.insert((i-1) * m + j);
                if (i < n-1) s.insert((i+1) * m + j);
                if (j > 0) s.insert(i * m + j - 1);
                if (j < m-1) s.insert(i * m + j + 1);
            }
        }
        for (int x : s) {
            land[x / m][x % m] = 'g';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << land[i][j];
        cout << endl;
    }
    return 0;
}