# include <iostream>
# include <vector>
# include <map>
# include <stack>
# include <string>
# include <sstream>
using namespace std;

# define INF 99999 // 不可达
# define NODE_NUM 0

string s;
int nodeNum;

struct Node {
    string name;
};

struct Edge {
    Node* start;
    Node* end;
    char symbol;
};

string itoStr(int num) {
    stringstream ss;
    ss << num;
    string s;
    ss >> s;
    return s;
}

class NFA {
public:
    Node* start;
    Node* end;
    vector<Edge> edges;

    NFA(Node* start, Node* end, Edge edge) {
        this->start = start;
        this->end = end;
        this->edges.push_back(edge);
    }

    NFA(char c) {
        // 构造节点
        Node* start = new Node{itoStr(nodeNum++)};
        Node* end = new Node{itoStr(nodeNum++)};
        // 构造边
        Edge* edge = new Edge{start, end, c};

        NFA* entry = new NFA(start, end, *edge);
        *this = *entry;
        // return entry;
    }

    // a+b
    static NFA* Unite(NFA* left, NFA* right) {
        Node* node = left->end;
        for (auto e : right->edges) {
            if (e.start == right->start) {
                e.start = node;
            }
            if (e.end == right->start) {
                e.end = node;
            }
            left->edges.push_back(e);
        }
        // 如果右部的不是只有一个节点，则将左部的尾节点置为右部的尾节点
        // 如果只有一个节点（闭包），则左部的尾节点不变
        if (right->start != right->end)
            left->end = right->end;
        return left;
    }

    // a|b
    static NFA* Join(NFA* left, NFA* right) {
        // 选择边数多的为主
        if (left->edges.size() < right->edges.size()) swap(left, right);

        for (auto e : right->edges) {
            if (e.start == right->start) {
                e.start = left->start;
            }
            if (e.end == right->end) {
                e.end = left->end;
            }
            // 尾节点自匹配，边的开始和结束都是自身
            if (e.start == right->end) {
                e.start = left->end;
            } else if (e.end == right->start) {
                // 首节点自匹配，边的首尾都是自身
                e.end = left->start;
            }
            left->edges.push_back(e);
        }
        return left;
    }

    // 闭包，a*
    static NFA* Closure(NFA* entry) {
        vector<Edge> v;
        for (auto e : entry->edges) {
            if (e.end == entry->end) {
                e.end = entry->start;
            }
            if (e.start == entry->end) {
                e.start = entry->start;
            }
            v.push_back(e);
        }
        entry->edges = v;
        entry->end = entry->start;
        return entry;
    }

    void Display() {
        cout << "NFA 的起始状态：" << this->start->name << endl;
        cout << "NFA 的结束状态：" << this->end->name << endl;
        cout << "NFA 的边数：" << this->edges.size() << endl;
        for (int i = 0; i < edges.size(); i++) {
            auto edage = edges[i];
            cout << "第" << i << "条边" << ' '
                << "起始状态：" << edage.start->name << ' '
                << "结束状态：" << edage.end->name << ' '
                << "转换符：" << edage.symbol << endl;
            // printf("第%d条边 起始状态:%s 结束状态:%s 转换符:%c\n", i, edage.start->name.c_str, edage.end->name, edage.symbol);
        }
        cout << "END" << endl;
    }
};

bool isLetter(char c) {
    return c <= 'Z' && c >= 'A' || c <= 'z' && c >= 'a' || c >= '0' && c <= '9';
}

void convertToDFA() {}

// 转为 NFA
void convertToNFA() {
    stack<NFA*> sk;
    for (char c : s) {
        switch (c) {
            case '+': {
                NFA* right = sk.top();
                sk.pop();
                NFA* left = sk.top();
                sk.pop();
                left = NFA::Unite(left, right);
                sk.push(left);
                break;
            } case '|': {
                NFA* right = sk.top();
                sk.pop();
                NFA* left = sk.top();
                sk.pop();
                left = NFA::Join(left, right);
                sk.push(left);
                break;
            } case '*': {
                NFA* entry = sk.top();
                sk.pop();
                entry = NFA::Closure(entry);
                sk.push(entry);
                break;
            } default: {
                NFA* entry = new NFA(c);
                sk.push(entry);
            }
        }
    }
    NFA* entry = sk.top();
    entry->Display();
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

// 检验是否合法
bool check() {
    return true;
}

int main() {
    cin >> s;
    check();

    connectorCompletion();
    cout << s << endl;
    convertToPostfixExpression();
    cout << s << endl;

    convertToNFA();

    return 0;
}

// 1(0|1)*10
