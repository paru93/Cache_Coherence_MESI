
///////////////////////////////////////
// File Name: BusElements.c
// Author: Chetan
//
///////////////////////////////////////

#include "includes.h"

#define CACHESIZE 256
#define MAINMEMORYSIZE 1024


// Variables
extern unsigned char shareData;
extern unsigned char lookInOthrSrc;
extern unsigned char DataFrmMem;
extern unsigned int TotalHitCntr;

unsigned char SM[MAINMEMORYSIZE];

//
unsigned char CacheCtrllr(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig)
{
    unsigned char Found = 1;

    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[CACHESIZE] = {0};
    static unsigned char Init = 0;
    static unsigned char InvldGen = 0;      // the master will only set this flag to indicate that the copy is modified

    for(cnt = 0; cnt < CACHESIZE && Init == 0; cnt++)
    {
        CacheMem[cnt].data = 0xFF;
        CacheMem[cnt].tag = 0xFF;
    }
    Init = 1;

    cc.index = addr & 0xFF;
    cc.tag   = (addr >> 8) & 0x3;
    cc.rw    = upRW;

    cacheMemAddrCheck(&cc, CacheMem, &Found);       //

    if(Found)   // the address is found in the cache
    {
        printf("CacheMem1: Addr: %d, Tag: %d, Index: %d, MESI: %d, Data: %d\n", addr, CacheMem[cc.index].tag, cc.index, CacheMem[cc.index].mesi, CacheMem[cc.index].data);
        AccessCache(&CacheMem, cc, InvalidateSig, &InvldGen, &Hit, done, upData);
        TotalHitCntr++;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;
        ReqDataFrmOthrSrc(CacheMem, cc, InvalidateSig, &state);
    }
    return 0;
}

/// CACHE CONTROLLER 2
unsigned char CacheCtrllr2(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig)
{
    unsigned char Found = 1;

    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[CACHESIZE] = {0};
    static unsigned char Init = 0;
    static unsigned char InvldGen = 0;      // flag to indicate that the source is master to generate the invalidate sig

    for(cnt = 0; cnt < CACHESIZE && Init == 0; cnt++)
    {
        CacheMem[cnt].data = 0xFF;
        CacheMem[cnt].tag = 0xFF;
    }
    Init = 1;

    cc.index = addr & 0xFF;
    cc.tag   = (addr >> 8) & 0x3;
    cc.rw    = upRW;

    cacheMemAddrCheck(&cc, CacheMem, &Found);       //

    if(Found)   // the address is found in the cache
    {
        printf("CacheMem2: Addr: %d, Tag: %d, Index: %d, MESI: %d, Data: %d\n", addr, CacheMem[cc.index].tag, cc.index, CacheMem[cc.index].mesi, CacheMem[cc.index].data);
        AccessCache(&CacheMem, cc, InvalidateSig, &InvldGen, &Hit, done, upData);
        TotalHitCntr++;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;
        ReqDataFrmOthrSrc(CacheMem, cc, InvalidateSig, &state);
    }
    return 0;
}


/// CACHE CONTROLLER 3
unsigned char CacheCtrllr3(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig)
{
    unsigned char Found = 1;
    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[CACHESIZE] = {0};
    static unsigned char Init = 0;
    static unsigned char InvldGen = 0;      // flag to indicate that the source is master to generate the invalidate sig

    for(cnt = 0; cnt < CACHESIZE && Init == 0; cnt++)
    {
        CacheMem[cnt].data = 0xFF;
        CacheMem[cnt].tag = 0xFF;
    }
    Init = 1;

    cc.index = addr & 0xFF;
    cc.tag   = (addr >> 8) & 0x3;
    cc.rw    = upRW;

    cacheMemAddrCheck(&cc, CacheMem, &Found);       //

    if(Found)   // the address is found in the cache
    {
        printf("CacheMem3: Addr: %d, Tag: %d, Index: %d, MESI: %d, Data: %d\n", addr, CacheMem[cc.index].tag, cc.index, CacheMem[cc.index].mesi, CacheMem[cc.index].data);
        AccessCache(&CacheMem, cc, InvalidateSig, &InvldGen, &Hit, done, upData);
        TotalHitCntr++;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;
        ReqDataFrmOthrSrc(CacheMem, cc, InvalidateSig, &state);
    }
    return 0;
}

/// CACHE CONTROLLER 4
unsigned char CacheCtrllr4(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig)
{
    unsigned char Found = 1;
    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[CACHESIZE] = {0};
    static unsigned char Init = 0;
    static unsigned char InvldGen = 0;      // flag to indicate that the source is master to generate the invalidate sig

    for(cnt = 0; cnt < CACHESIZE && Init == 0; cnt++)
    {
        CacheMem[cnt].data = 0xFF;
        CacheMem[cnt].tag = 0xFF;
    }
    Init = 1;

    cc.index = addr & 0xFF;
    cc.tag   = (addr >> 8) & 0x3;
    cc.rw    = upRW;

    cacheMemAddrCheck(&cc, CacheMem, &Found);       //

    if(Found)   // the address is found in the cache
    {
        printf("CacheMem4: Addr: %d, Tag: %d, Index: %d, MESI: %d, Data: %d\n", addr, CacheMem[cc.index].tag, cc.index, CacheMem[cc.index].mesi, CacheMem[cc.index].data);
        AccessCache(&CacheMem, cc, InvalidateSig, &InvldGen, &Hit, done, upData);
        TotalHitCntr++;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;
        ReqDataFrmOthrSrc(CacheMem, cc, InvalidateSig, &state);
    }
    return 0;
}


unsigned char SharedMemRd(unsigned int addr)
{
    unsigned char rdData = 0;
    rdData = SM[addr];
    lookInOthrSrc = 0;  //0- No cache had the data, memory will provide the data
    DataFrmMem = 1;
    return rdData;
}
