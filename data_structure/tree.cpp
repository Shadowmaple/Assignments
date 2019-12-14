// 二叉树递归遍历
// 根据1,2,3,...,n的顺序创建一个完全二叉树，用二叉链表方式存储，并使用递归方法进行前、中、后序遍历，输出遍历结果

# include <iostream>
using namespace std;

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} TreeNode;

TreeNode *creatBTree(int i, int n) {
    if (i <= n) {
        TreeNode *p = new TreeNode{i};
        TreeNode *pl = creatBTree(2*i, n);
        TreeNode *pr = creatBTree(2*i+1, n);
        p->left = pl;
        p->right = pr;
        return p;
    }
    return nullptr;
}

// 前序遍历
void preOrder(TreeNode *p) {
    if (p) {
        cout << p->data << " ";
        preOrder(p->left);
        preOrder(p->right);
    }
}

// 中序遍历
void inOrder(TreeNode *p) {
    if (p) {
        inOrder(p->left);
        cout << p->data << " ";
        inOrder(p->right);
    }
}

// 后序遍历
void postOrder(TreeNode *p) {
    if (!p) return ;

    postOrder(p->left);
    postOrder(p->right);
    cout << p->data << " ";
}

int main() {
    TreeNode *tree = creatBTree(1, 6);
    preOrder(tree);
    cout << endl;

    inOrder(tree);
    cout << endl;

    postOrder(tree);
    cout << endl;

    return 0;
}
