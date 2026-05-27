#include "debug.h"
#include "halt.h"

void ktest() {
    DEBUG("Start testing");
    DEBUG("End testing");
    halt();
}