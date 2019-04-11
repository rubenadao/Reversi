#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include "estado.h"
#include "stdio.h"
#include "game.h"

int main() {
    time_t t;
    srand((unsigned) time(&t));
    startEngine();
    return 0;
}