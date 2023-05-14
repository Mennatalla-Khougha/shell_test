#include "main.h"

char *strtok(char *str, const char *delim) {
    static char *last_token = NULL; // keeps track of last token found
    char *token; // pointer to the current token

    if (str != NULL) { // if a new string is passed in
        last_token = str; // set last_token to the start of the string
    }

    if (last_token == NULL) { // if we haven't found any tokens yet
        return NULL;
    }

    // find the first delimiter after the last token
    token = last_token;
    while (*token != '\0' && *token != *delim) {
        token++;
    }

    if (*token == '\0') { // if we've reached the end of the string
        last_token = NULL;
        return NULL;
    }

    // replace the delimiter with a null terminator and update last_token
    *token = '\0';
    last_token = token + 1;

    return last_token - 1; // return the current token
}
/* Sure! The `strtok` function is a standard C library function that is used to tokenize (split) a string into a series of smaller strings, based on a specified delimiter. Here's an explanation of its source code step by step:

Here's what each step does:

1. Declare the function `strtok`, which takes in a pointer to a string (`str`) and a pointer to a delimiter string (`delim`) and returns a pointer to the next token in the string, or `NULL` if there are no more tokens.

2. Declare a static variable `last_token` that keeps track of the last token found. This variable is static so that it retains its value between function calls.

3. Declare a local variable `token` which will be used to keep track of the current token.

4. Check if a new string has been passed in. If so, set `last_token` to the start of the string. This is the first token we will look for.

5. If we haven't found any tokens yet (i.e., `last_token` is `NULL`), return `NULL`.

6. Find the first delimiter after the last token. We start searching from `last_token` and keep advancing `token` until we either reach the end of the string or we find a character that matches the delimiter.

7. If we've reached the end of the string (i.e., `*token == '\0'`), set `last_token` to `NULL` and return `NULL`. This indicates that there are no more tokens in the string.

8. Replace the delimiter character with a null terminator (`'\0'`) to split the string into two parts: the current token and the rest of the string. Update `last_token` to point to the first character of the next token (i.e., `token + 1`).

9. Return the current token, which is the part of the string before the delimiter.

That's it! The `strtok` function is a powerful tool for splitting strings into smaller parts, and understanding how it works can be very helpful in working with text data in C. */