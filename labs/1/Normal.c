#include "Normal.h"

/*
 * qsort comparison function
 */
inline static int incompare(const void* first, const void* second) {
    return *(int*)first - *(int*)second;
    // return (*(int*)first < *(int*)second) ? -1 : (*(int*)first > *(int*)second);
    // return (*(int*)first > *(int*)second) - (*(int*)first < *(int*)second);
    /*
     * http://stackoverflow.com/questions/10996418/efficient-integer-compare-function
     */
}

/*
 * Total runtime n*u + 2u
 * where n is from -n
 * and u is length of userid
 */
void sorted(optionstruct opts, FILE* istream, FILE* ostream, FILE* countstream) {
    char* user = getenv("USER");
    int userlen = strlen(user); //used many times, so worth keeping it
    int* userval = (int*) malloc(sizeof(int) * strlen(user));
    int* nums = (int*) malloc(sizeof(int) * opts.num);
    if(!userval || !nums) {
        perror("malloc failed");
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
        int integer = readint(opts.max, opts.min, istream);
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
        fprintf(ostream, "%d\n", nums[i]);
    }
    // Runtime u where u is length of userid
    for(int i=0;i < userlen;i++) {
        fprintf(countstream, "%c\t%d\t%d\n", user[i], (int)user[i], userval[i]);
    }
    free(userval);
    free(nums);
}

/*
 * Helper function to read an integer from a stream
 * Loosely based on:
 * http://stackoverflow.com/a/4023921/1666415
 */
int readint(int max, int min, FILE* istream) {
    int num;
    char input[15];

    // for(int i=0;i<15;i++)
    //     input[i] = '\0';
    memset(&input, 0, sizeof(char) * 15);

    if(!fgets(input, 15, istream)) {
        if(errno) {
            perror("fgets failed");
            exit(1);
        }
    }
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
    if(num > max || num < min) {
        fprintf(stderr, "%d is out of bounds, must be within [%d,%d]\n", num, min, max);
        exit(1);
    }
    return num;
}

