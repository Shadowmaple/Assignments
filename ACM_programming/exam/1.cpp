# include <iostream>
using namespace std;

int main() {
    bool light[1000] = {false};
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            if (j % i == 0) {
                light[j-1] = !light[j-1];
            }
        }
    }

    for (int j = 0; j < n; j++) {
        if (!light[j]) cout << j + 1 << ' ';
    }
    cout << endl;

    return 0;
}