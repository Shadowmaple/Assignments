# include <iostream>
# include <vector>
# include <map>
# include <stack>
# include <queue>
# include <set>
# include <string>
# include <sstream>
using namespace std;

# define INF -1 // 不可达

string s;
int nodeNum;

struct Node {
    string name;
    int id;
};

struct Edge {
    Node* start;
    Node* end;
    char symbol;
};

// 数字转字符串
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
            auto edge = edges[i];
            cout << "第" << i << "条边" << ' '
                << "起始状态：" << edge.start->name << ' '
                << "结束状态：" << edge.end->name << ' '
                << "转换符：" << edge.symbol << endl;
            // printf("第%d条边 起始状态:%s 结束状态:%s 转换符:%c\n", i, edge.start->name.c_str, edge.end->name, edge.symbol);
        }
        cout << "END" << endl;
    }
};

class DFA {
public:
    vector<Node*> start;       // 开始状态
    vector<Node*> end;         // 终结状态
    vector<vector<Node*>> table; // 状态二维表
    set<char> symbols;         // 字符集
    vector<Node*> states;      // 状态集合

    DFA() {}

    void Display() {
        cout << "DFA 的开始状态：";
        for (auto node : start) {
            cout << node->id << " ";
        }
        cout << endl << "DFA 的结束状态：";
        for (auto node : end) {
            cout << node->id << " ";
        }
        // 打印x轴顶部栏（字符集）
        cout << endl << "  ";
        for (auto symbol : symbols) {
            cout << symbol << " ";
        }
        cout << endl;

        // 结果
        puts("--------");
        for (int i = 0; i < table.size(); i++) {
            cout << i << " ";
            for (auto node : table[i]) {
                if (node == nullptr) cout << "-" << " ";
                else cout << node->id << " ";
            }
            cout << endl;
        }
        cout << "END" << endl;
    }

    // 化简，最小化
    void Simplify() {
        vector<vector<Node*>> v;

        // 分为终态集合和非终态集合
        vector<Node*> terminalStates, noTerminalStates;
        for (auto node : states) {
            bool isEnd = false;
            for (auto endNode : end) {
                if (node->id == endNode->id) {
                    isEnd = true;
                    break;
                }
            }
            if (isEnd) terminalStates.push_back(node);
            else noTerminalStates.push_back(node);
        }
        v.push_back(noTerminalStates);
        v.push_back(terminalStates);

        // 若非终态集合能被划分，则划分集合
        // 若终态集合能被划分，则划分集合
        SplitStates(v, 0);

        if (v.size() == 2) return ;

        /* --- 构造最小化 DFA，合并状态 --- */

        // 映射，原先的状态属于新的某个状态，
        // 如，{2,3} -> 2
        // map<Node*, Node*> mp;
        map<int, Node*> idMap;
        vector<Node*> newStates;
        for (int i = 0; i < v.size(); i++) {
            Node* newState = new Node{itoStr(i), i};
            newStates.push_back(newState);
            for (auto node : v[i]) {
                // mp[node] = newState;
                idMap[node->id] = newState;
            }
        }

        // TO DO: vector<map<char, Node*>>
        vector<vector<Node*>> newTable;
        // v: {{0},{1,3},{2}}
        // ss: {1,3}...
        for (auto ss : v) {
            // 同一集合中状态转换都一样，所以只取第一个，如{1,3}取1
            Node* originNode = ss[0];
            vector<Node*> ax;
            for (int i = 0; i < symbols.size(); i++) {
                // 获取原先转换得到的状态
                Node* originTargetNode = table[originNode->id][i];
                if (originTargetNode == nullptr) {
                    ax.push_back(nullptr);
                } else {
                    // 获取新的转换状态，要取消合并后的状态，转到新的状态节点
                    Node* newTargetNode = idMap[originTargetNode->id];
                    ax.push_back(newTargetNode);
                }
                // if (table[originNode->id][i])
                //     cout << table[originNode->id][i]->id << " ";
                // else cout << "-" << " ";
            }
            newTable.push_back(ax);
            // cout << endl;
        }
        this->table = newTable;
        this->states = newStates;

        // 修正开始状态和终结状态
        vector<Node*> startStates, endStates;
        for (auto n : this->start) {
            startStates.push_back(idMap[n->id]);
        }
        for (auto n : this->end) {
            endStates.push_back(idMap[n->id]);
        }
        this->start = startStates;
        this->end = endStates;
    }

private:
    void SplitStates(vector<vector<Node*>>& v, int splitIndex) {
        if (splitIndex >= v.size()) return ;
        if (v[splitIndex].size() <= 1) {
            SplitStates(v, splitIndex + 1);
            return ;
        }

        // 已分隔的状态映射，作用：哪个节点属于哪个集合
        map<int, int> mp;
        for (int i = 0; i < v.size(); i++) {
            for (auto node : v[i]) {
                if (node->id != INF) mp[node->id] = i;
            }
        }

        bool hasSplited = false;
        // 对每个状态求其对应输入字符下转换得到的状态
        vector<vector<Node*>> vx;
        // 遍历每个输入字符
        for (int i = 0; i < symbols.size(); i++) {
            int splitCount = 0; // 分割集合数
            // exists[v.size()] 用于存储 INF
            int exists[v.size()+1];
            for (int j = 0; j <= v.size(); j++)  exists[j] = 0;

            // 若该状态集合是某个状态集合的子集，则无需分隔，否则需要分隔
            for (auto node : v[splitIndex]) {
                Node* toNode = table[node->id][i];
                // 空集也要分隔
                int vectorId = toNode != nullptr ? mp[toNode->id] : v.size();

                if (!exists[vectorId]) {
                    vx.push_back(vector<Node*>{node});
                    exists[vectorId] = ++splitCount;
                } else {
                    vx[exists[vectorId]-1].push_back(node);
                }
            }
            // 都转换到同一个集合，无需分隔
            if (splitCount == 1) {
                vx.clear();
                continue;
            }
            // 分割
            // 移除原有集合，如{A,B,C}
            auto it = v.begin();
            for (int j = 0; it != v.end(); it++, j++) {
                if (j == splitIndex) {
                    v.erase(it);
                    break;
                }
            }
            // 添加新的分隔后的集合，如{A,B},{C}
            // 在中间插入
            v.insert(it, vx.begin(), vx.end());
            hasSplited = true;
            break;
        }

        // 分隔
        if (hasSplited) SplitStates(v, splitIndex);
        else SplitStates(v, splitIndex + 1);
    }
};

