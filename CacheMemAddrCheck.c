
#include "includes.h"

// This module checks the tag address of the memory
// If the address is a match then the respective signals are asserted
// If the address is not a match then the respective signals like memRd and hIT are changed
// The control signals will then be given to the MESI protocol checker

// parameters: Cache controller:
// Parameter: CacheMem- receives the data of the respective index of the cache memory
void cacheMemAddrCheck(CacheCtrl_t *cc, CacheMem_t *CacheMem, unsigned char *Hit, unsigned char *memRd,
                       unsigned char *read, unsigned char *write)
{
    // Clear the signals which are used to indicate the other cache or memory that the data was not found
    *read = 0;
    *write = 0;

    // check if the cache location is empty or contains an invalid address/tag
    if(cc->tag != CacheMem[cc->index].tag)
    {
        *memRd = 1;
        *Hit = 0;
        (cc->rw == READ) ? (*read = 1):(*write = 1);        // according to read/write operation the respective signal is asserted
    }
    else    // the cache memory address matches with the address given by the processor
    {
        *memRd = 0;     // no need to go to memory for reading the data
        *Hit = 1;       // found in the cache location
    }
}
