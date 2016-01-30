#pragma once
#define DEBUG 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "Normal.h"
#include "Generate.h"

int main(int argc, char **argv, char *envp[]);


struct options {
    char g; //treated as a boolean
    int num;
    int min;
    int max;
    int seed;
    char* input;
    char* output;
    char* countfile;
};
typedef struct options optionstruct;
