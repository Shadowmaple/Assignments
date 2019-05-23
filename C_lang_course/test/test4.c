#include<stdio.h>
#include<string.h>

struct dm
{
    char dmy[5];
    char mc[11];
    int dj;
    int sl;
    long je;
};

typedef struct dm pr;

void sortdat(pr *p, int num)
{
    int i, j;
    pr x;
    FILE *f;
    f = fopen("file2.txt", "w+");

    for (i=0; i < num-1; i++) {
        for (j=i; j < num; j++) {
            if ((p[i].mc - '0') < (p[j].mc - '0')) {
                    x = p[i];
                    p[i] = p[j];
                    p[j] = x;
            } else if ((p[i].mc - '0') == (p[j].mc - '0')) {
                if (p[i].je < p[j].je) {
                    x = p[i];
                    p[i] = p[j];
                    p[j] = x;
                }
            }
        }
    }
    for (i=0; i < num; i++) {
        printf("%s %d\n", p[i].mc, p[i].je);
        fputs(p[i].dmy, f);
        fputc(' ', f);
        fputs(p[i].mc, f);
        fputc(' ', f);
        fprintf(f, "%d\t", &p[i].dj);
        fprintf(f, "%d\t", &p[i].sl);
        fprintf(f, "%ld\n",&p[i].je);
       // fputc(p[i].dj, f);
       // fputc('\t', f);
        //fputc(p[i].sl, f);
       // fputc('\t', f);
        //fputc(p[i].je, f);
        //fputc('\n', f);

    }

    fclose(f);
}

int main()
{
    struct dm p[1000];
    int i, j;

    for (i=0; 1; i++) {
        scanf("%s%s%d", p[i].dmy, p[i].mc, &p[i].dj);
        //if (strcmp(&p[i].mc, "break"))
          //  break;
        if (p[i].dj == 0)
            break;
        scanf("%d", &p[i].sl);
        p[i].je = p[i].dj*p[i].sl;

    }
    sortdat(p, i);

    return 0;
}
