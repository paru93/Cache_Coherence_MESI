#ifndef _CACHE_CONTROLLER_H
#define _CACHE_CONTROLLER_H
typedef struct
{
	char index;
	int tag;
	char rw;
	char data;
}Cache_controller;

#endif