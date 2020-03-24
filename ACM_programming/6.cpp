# include <iostream>
# include <queue>
using namespace std;

int main() {
    int n, m;
    while (1) {
        cin >> n >> m;
        if (!n && !m) break;

        queue<int> q;
        for (int i = 1; i <= n; i++)
            q.push(i);

        while (q.size() > 1) {
            for (int i = 1; i < m; i++) {
                q.push(q.front());
                q.pop();
            }
            q.pop();
        }
        cout << q.front() << endl;
    }
    return 0;
}