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

    // 计算等待时间
    int computeWaitTime() {}
};

float totalWaitTime;
// int curTime;
vector<Process*> v;

// 优先数调度算法

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
        // process->waitTime += totalWaitTime - process->runTime;
        process->waitTime += curTime;

        if (process->needTime <= robinTime) {
            curTime += process->needTime;
            process->runTime += process->needTime;
            process->needTime = 0;
            v.push_back(process);
            continue;
        }
        curTime += robinTime;
        process->needTime -= robinTime;
        process->runTime += robinTime;
        q.push(process);
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

        // 取最早的作业的时间为当前时间
        // curTime = curTime > inTime ? inTime : curTime;
    }

    totalWaitTime = 0;

    cout << "------ 调度结果 -------" << endl;

    // FIFO();
    RoundRobin();

    Display();

    return 0;
}

/*
1 20 1
2 10 2
3 40 0
4 10 2
*/