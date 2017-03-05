#include <stdio.h>
#include <stdlib.h>
#include "includes.h"

void TestCacheMemAddrCheck(unsigned char *Hit, unsigned char *memRd, unsigned char *read, unsigned char *write,
                           CacheMem_t *CacheMem, CacheCtrl_t *CacheCtrlInfo)
{
    CacheCtrlInfo->tag = 0x10;       // address is 0x10
    CacheCtrlInfo->index = 0x2;      // the index is 0x2
    CacheCtrlInfo->rw = READ;           // Read operation
    cacheMemAddrCheck(CacheCtrlInfo, &CacheMem[CacheCtrlInfo->index], Hit, memRd, read, write);

    CacheCtrlInfo->tag = 0x10;       // address is 0x10
    CacheCtrlInfo->index = 0x2;      // the index is 0x2
    CacheCtrlInfo->rw = WRITE;           // Read operation
    CacheCtrlInfo->data = 0x1234;       // write the data in the location
    cacheMemAddrCheck(CacheCtrlInfo, &CacheMem[CacheCtrlInfo->index], Hit, memRd, read, write);

    CacheCtrlInfo->tag = 0x10;       // address is 0x10
    CacheCtrlInfo->index = 0x2;      // the index is 0x2
    CacheCtrlInfo->rw = READ;           // Read operation
    cacheMemAddrCheck(CacheCtrlInfo, &CacheMem[CacheCtrlInfo->index], Hit, memRd, read, write);
}

int main()
{
    CacheCtrl_t CacheCtrlInfo;
    CacheMem_t  CacheMem[256];

    unsigned char Hit = 0, memRd = 0;       // these signals are used to synchronize the cache operations with mem
    unsigned char read = 0, write = 0;      // signals used to control the memory operation

    // 1. Get the address from the instruction memory
    // 2. Send the instruction received to the cache controller 1
    //CacheCtrllr_Chck();
    // Read operation requested from the processor
    TestCacheMemAddrCheck(&Hit, &memRd, &read, &write, CacheMem, &CacheCtrlInfo);
    cacheMemAddrCheck(&CacheCtrlInfo, CacheMem, &Hit, &memRd, &read, &write);
    MESICtrllr(CacheCtrlInfo, Hit, memRd, read, write, &CacheMem[CacheCtrlInfo.index]);
    return 0;
}
