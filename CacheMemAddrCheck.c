
#include "includes.h"

// This module checks the tag address of the memory
// If the address is a match then the respective signals are asserted
// If the address is not a match then the respective signals like memRd and hIT are changed
// The control signals will then be given to the MESI protocol checker

// parameters: Cache controller:
// Parameter: CacheMem- receives the data of the respective index of the cache memory
void cacheMemAddrCheck(CacheCtrl_t *cc, CacheMem_t *CacheMem, unsigned char *Hit)
{

    // check if the cache location is empty or contains an invalid address/tag
    if(cc->tag != CacheMem[cc->index].tag)
    {
        *Hit = 0;
    }
    else    // the cache memory address matches with the address given by the processor
    {
        *Hit = 1;       // found in the cache location
    }
}
