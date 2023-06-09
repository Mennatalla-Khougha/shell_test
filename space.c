#include "main.h"

void space(char **line)
{
    int i = 0, j = 0;
    char *ptr = malloc(_strlen(*line));
    while((*line)[i] && (*line)[i] == ' ')
        i++;
    while((*line)[i])
    {
        if((*line)[i] == ' ')
        {
            ptr[j] = ' ';
            j++;

            while((*line)[i] == ' ')
                i++;
        }
        else
        {
            ptr[j] = (*line)[i];
            i++;
            j++;
        }
    }
    if(ptr[j-1] == ' ')
        j--;
    ptr[j] = '\0';
    free(*line);
    *line = ptr;
}