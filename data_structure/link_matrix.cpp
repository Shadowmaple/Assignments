/*************************************************************************
题目：给定一个稀疏矩阵，编写程序将其转化为链式存储结构。
提示：
矩阵每行的非零元素用一个单链表存放，单链表中每个节点需要存放列信息和元素值。
数组parray用于存放每行单链表的首地址。编写函数createLinkMatrix根据矩阵创建链式结构，
函数displayLinkMatrix以[行、列、值]格式显示链式矩阵内容。
**************************************************************************/

# include <iostream>
using namespace std;

struct SingleNode {
    int column;
    int value;
    SingleNode *next;
};

struct LinkMatrix {
    SingleNode *link;
};

void createLinkMatrix(LinkMatrix *matrix, int *num, int row, int column) {
    for (int i = 0; i < row; i++) {
        matrix[i].link = nullptr;
        SingleNode *currentLink = matrix[i].link;

        for (int j = 0; j < column; j++) {
            int x = i * column + j;
            if (!num[x]) continue;
            SingleNode *link = new SingleNode{j, num[x], NULL};
            if (currentLink == nullptr) {
                matrix[i].link = link;
                currentLink = link;
                continue;
            }
            currentLink->next = link;
            currentLink = currentLink->next;
        }
    }
}

void displayLinkMatrix(LinkMatrix *matrix, int row) {
    int count = 0;
    for (int i = 0; i < row; i++) {
        SingleNode *link = matrix[i].link;
        while (link) {
            printf("[%d, %d, %d]\n", i, link->column, link->value);
            link = link->next;
            count++;
        }
    }
    printf("共%d个节点\n", count);
}

int main() {
    int num[25] = {
        3, 0, 0, 0, 7,
        0, 0, -1, 0, 0,
        -1, -2, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 2, 0
    };
    LinkMatrix matrix[5] = {NULL};
    createLinkMatrix(matrix, num, 5, 5);
    displayLinkMatrix(matrix, 5);

    return 0;
}
