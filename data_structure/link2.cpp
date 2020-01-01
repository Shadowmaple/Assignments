/*
题目：
给定一个无序数组，根据其正序构造一个带表头的循环链表，并对其采用插入排序法排序。
排序过程中利用无序表本身的节点进行排序，不构造新的节点，排序后链表仍为循环结构。
构造显示函数displayList显示排序前后链表的内容。
*/

# include <iostream>
using namespace std;

typedef struct node {
    int data;
    struct node *next;
} LinkNode;

LinkNode *createLink(int *num, int len) {
    LinkNode *head = new LinkNode;
    LinkNode *p = head;

    for (int i = 0; i < len; i++) {
        LinkNode *cur = new LinkNode{num[i]};
        p->next = cur;
        p = p->next;
    }
    p->next = head->next;

    return head;
}

// 插入排序
void sort(LinkNode *head) {
    // p为待排序节点，pre为p的前一节点，cur为已排序区间内遍历的当前节点
    LinkNode *p = head->next, *cur = head, *pre = head;
    do {
        while (cur->next != p) {
            if (cur->next->data > p->data) {
                // 插入
                pre->next = p->next;
                p->next = cur->next;
                cur->next = p;
                p = pre->next;
                break;
            }
            cur = cur->next;
        }
        cur = head;

        p = p->next;
        pre = pre->next;
    } while (p != head->next);
}

void displayLink(LinkNode *head) {
    LinkNode *p = head->next;
    do {
        cout << p->data << ' ';
        p = p->next;
    } while (p != head->next);
    cout << endl;
}

int main() {
    int num[] = {1, 4, 2, 18, 24, 3, 2, 8};
    LinkNode *link =  createLink(num, 8);
    displayLink(link);
    sort(link);
    displayLink(link);

    return 0;
}