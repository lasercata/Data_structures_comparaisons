#include "../include/common.h"

int max(int a, int b) {
    if (a < b)
        return b;

    return a;
}

int abs(int a) {
    if (a < 0)
        return -a;

    return a;
}
