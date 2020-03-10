# include <iostream>
using namespace std;

typedef struct Node {
    int data;
    struct Node *left, *right;
} TreeNode;

TreeNode* buildTree(int sk) {
    char c;
    do {
        c = getchar();
        if (c == '(') sk++;
        else if (c == ')') {
            sk--;
            if (!sk) return nullptr;
        }
    } while (c == ' ' || c == '\n' || c == '(' || c == ')');

    int num = c - '0';
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') continue;
        if (c == '(') break;
        num = (c - '0') + num*10;
    }
    TreeNode *tree = new TreeNode;
    tree->data = num;
    tree->left = buildTree(1);
    tree->right = buildTree(0);
    while (getchar() != ')') ;
    return tree;
}

bool visit(TreeNode *tree, int num, int& target) {
    if (!tree) {
        if (num == target) return true;
        return false;
    }
    num += tree->data;
    return visit(tree->left, num, target) || visit(tree->right, num, target);
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        TreeNode *tree = buildTree(0);
        if (visit(tree, 0, n)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
    return 0;
}