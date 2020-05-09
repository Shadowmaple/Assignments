# include <iostream>
using namespace std;

bool valid(bool *visit, int k) {
    int count = 5;
    while (k) {
        int x = k % 10;
        if (visit[x]) return false;
        visit[x] = true;
        k /= 10;
        count--;
    }
    while (count) {
        if (visit[0]) return false;
        visit[0] = true;
        count--;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    for (int i = 01234; i < 100000 / n; i++) {
        bool visit[10] = {false};
        if (!valid(visit, i)) continue;

        int abcde = n * i;
        if (!valid(visit, abcde)) continue;
        printf("%05d/%05d=%d\n", abcde, i, n);
    }

    return 0;
}