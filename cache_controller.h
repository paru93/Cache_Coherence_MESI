


#ifndef _CACHE_CONTROLLER_H
#define _CACHE_CONTROLLER_H
typedef struct
{
	char MESI;
	char index;
	char rw;
	char data;
	int tag;
}ccheCtrl_t;

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
}cacheDataFind_t;

#endif