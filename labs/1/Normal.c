#include "Normal.h"

/*
 * Total runtime n*u + 2u
 * where n is from -n
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
     * where n is num from opts
     * and u is the number of characters in the userid
     * This is relying on the user not putting in some
     * stupidly large number for -n.
     */
    for(int n = 0;n < opts.num;n++) {
        int integer = readint(opts.max, stdin);
        nums[n] = integer;
        for(int i=0;i < userlen;i++) {
            if(user[i] == integer)
                userval[i]++;
        }
    }
    int sz = opts.num;
    for(int i=0;i < opts.num;i++) {
        if(nums[i] == -1) {
            sz = i;
            break;
        }
    }
    qsort(&nums[0], sz, sizeof(int), incompare);
    for(int i=0;i < sz;i++) {
        printf("%d\n", nums[i]);
    }
    // Runtime u where u is length of userid
    for(int i=0;i < userlen;i++) {
        printf("%c\t%d\t%d\n", user[i], (int)user[i], userval[i]);
    }
    free(userval);
    free(nums);
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
    size_t size = strlen(str)+1;
    char input[size];
    for(int i=0;i<size;i++)
        input[i] = '\0';
    fgets(input, size, stream);
    size_t inputlen = strlen(input);
    // Case where there are no more ints being passed in
    if(inputlen <= 1)
        return -1;
    if(input[inputlen-1] != '\n' && input[inputlen-1] != EOF) {
        fprintf(stderr, "Bad input, exiting");
        exit(1);
    }
    // Trim the newline
    input[inputlen-1] = '\0';
    num = atoi(input);
    return num;
}

/*
 * qsort comparison function
 */
inline static int incompare(const void* first, const void* second) {
    return *(int*)first - *(int*)second;
}
