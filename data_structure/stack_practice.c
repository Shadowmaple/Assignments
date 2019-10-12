// 用栈实现回文数的判断

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// typedef char SElemType;

typedef struct {
    char *elem;
    // SElemType *elem;
    int top;
} Stack;

void stack_init(Stack *s, int size) {
    s->elem = (char *) malloc(sizeof(char) * size);
    s->top = -1;
}

void stack_push(Stack *s, char e) {
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

int is_palindrome(char *num) {
    Stack s;
    stack_init(&s, 100);

    for (int i = 0; i < strlen(num); i++) {
        if (s.top == -1)
            stack_push(&s, num[i]);
        else if (s.elem[s.top] == num[i])
            stack_pop(&s);
        else if (s.elem[s.top - 1] == num[i]) {
            stack_pop(&s);
            stack_pop(&s);
        } else
            stack_push(&s, num[i]);
    }
    if (s.top == -1)
        return 1;
    return 0;
}

int main() {
    char num[100];
    scanf("%s", num);
    printf("%s\n", is_palindrome(num) == 1 ? "yes":"no");
    return 0;
}