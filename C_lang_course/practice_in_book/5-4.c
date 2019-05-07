# include <stdio.h>

void main()
{
    printf("*****Time*****\n");
    printf("1     morning\n");
    printf("2     afternoon\n");
    printf("3     night\n");
    printf("Please enter your choice:\n");
    
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1: puts("Good morning");break;
        case 2: puts("Good afternoon"); break;
        case 3: puts("Good night"); break;
        default: puts("Selection error!");
    }
}