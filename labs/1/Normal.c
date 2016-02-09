#include "Normal.h"
#include "Main.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * qsort comparison function
 * http://stackoverflow.com/questions/10996418/efficient-integer-compare-function
 */
inline static int incompare(const void* first, const void* second) {
    return *(int*)first - *(int*)second;
    // return (*(int*)first < *(int*)second) ? -1 : (*(int*)first > *(int*)second);
    // return (*(int*)first > *(int*)second) - (*(int*)first < *(int*)second);
}

void sorted(optionstruct opts, FILE* istream, FILE* ostream, FILE* countstream) {
    char* input = (char*) malloc(sizeof(char) * 8);
    int nnum = readint(1000000, 1, istream, input);
    if(!opts.nd)
        opts.num = nnum;
    else if(opts.num != nnum) {
        fprintf(stderr, "-n argument not equal to input count");
        exit(1);
    }
    char* user = getenv("USER");
    size_t userlen = strlen(user); //used many times, so worth keeping it
    int* userval = (int*) malloc(sizeof(int) * userlen);
    int* nums = (int*) malloc(sizeof(int) * opts.num);
    if(!userval || !nums || !input) {
        perror("malloc failed");
        exit(1);
    }
    // Nums will be filled anyways, and input is memset in readint
    memset(userval, 0, userlen * sizeof(int));

    size_t size = opts.num;
    /*
     * Stage runs in n*u time where n is opts.num
     * and u is the number of characters in the userid
     */
    for(size_t n = 0;n < opts.num;n++) {
        int integer = readint(opts.max, opts.min, istream, input);
        // If opts.num was larger than the actual input size, end early
        if(!integer) {
            size = n;
            break;
        }
        nums[n] = integer;
        for(size_t i=0;i < userlen;i++) {
            if(user[i] == integer)
                userval[i]++;
        }
    }
    qsort(&nums[0], size, sizeof(int), incompare);
    // Runtime n where n is number of elements in nums
    for(size_t i=0;i < size;i++) {
        fprintf(ostream, "%d\n", nums[i]);
    }
    // Runtime u where u is length of userid
    for(size_t i=0;i < userlen;i++) {
        fprintf(countstream, "%c\t%d\t%d\n", user[i], (int)user[i], userval[i]);
    }
    free(userval);
    free(nums);
    free(input);
}

/*
 * Helper function to read an integer from a stream
 * Based on:
 * http://stackoverflow.com/a/4023921/1666415
 */
int readint(int max, int min, FILE* istream, char* input) {
    int num;
    //memset(input, 0, sizeof(char) * 8);
    input[0] = '\0';

    if(!fgets(input, 8, istream) && errno) {
        perror("fgets failed");
        exit(1);
    }
    size_t inputlen = strlen(input);
    // Case where there are no more ints being passed in
    if(inputlen <= 1)
        return 0;
    // Make sure input wasn't too long
    if(input[inputlen-1] != '\n' && input[inputlen-1] != EOF) {
        fprintf(stderr, "Bad input, exiting\n");
        exit(1);
    }
    // Trim the newline
    input[inputlen-1] = '\0';
    /*
     * Interesting performance note, atoi is significantly faster
     * than the sscanf way.  Even though atoi is pretty bad with
     * input validation, we can use it because numbers can't be
     * zero.  The only potential problem is if there's numbers
     * greater than INT_MAX or smaller than INT_MIN.
     */
    num = atoi(input);
    /*if(!sscanf(input, "%d", &num)) {
        perror("sscanf failed");
        exit(1);
    }*/
    if(num > max || num < min) {
        fprintf(stderr, "%d is out of bounds, must be within [%d,%d]\n", num, min, max);
        exit(1);
    }
    return num;
}
