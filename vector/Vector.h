#pragma once
#include <stdlib.h>

struct vectorstruct {
    size_t bytes;
    size_t size;
    size_t maxsize;
    void* arrp;
};
typedef struct vectorstruct vector;


vector makev(size_t, size_t);
void expand(vector);
