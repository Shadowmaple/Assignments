/*************************************************
题目：
给定一个二维数组作为图的边描述，为其构造邻接矩阵的存储方法，
给定一个起点，采用非递归输出深度遍历结果
**************************************************/

# include <iostream>
using namespace std;

# define NUM 6

typedef struct {
    int *elem;
    int top;
} Stack;

void stackInit(Stack *s, int size) {
    s->elem = new int(size);
    s->top = -1;
}

void stackPush(Stack *s, int e) {
    s->elem[++s->top] = e;
}

void stackPop(Stack *s, int *e) {
    *e = s->elem[s->top--];
}

int stackEmpty(Stack *s) {
    return s->top == -1;
}

void DFS(int matrix[][NUM], int v) {
    Stack sk;
    stackInit(&sk, NUM);
    stackPush(&sk, v);
    int visited[NUM] = {0};
    visited[v] = 1;
    cout << v + 1 << ' ';

    // sum 为剩余未遍历的节点数
    int i = 0, sum = NUM - 1;
    while (sum > 0 || !stackEmpty(&sk)) {
        // 超出范围，回溯
        if (i >= NUM) {
            stackPop(&sk, &v);
            i = 0;
            continue;
        }
        // 已访问的节点，或无边
        if (visited[i] || !matrix[v][i]) {
            i++;
            continue;
        }
        // 找到节点
        cout << i + 1 << ' ';
        visited[i] = 1;
        stackPush(&sk, i);
        sum--;
        v = i;
        i = 0;
    }
}

int main() {
    int matrix[][NUM] = {
        0,1,1,1,0,0,
        1,0,0,0,1,0,
        1,0,0,0,1,0,
        1,0,0,0,0,1,
        0,1,1,0,0,0,
        0,0,0,1,0,0
    };
    int v;
    cout << "输入起点（从1开始）：";
    cin >> v;

    // 输入的节点从1开始
    DFS(matrix, v - 1);
    cout << endl;

    return 0;
}
