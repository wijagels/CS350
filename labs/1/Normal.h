#pragma once
#include "Main.h"

typedef struct options optionstruct;
void sorted(optionstruct, FILE*, FILE*, FILE*);
int readint(int, FILE*);
inline static int incompare(const void* first, const void* second);
