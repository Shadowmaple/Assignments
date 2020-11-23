// 进程调度 v2

# include <iostream>
# include <vector>
# include <queue>
# include <algorithm>
using namespace std;

class Process {
public:
    int id;
    int state; // 进程状态 (1 就绪 2 等待 3 运行）
    int inTime; // 进入系统时间，1011 -> 10:11
    int needTime; // 需要运行时间
    int priority; // 优先级，0最高
    int waitTime;
    int runTime;

    Process() {}
    Process(int id, int inTime, int needTime, int priority) {
        this->id = id;
        this->state = 1;
        this->inTime = inTime;
        this->needTime = needTime;
        this->priority = priority;
        this->waitTime = 0;
        this->runTime = 0;
    }

    void Show() {
        cout << id << " " << waitTime << endl;
    }

    // 按进入时间比较，升序
    static int cmpByInTime(Process* p1, Process* p2) {
        return p1->inTime < p2->inTime;
    }
};

float totalWaitTime;
vector<Process*> v;

int convertTimeToMin(int time) {
    return time / 100 * 60 + time % 100;
}

int computeTime(int time, int duration) {
    int hour = time / 100;
    int min = time % 100;
    int sum = min + duration;
    min = sum % 60;
    hour += sum / 60;
    return hour * 100 + min;
}

struct Cmp {
    bool operator () (Process* a, Process* b) {
        return a->priority > b->priority;
    }
};

// 优先数调度算法，非抢占式
void PriorityScheduling() {
    sort(v.begin(), v.end(), Process::cmpByInTime);

    priority_queue<Process*, vector<Process*>, Cmp> priorityQueue;
    queue<Process*> q;
    for (auto p : v) q.push(p);
    v.clear();

    int curTime = v[0]->inTime;
    while (!q.empty() || !priorityQueue.empty()) {
        // 当前时间要进入系统的进程
        while (!q.empty() && q.front()->inTime <= curTime) {
            auto p = q.front();
            q.pop();
            priorityQueue.push(p);
        }

        // 处理已在系统中的进程
        auto process = priorityQueue.top();
        priorityQueue.pop();

        cout << process->id << " ";
        process->waitTime = convertTimeToMin(curTime) - convertTimeToMin(process->inTime);
        v.push_back(process);

        curTime = computeTime(curTime, process->needTime);
    }
    cout << endl;

    for (auto p : v) {
        totalWaitTime += p->waitTime;
    }
}

// 时间片轮转算法
void RoundRobin() {
    sort(v.begin(), v.end(), Process::cmpByInTime);

    // 时间片
    int robinTime = 5;
    queue<Process*> q, waitQueue;
    for (auto p : v) q.push(p);
    v.clear();

    int curTime = v[0]->inTime;
    while (!q.empty() || !waitQueue.empty()) {
        // 当前时间要进入系统的进程
        while (!q.empty() && q.front()->inTime <= curTime) {
            auto p = q.front();
            q.pop();
            waitQueue.push(p);
        }

        // 处理在等待的
        if (waitQueue.empty()) continue;

        auto process = waitQueue.front();
        waitQueue.pop();
        cout << process->id << " ";

        // 运行需要时间 <= 时间片轮转时间，即本次就结束
        if (process->needTime <= robinTime) {
            process->waitTime = convertTimeToMin(curTime) - convertTimeToMin(process->inTime) - process->runTime;

            curTime = computeTime(curTime, process->needTime);
            process->runTime += process->needTime;
            process->needTime = 0;

            v.push_back(process);
        } else {
            // 还需要下次接着运行
            curTime = computeTime(curTime, robinTime);
            process->runTime += robinTime;
            process->needTime -= robinTime;

            waitQueue.push(process);
        }
    }
    cout << endl;

    for (auto p : v) {
        totalWaitTime += p->waitTime;
    }
}

void FIFO() {
    sort(v.begin(), v.end(), Process::cmpByInTime);
    int curTime = v[0]->inTime;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i]->id << " ";

        int duration = convertTimeToMin(curTime) - convertTimeToMin(v[i]->inTime);
        v[i]->waitTime = duration > 0 ? duration : 0;

        curTime = computeTime(curTime, v[i]->needTime);
    }
    cout << endl;

    for (auto p : v) {
        totalWaitTime += p->waitTime;
    }
}

void Display() {
    for (auto p : v) {
        p->Show();
    }
    cout << "等待总时间：" << totalWaitTime << endl;
    cout << "平均等待时间：" << totalWaitTime / v.size() << endl;
}

int main() {
    // curTime = INT32_MAX;
    int n;
    cout << "输入作业数：";
    cin >> n;
    int id, inTime, needTime, priority;
    for (int i = 0; i < n; i++) {
        cin >> id >> inTime  >> needTime >> priority;
        Process* process = new Process(id, inTime, needTime, priority);
        v.push_back(process);
    }

    totalWaitTime = 0;

    cout << "------ 调度结果 -------" << endl;

    FIFO();
    // RoundRobin();
    // PriorityScheduling();

    Display();

    return 0;
}

/*
1 20 1
2 10 2
3 40 0
4 10 2
*/

/*
1 800 40 1
2 815 10 2
3 830 40 0
4 835 10 2
*/