// 是否是有效字符（字母、数字）
bool IsLetter(char c) {
    return c <= 'Z' && c >= 'A' || c <= 'z' && c >= 'a' || c >= '0' && c <= '9';
}

struct StateMap {
    vector<Node*> oldNodes;
    Node* newNode;
};

// 根据 NFA 状态集查找对应产生的 DFA 新状态
Node* GetNewStateByOldNodes(vector<StateMap*>& stateMapList, vector<Node*>& curNodes) {
    int len = curNodes.size();
    for (auto mp : stateMapList) {
        if (mp->oldNodes.size() != len) continue;

        bool flag = true;
        for (auto signedNode : mp->oldNodes) {
            bool find = false;
            for (auto n : curNodes) {
                if (signedNode->name == n->name) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                flag = false;
                break;
            }
        }
        if (flag) return mp->newNode;
    }
    return nullptr;
}

/*
// 当前新状态（DFA的旧状态集）是否被标记
bool hasExisted(vector<vector<Node*>>& signedNodesList, vector<Node*>& curNodes) {
    int len = curNodes.size();
    for (auto signedNodes : signedNodesList) {
        if (signedNodes.size() != len) continue;
        bool flag = true;
        for (auto signedNode : signedNodes) {
            bool find = false;
            for (auto n : curNodes) {
                if (signedNode->name == n->name) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;
}
*/

// 获取可达点
vector<Node*> GetReachableNodesA(const NFA* entry, const Node* node, char symbol) {
    vector<Node*> v;
    for (auto edge : entry->edges) {
        if (edge.start->name == node->name && edge.symbol == symbol) {
            v.push_back(edge.end);
        }
    }
    return v;
}

// 是否包含开始状态/结束状态，0 否，1 开始状态，2 结束状态，3 既是开始状态又是结束状态
int IsSpecialNode(Node* startNode, Node* endNode, vector<Node*>& curNodes) {
    int isStart = 0, isEnd = 0;
    for (auto node : curNodes) {
        if (node->name == startNode->name) {
            isStart = 1;
        } else if (node->name == endNode->name) {
            isEnd = 2;
        }
    }
    return isStart + isEnd;
}

