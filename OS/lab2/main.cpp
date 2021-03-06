// 进程调度

# include <iostream>
# include <vector>
# include <queue>
using namespace std;

class Process {
public:
    int id;
    int state; // 进程状态 (1 就绪 2 等待 3 运行）
    int needTime; // 需要运行时间
    int priority; // 优先级，0最高
    int waitTime;
    int runTime;

    Process() {}
    Process(int id, int needTime, int priority) {
        this->id = id;
        this->state = 1;
        this->needTime = needTime;
        this->priority = priority;
        this->waitTime = 0;
        this->runTime = 0;
    }

    void Show() {
        cout << id << " " << waitTime << endl;
    }
};

float totalWaitTime;
vector<Process*> v;

struct Cmp {
    bool operator () (Process* a, Process* b) {
        return a->priority > b->priority;
    }
};

// 优先数调度算法，非抢占式
void PriorityScheduling() {
    priority_queue<Process*, vector<Process*>, Cmp> q;
    // priority_queue<Process*> q;
    for (auto p : v) q.push(p);
    v.clear();

    float curTime = 0;
    while (!q.empty()) {
        auto process = q.top();
        q.pop();
        cout << process->id << " ";
        process->waitTime = curTime;
        curTime += process->needTime;
        v.push_back(process);
    }
    cout << endl;

    for (auto p : v) {
        totalWaitTime += p->waitTime;
    }
}

// 时间片轮转算法
void RoundRobin() {
    // 时间片
    float robinTime = 5;
    queue<Process*> q;
    for (auto p : v) q.push(p);
    v.clear();

    float curTime = 0;
    while (!q.empty()) {
        auto process = q.front();
        q.pop();
        cout << process->id << " ";
        process->waitTime = curTime - process->runTime;

        // 运行需要时间 <= 时间片轮转时间，即本次就结束
        if (process->needTime <= robinTime) {
            curTime += process->needTime;
            process->runTime += process->needTime;
            process->needTime = 0;
            v.push_back(process);
        } else {
            // 还需要下次接着运行
            curTime += robinTime;
            process->needTime -= robinTime;
            process->runTime += robinTime;
            q.push(process);
        }
    }
    cout << endl;

    for (auto p : v) {
        totalWaitTime += p->waitTime;
    }
}

void FIFO() {
    for (int i = 0; i < v.size(); i++) {
        v[i]->waitTime = totalWaitTime;

        if (i < v.size()-1) totalWaitTime += v[i]->needTime;
    }
}

void Display() {
    for (auto p : v) {
        p->Show();
    }
    cout << totalWaitTime << endl;
    cout << totalWaitTime / v.size() << endl;
}

int main() {
    // curTime = INT32_MAX;
    int n;
    cout << "输入作业数：";
    cin >> n;
    int id, state, needTime, priority;
    for (int i = 0; i < n; i++) {
        cin >> id  >> needTime >> priority;
        Process* process = new Process(id, needTime, priority);
        v.push_back(process);
    }

    totalWaitTime = 0;

    cout << "------ 调度结果 -------" << endl;

    // FIFO();
    // RoundRobin();
    PriorityScheduling();

    Display();

    return 0;
}

/*
1 20 1
2 10 2
3 40 0
4 10 2
*/