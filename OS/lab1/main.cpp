# include <iostream>
# include <vector>
# include <algorithm>
# include <time.h>
# include <unistd.h>
using namespace std;

class Task {
private:
    int id; // 序号
    int begin; // 开始时间，1011 -> 10:11
    int duration; // 持续时间

public:
    Task(int id, int begin, int duration) {
        this->id = id;
        this->begin = begin;
        this->duration = duration;
    }

    void Print() {
        printf("%d %d %d\n", id, begin, duration);
    }

    // 按持续时间比较，升序
    static int cmp(Task t1, Task t2) {
        return t1.duration < t2.duration;
    }

    // 计算响应比
    // 响应比 = 响应时间 / 要求服务时间 = （等待时间 + 要求服务时间） /  要求服务时间
    float CountResponseRate() {
        // 获取当前时间
        time_t nowTime = time(NULL);
        struct tm *t = localtime(&nowTime);
        int now = t->tm_hour * 100 + t->tm_min;

        // cout << now << endl;

        int waitTime = now - this->begin;

        return (waitTime + this->duration) / this->duration;
    }

    static int cmpByResponseRate(Task t1, Task t2) {
        float rate1 = t1.CountResponseRate();
        float rate2 = t2.CountResponseRate();
        return rate1 > rate2;
    }
};

vector<Task> v;

// 高响应比优先算法
void HighResponse() {
    vector<Task> vp = v;
    sort(vp.begin(), vp.end(), Task::cmpByResponseRate);
    for (Task task : vp) {
        task.Print();
    }
}

// 短作业优先
void ShortTaskFirst() {
    vector<Task> vp = v;
    sort(vp.begin(), vp.end(), Task::cmp);
    for (Task task : vp) {
        task.Print();
    }
}

void FIFO() {
    for (Task task : v) {
        task.Print();
    }
}

int main() {
    // getTime();

    int n;
    cin >> n;
    int id, begin, duration;
    for (int i = 0; i < n; i++) {
        cin >> id >> begin >> duration;
        v.push_back(Task(id, begin, duration));
    }

    cout << "作业调度，输出：" << endl;

    // while(1) {
    //     cout << v[0].CountResponseRate() << endl;
    //     sleep(1);
    // }

    // FIFO();
    // ShortTaskFirst();
    HighResponse();

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
