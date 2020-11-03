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
};

struct Edge {
    Node* start;
    Node* end;
    char symbol;
};

struct DNode {
    string name;
    int kind; // 类型，0 普通，1 开始状态，2 结束状态，3 既是开始状态又是结束状态
    map<char, DNode*> targets; // 输入字符后的转换状态
    // TO DO: set<Node*>
    set<Node*> elements;	// 新状态对应的原始状态集合

    DNode(string name) {
        this->name = name;
        kind = 0;
    }
};

// 数字转字符串
string itoStr(int num) {
    stringstream ss;
    ss << num;
    string s;
    ss >> s;
    return s;
}

// 生成状态标识
string GenerateName() {
    stringstream ss;
    ss << char(nodeNum++ + 'A');
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

    // 获取某状态在输入字符下的所有可达点
    void GetReachableNodes(set<Node*>& reachableNodes, const Node* node, char symbol) {
        for (auto edge : this->edges) {
            if (edge.start->name == node->name && edge.symbol == symbol) {
                reachableNodes.insert(edge.end);
            }
        }
    }
};

class DFA {
public:
    vector<DNode*> start;  // 开始状态
    vector<DNode*> end;    // 终结状态
    vector<DNode*> states; // 状态集合
    set<char> symbols;     // 字符集

    void Display() {
        cout << "DFA 的开始状态：";
        for (auto node : start) {
            cout << node->name << " ";
        }
        cout << endl << "DFA 的结束状态：";
        for (auto node : end) {
            cout << node->name << " ";
        }
        cout << endl;

        // 结果
        for (auto state : states) {
            cout << "状态" << state->name << "：";
            for (auto target : state->targets) {
                if (target.second == nullptr) continue;
                cout << "输入" << target.first << " -> " << target.second->name << " ";
            }
            cout << endl;
        }
        cout << "END" << endl;
    }

