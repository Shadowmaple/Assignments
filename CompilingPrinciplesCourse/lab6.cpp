# include <iostream>
# include <cctype>
# include <vector>
# include <map>
# include <stack>
# include <string>
using namespace std;

# define INF 99999 // 不可达
# define EMU 0

string s;

class Node {
public:
    char ID;
    Node() {}
};

bool isLetter(char c) {
    if (c <= 'Z' && c >= 'A' || c <= 'z' && c >= 'a' || c >= '0' && c <= '9')
        return true;
    return false;
}

void convertToDFA() {}

void convertToNFA() {
    stack<char> sk;
}

// 转后缀表达式/逆波兰式
void convertToPostfixExpression() {
    stack<char> st;
    string r;
    map<char, int> priority;
    priority['*'] = 10;
    priority['+'] = 7;
    priority['|'] = 5;
    priority['('] = 12;
    priority[')'] = 3;

    for (char c : s) {
        bool cur = isLetter(c);
        if (cur) {
            r += c;
            continue;
        }
        if (c == '(') {
            st.push(c);
            continue;
        }
        if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                r += st.top();
                st.pop();
            }
            // 弹出 (
            st.pop();
            continue;
        }
        while (!st.empty() && st.top() != '(' && priority[c] <= priority[st.top()]) {
            r += st.top();
            st.pop();
        }
        if (c != ')') st.push(c);
    }
    while (!st.empty()) {
        r += st.top();
        st.pop();
    }
    s = r;
}

// 连接符补全
// +，|，*，(，)
void connectorCompletion() {
    string r;
    bool pre = false; // 前一个是否是字符或右括号，即是否需要加+
    for (int i = 0; i < s.length(); i++) {
        bool cur = isLetter(s[i]);
        if (pre && (cur || s[i] == '(')) r += '+';
        r += s[i];
        pre = (s[i] == ')' || cur || s[i] == '*');
    }
    s = r;
}

int main() {
    cin >> s;
    // cout << s << endl;
    connectorCompletion();
    cout << s << endl;
    convertToPostfixExpression();
    cout << s << endl;
    return 0;
}

// 1(0|1)*101
