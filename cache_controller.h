///////////////////////////////////////
// File Name: CacheController.h
// Author: Chetan
//
///////////////////////////////////////



#ifndef _CACHE_CONTROLLER_H
#define _CACHE_CONTROLLER_H

typedef struct
{
	unsigned char MESI;
	unsigned char index;
	unsigned char rw;
	unsigned char data;
	unsigned int tag;
}CacheCtrl_t;

typedef enum
{
	I = 0,
	M = 1,
	S = 2,
	E = 3
}MESI_t;

typedef enum
{
	WRITE,
	READ
}memOpr_t;

typedef enum
{
	CACHE_EMPTY,
	FOUND_IN_CACHE,
	NOTFOUND_IN_CACHE
}CacheDataFind_t;

#endif
