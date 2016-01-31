#pragma once
#include <errno.h>

#include "Main.h"

typedef struct options optionstruct;
void sorted(optionstruct, FILE*, FILE*, FILE*);
int readint(int, int, FILE*);
