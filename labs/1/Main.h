#pragma once
#define DEBUG 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>

#include "Normal.h"
#include "Generate.h"
#include "mytimer.h"

int main(int argc, char **argv, char *envp[]);


struct options {
    char g; //treated as a boolean
    int num;
    int min;
    int max;
    unsigned long seed;
    char* input;
    char* output;
    char* countfile;
};
typedef struct options optionstruct;
