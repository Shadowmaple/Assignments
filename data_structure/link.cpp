/*******************************************************************************
题目：
26个英文字母的正常排序为ABC...XYZ。利用链表构造存放26个英文字母的线性表，
同时允许用户输入不同的整数以改变字母序列的输出如下：
当用户输入正数，如输入4时，输出E F G H I J K L M N O P Q R S T U V W X Y Z A B C D ，
当输入28时，输出C D E F G H I J K L M N O P Q R S T U V W X Y Z A B，
当输入-4时输出W X Y Z A B C D E F G H I J K L M N O P Q R S T U V
********************************************************************************/

# include <iostream>
using namespace std;

// 双向链表
typedef struct node {
    char data;
    struct node *pre, *next;
} LinkNode;

LinkNode *createLink() {
    LinkNode *head = new LinkNode{'A'};
    LinkNode *pre = head, *current;
    for (int i = 1; i < 26; i++) {
        char c = 'A' + i;
        current = new LinkNode{c};
        pre->next = current;
        current->pre = pre;
        pre = current;
    }
    // 构建循环链表，连接首尾
    current->next = head;
    head->pre = current;
    return head;
}

void displayLink(LinkNode *head, int n) {
    if (n > 0)
        while (n--) head = head->next;
    else if (n < 0)
        while (n++) head = head->pre;

    LinkNode *p = head;
    do {
        cout << p->data << ' ';
        p = p->next;
    } while (p != head);
    cout << endl;
}

int main() {
    LinkNode *link = createLink();
    LinkNode *p = link;

    int n;
    cout << "输入整数：";
    cin >> n;
    displayLink(link, n);

    return 0;
}