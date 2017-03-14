
///////////////////////////////////////
// File Name: CacheOperation.c
// Author: Chetan
//
///////////////////////////////////////

#include "includes.h"

extern unsigned char lookInOthrSrc;
extern unsigned char shareData;
extern unsigned char SM[];
extern unsigned char DataFrmMem;


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

unsigned char AccessCache(CacheMem_t *CacheMem, CacheCtrl_t cc, unsigned char *InvalidateSig, unsigned char *InvldGen, unsigned char *Hit,
                               unsigned char *done, unsigned char upData)
{
    unsigned char rdData;

    if(lookInOthrSrc || (*InvalidateSig && (*InvldGen == 0)))   // 1- If other cache is requesting data which is in this cache
    {
        if(*InvalidateSig)
            MESICtrllr(SLAVE, WRITE, &CacheMem[cc.index].mesi, *Hit);    // update the MESI from S->I
        else
        {
            shareData = CacheRead(cc, CacheMem);
            MESICtrllr(SLAVE, READ, &CacheMem[cc.index].mesi, *Hit);
            lookInOthrSrc = 0;  // clear the flag to indicate that the data is available
        }
        return shareData;
    }
    else
    {
        if(*InvalidateSig && *InvldGen) // invalidate signal has been sent to all the cache
        {
            *InvalidateSig = 0;
            *InvldGen = 0;
            *done = 1;          // on a write the operation is over when all the other cache have invalidated their copies

        }
        else if(cc.rw == 1)  // if read operation
        {
            rdData = CacheRead(cc, CacheMem);  // Read the data for the processor which is requesting the data
            *Hit = 1;
            MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, *Hit);
            *done = 1;
            return rdData;
        }
        else
        {
            // if address exists then before overwrite need to update the second cache MESI status
            *InvalidateSig = 1;  // On a write invalidate the other copies of the cache
            *InvldGen = 1;
            CacheWrite(CacheMem, cc, upData);  // Write the data in the cache which is given by processor
            *Hit = 1;
            MESICtrllr(MASTER, WRITE, &CacheMem[cc.index].mesi, *Hit);
        }
    }
    return 0;
}

//
void ReqDataFrmOthrSrc(CacheMem_t *CacheMem, CacheCtrl_t cc, unsigned char *InvalidateSig, unsigned char *state)
{
    unsigned char Hit = 0;

    if(*InvalidateSig == 0)     // Do not enter on invalidate req, the data is already not present in the cache
    switch(*state)
    {
        case 0: if(lookInOthrSrc == 0)      // checker for the flag
            {
                if(CacheMem[cc.index].mesi == M)    // writeback condition
                {
                    unsigned int temp = (CacheMem[cc.index].tag << 8) | cc.index;
                    SM[temp] = CacheMem[cc.index].data;
                }
                CacheMem[cc.index].mesi = I;    // Since the data was not found the cache MESI should be invalid
                lookInOthrSrc = 1;
                *state = 1;
            }
            break;


        case 1: if(lookInOthrSrc == 0)
            {
                if(DataFrmMem)      // the data was read from the shared memory
                    Hit = 0;        // MESI - Exclusive
                else
                    Hit = 1;        // MESI - Shared // Data read from other cache

                CacheWrite(CacheMem, cc, shareData);
                MESICtrllr(MASTER, READ, &CacheMem[cc.index].mesi, Hit);
                *state = 0;
            }
            break;
    }
}
