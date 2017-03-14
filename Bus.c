
#include "includes.h"


extern unsigned char shareData;
extern unsigned char lookInOthrSrc;
extern unsigned char DataFrmMem;
extern unsigned int  MissCounter;


unsigned char NextStateCal(unsigned short *stateCnt, unsigned char InvalidateSig, unsigned char OrgCacheCtrlSelState, unsigned char *CacheCtrlSel)
{
     if(lookInOthrSrc || InvalidateSig)
     {
        if(*stateCnt < CACHECTRLLRS-1)   // check if all the other cache's are covered
        {
            (*stateCnt)++;
            (*CacheCtrlSel)++;
            *CacheCtrlSel &= CACHECTRLLRS - 1;
        }
        else if(InvalidateSig)
            *CacheCtrlSel = OrgCacheCtrlSelState;    // signal will be cleared by master
        else
            *CacheCtrlSel = MEMORYRD;
     }
     else
        *CacheCtrlSel = OrgCacheCtrlSelState;
    return *CacheCtrlSel;
}

void Bus(unsigned char CacheCtrlSel, unsigned int addr, unsigned char upData, unsigned char upRW)
{
    unsigned char done = 0;
    unsigned short stateCnt = 0;    // used to check if all the cache are read for a read/write miss
    unsigned char OrgCacheCtrlSelState = CacheCtrlSel;
    unsigned char InvalidateSig = 0;

    while(done == 0)
    {
        switch (CacheCtrlSel)
        {
        case CACHECTRL1: CacheCtrllr(addr, upData, upRW, &done, &InvalidateSig);
                         CacheCtrlSel = NextStateCal(&stateCnt, InvalidateSig, OrgCacheCtrlSelState, &CacheCtrlSel);
                         break;

        case CACHECTRL2: CacheCtrllr2(addr, upData, upRW, &done, &InvalidateSig);
                         CacheCtrlSel = NextStateCal(&stateCnt, InvalidateSig, OrgCacheCtrlSelState, &CacheCtrlSel);
                         break;

        case CACHECTRL3: CacheCtrllr3(addr, upData, upRW, &done, &InvalidateSig);
                         CacheCtrlSel = NextStateCal(&stateCnt, InvalidateSig, OrgCacheCtrlSelState, &CacheCtrlSel);
                         break;

        case CACHECTRL4: CacheCtrllr4(addr, upData, upRW, &done, &InvalidateSig);
                         CacheCtrlSel = NextStateCal(&stateCnt, InvalidateSig, OrgCacheCtrlSelState, &CacheCtrlSel);
                         break;

        case MEMORYRD:   shareData = SharedMemRd(addr);
                         stateCnt = 0;
                         CacheCtrlSel = OrgCacheCtrlSelState;
                         MissCounter++;
                         break;
        }
    }
}
