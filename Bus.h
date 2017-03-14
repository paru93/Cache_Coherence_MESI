///////////////////////////////////////
// File Name: Bus.h
// Author: Chetan
//
///////////////////////////////////////


#ifndef BUS_H_INCLUDED
#define BUS_H_INCLUDED

#define CACHECTRLLRS (4)

enum
{
    CACHECTRL1 = 0,
    CACHECTRL2,
    CACHECTRL3,
    CACHECTRL4,
    MEMORYRD
};

unsigned char NextStateCal(unsigned short *stateCnt, unsigned char InvalidateSig, unsigned char OrgCacheCtrlSelState, unsigned char *CacheCtrlSel);
void Bus(unsigned char CacheCtrlSel, unsigned int addr, unsigned char upData, unsigned char upRW);

#endif // BUS_H_INCLUDED
