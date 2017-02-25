


#ifndef _CACHE_CONTROLLER_H
#define _CACHE_CONTROLLER_H
typedef struct
{
	char index;
	int tag;
	char rw;
	char data;
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

#endif