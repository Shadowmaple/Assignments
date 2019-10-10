// 课程：C++面向对象程序设计
// 题目：
// 设计一个闹钟程序，可以设置至少两个闹铃时间。设置时钟运行的起始时间、闹铃时间，
// 然后通过运行函数run()启动。时钟显示格式为hh:mm:ss, 闹铃用机器喇叭或显示闹铃字样，闹铃不影响时钟运行与显示。
// 使用读机器时钟的函数完成本作业，可以在网上查到该函数。
//
// 开发环境：Linux
// 编译器：g++
// 时间：2019.10.10

# include <iostream>
# include <time.h>
# include <stdio.h>

using namespace std;

// 最大响铃设定时间次数
# define BELL_TIME_MAX 10

struct time {
    int h, m, s;
};

class Clock {
private:
    struct time start_time;
    // 响铃时间，有多个，所以设为数组
    struct time bell_time[BELL_TIME_MAX];

public:
    Clock(int h, int m, int s);
    ~Clock() {delete this;};
    // 设定的响铃次数
    int bell_count = 0;
    // 设定响铃时间
    void bell_time_config(int h, int m, int s);
    void run();
    // 更新时钟
    void update();
};

Clock::Clock(int h, int m, int s) {
    start_time.h = h;
    start_time.m = m;
    start_time.s = s;
}

void Clock::bell_time_config(int h, int m, int s) {
    bell_time[bell_count].h = h;
    bell_time[bell_count].m = m;
    bell_time[bell_count].s = s;
    bell_count++;
}

void Clock::run() {
    time_t pre, now;
    time(&pre);

    while (1) {
        time(&now);
        if (now - pre != 1)
            continue;

        // 更新时钟
        this->update();

        // 输出时钟时间
        cout << "\r                                 \r";
        printf("%02d:%02d:%02d", start_time.h, start_time.m, start_time.s);

        // 循环遍历响铃时间
        for (int i = 0; i < bell_count; i++) {
            if (start_time.s == bell_time[i].s && start_time.m == bell_time[i].m && start_time.h == bell_time[i].h) {
                cout << "\a\a\a" << " The clock is ringing!";
            }
        }
        fflush(stdout);

        pre = now;
    }
}

void Clock::update() {
    start_time.s++;
    // 秒位进位
    if (start_time.s >= 60) {
        start_time.m++;
        start_time.s = 0;
    }
    // 分位进位
    if (start_time.m >= 60) {
        start_time.h++;
        start_time.m = 0;
    }
    if (start_time.h >= 24) {
        start_time.h = 0;
    }
}

int main() {
    int h, m, s;
    cout << "时钟开始时间：";
    cin >> h >> m >> s;
    Clock clock1(h, m, s);

    // 输入响铃时间
    // 设定的闹铃次数
    int count = 0;
    while (count < BELL_TIME_MAX) {
        count++;
        cout << "响铃时间" << count << "（-1停止输入）：";
        cin >> h;
        // 停止输入，退出循环
        if (h == -1) {
            break;
        }
        cin >> m >> s;
        clock1.bell_time_config(h, m, s);
    }

    // 时钟运行
    clock1.run();

    return 0;
}