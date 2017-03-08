#include <stdio.h>
#include <stdlib.h>
#include "includes.h"

#define SM_CAL_ADDR ((cc.tag << sizeof(cc.index)) | cc.index)
#define CACHECTRLLRS (2)

enum
{
    CACHECTRL1 = 0,
    CACHECTRL2,
    MEMORYRD
};

// Variables
unsigned char shareData = 0;
unsigned char lookInOthrSrc = 0;
unsigned char SM[1024] = {0};
unsigned char DataFrmMem = 0;

//
unsigned char CacheRead(CacheCtrl_t cc, CacheMem_t *CacheMem)
{
    unsigned char rdData = 0;
    return (CacheMem[cc.index].data);
}


// Cache Write operation
void CacheWrite(CacheMem_t *CacheMem, CacheCtrl_t cc, unsigned char wrData)
{
    CacheMem[cc.index].tag  = cc.tag;
    CacheMem[cc.index].data = wrData;
}


//
unsigned char CacheCtrllr(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done)
{
    enum
    {
        S0, S1
    };

    unsigned char Found = 1;
    unsigned char rdData;
    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[256] = {0};
    static Init = 0;

    for(cnt = 0; cnt < 256 && Init == 0; cnt++)
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
        if(lookInOthrSrc)   // 1- If other cache is requesting data which is in this cache
        {
            shareData = CacheRead(cc, &CacheMem);
            MESICtrllr(SLAVE, READ, &CacheMem[cc.index].mesi, Hit);
            lookInOthrSrc = 0;  // clear the flag to indicate that the data is available
            return shareData;
        }
        else
        {
            if(cc.rw == 1)  // if read operation
            {
                rdData = CacheRead(cc, &CacheMem);  // Read the data for the processor which is requesting the data
                Hit = 1;
                MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, Hit);
                *done = 1;
                return rdData;
            }
            else
            {
                CacheWrite(&CacheMem, cc, upData);  // Write the data in the cache which is given by processor
                Hit = 1;
                MESICtrllr(MASTER, WRITE, &CacheMem[cc.index].mesi, Hit);
            }
        }
        *done = 1;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;

        switch(state)
        {
            case 0: if(lookInOthrSrc == 0)      // checker for the flag
                {
                    if(CacheMem[cc.index].mesi == M)    // writeback condition
                    {
                        unsigned int temp = (cc.tag << 8) | cc.index;
                        SM[temp] = CacheMem[cc.index].data;
                    }

                    lookInOthrSrc = 1;
                    state = 1;
                }
                break;


            case 1: if(lookInOthrSrc == 0)
                {
                    if(DataFrmMem)      // the data was read from the shared memory
                        Hit = 0;        // MESI - Exclusive
                    else
                        Hit = 1;        // MESI - Shared // Data read from other cache

                    CacheWrite(&CacheMem, cc, shareData);
                    MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, Hit);
                    state = S0;
                }
                break;
        }
    }
    return 0;
}

/// CACHE CONTROLLER 2
unsigned char CacheCtrllr2(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done)
{
    enum
    {
        S0, S1
    };

    unsigned char Found = 1;
    unsigned char rdData;
    unsigned short cnt = 0;
    static unsigned char Hit = 0;
    static CacheCtrl_t cc = {0};
    static CacheMem_t CacheMem[256] = {0};
    static Init = 0;

    for(cnt = 0; cnt < 256 && Init == 0; cnt++)
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
        if(lookInOthrSrc)   // 1- If other cache is requesting data which is in this cache
        {
            shareData = CacheRead(cc, &CacheMem);
            MESICtrllr(SLAVE, READ, &CacheMem[cc.index].mesi, Hit);
            lookInOthrSrc = 0;  // clear the flag to indicate that the data is available
            return shareData;
        }
        else
        {
            if(cc.rw == 1)  // if read operation
            {
                rdData = CacheRead(cc, &CacheMem);  // Read the data for the processor which is requesting the data
                Hit = 1;
                MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, Hit);
                *done = 1;
                return rdData;
            }
            else
            {
                CacheWrite(&CacheMem, cc, upData);  // Write the data in the cache which is given by processor
                Hit = 1;
                MESICtrllr(MASTER, WRITE, &CacheMem[cc.index].mesi, Hit);
            }
        }
        *done = 1;
    }
    else if(Found == 0)   // not found in the cache
    {
        static unsigned char state = 0;

        switch(state)
        {
            case 0: if(lookInOthrSrc == 0)      // checker for the flag
                {
                    if(CacheMem[cc.index].mesi == M)    // writeback condition
                    {
                        unsigned int temp = (cc.tag << 8) | cc.index;
                        SM[temp] = CacheMem[cc.index].data;
                    }

                    lookInOthrSrc = 1;
                    state = 1;
                }
                break;


            case 1: if(lookInOthrSrc == 0)
                {
                    if(DataFrmMem)      // the data was read from the shared memory
                        Hit = 0;        // MESI - Exclusive
                    else
                        Hit = 1;        // MESI - Shared // Data read from other cache
                    CacheWrite(&CacheMem, cc, shareData);
                    MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, Hit);
                    state = S0;
                }
                break;
        }
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

void CacheCtrlMgr(unsigned char CacheCtrlSel, unsigned int addr, unsigned char upData, unsigned char upRW)
{
    unsigned char done = 0;
    unsigned short stateCnt = 0;    // used to check if all the cache are read for a read/write miss
    unsigned char OrgCacheCtrlSelState = CacheCtrlSel;

    DataFrmMem = 0;

    while(done == 0)
    {
        switch (CacheCtrlSel)
        {
        case CACHECTRL1: CacheCtrllr(addr, upData, upRW, &done);
                         if(lookInOthrSrc)
                         {
                            if(stateCnt < CACHECTRLLRS-1)
                            {
                                stateCnt++;
                                CacheCtrlSel++;
                                CacheCtrlSel &= CACHECTRLLRS - 1;
                            }
                            else
                                CacheCtrlSel = MEMORYRD;
                         }
                         else
                            CacheCtrlSel = OrgCacheCtrlSelState;
                         break;

        case CACHECTRL2: CacheCtrllr2(addr, upData, upRW, &done);
                         if(lookInOthrSrc)
                         {
                            if(stateCnt < CACHECTRLLRS-1)
                            {
                                stateCnt++;
                                CacheCtrlSel++;
                                CacheCtrlSel &= CACHECTRLLRS - 1;
                            }
                            else
                                CacheCtrlSel = MEMORYRD;
                         }
                         else
                            CacheCtrlSel = OrgCacheCtrlSelState;
                         break;

        case MEMORYRD:   shareData = SharedMemRd(addr);
                         CacheCtrlSel = OrgCacheCtrlSelState;
                         break;
        }
    }
}

int main()
{
    unsigned int addr = 0x01;
    unsigned char upData = 0xF4;
    unsigned char upRW = 0;

    /// Data written to one memory and read back
    CacheCtrlMgr(CACHECTRL1, addr, upData, upRW);
    addr = 0x01;
    upRW = 1;
    CacheCtrlMgr(CACHECTRL1, addr, upData, upRW);

    /// Data written in other cache will be read in other cache
    addr = 0x01;
    upRW = 1;
    CacheCtrlMgr(CACHECTRL2, addr, upData, upRW);
    return 0;
}
