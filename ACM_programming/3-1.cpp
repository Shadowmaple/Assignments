# include <iostream>
# include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++) {
        stack<char> sk;
        string s;
        getline(cin, s);
        for (char c : s) {
            if (sk.empty()) {
                sk.push(c);
                continue;
            }
            if (c == ')' && sk.top() == '(' || c == ']' && sk.top() == '[') {
                sk.pop();
                continue;
            }
            sk.push(c);
        }
        if (sk.empty()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}