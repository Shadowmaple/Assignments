// 背包问题，回溯法，八皇后问题

# include <stdio.h>
# include <stdlib.h>

typedef struct {
    int *elem;
    int top;
} Stack;

void stack_init(Stack *s, int size) {
    s->elem = (int *) malloc(sizeof(int) * size);
    s->top = -1;
}

void stack_push(Stack *s, int e) {
    s->top++;
    s->elem[s->top] = e;
}

void stack_pop(Stack *s) {
    s->top--;
}

int stack_is_empty(Stack *s) {
    if (s->top == -1) return 1;
    return 0;
}

int stack_is_full(Stack *s, int size) {
    if (s->top == size - 1) return 1;
    return 0;
}

int is_valid(Stack *s, int e) {
    int s_x, s_y, e_x, e_y;
    for (int i = 0; i <= s->top; i++) {
         s_x = s->elem[i] % 8;
         s_y = s->elem[i] / 8;
         e_x = e % 8;
         e_y = e / 8;
        //  if (s_x == e_x || s_y == e_y || abs(s_x - e_x) == abs(s_y - e_y))
        if (s_x == e_x || abs(s_x - e_x) == abs(s_y - e_y))
            return 0;
    }
    return 1;
}

void put_result(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        int x = s->elem[i] % 8;
        int y = s->elem[i] / 8;
        printf("%d, %d \t", y, x);
    }
    putchar('\n');
}

int main() {
    Stack s;
    stack_init(&s, 8);
    int i = 0, cout = 0;

    do {
        while (i < 64 && !stack_is_full(&s, 8)) {
            if (!is_valid(&s, i)) {
                i++;
                continue;
            }
            stack_push(&s, i);
            // i 换到下一行的棋盘
            i = (s.elem[s.top] / 8 + 1) * 8;
        }
        if (stack_is_full(&s, 8)) {
            put_result(&s);
            cout++;
        } else
            i = s.elem[s.top] + 1;

        stack_pop(&s);
    } while (!stack_is_empty(&s) || i < 64);

    printf("共%d种解法\n", cout);

    return 0;
}