#include <stdlib.h>
#include <string.h>

int putenv(char *string) {
    if (string == NULL) {
        return -1; // Invalid input
    }

    // Extract the name and value parts from the string
    char *name = strtok(string, "=");
    char *value = strtok(NULL, "=");

    if (name == NULL || value == NULL) {
        return -1; // Invalid format
    }

    // Set the variable using setenv()
    if (setenv(name, value, 1) != 0) {
        return -1; // Error setting the variable
    }

    return 0; // Success
}

int setenv(const char *name, const char *value, int overwrite) {
    if (name == NULL || value == NULL) {
        return -1; // Invalid input
    }

    // Check if the variable already exists
    char *env_entry = getenv(name);
    if (env_entry != NULL) {
        if (overwrite == 0) {
            return 0; // Variable exists and overwrite is disabled
        } else {
            // Remove the existing variable
            unsetenv(name);
        }
    }

    // Concatenate name and value into "name=value" format
    size_t entry_length = strlen(name) + strlen(value) + 2;
    char *env_str = (char *) malloc(entry_length * sizeof(char));
    if (env_str == NULL) {
        return -1; // Memory allocation error
    }
    strcpy(env_str, name);
    strcat(env_str, "=");
    strcat(env_str, value);

    // Add the variable to the environment
    if (putenv(env_str) != 0) {
        free(env_str); // Clean up allocated memory
        return -1; // Error setting the variable
    }

    return 0; // Success
}


#include <stdlib.h>
#include <string.h>

int unsetenv(const char *name) {
    if (name == NULL) {
        return -1; // Invalid input
    }

    // Check if the variable exists
    char *env_entry = getenv(name);
    if (env_entry == NULL) {
        return 0; // Variable does not exist
    }

    // Open /dev/null to discard the variable assignment
    int fd = open("/dev/null", O_WRONLY);

    if (fd == -1) {
        return -1; // Error opening /dev/null
    }

    // Write the assignment to /dev/null
    char *env_str;
    size_t entry_length = strlen(name) + 2;
    env_str = (char *) malloc(entry_length * sizeof(char));
    if (env_str == NULL) {
        close(fd); // Close the file descriptor
        return -1; // Memory allocation error
    }
    strcpy(env_str, name);
    strcat(env_str, "=");
    write(fd, env_str, strlen(env_str));

    // Close the file descriptor and free allocated memory
    close(fd);
    free(env_str);

    return 0; // Success
}
