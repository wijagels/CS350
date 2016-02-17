#pragma once

struct options {
    int levels;
    int children;
    char pause;
    char* sleep;
};
typedef struct options optionstruct;

void tree(optionstruct, char**);
