// 作业调度

# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

int curTime;

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

class Task {
public:
    int id; // 序号
    int inTime; // 进入系统时间，1011 -> 10:11
    int duration; // 持续时间
    int beginTime; // 开始运行时间

    Task() {}
    Task(int id, int inTime, int duration) {
        this->id = id;
        this->inTime = inTime;
        this->duration = duration;
        this->beginTime = 0;
    }

    void Print() {
        printf("%d %d %d %d\n", id, inTime, duration, beginTime);
    }

    // 计算响应比
    // 响应比 = 响应时间 / 要求服务时间
    //       = （等待时间 + 要求服务时间） / 要求服务时间
    //       = 1 + 等待时间 / 要求服务时间
    float CountResponseRate() {
        int waitTime = convertTimeToMin(curTime) - convertTimeToMin(this->inTime);
        return 1 + waitTime / this->duration;
    }

    // 按进入时间比较，升序
    static int cmpByInTime(Task* t1, Task* t2) {
        return t1->inTime < t2->inTime;
    }

    static int cmpByResponseRate(Task t1, Task t2) {
        float rate1 = t1.CountResponseRate();
        float rate2 = t2.CountResponseRate();
        return rate1 > rate2;
    }
};

vector<Task*> v;

// ----------------------------------------------------------------------------

// 高响应比优先算法
void HighResponse() {
    int len = v.size();

    // 调度
    for (int i = 0; i < len; i++) {
        int k = i;
        for (int j = i+1; j < len; j++) {
            if (Task::cmpByResponseRate(*v[j], *v[k])) k = j;
        }
        v[k]->beginTime = v[k]->inTime > curTime ? v[k]->inTime : curTime;

        curTime = computeTime(v[k]->beginTime, v[k]->duration);
        swap(v[i], v[k]);
    }
}

// 短作业优先
void ShortTaskFirst() {
    int len = v.size();

    // 调度
    for (int i=0; i < len; i++) {
        bool hasWait = false; // 是否有当前等待运行调度的任务，即已进入系统
        int k = i;
        int x = i; // 标记为在未进入系统的任务中优先调度的
        for (int j = i+1; j < len; j++) {
            // 未进入系统的任务
            if (v[j]->inTime > curTime) {
                // 已经有等待调度的
                if (hasWait) continue;
                // 最先进入系统的，或同时进入系统但持续时间最短的
                if (v[x]->inTime > v[j]->inTime ||
                    v[x]->inTime == v[j]->inTime && v[x]->duration > v[j]->duration)
                    x = j;
                continue;
            }
            // 已进入系统，等待调度的
            hasWait = true;
            if (v[k]->duration > v[j]->duration) {
                k = j;
            }
        }
        if (!hasWait) {
            k = x;
            v[k]->beginTime = v[k]->inTime > curTime ? v[k]->inTime : curTime;
        } else {
            v[k]->beginTime = curTime;
        }

        curTime = computeTime(v[k]->beginTime, v[k]->duration);
        swap(v[i], v[k]);
    }
}

// 先进先出
void FIFO() {
    sort(v.begin(), v.end(), Task::cmpByInTime);
    for (Task* task : v) {
        task->beginTime = curTime;
        curTime = computeTime(task->beginTime, task->duration);
    }
}

// -----------------------------------------------------------------

int main() {
    curTime = INT32_MAX;
    int n;
    cout << "输入作业数：";
    cin >> n;
    int id, inTime, duration;
    for (int i = 0; i < n; i++) {
        cin >> id >> inTime >> duration;
        Task* task = new Task(id, inTime, duration);
        v.push_back(task);

        // 取最早的作业的时间为当前时间
        curTime = curTime > inTime ? inTime : curTime;
    }

    // FIFO();
    // ShortTaskFirst();
    HighResponse();

    cout << "作业调度顺序，输出：" << endl;
    for (Task* task : v) {
        task->Print();
    }

    return 0;
}

/*
1 800 50
2 815 30
3 830 25
4 835 20
5 845 15
6 900 10
7 920 5
*/

// 1256743
