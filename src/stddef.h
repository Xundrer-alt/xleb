#pragma once
#include "stdint.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef offsetof
#define offsetof(TYPE, FIELD) __builtin_offsetof(TYPE, FIELD)
#endif
