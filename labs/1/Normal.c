#include "Normal.h"

/*
 * Total runtime n*u + 2u
 * where n is chars in input
 * and u is length of userid
 */
void sorted(optionstruct opts) {
    char* user = getenv("USER");
    int userlen = strlen(user); //used many times, so worth keeping it
    int* userval = (int*) malloc(sizeof(int) * strlen(user));
    int* nums = (int*) malloc(sizeof(int) * opts.num);
    if(!userval) {
        perror("Malloc failed: ");
        exit(1);
    }
    // Runtime u where u is length of userid
    for(int i=0;i < userlen;i++) {
        // Malloc'd array might contain garbage, so need to initialize
        userval[i] = 0;
    }
    /*
     * Stage runs in n*u time
     * where n is number of ints in the input
     * and u is the number of characters in the userid
     */
    for(int n = 0;n < opts.num;n++) {
        int integer = readint(opts.max, stdin);
        nums[n] = integer;
        for(int i=0;i < userlen;i++) {
            if(user[i] == integer)
                userval[i]++;
        }
    }
    // End of stage
    // Runtime u where u is length of userid
    for(int i=0;i < userlen;i++) {
        printf("%c\t%d\t%d\n", user[i], (int)user[i], userval[i]);
    }
    free(userval);
}

/*
 * Helper function to read an integer from a stream
 * Loosely based on:
 * http://stackoverflow.com/a/4023921/1666415
 */
int readint(int max, FILE* stream) {
    int num;
    // Intelligently determine the upper bound on digits
    char str[15];
    sprintf(str, "%d", max);
    int size = strlen(str)+1;
    char input[size];
    fgets(input, size, stream);
    if(input[strlen(input)-1] != '\n' && input[strlen(input)-1] != EOF) {
        printf("%d\n", input[strlen(input)-1]);
        fprintf(stderr, "Bad input, exiting");
        exit(1);
    }
    // Trim the newline
    input[strlen(input)-1] = '\0';
    num = atoi(input);
    return num;
}
