#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGUMENTS 10

int main()
{
    char* path_variable = getenv("PATH"); // get the value of the PATH environment variable
    char* path_copy = strdup(path_variable); // create a copy of the PATH variable string
    
    char* path_component = strtok(path_copy, ":"); // split the string into individual directory paths using ':' as a delimiter
    
    while (path_component != NULL)
    {
        char command[MAX_COMMAND_LENGTH];
        sprintf(command, "%s/ls", path_component); // construct a path to the "ls" command in the current directory
        
        if (access(command, X_OK) == 0) // check if the file exists and is executable
        {
            printf("Found ls at: %s\n", command);
            // execute the "ls" command using execve() or a similar function
            break;
        }
        
        path_component = strtok(NULL, ":"); // move on to the next directory path in the list
    }
    
    free(path_copy); // free the memory used by the copied string
    
    return 0;
}