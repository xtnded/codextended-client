#pragma once
#include "keycodes.h"

#define MAX_KEYS        256

typedef struct {
	int down;
	int repeats;                // if > 1, it is autorepeating
	char        *binding;
//	int hash; //cod1 doesn't use this anymore
} qkey_t; //size is 0xc


extern qkey_t *keys;

static void(*Key_SetCatcher)(int) = (void(*)(int))0x4180A0;