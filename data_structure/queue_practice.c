# include <stdio.h>
# include <stdlib.h>

typedef struct {
    int *elem;
    int front, rear;
    int size;
} Queue;

void queue_init(Queue *q, int size) {
    q->size = size;
    q->front = 0;
    q->rear = 0;
    q->elem = (int *) malloc(sizeof(int) * size);
}

void queue_push(Queue *q, int e) {
    q->elem[q->rear] = e;
    q->rear = ++q->rear % q->size;
}

int queue_pop(Queue *q) {
    int e = q->elem[q->front];
    q->front = ++q->front % q->size;
    return e;
}

int queue_is_empty(Queue *q) {
    return q->front == q->rear;
}

int queue_is_full(Queue *q) {
    return (q->front - 1) % q->size == q->rear;
}

int main() {
    int size = 8;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Queue q;
    queue_init(&q, size + 1);
    for (int i = 0; i < size; i++)
        queue_push(&q, a[i]);

    int k = 0;
    while (!queue_is_empty(&q)) {
        if (k % 2) {
            queue_push(&q, queue_pop(&q));
        } else {
            printf("%d ", queue_pop(&q));
        }
        k = ++k % size;
    }
    putchar('\n');

    return 0;
}