// 转为 DFA
void ConvertToDFA(const NFA* entry) {
    // 获取字符集
    set<char> symbols;
    for (auto e : entry->edges) {
        symbols.insert(e.symbol);
    }

    DFA* dfa = new DFA();
    // 存储 DFA 状态图的二维表，y 为状态，x 为转换字符
    vector<vector<Node*>> x;
    // DFA的新产生的状态集
    vector<Node*> states{entry->start};

    // 未标记的状态集队列
    queue<StateMap*> q;
    StateMap* mp = new StateMap{vector<Node*>{entry->start}, new Node{itoStr(nodeNum), nodeNum++}};
    q.push(mp);

    // 保存状态映射集合，用于根据NFA状态集获取产生的DFA新状态
    vector<StateMap*> stateMapList{mp};
    // vector<vector<Node*>> signedNodes{vector<Node*>{entry->start}};

    while (!q.empty()) {
        auto stateMp = q.front();
        q.pop();

        // 该状态是否是开始状态或结束状态（包含NFA的开始和结束状态）
        switch (IsSpecialNode(entry->start, entry->end, stateMp->oldNodes)) {
            case 1: dfa->start.push_back(stateMp->newNode); break;
            case 2: dfa->end.push_back(stateMp->newNode); break;
            case 3:
                dfa->start.push_back(stateMp->newNode);
                dfa->end.push_back(stateMp->newNode);
        }

        vector<Node*> v;
        // 遍历字符集
        for (auto symbol : symbols) {
            vector<Node*> allReachableNodes;
            // 遍历状态集
            for (auto node : stateMp->oldNodes) {
                auto reachableNodes = GetReachableNodesA(entry, node, symbol);
                if (reachableNodes.empty()) continue;
                allReachableNodes.insert(allReachableNodes.end(), reachableNodes.begin(), reachableNodes.end());
            }
            if (allReachableNodes.empty()) {
                v.push_back(nullptr);
                continue;
            }
            Node* curState = GetNewStateByOldNodes(stateMapList, allReachableNodes);
            // 若未查找到，即该状态未被标记，则加入队列
            if (curState == nullptr) {
                // 新的状态节点
			    curState = new Node{itoStr(nodeNum), nodeNum++};
                states.push_back(curState);

				StateMap* newStateMp = new StateMap{allReachableNodes, curState};
				q.push(newStateMp);
				// signedNodes.push_back(allReachableNodes);
                stateMapList.push_back(newStateMp);
            }

			// 加入新的状态映射
			v.push_back(curState);
        }
        x.push_back(v);
    }
    dfa->table = x;
    dfa->symbols = symbols;
    dfa->states = states;
    dfa->Display();

    dfa->Simplify();
    dfa->Display();
}

// 转为 NFA
NFA* ConvertToNFA() {
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
    return entry;
}

// 转后缀表达式/逆波兰式
void ConvertToPostfixExpression() {
    stack<char> st;
    string r;
    map<char, int> priority;
    priority['*'] = 10;
    priority['+'] = 7;
    priority['|'] = 5;
    priority['('] = 12;
    priority[')'] = 3;

    for (char c : s) {
        bool cur = IsLetter(c);
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
void ConnectorCompletion() {
    string r;
    bool pre = false; // 前一个是否是字符或右括号，即是否需要加+
    for (int i = 0; i < s.length(); i++) {
        bool cur = IsLetter(s[i]);
        if (pre && (cur || s[i] == '(')) r += '+';
        r += s[i];
        pre = (s[i] == ')' || cur || s[i] == '*');
    }
    s = r;
}

// 检验是否合法
// TO DO
bool CheckValid() {
    stack<char> sk;
    for (char c : s) {

    }
    return true;
}

int main() {
    cin >> s;
    if (!CheckValid()) {
        cout << "正规式输入错误！" << endl;
        return 0;
    }

    ConnectorCompletion();
    cout << s << endl;
    ConvertToPostfixExpression();
    cout << s << endl;

    NFA* entry = ConvertToNFA();

    nodeNum = 0;
    ConvertToDFA(entry);

    return 0;
}

// 1(0|1)*10
// (01|1)*1
// b*ab(b|ab)*
// (a|b)*(aa|bb)(a|b)*
