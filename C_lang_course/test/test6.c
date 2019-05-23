# include <stdio.h>

int main()
{
    int i, j;
    char name[5][10];
    int data[5][4];
    FILE *f1, *f2;

    f1 = fopen("f1.txt", "r+");

    for (i=0; i < 5; i++) {
        fscanf(f1, "%s %d %d %d %d", name[i], &data[i][0],&data[i][1],&data[i][2],&data[i][3]);
    }
    f2 = fopen("f2.txt", "w+");

    for (i=0; i < 5; i++) {
        printf("%s %d %d %d %d\n", name[i], data[i][0],data[i][1],data[i][2],data[i][3]);
        fprintf(f2, "%s %d %d %d %d\n", name[i], data[i][0],data[i][1],data[i][2],data[i][3]);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
