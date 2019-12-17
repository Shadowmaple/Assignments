// 给定一个先序序列字符串如“ABC##DE#G##F###”，其中符号#表示空节点，
// 根据该序列，利用非递归方法先序创建一颗二叉树，用二叉链表方式存储
// 很难、很麻烦的一题

# include <iostream>
using namespace std;

# define NUM 10

typedef struct Node {
    char data;
    struct Node *left, *right;
} TreeNode, *pTreeNode;

typedef struct {
    pTreeNode **elem;
    int top;
} Stack;

void stackInit(Stack *s, int size) {
    s->elem = new pTreeNode *[NUM];
    s->top = -1;
}

void stackPush(Stack *s, TreeNode **p) {
    s->elem[++s->top] = p;
}

void stackPop(Stack *s) {
    if (s->top == -1) {
        cout << "Stack is empty" << endl;
        return ;
    }
    s->top--;
}

int stackEmpty(Stack *s) {
    return s->top == -1;
}

TreeNode *createBTree(char *s) {
    if (s[0] == '\0') return NULL;

    TreeNode *root = new TreeNode{s[0]};
    TreeNode *preNode = root, *newNode;
    pTreeNode *p;
    Stack sk;
    stackInit(&sk, NUM);
    stackPush(&sk, &root->right);
    int hasPop = 0;

    for (int i = 1; s[i] != '\0'; i++) {
        if (s[i] != '#') {
            newNode = new TreeNode{s[i]};

            if (!hasPop) {
                preNode->left = newNode;
            } else {
                /// 弹出栈、右节点情况
                *p = newNode;
                // p->data = s[i];
                hasPop = 0;
            }
            stackPush(&sk, &newNode->right);
            preNode = newNode;

        } else if (s[i] == '#' && !stackEmpty(&sk)) {
            p = sk.elem[sk.top];
            stackPop(&sk);
            hasPop = 1;
        }
    }
    return root;
}

void postTree(TreeNode *p) {
    if (!p)  {
        cout << '#';
    } else {
        cout << p->data;
        postTree(p->left);
        postTree(p->right);
    }
}

int main() {
    char s[] = "ABC##DE#G##F###";
    TreeNode *p = createBTree(s);
    postTree(p);
    cout << endl;

    return 0;
}