    // 化简，最小化
    void Simplify() {
        vector<vector<DNode*>> v;

        // 分为终态集合和非终态集合
        vector<DNode*> terminalStates, noTerminalStates;
        for (auto state : states) {
            if (state->kind > 1) terminalStates.push_back(state);
            else noTerminalStates.push_back(state);
        }
        v.push_back(noTerminalStates);
        v.push_back(terminalStates);

        // 若非终态集合能被划分，则划分集合
        // 若终态集合能被划分，则划分集合
        SplitStates(v, 0);

        if (v.size() == 2) return ;

        // --- 构造最小化 DFA，合并状态 ---

        // 映射，原先的状态属于新的某个状态，
        // 如，{2,3} -> 5
        // map<Node*, Node*> mp;
        map<string, DNode*> idMap;
        vector<DNode*> newStates;
        for (int i = 0; i < v.size(); i++) {
            DNode* newState = new DNode(GenerateName());
            newStates.push_back(newState);
            for (DNode* node : v[i]) {
                // mp[node] = newState;
                idMap[node->name] = newState;
                // 开始和终结状态
                // if (node->kind == 1) newState->kind = 1;
                // else if (node->kind == 2) newState->kind = 2;
                newState->kind |= node->kind;
            }
        }

        // 遍历原状态
        for (DNode* originNode : states) {
            // 该状态最小化后对应的新状态
            DNode* newState = idMap[originNode->name];
            // 遍历原状态对应字符的转换
            for (auto target : originNode->targets) {
                auto symbol = target.first;
                auto targetNode = target.second;

                if (targetNode == nullptr) newState->targets[symbol] = nullptr;
                else {
                    // 原目标状态经最小化后的新的状态
                    auto newTargetNode = idMap[targetNode->name];
                    newState->targets[symbol] = newTargetNode;
                }
            }
        }
        this->states = newStates;

        // 修正开始状态和终结状态
        vector<DNode*> startStates, endStates;
        for (auto n : this->start) {
            startStates.push_back(idMap[n->name]);
        }
        for (auto n : this->end) {
            endStates.push_back(idMap[n->name]);
        }
        this->start = startStates;
        this->end = endStates;
    }

private:
    // 分割状态集合，对下标为 splitIndex 集合进行分隔
    void SplitStates(vector<vector<DNode*>>& v, int splitIndex) {
        if (splitIndex >= v.size()) return ;
        if (v[splitIndex].size() <= 1) {
            SplitStates(v, splitIndex + 1);
            return ;
        }

        // 已分隔的状态映射，作用：哪个节点属于哪个集合
        map<string, int> mp;
        for (int i = 0; i < v.size(); i++) {
            for (auto node : v[i]) {
                mp[node->name] = i;
            }
        }

        bool hasSplited = false;
        // 对每个状态求其对应输入字符下转换得到的状态
        vector<vector<DNode*>> vx;
        // 遍历每个输入字符
        for (char symbol : this->symbols) {
            int splitCount = 0; // 分割集合数
            // exists[v.size()] 用于存储 INF
            int exists[v.size()+1];
            for (int j = 0; j <= v.size(); j++)  exists[j] = 0;

            // 对该下标的状态集合进行划分，如 {A,B,C}
            // 若该状态集合是某个状态集合的子集，则无需分隔，否则需要分隔
            for (DNode* node : v[splitIndex]) {
                // 获取输入字符后转换得到的状态
                DNode* targetNode = node->targets[symbol];
                // 空集也要分隔
                int vectorId = targetNode != nullptr ? mp[targetNode->name] : v.size();
                // 将该状态放入分组
                if (!exists[vectorId]) {
                    vx.push_back(vector<DNode*>{node});
                    exists[vectorId] = ++splitCount;
                } else {
                    vx[exists[vectorId]-1].push_back(node);
                }
            }
            // 只有一个分组，即该集合内各个状态都转换到同一个集合，无需分割
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
            // 添加新的分割后的集合，如{A,B},{C}
            // 在原删除处插入
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

// 根据 NFA 状态集查找对应产生的 DFA 新状态
DNode* GetNewStateByOldNodes(vector<DNode*>& states, set<Node*>& curNodes) {
    int len = curNodes.size();
    for (auto newState : states) {
        if (newState->elements.size() != len) continue;

        bool flag = true;
        for (auto signedState : newState->elements) {
            bool find = false;
            for (auto n : curNodes) {
                if (signedState->name == n->name) {
                    find = true;
                    break;
                }
            }
            if (!find) {
                flag = false;
                break;
            }
        }
        if (flag) return newState;
    }
    return nullptr;
}

// 状态集中是否包含原开始状态/结束状态，0 否，1 开始状态，2 结束状态，3 既是开始状态又是结束状态
int IsSpecialNode(Node* startNode, Node* endNode, set<Node*>& curNodes) {
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
void ConvertToDFA(NFA* entry) {
    // 获取字符集
    set<char> symbols;
    for (auto e : entry->edges) {
        symbols.insert(e.symbol);
    }

    DFA* dfa = new DFA();
    // DFA的新产生的状态集
    vector<DNode*> states;
    DNode* curState = new DNode(GenerateName());
    curState->elements = set<Node*>{entry->start};
    states.push_back(curState);

    // 状态集队列
    queue<DNode*> q;
    q.push(curState);

    while (!q.empty()) {
        curState = q.front();
        q.pop();

        // 该状态是否是开始状态或结束状态（包含NFA的开始和结束状态）
        int kind = IsSpecialNode(entry->start, entry->end, curState->elements);
        curState->kind = kind;
        switch (kind) {
            case 1: dfa->start.push_back(curState); break;
            case 2: dfa->end.push_back(curState); break;
            case 3:
                dfa->start.push_back(curState);
                dfa->end.push_back(curState);
        }

        // 遍历字符集
        for (auto symbol : symbols) {
            // 获取该输入字符下所有可达的状态
            set<Node*> reachableNodes;
            // 遍历状态集
            for (auto node : curState->elements) {
                // 获取可达状态
                entry->GetReachableNodes(reachableNodes, node, symbol);
            }
            // 若为空集
            if (reachableNodes.empty()) {
                curState->targets[symbol] = nullptr;
                continue;
            }

            // 查找该可达的状态集对应的被标记的新状态
            DNode* targetState = GetNewStateByOldNodes(states, reachableNodes);
            // 若未查找到，即该状态未被标记，则加入队列
            if (targetState == nullptr) {
                // 新的状态节点
			    targetState = new DNode(GenerateName());
                targetState->elements = reachableNodes;
                states.push_back(targetState);

				q.push(targetState);
            }

            // 加入新的状态映射
            curState->targets[symbol] = targetState;
        }
    }
    dfa->states = states;
    dfa->symbols = symbols;
    dfa->Display();

    cout << "---------------- DFA 最小化 ----------------" << endl;
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

    cout << "------------------- NFA -------------------" << endl;
    NFA* entry = ConvertToNFA();

    nodeNum = 0;
    cout << "------------------- DFA -------------------" << endl;
    ConvertToDFA(entry);

    return 0;
}

// 1(0|1)*10
// (01|1)*1
// b*ab(b|ab)*
// (a|b)*(aa|bb)(a|b)*
