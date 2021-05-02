#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void compress(char *source)
{
    int n1 = strlen(source);
    char *output = (char*)malloc(2 * n1+1);
    for (int i = 0; i < n1; i++) {
        for (int j = i+1; j < n1; j++)
        {
            if (source[i] == source[j]) {
                continue;
            } else {
                output += sprintf(output, "%c%d", source[i], j -i);
                i = j - 1;
                break;
            }
        }

    }
}