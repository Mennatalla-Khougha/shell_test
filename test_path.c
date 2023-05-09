#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    char *home_dir = NULL;
    char *path = NULL;
    for (int i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            path = &envp[i][5];
        }
    }
    
    // Find the value of the PATH variable
    
    // Print out the results
    printf("PATH variable: %s\n", home_dir);

    
   /* for (int i = 0; envp[i] != NULL; i++){
    printf("%s\n\n", envp[i]);
   } */
    return 0;
}
